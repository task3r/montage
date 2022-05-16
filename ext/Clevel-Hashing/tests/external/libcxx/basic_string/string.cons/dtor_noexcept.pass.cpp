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

namespace pmem_exp = pmem::obj::experimental;

int main() {
    {
        typedef pmem_exp::string C;
        static_assert(std::is_nothrow_destructible<C>::value, "");
    }
}
