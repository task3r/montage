//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Copyright 2018, Intel Corporation
//
// Modified to test pmem::obj containers
//

#include <libpmemobj++/experimental/array.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/transaction.hpp>

#include "unittest.hpp"

namespace pmem_exp = pmem::obj::experimental;

struct Testcase1 {
    typedef double T;
    typedef pmem_exp::array<T, 3> C;
    C c = {{1, 2, 3.5}};

    void run() {
        UT_ASSERT(c.size() == 3);
        UT_ASSERT(c.max_size() == 3);
        UT_ASSERT(!c.empty());
    }
};

struct Testcase2 {
    typedef double T;
    typedef pmem_exp::array<T, 0> C;
    C c = {{}};

    void run() {
        UT_ASSERT(c.size() == 0);
        UT_ASSERT(c.max_size() == 0);
        UT_ASSERT(c.empty());
    }
};

struct root {
    pmem::obj::persistent_ptr<Testcase1> r1;
    pmem::obj::persistent_ptr<Testcase2> r2;
};

void run(pmem::obj::pool<root> &pop) {
    try {
        pmem::obj::transaction::run(pop, [&] {
            pop.root()->r1 = pmem::obj::make_persistent<Testcase1>();
            pop.root()->r2 = pmem::obj::make_persistent<Testcase2>();
        });

        pmem::obj::transaction::run(pop, [&] {
            pop.root()->r1->run();
            pop.root()->r2->run();
        });
    } catch (...) {
        UT_ASSERT(0);
    }
}

int main(int argc, char *argv[]) {
    START();

    if (argc != 2) UT_FATAL("usage: %s file-name", argv[0]);

    const char *path = argv[1];

    pmem::obj::pool<root> pop;
    try {
        pop = pmem::obj::pool<root>::create(path, "size.pass", PMEMOBJ_MIN_POOL,
                                            S_IWUSR | S_IRUSR);
    } catch (...) {
        UT_FATAL("!pmemobj_create: %s", path);
    }

    run(pop);

    return 0;
}
