## Montage Rideables
* Rideable 3 : MontageMSQueue
    - recoverable but recover is not implemented
* Rideable 6 : MontageQueue
* Rideable 11 : MontageLfHashTable
* Rideable 18 : MontageSSHashTable
    - recoverable but recover is not implemented
* Rideable 23 : MontageHashTable
* Rideable 25 : MontageNataTree
    - recoverable but recover is not implemented
* Rideable 28 : MontageLfSkipList
* Rideable 34 : MontageGraph 
* Rideable 37 : MontageLfHashTable<uint64_t>

3 6 11 18 23 25 28 34 37  
## All Rideables
* Rideable 0 : MSQueue
* Rideable 1 : NVMMSQueue
* Rideable 2 : FriedmanQueue
* Rideable 3 : MontageMSQueue
* Rideable 4 : TransientQueue<DRAM>
* Rideable 5 : TransientQueue<NVM>
* Rideable 6 : MontageQueue
* Rideable 7 : MODQueue
* Rideable 8 : LfHashTable
* Rideable 9 : NVMLockfreeHashTable
* Rideable 10 : PLockfreeHashTable
* Rideable 11 : MontageLfHashTable
* Rideable 12 : Dali
* Rideable 13 : SOFT
* Rideable 14 : MODHashTable
* Rideable 15 : NVMSOFT
* Rideable 16 : NVTraverseHashTable
* Rideable 17 : SSHashTable
* Rideable 18 : MontageSSHashTable
* Rideable 19 : NataTree
* Rideable 20 : NVMNataTree
* Rideable 21 : TransientHashTable<DRAM>
* Rideable 22 : TransientHashTable<NVM>
* Rideable 23 : MontageHashTable
* Rideable 24 : PNataTree
* Rideable 25 : MontageNataTree
* Rideable 26 : NVTraverseNataTree
* Rideable 27 : LockfreeSkipList
* Rideable 28 : MontageLfSkipList
* Rideable 29 : NVMLockfreeSkipList
* Rideable 30 : PLockfreeSkipList
* Rideable 31 : NVTLockfreeSkipList
* Rideable 32 : TGraph
* Rideable 33 : NVMGraph
* Rideable 34 : MontageGraph
* Rideable 35 : Orkut
* Rideable 36 : TransientOrkut
* Rideable 37 : MontageLfHashTable<uint64_t>
* Rideable 38 : LfHashTable<uint64_t>
* Rideable 39 : NVMLockfreeHashTable<uint64_t>


## Assertion failure's
```c
//main: src/BaseMeta.cpp:294: uint32_t BaseMeta::compute_idx(char*, char*, size_t): Assertion "block < superblock + sc->sb_size" failed.
main: src/BaseMeta.cpp:407: void BaseMeta::flush_cache(size_t, TCacheBin*): Assertion "newanchor.count < maxcount" failed.
main: src/BaseMeta.cpp:929: int InuseRecovery::iterator::update_status_dirty(): Assertion "curr_desc->maxcount == 1" failed.
main: src/BaseMeta.cpp:951: int InuseRecovery::iterator::update_status_clean(): Assertion "curr_desc->maxcount == 1" failed.
```

