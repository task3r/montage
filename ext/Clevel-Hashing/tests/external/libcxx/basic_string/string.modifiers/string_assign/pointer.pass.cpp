//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Copyright 2019, Intel Corporation
//
// Modified to test pmem::obj containers
//

#include <libpmemobj++/experimental/string.hpp>

#include "unittest.hpp"

namespace nvobj = pmem::obj;
namespace pmem_exp = pmem::obj::experimental;
using S = pmem_exp::string;

struct root {
    nvobj::persistent_ptr<S> s, s_short, s_long;
    nvobj::persistent_ptr<S> s_arr[5];
};

template <class S>
void test(nvobj::pool<struct root> &pop, const S &s1,
          const typename S::value_type *str, const S &expected) {
    auto r = pop.root();

    nvobj::transaction::run(pop, [&] { r->s = nvobj::make_persistent<S>(s1); });

    auto &s = *r->s;

    s.assign(str);
    UT_ASSERT(s == expected);

    nvobj::transaction::run(pop, [&] { nvobj::delete_persistent<S>(r->s); });
}

int main(int argc, char *argv[]) {
    START();

    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " file-name" << std::endl;
        return 1;
    }

    auto path = argv[1];
    auto pop = nvobj::pool<root>::create(path, "string_test", PMEMOBJ_MIN_POOL,
                                         S_IWUSR | S_IRUSR);

    auto r = pop.root();
    {
        auto &s_arr = r->s_arr;
        try {
            nvobj::transaction::run(pop, [&] {
                s_arr[0] = nvobj::make_persistent<S>();
                s_arr[1] = nvobj::make_persistent<S>("12345");
                s_arr[2] = nvobj::make_persistent<S>("1234567890");
                s_arr[3] = nvobj::make_persistent<S>("12345678901234567890");
                s_arr[4] = nvobj::make_persistent<S>(
                    "1234567890123456789012345678901234567890123456789012345678"
                    "901234567890");
            });

            test(pop, *s_arr[0], "", *s_arr[0]);
            test(pop, *s_arr[0], "12345", *s_arr[1]);
            test(pop, *s_arr[0], "12345678901234567890", *s_arr[3]);
            test(pop, *s_arr[0],
                 "1234567890123456789012345678901234567890123456789012345678901"
                 "234567890",
                 *s_arr[4]);

            test(pop, *s_arr[1], "", *s_arr[0]);
            test(pop, *s_arr[1], "12345", *s_arr[1]);
            test(pop, *s_arr[1], "1234567890", *s_arr[2]);
            test(pop, *s_arr[1],
                 "1234567890123456789012345678901234567890123456789012345678901"
                 "234567890",
                 *s_arr[4]);

            test(pop, *s_arr[3], "", *s_arr[0]);
            test(pop, *s_arr[3], "12345", *s_arr[1]);
            test(pop, *s_arr[3], "12345678901234567890", *s_arr[3]);
            test(pop, *s_arr[3],
                 "1234567890123456789012345678901234567890123456789012345678901"
                 "234567890",
                 *s_arr[4]);

            test(pop, *s_arr[4], "", *s_arr[0]);
            test(pop, *s_arr[4], "12345", *s_arr[1]);
            test(pop, *s_arr[4], "12345678901234567890", *s_arr[3]);
            test(pop, *s_arr[4],
                 "1234567890123456789012345678901234567890123456789012345678901"
                 "234567890",
                 *s_arr[4]);

            nvobj::transaction::run(pop, [&] {
                for (unsigned i = 0; i < 5; ++i) {
                    nvobj::delete_persistent<S>(s_arr[i]);
                }
            });
        } catch (std::exception &e) {
            UT_FATALexc(e);
        }
    }
    {  // test assignment to self
        try {
            nvobj::transaction::run(pop, [&] {
                r->s_short = nvobj::make_persistent<S>("123/");
                r->s_long = nvobj::make_persistent<S>(
                    "Lorem ipsum dolor sit amet, consectetur/");
            });

            auto &s_short = *r->s_short;
            auto &s_long = *r->s_long;

            s_short.assign(s_short.c_str());
            UT_ASSERT(s_short == "123/");
            s_short.assign(s_short.c_str() + 2);
            UT_ASSERT(s_short == "3/");

            s_long.assign(s_long.c_str() + 30);
            UT_ASSERT(s_long == "nsectetur/");

            nvobj::transaction::run(pop, [&] {
                nvobj::delete_persistent<S>(r->s_short);
                nvobj::delete_persistent<S>(r->s_long);
            });
        } catch (std::exception &e) {
            UT_FATALexc(e);
        }
    }

    pop.close();

    return 0;
}
