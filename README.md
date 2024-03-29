# Montage: A Fast, General System for Buffered Persistent Data Structures

Montage is a system for building fast buffered persistent data
structures, developed at the University of Rochester by H. Wen, W.
Cai, M. Du, L. Jenkins, B. Valpey, and M. L. Scott. The paper of
Montage appears in ICPP' 21
([link](https://www.cs.rochester.edu/u/scott/papers/2021_Wen_ICPP_Montage.pdf)).

As a fully nonblocking variant of Montage, nbMontage has a better
API for buildilng CAS-based nonblocking data structures and, most
importantly, nbMontage provides _wait-free sync_. The paper of
nbMontage, _Fast Nonblocking Persistence for Concurrent Data Structures_ 
by W. Cai, H. Wen, V. Maksimovski, M. Du, R. Sanna, S. Abdallah, and
M. L. Scott, appears in DISC' 21 ([link](https://www.cs.rochester.edu/u/scott/papers/2021_Cai_DISC_nbMontage.pdf)). 

The testing harness is based on J. Izraelevitz's
[parHarness](https://github.com/izrajoe/parHarness).

- [Montage: A Fast, General System for Buffered Persistent Data Structures](#montage-a-fast-general-system-for-buffered-persistent-data-structures)
  - [1. Required Libraries](#1-required-libraries)
  - [2. Commands](#2-commands)
    - [2.1. Run Specific Queue or Map Test](#21-run-specific-queue-or-map-test)
    - [2.2. Run Specific Graph Test](#22-run-specific-graph-test)
    - [2.3. Use Montage in Your Code](#23-use-montage-in-your-code)
    - [2.4. Different Mount Point](#24-different-mount-point)
  - [3. Static and Dynamic Environment Variables](#3-static-and-dynamic-environment-variables)
    - [3.1. Static Variables](#31-static-variables)
    - [3.2. Dynamic Variables](#32-dynamic-variables)
    - [3.3. Obsolete Variables](#33-obsolete-variables)

## 1. Required Libraries

Source code of most of required libraries are provided in `./ext`,
which includes
[Mnemosyne](https://github.com/snalli/mnemosyne-gcc/tree/master),
[libitm.so](https://pkgs.org/download/libitm),
[Pronto](https://zenodo.org/record/3605351#.X3YlJmhKj-g),
[MOD](https://zenodo.org/record/35636#.X3YlXmhKj-g) (which contains
nvm_malloc and immutable data structures),
[Ralloc](https://github.com/urcs-sync/ralloc), and
[threadcached](https://github.com/ChrisKjellqvist/MemcachedProtectedLibrary/tree/nohodor).
Most of them are customized for the experiment.
[nvm_malloc](https://github.com/IMCG/nvm-malloc) is vanilla. Please
refer to
[ext/README.md](https://github.com/urcs-sync/Montage/blob/master/ext/README.md)
for more information of those libraries.
[CLevel](https://github.com/chenzhangyu/Clevel-Hashing) is also
included in `./ext` for comparison to nbMontage.


Other than those in `./ext`, this repository also depends on
`libhwloc`, `libjemalloc`, `libuuid`, `libpthread`, and `libgomp`.
Running with Mnemosyne requires additional `libelf`, `libconfig`, and
`libitm` libraries.

Before running Pronto, ensure that huge pages are turned on, or an
error such as `ckpt_alloc.cpp:44: GlobalAlloc::GlobalAlloc(const
char*, const char*): Assertion newBlock(&region, BaseAddress,
MinPoolSize) failed` would occur. You may use the following command
to turn on:

```bash
sudo sysctl -w vm.nr_hugepages=32768
```

## 2. Commands

First, make sure persistent memory is mounted in DAX mode at
`/mnt/pmem`. Montage, MOD, and other native data structures in this
harness will create heap files prefixed by the user name. Pronto and
Mnemosyne handle heap files by their own and don't have the user name
prefix. Please refer to Section [2.3](#23-different-mount-point) if
NVM is mounted in a different path.

(All scripts mentioned below are for Montage. Testing and plotting
scripts for nbMontage are located in `./nb_script` and `./nb_data`.)

To test scalability (with different thread counts) of queues and maps:

```bash
./script/run_thread.sh
```

To test queues and maps with different value sizes:

```bash
./script/run_size.sh
```

To test memcached on YCSB:

```bash
./script/run_memcached.sh
```

To test graph scalability and recovery, set up dataset and run
workloads using the following commands:

```bash
./script/setup-datasets.sh
./script/run_graph.sh
```

To plot, run the following commands:
```bash
./data/plot.sh
```

To run epoch length sensitivity test:
```bash
./script/EpochLengthSensitivity.sh
```

### 2.1. Run Specific Queue or Map Test

**Please read this subsection if you want to manually test specific
queues or maps on some workloads.**

To build harness for testing all the queues or maps *except* those with
Pronto and Mnemosyne:

```bash
make
```

To build with Pronto full version (with background threads) and Pronto
sync version (worker threads do their own logging), respectively:

```bash
make pronto-full
make pronto-sync
```

To compile with Mnemosyne:

```bash
make mnemosyne
```

Static variables such as `K_SZ` and `V_SZ` can be set while building,
to adjust key and value size of workloads. See Section
[3](#3-static-and-dynamic-environment-variables) for more details.

After building, run the following with proper arguments:

```bash
./bin/main -r <rideable> -m <test_mode> -t <thread_num> -i <duration_of_some_tests> [-v]
``` 

Running `./bin/main` without an argument will
print help info listing available options.

### 2.2. Run Specific Graph Test

If you want to manually run graph tests, do as follows:

To building for testing multithreading performance:

```bash
make
```

To test recovery, run the following command to build harness with
default thread pinning on the harness disabled, so that it won't
interfere with OpenMP threads spawned during recovery:

```bash
make graph-rec
```

After building, run the following with proper arguments:

```bash
./bin/main -r <rideable> -m <test_mode> -t <thread_num> -i <duration_of_some_tests> [-v]
``` 

Running
`./bin/main` without an argument will print help info listing
available options. The performance test is `GraphTest:1m:i33r33l33:c1`
and `GraphTest:1m:i25r25l25:c25`, while the recovery test is
`GraphRecoveryTest:Orkut:verify` and `TGraphConstructionTest:Orkut`.

### 2.3. Use Montage in Your Code

Montage's API can be found in `src/persist/api`. Currently, all Montage-based data structures
in `src/rideables` are using the *Object-oriented* API by deriving from class `Recoverable`.
Please see data structures `src/rideables/Montage*.hpp` as examples of detailed usage.

Non-OO API, as described in the paper, is preserved in `src/persist/api/MontageGlobalAPI.hpp`.
This is a wrapper of a globally visible Montage instance (`EpochSys`). Only threadcached is
currently using this API in this repo.

The two sets of API share the same semantics as described in the paper, and is subject to
further adjustments as we apply it to more applications. We will consider releasing 
documentations on the API once they become stable.

### 2.4. Different Mount Point

If NVM is mounted in a different path, please either create a symbolic
link at `/mnt/pmem` (recommended) or search for `/mnt/pmem` in this
repository and replace them appeared in the following files:

```bash
ext/mnemosyne-gcc/username/mnemosyne.ini # Mnemosyne
ext/mnemosyne-gcc/usermode/library/mcore/include/config.h # Mnemosyne
ext/pronto-v1.1/src/savitar.hpp # Pronto
ext/ralloc/src/pm_config.hpp # Ralloc

script/EpochLengthSensitivity.sh # script for testing epoch lengths
script/explore_hashtable.sh # script for exploring Montage config on hash table
script/explore_memcached.sh # script for exploring Montage config on threadcached
script/run_graph.sh # script for running graph benchmarks
script/run_memcached.sh # script for running ycsb on memcached
script/run_size.sh # script for running Montage harness with different sizes
script/run_thread.sh # script for running Montage harness with different threads

src/rideables/MODHashTable.hpp # MOD nvm_malloc init path
src/rideables/MODQueue.hpp # MOD nvm_malloc init path
```

## 3. Static and Dynamic Environment Variables

### 3.1. Static Variables

`K_SZ`: Static variable to control key size (Byte) for maps. By
default it's 32. It needs to be set before compilation to take effect,
e.g., `K_SZ=40 make`. Don't pass values less than 10!

`V_SZ`: Static variable to control value size (Byte) for maps and
queues. By default it's 24. It needs to be set before compilation to
take effect, e.g., `V_SZ=2048 make`.

### 3.2. Dynamic Variables

`prefill`: The number of elements to be prefilled into the tested data
structure. This variable will overwrite the `prefill` argument passed
to Test constructors.

`range`: This decides the range of keys in map tests. This variable
will also overwirte the `range` argument passed to Test constructors.

There are also options mentioned in `./src/persist/README.md` for
configuring Montage parameter, e.g., epoch length, persisting
strategy, and buffering container.

### 3.3. Obsolete Variables

There're some obsolete variables no longer useable and are not
mentioned above. 

To name a few: `KeySize` and `ValueSize`. Inconsistency between them
and `K_SZ` and `V_SZ` will trigger assertion.
Please don't use any not mentioned above, unless you know what exactly
you are doing.
