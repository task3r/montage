//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <string>

// basic_string<charT,traits,Allocator>&
//   replace(size_type pos, size_type n1, const charT* s, size_type n2);

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <string>

#include "min_allocator.h"
#include "test_macros.h"

template <class S>
void test(S s, typename S::size_type pos, typename S::size_type n1,
          const typename S::value_type* str, typename S::size_type n2,
          S expected) {
    const typename S::size_type old_size = s.size();
    S s0 = s;
    if (pos <= old_size) {
        s.replace(pos, n1, str, n2);
        LIBCPP_ASSERT(s.__invariants());
        assert(s == expected);
        typename S::size_type xlen = std::min(n1, old_size - pos);
        typename S::size_type rlen = n2;
        assert(s.size() == old_size - xlen + rlen);
    }
#ifndef TEST_HAS_NO_EXCEPTIONS
    else {
        try {
            s.replace(pos, n1, str, n2);
            assert(false);
        } catch (std::out_of_range&) {
            assert(pos > old_size);
            assert(s == s0);
        }
    }
#endif
}

template <class S>
void test0() {
    test(S(""), 0, 0, "", 0, S(""));
    test(S(""), 0, 0, "12345", 0, S(""));
    test(S(""), 0, 0, "12345", 1, S("1"));
    test(S(""), 0, 0, "12345", 2, S("12"));
    test(S(""), 0, 0, "12345", 4, S("1234"));
    test(S(""), 0, 0, "12345", 5, S("12345"));
    test(S(""), 0, 0, "1234567890", 0, S(""));
    test(S(""), 0, 0, "1234567890", 1, S("1"));
    test(S(""), 0, 0, "1234567890", 5, S("12345"));
    test(S(""), 0, 0, "1234567890", 9, S("123456789"));
    test(S(""), 0, 0, "1234567890", 10, S("1234567890"));
    test(S(""), 0, 0, "12345678901234567890", 0, S(""));
    test(S(""), 0, 0, "12345678901234567890", 1, S("1"));
    test(S(""), 0, 0, "12345678901234567890", 10, S("1234567890"));
    test(S(""), 0, 0, "12345678901234567890", 19, S("1234567890123456789"));
    test(S(""), 0, 0, "12345678901234567890", 20, S("12345678901234567890"));
    test(S(""), 0, 1, "", 0, S(""));
    test(S(""), 0, 1, "12345", 0, S(""));
    test(S(""), 0, 1, "12345", 1, S("1"));
    test(S(""), 0, 1, "12345", 2, S("12"));
    test(S(""), 0, 1, "12345", 4, S("1234"));
    test(S(""), 0, 1, "12345", 5, S("12345"));
    test(S(""), 0, 1, "1234567890", 0, S(""));
    test(S(""), 0, 1, "1234567890", 1, S("1"));
    test(S(""), 0, 1, "1234567890", 5, S("12345"));
    test(S(""), 0, 1, "1234567890", 9, S("123456789"));
    test(S(""), 0, 1, "1234567890", 10, S("1234567890"));
    test(S(""), 0, 1, "12345678901234567890", 0, S(""));
    test(S(""), 0, 1, "12345678901234567890", 1, S("1"));
    test(S(""), 0, 1, "12345678901234567890", 10, S("1234567890"));
    test(S(""), 0, 1, "12345678901234567890", 19, S("1234567890123456789"));
    test(S(""), 0, 1, "12345678901234567890", 20, S("12345678901234567890"));
    test(S(""), 1, 0, "", 0, S("can't happen"));
    test(S(""), 1, 0, "12345", 0, S("can't happen"));
    test(S(""), 1, 0, "12345", 1, S("can't happen"));
    test(S(""), 1, 0, "12345", 2, S("can't happen"));
    test(S(""), 1, 0, "12345", 4, S("can't happen"));
    test(S(""), 1, 0, "12345", 5, S("can't happen"));
    test(S(""), 1, 0, "1234567890", 0, S("can't happen"));
    test(S(""), 1, 0, "1234567890", 1, S("can't happen"));
    test(S(""), 1, 0, "1234567890", 5, S("can't happen"));
    test(S(""), 1, 0, "1234567890", 9, S("can't happen"));
    test(S(""), 1, 0, "1234567890", 10, S("can't happen"));
    test(S(""), 1, 0, "12345678901234567890", 0, S("can't happen"));
    test(S(""), 1, 0, "12345678901234567890", 1, S("can't happen"));
    test(S(""), 1, 0, "12345678901234567890", 10, S("can't happen"));
    test(S(""), 1, 0, "12345678901234567890", 19, S("can't happen"));
    test(S(""), 1, 0, "12345678901234567890", 20, S("can't happen"));
    test(S("abcde"), 0, 0, "", 0, S("abcde"));
    test(S("abcde"), 0, 0, "12345", 0, S("abcde"));
    test(S("abcde"), 0, 0, "12345", 1, S("1abcde"));
    test(S("abcde"), 0, 0, "12345", 2, S("12abcde"));
    test(S("abcde"), 0, 0, "12345", 4, S("1234abcde"));
    test(S("abcde"), 0, 0, "12345", 5, S("12345abcde"));
    test(S("abcde"), 0, 0, "1234567890", 0, S("abcde"));
    test(S("abcde"), 0, 0, "1234567890", 1, S("1abcde"));
    test(S("abcde"), 0, 0, "1234567890", 5, S("12345abcde"));
    test(S("abcde"), 0, 0, "1234567890", 9, S("123456789abcde"));
    test(S("abcde"), 0, 0, "1234567890", 10, S("1234567890abcde"));
    test(S("abcde"), 0, 0, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 0, 0, "12345678901234567890", 1, S("1abcde"));
    test(S("abcde"), 0, 0, "12345678901234567890", 10, S("1234567890abcde"));
    test(S("abcde"), 0, 0, "12345678901234567890", 19,
         S("1234567890123456789abcde"));
    test(S("abcde"), 0, 0, "12345678901234567890", 20,
         S("12345678901234567890abcde"));
    test(S("abcde"), 0, 1, "", 0, S("bcde"));
    test(S("abcde"), 0, 1, "12345", 0, S("bcde"));
    test(S("abcde"), 0, 1, "12345", 1, S("1bcde"));
    test(S("abcde"), 0, 1, "12345", 2, S("12bcde"));
    test(S("abcde"), 0, 1, "12345", 4, S("1234bcde"));
    test(S("abcde"), 0, 1, "12345", 5, S("12345bcde"));
    test(S("abcde"), 0, 1, "1234567890", 0, S("bcde"));
    test(S("abcde"), 0, 1, "1234567890", 1, S("1bcde"));
    test(S("abcde"), 0, 1, "1234567890", 5, S("12345bcde"));
    test(S("abcde"), 0, 1, "1234567890", 9, S("123456789bcde"));
    test(S("abcde"), 0, 1, "1234567890", 10, S("1234567890bcde"));
    test(S("abcde"), 0, 1, "12345678901234567890", 0, S("bcde"));
    test(S("abcde"), 0, 1, "12345678901234567890", 1, S("1bcde"));
    test(S("abcde"), 0, 1, "12345678901234567890", 10, S("1234567890bcde"));
    test(S("abcde"), 0, 1, "12345678901234567890", 19,
         S("1234567890123456789bcde"));
    test(S("abcde"), 0, 1, "12345678901234567890", 20,
         S("12345678901234567890bcde"));
    test(S("abcde"), 0, 2, "", 0, S("cde"));
    test(S("abcde"), 0, 2, "12345", 0, S("cde"));
    test(S("abcde"), 0, 2, "12345", 1, S("1cde"));
    test(S("abcde"), 0, 2, "12345", 2, S("12cde"));
    test(S("abcde"), 0, 2, "12345", 4, S("1234cde"));
    test(S("abcde"), 0, 2, "12345", 5, S("12345cde"));
    test(S("abcde"), 0, 2, "1234567890", 0, S("cde"));
    test(S("abcde"), 0, 2, "1234567890", 1, S("1cde"));
    test(S("abcde"), 0, 2, "1234567890", 5, S("12345cde"));
    test(S("abcde"), 0, 2, "1234567890", 9, S("123456789cde"));
    test(S("abcde"), 0, 2, "1234567890", 10, S("1234567890cde"));
    test(S("abcde"), 0, 2, "12345678901234567890", 0, S("cde"));
    test(S("abcde"), 0, 2, "12345678901234567890", 1, S("1cde"));
    test(S("abcde"), 0, 2, "12345678901234567890", 10, S("1234567890cde"));
    test(S("abcde"), 0, 2, "12345678901234567890", 19,
         S("1234567890123456789cde"));
    test(S("abcde"), 0, 2, "12345678901234567890", 20,
         S("12345678901234567890cde"));
    test(S("abcde"), 0, 4, "", 0, S("e"));
    test(S("abcde"), 0, 4, "12345", 0, S("e"));
    test(S("abcde"), 0, 4, "12345", 1, S("1e"));
    test(S("abcde"), 0, 4, "12345", 2, S("12e"));
}

template <class S>
void test1() {
    test(S("abcde"), 0, 4, "12345", 4, S("1234e"));
    test(S("abcde"), 0, 4, "12345", 5, S("12345e"));
    test(S("abcde"), 0, 4, "1234567890", 0, S("e"));
    test(S("abcde"), 0, 4, "1234567890", 1, S("1e"));
    test(S("abcde"), 0, 4, "1234567890", 5, S("12345e"));
    test(S("abcde"), 0, 4, "1234567890", 9, S("123456789e"));
    test(S("abcde"), 0, 4, "1234567890", 10, S("1234567890e"));
    test(S("abcde"), 0, 4, "12345678901234567890", 0, S("e"));
    test(S("abcde"), 0, 4, "12345678901234567890", 1, S("1e"));
    test(S("abcde"), 0, 4, "12345678901234567890", 10, S("1234567890e"));
    test(S("abcde"), 0, 4, "12345678901234567890", 19,
         S("1234567890123456789e"));
    test(S("abcde"), 0, 4, "12345678901234567890", 20,
         S("12345678901234567890e"));
    test(S("abcde"), 0, 5, "", 0, S(""));
    test(S("abcde"), 0, 5, "12345", 0, S(""));
    test(S("abcde"), 0, 5, "12345", 1, S("1"));
    test(S("abcde"), 0, 5, "12345", 2, S("12"));
    test(S("abcde"), 0, 5, "12345", 4, S("1234"));
    test(S("abcde"), 0, 5, "12345", 5, S("12345"));
    test(S("abcde"), 0, 5, "1234567890", 0, S(""));
    test(S("abcde"), 0, 5, "1234567890", 1, S("1"));
    test(S("abcde"), 0, 5, "1234567890", 5, S("12345"));
    test(S("abcde"), 0, 5, "1234567890", 9, S("123456789"));
    test(S("abcde"), 0, 5, "1234567890", 10, S("1234567890"));
    test(S("abcde"), 0, 5, "12345678901234567890", 0, S(""));
    test(S("abcde"), 0, 5, "12345678901234567890", 1, S("1"));
    test(S("abcde"), 0, 5, "12345678901234567890", 10, S("1234567890"));
    test(S("abcde"), 0, 5, "12345678901234567890", 19,
         S("1234567890123456789"));
    test(S("abcde"), 0, 5, "12345678901234567890", 20,
         S("12345678901234567890"));
    test(S("abcde"), 0, 6, "", 0, S(""));
    test(S("abcde"), 0, 6, "12345", 0, S(""));
    test(S("abcde"), 0, 6, "12345", 1, S("1"));
    test(S("abcde"), 0, 6, "12345", 2, S("12"));
    test(S("abcde"), 0, 6, "12345", 4, S("1234"));
    test(S("abcde"), 0, 6, "12345", 5, S("12345"));
    test(S("abcde"), 0, 6, "1234567890", 0, S(""));
    test(S("abcde"), 0, 6, "1234567890", 1, S("1"));
    test(S("abcde"), 0, 6, "1234567890", 5, S("12345"));
    test(S("abcde"), 0, 6, "1234567890", 9, S("123456789"));
    test(S("abcde"), 0, 6, "1234567890", 10, S("1234567890"));
    test(S("abcde"), 0, 6, "12345678901234567890", 0, S(""));
    test(S("abcde"), 0, 6, "12345678901234567890", 1, S("1"));
    test(S("abcde"), 0, 6, "12345678901234567890", 10, S("1234567890"));
    test(S("abcde"), 0, 6, "12345678901234567890", 19,
         S("1234567890123456789"));
    test(S("abcde"), 0, 6, "12345678901234567890", 20,
         S("12345678901234567890"));
    test(S("abcde"), 1, 0, "", 0, S("abcde"));
    test(S("abcde"), 1, 0, "12345", 0, S("abcde"));
    test(S("abcde"), 1, 0, "12345", 1, S("a1bcde"));
    test(S("abcde"), 1, 0, "12345", 2, S("a12bcde"));
    test(S("abcde"), 1, 0, "12345", 4, S("a1234bcde"));
    test(S("abcde"), 1, 0, "12345", 5, S("a12345bcde"));
    test(S("abcde"), 1, 0, "1234567890", 0, S("abcde"));
    test(S("abcde"), 1, 0, "1234567890", 1, S("a1bcde"));
    test(S("abcde"), 1, 0, "1234567890", 5, S("a12345bcde"));
    test(S("abcde"), 1, 0, "1234567890", 9, S("a123456789bcde"));
    test(S("abcde"), 1, 0, "1234567890", 10, S("a1234567890bcde"));
    test(S("abcde"), 1, 0, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 1, 0, "12345678901234567890", 1, S("a1bcde"));
    test(S("abcde"), 1, 0, "12345678901234567890", 10, S("a1234567890bcde"));
    test(S("abcde"), 1, 0, "12345678901234567890", 19,
         S("a1234567890123456789bcde"));
    test(S("abcde"), 1, 0, "12345678901234567890", 20,
         S("a12345678901234567890bcde"));
    test(S("abcde"), 1, 1, "", 0, S("acde"));
    test(S("abcde"), 1, 1, "12345", 0, S("acde"));
    test(S("abcde"), 1, 1, "12345", 1, S("a1cde"));
    test(S("abcde"), 1, 1, "12345", 2, S("a12cde"));
    test(S("abcde"), 1, 1, "12345", 4, S("a1234cde"));
    test(S("abcde"), 1, 1, "12345", 5, S("a12345cde"));
    test(S("abcde"), 1, 1, "1234567890", 0, S("acde"));
    test(S("abcde"), 1, 1, "1234567890", 1, S("a1cde"));
    test(S("abcde"), 1, 1, "1234567890", 5, S("a12345cde"));
    test(S("abcde"), 1, 1, "1234567890", 9, S("a123456789cde"));
    test(S("abcde"), 1, 1, "1234567890", 10, S("a1234567890cde"));
    test(S("abcde"), 1, 1, "12345678901234567890", 0, S("acde"));
    test(S("abcde"), 1, 1, "12345678901234567890", 1, S("a1cde"));
    test(S("abcde"), 1, 1, "12345678901234567890", 10, S("a1234567890cde"));
    test(S("abcde"), 1, 1, "12345678901234567890", 19,
         S("a1234567890123456789cde"));
    test(S("abcde"), 1, 1, "12345678901234567890", 20,
         S("a12345678901234567890cde"));
    test(S("abcde"), 1, 2, "", 0, S("ade"));
    test(S("abcde"), 1, 2, "12345", 0, S("ade"));
    test(S("abcde"), 1, 2, "12345", 1, S("a1de"));
    test(S("abcde"), 1, 2, "12345", 2, S("a12de"));
    test(S("abcde"), 1, 2, "12345", 4, S("a1234de"));
    test(S("abcde"), 1, 2, "12345", 5, S("a12345de"));
    test(S("abcde"), 1, 2, "1234567890", 0, S("ade"));
    test(S("abcde"), 1, 2, "1234567890", 1, S("a1de"));
    test(S("abcde"), 1, 2, "1234567890", 5, S("a12345de"));
    test(S("abcde"), 1, 2, "1234567890", 9, S("a123456789de"));
    test(S("abcde"), 1, 2, "1234567890", 10, S("a1234567890de"));
    test(S("abcde"), 1, 2, "12345678901234567890", 0, S("ade"));
    test(S("abcde"), 1, 2, "12345678901234567890", 1, S("a1de"));
    test(S("abcde"), 1, 2, "12345678901234567890", 10, S("a1234567890de"));
    test(S("abcde"), 1, 2, "12345678901234567890", 19,
         S("a1234567890123456789de"));
    test(S("abcde"), 1, 2, "12345678901234567890", 20,
         S("a12345678901234567890de"));
    test(S("abcde"), 1, 3, "", 0, S("ae"));
    test(S("abcde"), 1, 3, "12345", 0, S("ae"));
    test(S("abcde"), 1, 3, "12345", 1, S("a1e"));
    test(S("abcde"), 1, 3, "12345", 2, S("a12e"));
    test(S("abcde"), 1, 3, "12345", 4, S("a1234e"));
    test(S("abcde"), 1, 3, "12345", 5, S("a12345e"));
    test(S("abcde"), 1, 3, "1234567890", 0, S("ae"));
    test(S("abcde"), 1, 3, "1234567890", 1, S("a1e"));
}

template <class S>
void test2() {
    test(S("abcde"), 1, 3, "1234567890", 5, S("a12345e"));
    test(S("abcde"), 1, 3, "1234567890", 9, S("a123456789e"));
    test(S("abcde"), 1, 3, "1234567890", 10, S("a1234567890e"));
    test(S("abcde"), 1, 3, "12345678901234567890", 0, S("ae"));
    test(S("abcde"), 1, 3, "12345678901234567890", 1, S("a1e"));
    test(S("abcde"), 1, 3, "12345678901234567890", 10, S("a1234567890e"));
    test(S("abcde"), 1, 3, "12345678901234567890", 19,
         S("a1234567890123456789e"));
    test(S("abcde"), 1, 3, "12345678901234567890", 20,
         S("a12345678901234567890e"));
    test(S("abcde"), 1, 4, "", 0, S("a"));
    test(S("abcde"), 1, 4, "12345", 0, S("a"));
    test(S("abcde"), 1, 4, "12345", 1, S("a1"));
    test(S("abcde"), 1, 4, "12345", 2, S("a12"));
    test(S("abcde"), 1, 4, "12345", 4, S("a1234"));
    test(S("abcde"), 1, 4, "12345", 5, S("a12345"));
    test(S("abcde"), 1, 4, "1234567890", 0, S("a"));
    test(S("abcde"), 1, 4, "1234567890", 1, S("a1"));
    test(S("abcde"), 1, 4, "1234567890", 5, S("a12345"));
    test(S("abcde"), 1, 4, "1234567890", 9, S("a123456789"));
    test(S("abcde"), 1, 4, "1234567890", 10, S("a1234567890"));
    test(S("abcde"), 1, 4, "12345678901234567890", 0, S("a"));
    test(S("abcde"), 1, 4, "12345678901234567890", 1, S("a1"));
    test(S("abcde"), 1, 4, "12345678901234567890", 10, S("a1234567890"));
    test(S("abcde"), 1, 4, "12345678901234567890", 19,
         S("a1234567890123456789"));
    test(S("abcde"), 1, 4, "12345678901234567890", 20,
         S("a12345678901234567890"));
    test(S("abcde"), 1, 5, "", 0, S("a"));
    test(S("abcde"), 1, 5, "12345", 0, S("a"));
    test(S("abcde"), 1, 5, "12345", 1, S("a1"));
    test(S("abcde"), 1, 5, "12345", 2, S("a12"));
    test(S("abcde"), 1, 5, "12345", 4, S("a1234"));
    test(S("abcde"), 1, 5, "12345", 5, S("a12345"));
    test(S("abcde"), 1, 5, "1234567890", 0, S("a"));
    test(S("abcde"), 1, 5, "1234567890", 1, S("a1"));
    test(S("abcde"), 1, 5, "1234567890", 5, S("a12345"));
    test(S("abcde"), 1, 5, "1234567890", 9, S("a123456789"));
    test(S("abcde"), 1, 5, "1234567890", 10, S("a1234567890"));
    test(S("abcde"), 1, 5, "12345678901234567890", 0, S("a"));
    test(S("abcde"), 1, 5, "12345678901234567890", 1, S("a1"));
    test(S("abcde"), 1, 5, "12345678901234567890", 10, S("a1234567890"));
    test(S("abcde"), 1, 5, "12345678901234567890", 19,
         S("a1234567890123456789"));
    test(S("abcde"), 1, 5, "12345678901234567890", 20,
         S("a12345678901234567890"));
    test(S("abcde"), 2, 0, "", 0, S("abcde"));
    test(S("abcde"), 2, 0, "12345", 0, S("abcde"));
    test(S("abcde"), 2, 0, "12345", 1, S("ab1cde"));
    test(S("abcde"), 2, 0, "12345", 2, S("ab12cde"));
    test(S("abcde"), 2, 0, "12345", 4, S("ab1234cde"));
    test(S("abcde"), 2, 0, "12345", 5, S("ab12345cde"));
    test(S("abcde"), 2, 0, "1234567890", 0, S("abcde"));
    test(S("abcde"), 2, 0, "1234567890", 1, S("ab1cde"));
    test(S("abcde"), 2, 0, "1234567890", 5, S("ab12345cde"));
    test(S("abcde"), 2, 0, "1234567890", 9, S("ab123456789cde"));
    test(S("abcde"), 2, 0, "1234567890", 10, S("ab1234567890cde"));
    test(S("abcde"), 2, 0, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 2, 0, "12345678901234567890", 1, S("ab1cde"));
    test(S("abcde"), 2, 0, "12345678901234567890", 10, S("ab1234567890cde"));
    test(S("abcde"), 2, 0, "12345678901234567890", 19,
         S("ab1234567890123456789cde"));
    test(S("abcde"), 2, 0, "12345678901234567890", 20,
         S("ab12345678901234567890cde"));
    test(S("abcde"), 2, 1, "", 0, S("abde"));
    test(S("abcde"), 2, 1, "12345", 0, S("abde"));
    test(S("abcde"), 2, 1, "12345", 1, S("ab1de"));
    test(S("abcde"), 2, 1, "12345", 2, S("ab12de"));
    test(S("abcde"), 2, 1, "12345", 4, S("ab1234de"));
    test(S("abcde"), 2, 1, "12345", 5, S("ab12345de"));
    test(S("abcde"), 2, 1, "1234567890", 0, S("abde"));
    test(S("abcde"), 2, 1, "1234567890", 1, S("ab1de"));
    test(S("abcde"), 2, 1, "1234567890", 5, S("ab12345de"));
    test(S("abcde"), 2, 1, "1234567890", 9, S("ab123456789de"));
    test(S("abcde"), 2, 1, "1234567890", 10, S("ab1234567890de"));
    test(S("abcde"), 2, 1, "12345678901234567890", 0, S("abde"));
    test(S("abcde"), 2, 1, "12345678901234567890", 1, S("ab1de"));
    test(S("abcde"), 2, 1, "12345678901234567890", 10, S("ab1234567890de"));
    test(S("abcde"), 2, 1, "12345678901234567890", 19,
         S("ab1234567890123456789de"));
    test(S("abcde"), 2, 1, "12345678901234567890", 20,
         S("ab12345678901234567890de"));
    test(S("abcde"), 2, 2, "", 0, S("abe"));
    test(S("abcde"), 2, 2, "12345", 0, S("abe"));
    test(S("abcde"), 2, 2, "12345", 1, S("ab1e"));
    test(S("abcde"), 2, 2, "12345", 2, S("ab12e"));
    test(S("abcde"), 2, 2, "12345", 4, S("ab1234e"));
    test(S("abcde"), 2, 2, "12345", 5, S("ab12345e"));
    test(S("abcde"), 2, 2, "1234567890", 0, S("abe"));
    test(S("abcde"), 2, 2, "1234567890", 1, S("ab1e"));
    test(S("abcde"), 2, 2, "1234567890", 5, S("ab12345e"));
    test(S("abcde"), 2, 2, "1234567890", 9, S("ab123456789e"));
    test(S("abcde"), 2, 2, "1234567890", 10, S("ab1234567890e"));
    test(S("abcde"), 2, 2, "12345678901234567890", 0, S("abe"));
    test(S("abcde"), 2, 2, "12345678901234567890", 1, S("ab1e"));
    test(S("abcde"), 2, 2, "12345678901234567890", 10, S("ab1234567890e"));
    test(S("abcde"), 2, 2, "12345678901234567890", 19,
         S("ab1234567890123456789e"));
    test(S("abcde"), 2, 2, "12345678901234567890", 20,
         S("ab12345678901234567890e"));
    test(S("abcde"), 2, 3, "", 0, S("ab"));
    test(S("abcde"), 2, 3, "12345", 0, S("ab"));
    test(S("abcde"), 2, 3, "12345", 1, S("ab1"));
    test(S("abcde"), 2, 3, "12345", 2, S("ab12"));
    test(S("abcde"), 2, 3, "12345", 4, S("ab1234"));
    test(S("abcde"), 2, 3, "12345", 5, S("ab12345"));
    test(S("abcde"), 2, 3, "1234567890", 0, S("ab"));
    test(S("abcde"), 2, 3, "1234567890", 1, S("ab1"));
    test(S("abcde"), 2, 3, "1234567890", 5, S("ab12345"));
    test(S("abcde"), 2, 3, "1234567890", 9, S("ab123456789"));
    test(S("abcde"), 2, 3, "1234567890", 10, S("ab1234567890"));
    test(S("abcde"), 2, 3, "12345678901234567890", 0, S("ab"));
}

template <class S>
void test3() {
    test(S("abcde"), 2, 3, "12345678901234567890", 1, S("ab1"));
    test(S("abcde"), 2, 3, "12345678901234567890", 10, S("ab1234567890"));
    test(S("abcde"), 2, 3, "12345678901234567890", 19,
         S("ab1234567890123456789"));
    test(S("abcde"), 2, 3, "12345678901234567890", 20,
         S("ab12345678901234567890"));
    test(S("abcde"), 2, 4, "", 0, S("ab"));
    test(S("abcde"), 2, 4, "12345", 0, S("ab"));
    test(S("abcde"), 2, 4, "12345", 1, S("ab1"));
    test(S("abcde"), 2, 4, "12345", 2, S("ab12"));
    test(S("abcde"), 2, 4, "12345", 4, S("ab1234"));
    test(S("abcde"), 2, 4, "12345", 5, S("ab12345"));
    test(S("abcde"), 2, 4, "1234567890", 0, S("ab"));
    test(S("abcde"), 2, 4, "1234567890", 1, S("ab1"));
    test(S("abcde"), 2, 4, "1234567890", 5, S("ab12345"));
    test(S("abcde"), 2, 4, "1234567890", 9, S("ab123456789"));
    test(S("abcde"), 2, 4, "1234567890", 10, S("ab1234567890"));
    test(S("abcde"), 2, 4, "12345678901234567890", 0, S("ab"));
    test(S("abcde"), 2, 4, "12345678901234567890", 1, S("ab1"));
    test(S("abcde"), 2, 4, "12345678901234567890", 10, S("ab1234567890"));
    test(S("abcde"), 2, 4, "12345678901234567890", 19,
         S("ab1234567890123456789"));
    test(S("abcde"), 2, 4, "12345678901234567890", 20,
         S("ab12345678901234567890"));
    test(S("abcde"), 4, 0, "", 0, S("abcde"));
    test(S("abcde"), 4, 0, "12345", 0, S("abcde"));
    test(S("abcde"), 4, 0, "12345", 1, S("abcd1e"));
    test(S("abcde"), 4, 0, "12345", 2, S("abcd12e"));
    test(S("abcde"), 4, 0, "12345", 4, S("abcd1234e"));
    test(S("abcde"), 4, 0, "12345", 5, S("abcd12345e"));
    test(S("abcde"), 4, 0, "1234567890", 0, S("abcde"));
    test(S("abcde"), 4, 0, "1234567890", 1, S("abcd1e"));
    test(S("abcde"), 4, 0, "1234567890", 5, S("abcd12345e"));
    test(S("abcde"), 4, 0, "1234567890", 9, S("abcd123456789e"));
    test(S("abcde"), 4, 0, "1234567890", 10, S("abcd1234567890e"));
    test(S("abcde"), 4, 0, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 4, 0, "12345678901234567890", 1, S("abcd1e"));
    test(S("abcde"), 4, 0, "12345678901234567890", 10, S("abcd1234567890e"));
    test(S("abcde"), 4, 0, "12345678901234567890", 19,
         S("abcd1234567890123456789e"));
    test(S("abcde"), 4, 0, "12345678901234567890", 20,
         S("abcd12345678901234567890e"));
    test(S("abcde"), 4, 1, "", 0, S("abcd"));
    test(S("abcde"), 4, 1, "12345", 0, S("abcd"));
    test(S("abcde"), 4, 1, "12345", 1, S("abcd1"));
    test(S("abcde"), 4, 1, "12345", 2, S("abcd12"));
    test(S("abcde"), 4, 1, "12345", 4, S("abcd1234"));
    test(S("abcde"), 4, 1, "12345", 5, S("abcd12345"));
    test(S("abcde"), 4, 1, "1234567890", 0, S("abcd"));
    test(S("abcde"), 4, 1, "1234567890", 1, S("abcd1"));
    test(S("abcde"), 4, 1, "1234567890", 5, S("abcd12345"));
    test(S("abcde"), 4, 1, "1234567890", 9, S("abcd123456789"));
    test(S("abcde"), 4, 1, "1234567890", 10, S("abcd1234567890"));
    test(S("abcde"), 4, 1, "12345678901234567890", 0, S("abcd"));
    test(S("abcde"), 4, 1, "12345678901234567890", 1, S("abcd1"));
    test(S("abcde"), 4, 1, "12345678901234567890", 10, S("abcd1234567890"));
    test(S("abcde"), 4, 1, "12345678901234567890", 19,
         S("abcd1234567890123456789"));
    test(S("abcde"), 4, 1, "12345678901234567890", 20,
         S("abcd12345678901234567890"));
    test(S("abcde"), 4, 2, "", 0, S("abcd"));
    test(S("abcde"), 4, 2, "12345", 0, S("abcd"));
    test(S("abcde"), 4, 2, "12345", 1, S("abcd1"));
    test(S("abcde"), 4, 2, "12345", 2, S("abcd12"));
    test(S("abcde"), 4, 2, "12345", 4, S("abcd1234"));
    test(S("abcde"), 4, 2, "12345", 5, S("abcd12345"));
    test(S("abcde"), 4, 2, "1234567890", 0, S("abcd"));
    test(S("abcde"), 4, 2, "1234567890", 1, S("abcd1"));
    test(S("abcde"), 4, 2, "1234567890", 5, S("abcd12345"));
    test(S("abcde"), 4, 2, "1234567890", 9, S("abcd123456789"));
    test(S("abcde"), 4, 2, "1234567890", 10, S("abcd1234567890"));
    test(S("abcde"), 4, 2, "12345678901234567890", 0, S("abcd"));
    test(S("abcde"), 4, 2, "12345678901234567890", 1, S("abcd1"));
    test(S("abcde"), 4, 2, "12345678901234567890", 10, S("abcd1234567890"));
    test(S("abcde"), 4, 2, "12345678901234567890", 19,
         S("abcd1234567890123456789"));
    test(S("abcde"), 4, 2, "12345678901234567890", 20,
         S("abcd12345678901234567890"));
    test(S("abcde"), 5, 0, "", 0, S("abcde"));
    test(S("abcde"), 5, 0, "12345", 0, S("abcde"));
    test(S("abcde"), 5, 0, "12345", 1, S("abcde1"));
    test(S("abcde"), 5, 0, "12345", 2, S("abcde12"));
    test(S("abcde"), 5, 0, "12345", 4, S("abcde1234"));
    test(S("abcde"), 5, 0, "12345", 5, S("abcde12345"));
    test(S("abcde"), 5, 0, "1234567890", 0, S("abcde"));
    test(S("abcde"), 5, 0, "1234567890", 1, S("abcde1"));
    test(S("abcde"), 5, 0, "1234567890", 5, S("abcde12345"));
    test(S("abcde"), 5, 0, "1234567890", 9, S("abcde123456789"));
    test(S("abcde"), 5, 0, "1234567890", 10, S("abcde1234567890"));
    test(S("abcde"), 5, 0, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 5, 0, "12345678901234567890", 1, S("abcde1"));
    test(S("abcde"), 5, 0, "12345678901234567890", 10, S("abcde1234567890"));
    test(S("abcde"), 5, 0, "12345678901234567890", 19,
         S("abcde1234567890123456789"));
    test(S("abcde"), 5, 0, "12345678901234567890", 20,
         S("abcde12345678901234567890"));
    test(S("abcde"), 5, 1, "", 0, S("abcde"));
    test(S("abcde"), 5, 1, "12345", 0, S("abcde"));
    test(S("abcde"), 5, 1, "12345", 1, S("abcde1"));
    test(S("abcde"), 5, 1, "12345", 2, S("abcde12"));
    test(S("abcde"), 5, 1, "12345", 4, S("abcde1234"));
    test(S("abcde"), 5, 1, "12345", 5, S("abcde12345"));
    test(S("abcde"), 5, 1, "1234567890", 0, S("abcde"));
    test(S("abcde"), 5, 1, "1234567890", 1, S("abcde1"));
    test(S("abcde"), 5, 1, "1234567890", 5, S("abcde12345"));
    test(S("abcde"), 5, 1, "1234567890", 9, S("abcde123456789"));
    test(S("abcde"), 5, 1, "1234567890", 10, S("abcde1234567890"));
    test(S("abcde"), 5, 1, "12345678901234567890", 0, S("abcde"));
    test(S("abcde"), 5, 1, "12345678901234567890", 1, S("abcde1"));
    test(S("abcde"), 5, 1, "12345678901234567890", 10, S("abcde1234567890"));
    test(S("abcde"), 5, 1, "12345678901234567890", 19,
         S("abcde1234567890123456789"));
    test(S("abcde"), 5, 1, "12345678901234567890", 20,
         S("abcde12345678901234567890"));
}

template <class S>
void test4() {
    test(S("abcde"), 6, 0, "", 0, S("can't happen"));
    test(S("abcde"), 6, 0, "12345", 0, S("can't happen"));
    test(S("abcde"), 6, 0, "12345", 1, S("can't happen"));
    test(S("abcde"), 6, 0, "12345", 2, S("can't happen"));
    test(S("abcde"), 6, 0, "12345", 4, S("can't happen"));
    test(S("abcde"), 6, 0, "12345", 5, S("can't happen"));
    test(S("abcde"), 6, 0, "1234567890", 0, S("can't happen"));
    test(S("abcde"), 6, 0, "1234567890", 1, S("can't happen"));
    test(S("abcde"), 6, 0, "1234567890", 5, S("can't happen"));
    test(S("abcde"), 6, 0, "1234567890", 9, S("can't happen"));
    test(S("abcde"), 6, 0, "1234567890", 10, S("can't happen"));
    test(S("abcde"), 6, 0, "12345678901234567890", 0, S("can't happen"));
    test(S("abcde"), 6, 0, "12345678901234567890", 1, S("can't happen"));
    test(S("abcde"), 6, 0, "12345678901234567890", 10, S("can't happen"));
    test(S("abcde"), 6, 0, "12345678901234567890", 19, S("can't happen"));
    test(S("abcde"), 6, 0, "12345678901234567890", 20, S("can't happen"));
    test(S("abcdefghij"), 0, 0, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345", 1, S("1abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345", 2, S("12abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345", 4, S("1234abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345", 5, S("12345abcdefghij"));
    test(S("abcdefghij"), 0, 0, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 0, 0, "1234567890", 1, S("1abcdefghij"));
    test(S("abcdefghij"), 0, 0, "1234567890", 5, S("12345abcdefghij"));
    test(S("abcdefghij"), 0, 0, "1234567890", 9, S("123456789abcdefghij"));
    test(S("abcdefghij"), 0, 0, "1234567890", 10, S("1234567890abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345678901234567890", 1, S("1abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345678901234567890", 10,
         S("1234567890abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345678901234567890", 19,
         S("1234567890123456789abcdefghij"));
    test(S("abcdefghij"), 0, 0, "12345678901234567890", 20,
         S("12345678901234567890abcdefghij"));
    test(S("abcdefghij"), 0, 1, "", 0, S("bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345", 0, S("bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345", 1, S("1bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345", 2, S("12bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345", 4, S("1234bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345", 5, S("12345bcdefghij"));
    test(S("abcdefghij"), 0, 1, "1234567890", 0, S("bcdefghij"));
    test(S("abcdefghij"), 0, 1, "1234567890", 1, S("1bcdefghij"));
    test(S("abcdefghij"), 0, 1, "1234567890", 5, S("12345bcdefghij"));
    test(S("abcdefghij"), 0, 1, "1234567890", 9, S("123456789bcdefghij"));
    test(S("abcdefghij"), 0, 1, "1234567890", 10, S("1234567890bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345678901234567890", 0, S("bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345678901234567890", 1, S("1bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345678901234567890", 10,
         S("1234567890bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345678901234567890", 19,
         S("1234567890123456789bcdefghij"));
    test(S("abcdefghij"), 0, 1, "12345678901234567890", 20,
         S("12345678901234567890bcdefghij"));
    test(S("abcdefghij"), 0, 5, "", 0, S("fghij"));
    test(S("abcdefghij"), 0, 5, "12345", 0, S("fghij"));
    test(S("abcdefghij"), 0, 5, "12345", 1, S("1fghij"));
    test(S("abcdefghij"), 0, 5, "12345", 2, S("12fghij"));
    test(S("abcdefghij"), 0, 5, "12345", 4, S("1234fghij"));
    test(S("abcdefghij"), 0, 5, "12345", 5, S("12345fghij"));
    test(S("abcdefghij"), 0, 5, "1234567890", 0, S("fghij"));
    test(S("abcdefghij"), 0, 5, "1234567890", 1, S("1fghij"));
    test(S("abcdefghij"), 0, 5, "1234567890", 5, S("12345fghij"));
    test(S("abcdefghij"), 0, 5, "1234567890", 9, S("123456789fghij"));
    test(S("abcdefghij"), 0, 5, "1234567890", 10, S("1234567890fghij"));
    test(S("abcdefghij"), 0, 5, "12345678901234567890", 0, S("fghij"));
    test(S("abcdefghij"), 0, 5, "12345678901234567890", 1, S("1fghij"));
    test(S("abcdefghij"), 0, 5, "12345678901234567890", 10,
         S("1234567890fghij"));
    test(S("abcdefghij"), 0, 5, "12345678901234567890", 19,
         S("1234567890123456789fghij"));
    test(S("abcdefghij"), 0, 5, "12345678901234567890", 20,
         S("12345678901234567890fghij"));
    test(S("abcdefghij"), 0, 9, "", 0, S("j"));
    test(S("abcdefghij"), 0, 9, "12345", 0, S("j"));
    test(S("abcdefghij"), 0, 9, "12345", 1, S("1j"));
    test(S("abcdefghij"), 0, 9, "12345", 2, S("12j"));
    test(S("abcdefghij"), 0, 9, "12345", 4, S("1234j"));
    test(S("abcdefghij"), 0, 9, "12345", 5, S("12345j"));
    test(S("abcdefghij"), 0, 9, "1234567890", 0, S("j"));
    test(S("abcdefghij"), 0, 9, "1234567890", 1, S("1j"));
    test(S("abcdefghij"), 0, 9, "1234567890", 5, S("12345j"));
    test(S("abcdefghij"), 0, 9, "1234567890", 9, S("123456789j"));
    test(S("abcdefghij"), 0, 9, "1234567890", 10, S("1234567890j"));
    test(S("abcdefghij"), 0, 9, "12345678901234567890", 0, S("j"));
    test(S("abcdefghij"), 0, 9, "12345678901234567890", 1, S("1j"));
    test(S("abcdefghij"), 0, 9, "12345678901234567890", 10, S("1234567890j"));
    test(S("abcdefghij"), 0, 9, "12345678901234567890", 19,
         S("1234567890123456789j"));
    test(S("abcdefghij"), 0, 9, "12345678901234567890", 20,
         S("12345678901234567890j"));
    test(S("abcdefghij"), 0, 10, "", 0, S(""));
    test(S("abcdefghij"), 0, 10, "12345", 0, S(""));
    test(S("abcdefghij"), 0, 10, "12345", 1, S("1"));
    test(S("abcdefghij"), 0, 10, "12345", 2, S("12"));
    test(S("abcdefghij"), 0, 10, "12345", 4, S("1234"));
    test(S("abcdefghij"), 0, 10, "12345", 5, S("12345"));
    test(S("abcdefghij"), 0, 10, "1234567890", 0, S(""));
    test(S("abcdefghij"), 0, 10, "1234567890", 1, S("1"));
    test(S("abcdefghij"), 0, 10, "1234567890", 5, S("12345"));
    test(S("abcdefghij"), 0, 10, "1234567890", 9, S("123456789"));
    test(S("abcdefghij"), 0, 10, "1234567890", 10, S("1234567890"));
    test(S("abcdefghij"), 0, 10, "12345678901234567890", 0, S(""));
    test(S("abcdefghij"), 0, 10, "12345678901234567890", 1, S("1"));
    test(S("abcdefghij"), 0, 10, "12345678901234567890", 10, S("1234567890"));
    test(S("abcdefghij"), 0, 10, "12345678901234567890", 19,
         S("1234567890123456789"));
    test(S("abcdefghij"), 0, 10, "12345678901234567890", 20,
         S("12345678901234567890"));
    test(S("abcdefghij"), 0, 11, "", 0, S(""));
    test(S("abcdefghij"), 0, 11, "12345", 0, S(""));
    test(S("abcdefghij"), 0, 11, "12345", 1, S("1"));
    test(S("abcdefghij"), 0, 11, "12345", 2, S("12"));
}

template <class S>
void test5() {
    test(S("abcdefghij"), 0, 11, "12345", 4, S("1234"));
    test(S("abcdefghij"), 0, 11, "12345", 5, S("12345"));
    test(S("abcdefghij"), 0, 11, "1234567890", 0, S(""));
    test(S("abcdefghij"), 0, 11, "1234567890", 1, S("1"));
    test(S("abcdefghij"), 0, 11, "1234567890", 5, S("12345"));
    test(S("abcdefghij"), 0, 11, "1234567890", 9, S("123456789"));
    test(S("abcdefghij"), 0, 11, "1234567890", 10, S("1234567890"));
    test(S("abcdefghij"), 0, 11, "12345678901234567890", 0, S(""));
    test(S("abcdefghij"), 0, 11, "12345678901234567890", 1, S("1"));
    test(S("abcdefghij"), 0, 11, "12345678901234567890", 10, S("1234567890"));
    test(S("abcdefghij"), 0, 11, "12345678901234567890", 19,
         S("1234567890123456789"));
    test(S("abcdefghij"), 0, 11, "12345678901234567890", 20,
         S("12345678901234567890"));
    test(S("abcdefghij"), 1, 0, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345", 1, S("a1bcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345", 2, S("a12bcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345", 4, S("a1234bcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345", 5, S("a12345bcdefghij"));
    test(S("abcdefghij"), 1, 0, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 1, 0, "1234567890", 1, S("a1bcdefghij"));
    test(S("abcdefghij"), 1, 0, "1234567890", 5, S("a12345bcdefghij"));
    test(S("abcdefghij"), 1, 0, "1234567890", 9, S("a123456789bcdefghij"));
    test(S("abcdefghij"), 1, 0, "1234567890", 10, S("a1234567890bcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345678901234567890", 1, S("a1bcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345678901234567890", 10,
         S("a1234567890bcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345678901234567890", 19,
         S("a1234567890123456789bcdefghij"));
    test(S("abcdefghij"), 1, 0, "12345678901234567890", 20,
         S("a12345678901234567890bcdefghij"));
    test(S("abcdefghij"), 1, 1, "", 0, S("acdefghij"));
    test(S("abcdefghij"), 1, 1, "12345", 0, S("acdefghij"));
    test(S("abcdefghij"), 1, 1, "12345", 1, S("a1cdefghij"));
    test(S("abcdefghij"), 1, 1, "12345", 2, S("a12cdefghij"));
    test(S("abcdefghij"), 1, 1, "12345", 4, S("a1234cdefghij"));
    test(S("abcdefghij"), 1, 1, "12345", 5, S("a12345cdefghij"));
    test(S("abcdefghij"), 1, 1, "1234567890", 0, S("acdefghij"));
    test(S("abcdefghij"), 1, 1, "1234567890", 1, S("a1cdefghij"));
    test(S("abcdefghij"), 1, 1, "1234567890", 5, S("a12345cdefghij"));
    test(S("abcdefghij"), 1, 1, "1234567890", 9, S("a123456789cdefghij"));
    test(S("abcdefghij"), 1, 1, "1234567890", 10, S("a1234567890cdefghij"));
    test(S("abcdefghij"), 1, 1, "12345678901234567890", 0, S("acdefghij"));
    test(S("abcdefghij"), 1, 1, "12345678901234567890", 1, S("a1cdefghij"));
    test(S("abcdefghij"), 1, 1, "12345678901234567890", 10,
         S("a1234567890cdefghij"));
    test(S("abcdefghij"), 1, 1, "12345678901234567890", 19,
         S("a1234567890123456789cdefghij"));
    test(S("abcdefghij"), 1, 1, "12345678901234567890", 20,
         S("a12345678901234567890cdefghij"));
    test(S("abcdefghij"), 1, 4, "", 0, S("afghij"));
    test(S("abcdefghij"), 1, 4, "12345", 0, S("afghij"));
    test(S("abcdefghij"), 1, 4, "12345", 1, S("a1fghij"));
    test(S("abcdefghij"), 1, 4, "12345", 2, S("a12fghij"));
    test(S("abcdefghij"), 1, 4, "12345", 4, S("a1234fghij"));
    test(S("abcdefghij"), 1, 4, "12345", 5, S("a12345fghij"));
    test(S("abcdefghij"), 1, 4, "1234567890", 0, S("afghij"));
    test(S("abcdefghij"), 1, 4, "1234567890", 1, S("a1fghij"));
    test(S("abcdefghij"), 1, 4, "1234567890", 5, S("a12345fghij"));
    test(S("abcdefghij"), 1, 4, "1234567890", 9, S("a123456789fghij"));
    test(S("abcdefghij"), 1, 4, "1234567890", 10, S("a1234567890fghij"));
    test(S("abcdefghij"), 1, 4, "12345678901234567890", 0, S("afghij"));
    test(S("abcdefghij"), 1, 4, "12345678901234567890", 1, S("a1fghij"));
    test(S("abcdefghij"), 1, 4, "12345678901234567890", 10,
         S("a1234567890fghij"));
    test(S("abcdefghij"), 1, 4, "12345678901234567890", 19,
         S("a1234567890123456789fghij"));
    test(S("abcdefghij"), 1, 4, "12345678901234567890", 20,
         S("a12345678901234567890fghij"));
    test(S("abcdefghij"), 1, 8, "", 0, S("aj"));
    test(S("abcdefghij"), 1, 8, "12345", 0, S("aj"));
    test(S("abcdefghij"), 1, 8, "12345", 1, S("a1j"));
    test(S("abcdefghij"), 1, 8, "12345", 2, S("a12j"));
    test(S("abcdefghij"), 1, 8, "12345", 4, S("a1234j"));
    test(S("abcdefghij"), 1, 8, "12345", 5, S("a12345j"));
    test(S("abcdefghij"), 1, 8, "1234567890", 0, S("aj"));
    test(S("abcdefghij"), 1, 8, "1234567890", 1, S("a1j"));
    test(S("abcdefghij"), 1, 8, "1234567890", 5, S("a12345j"));
    test(S("abcdefghij"), 1, 8, "1234567890", 9, S("a123456789j"));
    test(S("abcdefghij"), 1, 8, "1234567890", 10, S("a1234567890j"));
    test(S("abcdefghij"), 1, 8, "12345678901234567890", 0, S("aj"));
    test(S("abcdefghij"), 1, 8, "12345678901234567890", 1, S("a1j"));
    test(S("abcdefghij"), 1, 8, "12345678901234567890", 10, S("a1234567890j"));
    test(S("abcdefghij"), 1, 8, "12345678901234567890", 19,
         S("a1234567890123456789j"));
    test(S("abcdefghij"), 1, 8, "12345678901234567890", 20,
         S("a12345678901234567890j"));
    test(S("abcdefghij"), 1, 9, "", 0, S("a"));
    test(S("abcdefghij"), 1, 9, "12345", 0, S("a"));
    test(S("abcdefghij"), 1, 9, "12345", 1, S("a1"));
    test(S("abcdefghij"), 1, 9, "12345", 2, S("a12"));
    test(S("abcdefghij"), 1, 9, "12345", 4, S("a1234"));
    test(S("abcdefghij"), 1, 9, "12345", 5, S("a12345"));
    test(S("abcdefghij"), 1, 9, "1234567890", 0, S("a"));
    test(S("abcdefghij"), 1, 9, "1234567890", 1, S("a1"));
    test(S("abcdefghij"), 1, 9, "1234567890", 5, S("a12345"));
    test(S("abcdefghij"), 1, 9, "1234567890", 9, S("a123456789"));
    test(S("abcdefghij"), 1, 9, "1234567890", 10, S("a1234567890"));
    test(S("abcdefghij"), 1, 9, "12345678901234567890", 0, S("a"));
    test(S("abcdefghij"), 1, 9, "12345678901234567890", 1, S("a1"));
    test(S("abcdefghij"), 1, 9, "12345678901234567890", 10, S("a1234567890"));
    test(S("abcdefghij"), 1, 9, "12345678901234567890", 19,
         S("a1234567890123456789"));
    test(S("abcdefghij"), 1, 9, "12345678901234567890", 20,
         S("a12345678901234567890"));
    test(S("abcdefghij"), 1, 10, "", 0, S("a"));
    test(S("abcdefghij"), 1, 10, "12345", 0, S("a"));
    test(S("abcdefghij"), 1, 10, "12345", 1, S("a1"));
    test(S("abcdefghij"), 1, 10, "12345", 2, S("a12"));
    test(S("abcdefghij"), 1, 10, "12345", 4, S("a1234"));
    test(S("abcdefghij"), 1, 10, "12345", 5, S("a12345"));
    test(S("abcdefghij"), 1, 10, "1234567890", 0, S("a"));
    test(S("abcdefghij"), 1, 10, "1234567890", 1, S("a1"));
}

template <class S>
void test6() {
    test(S("abcdefghij"), 1, 10, "1234567890", 5, S("a12345"));
    test(S("abcdefghij"), 1, 10, "1234567890", 9, S("a123456789"));
    test(S("abcdefghij"), 1, 10, "1234567890", 10, S("a1234567890"));
    test(S("abcdefghij"), 1, 10, "12345678901234567890", 0, S("a"));
    test(S("abcdefghij"), 1, 10, "12345678901234567890", 1, S("a1"));
    test(S("abcdefghij"), 1, 10, "12345678901234567890", 10, S("a1234567890"));
    test(S("abcdefghij"), 1, 10, "12345678901234567890", 19,
         S("a1234567890123456789"));
    test(S("abcdefghij"), 1, 10, "12345678901234567890", 20,
         S("a12345678901234567890"));
    test(S("abcdefghij"), 5, 0, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 5, 0, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 5, 0, "12345", 1, S("abcde1fghij"));
    test(S("abcdefghij"), 5, 0, "12345", 2, S("abcde12fghij"));
    test(S("abcdefghij"), 5, 0, "12345", 4, S("abcde1234fghij"));
    test(S("abcdefghij"), 5, 0, "12345", 5, S("abcde12345fghij"));
    test(S("abcdefghij"), 5, 0, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 5, 0, "1234567890", 1, S("abcde1fghij"));
    test(S("abcdefghij"), 5, 0, "1234567890", 5, S("abcde12345fghij"));
    test(S("abcdefghij"), 5, 0, "1234567890", 9, S("abcde123456789fghij"));
    test(S("abcdefghij"), 5, 0, "1234567890", 10, S("abcde1234567890fghij"));
    test(S("abcdefghij"), 5, 0, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 5, 0, "12345678901234567890", 1, S("abcde1fghij"));
    test(S("abcdefghij"), 5, 0, "12345678901234567890", 10,
         S("abcde1234567890fghij"));
    test(S("abcdefghij"), 5, 0, "12345678901234567890", 19,
         S("abcde1234567890123456789fghij"));
    test(S("abcdefghij"), 5, 0, "12345678901234567890", 20,
         S("abcde12345678901234567890fghij"));
    test(S("abcdefghij"), 5, 1, "", 0, S("abcdeghij"));
    test(S("abcdefghij"), 5, 1, "12345", 0, S("abcdeghij"));
    test(S("abcdefghij"), 5, 1, "12345", 1, S("abcde1ghij"));
    test(S("abcdefghij"), 5, 1, "12345", 2, S("abcde12ghij"));
    test(S("abcdefghij"), 5, 1, "12345", 4, S("abcde1234ghij"));
    test(S("abcdefghij"), 5, 1, "12345", 5, S("abcde12345ghij"));
    test(S("abcdefghij"), 5, 1, "1234567890", 0, S("abcdeghij"));
    test(S("abcdefghij"), 5, 1, "1234567890", 1, S("abcde1ghij"));
    test(S("abcdefghij"), 5, 1, "1234567890", 5, S("abcde12345ghij"));
    test(S("abcdefghij"), 5, 1, "1234567890", 9, S("abcde123456789ghij"));
    test(S("abcdefghij"), 5, 1, "1234567890", 10, S("abcde1234567890ghij"));
    test(S("abcdefghij"), 5, 1, "12345678901234567890", 0, S("abcdeghij"));
    test(S("abcdefghij"), 5, 1, "12345678901234567890", 1, S("abcde1ghij"));
    test(S("abcdefghij"), 5, 1, "12345678901234567890", 10,
         S("abcde1234567890ghij"));
    test(S("abcdefghij"), 5, 1, "12345678901234567890", 19,
         S("abcde1234567890123456789ghij"));
    test(S("abcdefghij"), 5, 1, "12345678901234567890", 20,
         S("abcde12345678901234567890ghij"));
    test(S("abcdefghij"), 5, 2, "", 0, S("abcdehij"));
    test(S("abcdefghij"), 5, 2, "12345", 0, S("abcdehij"));
    test(S("abcdefghij"), 5, 2, "12345", 1, S("abcde1hij"));
    test(S("abcdefghij"), 5, 2, "12345", 2, S("abcde12hij"));
    test(S("abcdefghij"), 5, 2, "12345", 4, S("abcde1234hij"));
    test(S("abcdefghij"), 5, 2, "12345", 5, S("abcde12345hij"));
    test(S("abcdefghij"), 5, 2, "1234567890", 0, S("abcdehij"));
    test(S("abcdefghij"), 5, 2, "1234567890", 1, S("abcde1hij"));
    test(S("abcdefghij"), 5, 2, "1234567890", 5, S("abcde12345hij"));
    test(S("abcdefghij"), 5, 2, "1234567890", 9, S("abcde123456789hij"));
    test(S("abcdefghij"), 5, 2, "1234567890", 10, S("abcde1234567890hij"));
    test(S("abcdefghij"), 5, 2, "12345678901234567890", 0, S("abcdehij"));
    test(S("abcdefghij"), 5, 2, "12345678901234567890", 1, S("abcde1hij"));
    test(S("abcdefghij"), 5, 2, "12345678901234567890", 10,
         S("abcde1234567890hij"));
    test(S("abcdefghij"), 5, 2, "12345678901234567890", 19,
         S("abcde1234567890123456789hij"));
    test(S("abcdefghij"), 5, 2, "12345678901234567890", 20,
         S("abcde12345678901234567890hij"));
    test(S("abcdefghij"), 5, 4, "", 0, S("abcdej"));
    test(S("abcdefghij"), 5, 4, "12345", 0, S("abcdej"));
    test(S("abcdefghij"), 5, 4, "12345", 1, S("abcde1j"));
    test(S("abcdefghij"), 5, 4, "12345", 2, S("abcde12j"));
    test(S("abcdefghij"), 5, 4, "12345", 4, S("abcde1234j"));
    test(S("abcdefghij"), 5, 4, "12345", 5, S("abcde12345j"));
    test(S("abcdefghij"), 5, 4, "1234567890", 0, S("abcdej"));
    test(S("abcdefghij"), 5, 4, "1234567890", 1, S("abcde1j"));
    test(S("abcdefghij"), 5, 4, "1234567890", 5, S("abcde12345j"));
    test(S("abcdefghij"), 5, 4, "1234567890", 9, S("abcde123456789j"));
    test(S("abcdefghij"), 5, 4, "1234567890", 10, S("abcde1234567890j"));
    test(S("abcdefghij"), 5, 4, "12345678901234567890", 0, S("abcdej"));
    test(S("abcdefghij"), 5, 4, "12345678901234567890", 1, S("abcde1j"));
    test(S("abcdefghij"), 5, 4, "12345678901234567890", 10,
         S("abcde1234567890j"));
    test(S("abcdefghij"), 5, 4, "12345678901234567890", 19,
         S("abcde1234567890123456789j"));
    test(S("abcdefghij"), 5, 4, "12345678901234567890", 20,
         S("abcde12345678901234567890j"));
    test(S("abcdefghij"), 5, 5, "", 0, S("abcde"));
    test(S("abcdefghij"), 5, 5, "12345", 0, S("abcde"));
    test(S("abcdefghij"), 5, 5, "12345", 1, S("abcde1"));
    test(S("abcdefghij"), 5, 5, "12345", 2, S("abcde12"));
    test(S("abcdefghij"), 5, 5, "12345", 4, S("abcde1234"));
    test(S("abcdefghij"), 5, 5, "12345", 5, S("abcde12345"));
    test(S("abcdefghij"), 5, 5, "1234567890", 0, S("abcde"));
    test(S("abcdefghij"), 5, 5, "1234567890", 1, S("abcde1"));
    test(S("abcdefghij"), 5, 5, "1234567890", 5, S("abcde12345"));
    test(S("abcdefghij"), 5, 5, "1234567890", 9, S("abcde123456789"));
    test(S("abcdefghij"), 5, 5, "1234567890", 10, S("abcde1234567890"));
    test(S("abcdefghij"), 5, 5, "12345678901234567890", 0, S("abcde"));
    test(S("abcdefghij"), 5, 5, "12345678901234567890", 1, S("abcde1"));
    test(S("abcdefghij"), 5, 5, "12345678901234567890", 10,
         S("abcde1234567890"));
    test(S("abcdefghij"), 5, 5, "12345678901234567890", 19,
         S("abcde1234567890123456789"));
    test(S("abcdefghij"), 5, 5, "12345678901234567890", 20,
         S("abcde12345678901234567890"));
    test(S("abcdefghij"), 5, 6, "", 0, S("abcde"));
    test(S("abcdefghij"), 5, 6, "12345", 0, S("abcde"));
    test(S("abcdefghij"), 5, 6, "12345", 1, S("abcde1"));
    test(S("abcdefghij"), 5, 6, "12345", 2, S("abcde12"));
    test(S("abcdefghij"), 5, 6, "12345", 4, S("abcde1234"));
    test(S("abcdefghij"), 5, 6, "12345", 5, S("abcde12345"));
    test(S("abcdefghij"), 5, 6, "1234567890", 0, S("abcde"));
    test(S("abcdefghij"), 5, 6, "1234567890", 1, S("abcde1"));
    test(S("abcdefghij"), 5, 6, "1234567890", 5, S("abcde12345"));
    test(S("abcdefghij"), 5, 6, "1234567890", 9, S("abcde123456789"));
    test(S("abcdefghij"), 5, 6, "1234567890", 10, S("abcde1234567890"));
    test(S("abcdefghij"), 5, 6, "12345678901234567890", 0, S("abcde"));
}

template <class S>
void test7() {
    test(S("abcdefghij"), 5, 6, "12345678901234567890", 1, S("abcde1"));
    test(S("abcdefghij"), 5, 6, "12345678901234567890", 10,
         S("abcde1234567890"));
    test(S("abcdefghij"), 5, 6, "12345678901234567890", 19,
         S("abcde1234567890123456789"));
    test(S("abcdefghij"), 5, 6, "12345678901234567890", 20,
         S("abcde12345678901234567890"));
    test(S("abcdefghij"), 9, 0, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 9, 0, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 9, 0, "12345", 1, S("abcdefghi1j"));
    test(S("abcdefghij"), 9, 0, "12345", 2, S("abcdefghi12j"));
    test(S("abcdefghij"), 9, 0, "12345", 4, S("abcdefghi1234j"));
    test(S("abcdefghij"), 9, 0, "12345", 5, S("abcdefghi12345j"));
    test(S("abcdefghij"), 9, 0, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 9, 0, "1234567890", 1, S("abcdefghi1j"));
    test(S("abcdefghij"), 9, 0, "1234567890", 5, S("abcdefghi12345j"));
    test(S("abcdefghij"), 9, 0, "1234567890", 9, S("abcdefghi123456789j"));
    test(S("abcdefghij"), 9, 0, "1234567890", 10, S("abcdefghi1234567890j"));
    test(S("abcdefghij"), 9, 0, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 9, 0, "12345678901234567890", 1, S("abcdefghi1j"));
    test(S("abcdefghij"), 9, 0, "12345678901234567890", 10,
         S("abcdefghi1234567890j"));
    test(S("abcdefghij"), 9, 0, "12345678901234567890", 19,
         S("abcdefghi1234567890123456789j"));
    test(S("abcdefghij"), 9, 0, "12345678901234567890", 20,
         S("abcdefghi12345678901234567890j"));
    test(S("abcdefghij"), 9, 1, "", 0, S("abcdefghi"));
    test(S("abcdefghij"), 9, 1, "12345", 0, S("abcdefghi"));
    test(S("abcdefghij"), 9, 1, "12345", 1, S("abcdefghi1"));
    test(S("abcdefghij"), 9, 1, "12345", 2, S("abcdefghi12"));
    test(S("abcdefghij"), 9, 1, "12345", 4, S("abcdefghi1234"));
    test(S("abcdefghij"), 9, 1, "12345", 5, S("abcdefghi12345"));
    test(S("abcdefghij"), 9, 1, "1234567890", 0, S("abcdefghi"));
    test(S("abcdefghij"), 9, 1, "1234567890", 1, S("abcdefghi1"));
    test(S("abcdefghij"), 9, 1, "1234567890", 5, S("abcdefghi12345"));
    test(S("abcdefghij"), 9, 1, "1234567890", 9, S("abcdefghi123456789"));
    test(S("abcdefghij"), 9, 1, "1234567890", 10, S("abcdefghi1234567890"));
    test(S("abcdefghij"), 9, 1, "12345678901234567890", 0, S("abcdefghi"));
    test(S("abcdefghij"), 9, 1, "12345678901234567890", 1, S("abcdefghi1"));
    test(S("abcdefghij"), 9, 1, "12345678901234567890", 10,
         S("abcdefghi1234567890"));
    test(S("abcdefghij"), 9, 1, "12345678901234567890", 19,
         S("abcdefghi1234567890123456789"));
    test(S("abcdefghij"), 9, 1, "12345678901234567890", 20,
         S("abcdefghi12345678901234567890"));
    test(S("abcdefghij"), 9, 2, "", 0, S("abcdefghi"));
    test(S("abcdefghij"), 9, 2, "12345", 0, S("abcdefghi"));
    test(S("abcdefghij"), 9, 2, "12345", 1, S("abcdefghi1"));
    test(S("abcdefghij"), 9, 2, "12345", 2, S("abcdefghi12"));
    test(S("abcdefghij"), 9, 2, "12345", 4, S("abcdefghi1234"));
    test(S("abcdefghij"), 9, 2, "12345", 5, S("abcdefghi12345"));
    test(S("abcdefghij"), 9, 2, "1234567890", 0, S("abcdefghi"));
    test(S("abcdefghij"), 9, 2, "1234567890", 1, S("abcdefghi1"));
    test(S("abcdefghij"), 9, 2, "1234567890", 5, S("abcdefghi12345"));
    test(S("abcdefghij"), 9, 2, "1234567890", 9, S("abcdefghi123456789"));
    test(S("abcdefghij"), 9, 2, "1234567890", 10, S("abcdefghi1234567890"));
    test(S("abcdefghij"), 9, 2, "12345678901234567890", 0, S("abcdefghi"));
    test(S("abcdefghij"), 9, 2, "12345678901234567890", 1, S("abcdefghi1"));
    test(S("abcdefghij"), 9, 2, "12345678901234567890", 10,
         S("abcdefghi1234567890"));
    test(S("abcdefghij"), 9, 2, "12345678901234567890", 19,
         S("abcdefghi1234567890123456789"));
    test(S("abcdefghij"), 9, 2, "12345678901234567890", 20,
         S("abcdefghi12345678901234567890"));
    test(S("abcdefghij"), 10, 0, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, 0, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, 0, "12345", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, 0, "12345", 2, S("abcdefghij12"));
    test(S("abcdefghij"), 10, 0, "12345", 4, S("abcdefghij1234"));
    test(S("abcdefghij"), 10, 0, "12345", 5, S("abcdefghij12345"));
    test(S("abcdefghij"), 10, 0, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, 0, "1234567890", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, 0, "1234567890", 5, S("abcdefghij12345"));
    test(S("abcdefghij"), 10, 0, "1234567890", 9, S("abcdefghij123456789"));
    test(S("abcdefghij"), 10, 0, "1234567890", 10, S("abcdefghij1234567890"));
    test(S("abcdefghij"), 10, 0, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, 0, "12345678901234567890", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, 0, "12345678901234567890", 10,
         S("abcdefghij1234567890"));
    test(S("abcdefghij"), 10, 0, "12345678901234567890", 19,
         S("abcdefghij1234567890123456789"));
    test(S("abcdefghij"), 10, 0, "12345678901234567890", 20,
         S("abcdefghij12345678901234567890"));
    test(S("abcdefghij"), 10, 1, "", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, 1, "12345", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, 1, "12345", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, 1, "12345", 2, S("abcdefghij12"));
    test(S("abcdefghij"), 10, 1, "12345", 4, S("abcdefghij1234"));
    test(S("abcdefghij"), 10, 1, "12345", 5, S("abcdefghij12345"));
    test(S("abcdefghij"), 10, 1, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, 1, "1234567890", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, 1, "1234567890", 5, S("abcdefghij12345"));
    test(S("abcdefghij"), 10, 1, "1234567890", 9, S("abcdefghij123456789"));
    test(S("abcdefghij"), 10, 1, "1234567890", 10, S("abcdefghij1234567890"));
    test(S("abcdefghij"), 10, 1, "12345678901234567890", 0, S("abcdefghij"));
    test(S("abcdefghij"), 10, 1, "12345678901234567890", 1, S("abcdefghij1"));
    test(S("abcdefghij"), 10, 1, "12345678901234567890", 10,
         S("abcdefghij1234567890"));
    test(S("abcdefghij"), 10, 1, "12345678901234567890", 19,
         S("abcdefghij1234567890123456789"));
    test(S("abcdefghij"), 10, 1, "12345678901234567890", 20,
         S("abcdefghij12345678901234567890"));
    test(S("abcdefghij"), 11, 0, "", 0, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345", 0, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345", 1, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345", 2, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345", 4, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345", 5, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "1234567890", 0, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "1234567890", 1, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "1234567890", 5, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "1234567890", 9, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "1234567890", 10, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345678901234567890", 0, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345678901234567890", 1, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345678901234567890", 10, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345678901234567890", 19, S("can't happen"));
    test(S("abcdefghij"), 11, 0, "12345678901234567890", 20, S("can't happen"));
}

template <class S>
void test8() {
    test(S("abcdefghijklmnopqrst"), 0, 0, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345", 1,
         S("1abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345", 2,
         S("12abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345", 4,
         S("1234abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345", 5,
         S("12345abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "1234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "1234567890", 1,
         S("1abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "1234567890", 5,
         S("12345abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "1234567890", 9,
         S("123456789abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "1234567890", 10,
         S("1234567890abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345678901234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345678901234567890", 1,
         S("1abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345678901234567890", 10,
         S("1234567890abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345678901234567890", 19,
         S("1234567890123456789abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 0, "12345678901234567890", 20,
         S("12345678901234567890abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "", 0, S("bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345", 0, S("bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345", 1,
         S("1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345", 2,
         S("12bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345", 4,
         S("1234bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345", 5,
         S("12345bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "1234567890", 0,
         S("bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "1234567890", 1,
         S("1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "1234567890", 5,
         S("12345bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "1234567890", 9,
         S("123456789bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "1234567890", 10,
         S("1234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345678901234567890", 0,
         S("bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345678901234567890", 1,
         S("1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345678901234567890", 10,
         S("1234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345678901234567890", 19,
         S("1234567890123456789bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 1, "12345678901234567890", 20,
         S("12345678901234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "", 0, S("klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345", 0, S("klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345", 1, S("1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345", 2, S("12klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345", 4, S("1234klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345", 5, S("12345klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "1234567890", 0, S("klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "1234567890", 1, S("1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "1234567890", 5,
         S("12345klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "1234567890", 9,
         S("123456789klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "1234567890", 10,
         S("1234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345678901234567890", 0,
         S("klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345678901234567890", 1,
         S("1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345678901234567890", 10,
         S("1234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345678901234567890", 19,
         S("1234567890123456789klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 10, "12345678901234567890", 20,
         S("12345678901234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "", 0, S("t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345", 0, S("t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345", 1, S("1t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345", 2, S("12t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345", 4, S("1234t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345", 5, S("12345t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "1234567890", 0, S("t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "1234567890", 1, S("1t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "1234567890", 5, S("12345t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "1234567890", 9, S("123456789t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "1234567890", 10, S("1234567890t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345678901234567890", 0, S("t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345678901234567890", 1, S("1t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345678901234567890", 10,
         S("1234567890t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345678901234567890", 19,
         S("1234567890123456789t"));
    test(S("abcdefghijklmnopqrst"), 0, 19, "12345678901234567890", 20,
         S("12345678901234567890t"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "", 0, S(""));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345", 0, S(""));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345", 1, S("1"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345", 2, S("12"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345", 4, S("1234"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345", 5, S("12345"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "1234567890", 0, S(""));
    test(S("abcdefghijklmnopqrst"), 0, 20, "1234567890", 1, S("1"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "1234567890", 5, S("12345"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "1234567890", 9, S("123456789"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "1234567890", 10, S("1234567890"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345678901234567890", 0, S(""));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345678901234567890", 1, S("1"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345678901234567890", 10,
         S("1234567890"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345678901234567890", 19,
         S("1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 0, 20, "12345678901234567890", 20,
         S("12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "", 0, S(""));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345", 0, S(""));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345", 1, S("1"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345", 2, S("12"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345", 4, S("1234"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345", 5, S("12345"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "1234567890", 0, S(""));
    test(S("abcdefghijklmnopqrst"), 0, 21, "1234567890", 1, S("1"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "1234567890", 5, S("12345"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "1234567890", 9, S("123456789"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "1234567890", 10, S("1234567890"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345678901234567890", 0, S(""));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345678901234567890", 1, S("1"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345678901234567890", 10,
         S("1234567890"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345678901234567890", 19,
         S("1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 0, 21, "12345678901234567890", 20,
         S("12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345", 1,
         S("a1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345", 2,
         S("a12bcdefghijklmnopqrst"));
}

template <class S>
void test9() {
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345", 4,
         S("a1234bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345", 5,
         S("a12345bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "1234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "1234567890", 1,
         S("a1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "1234567890", 5,
         S("a12345bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "1234567890", 9,
         S("a123456789bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "1234567890", 10,
         S("a1234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345678901234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345678901234567890", 1,
         S("a1bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345678901234567890", 10,
         S("a1234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345678901234567890", 19,
         S("a1234567890123456789bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 0, "12345678901234567890", 20,
         S("a12345678901234567890bcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "", 0, S("acdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345", 0, S("acdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345", 1,
         S("a1cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345", 2,
         S("a12cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345", 4,
         S("a1234cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345", 5,
         S("a12345cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "1234567890", 0,
         S("acdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "1234567890", 1,
         S("a1cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "1234567890", 5,
         S("a12345cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "1234567890", 9,
         S("a123456789cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "1234567890", 10,
         S("a1234567890cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345678901234567890", 0,
         S("acdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345678901234567890", 1,
         S("a1cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345678901234567890", 10,
         S("a1234567890cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345678901234567890", 19,
         S("a1234567890123456789cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 1, "12345678901234567890", 20,
         S("a12345678901234567890cdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "", 0, S("aklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345", 0, S("aklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345", 1, S("a1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345", 2, S("a12klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345", 4, S("a1234klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345", 5, S("a12345klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "1234567890", 0, S("aklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "1234567890", 1, S("a1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "1234567890", 5,
         S("a12345klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "1234567890", 9,
         S("a123456789klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "1234567890", 10,
         S("a1234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345678901234567890", 0,
         S("aklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345678901234567890", 1,
         S("a1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345678901234567890", 10,
         S("a1234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345678901234567890", 19,
         S("a1234567890123456789klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 9, "12345678901234567890", 20,
         S("a12345678901234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "", 0, S("at"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345", 0, S("at"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345", 1, S("a1t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345", 2, S("a12t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345", 4, S("a1234t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345", 5, S("a12345t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "1234567890", 0, S("at"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "1234567890", 1, S("a1t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "1234567890", 5, S("a12345t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "1234567890", 9, S("a123456789t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "1234567890", 10, S("a1234567890t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345678901234567890", 0, S("at"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345678901234567890", 1, S("a1t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345678901234567890", 10,
         S("a1234567890t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345678901234567890", 19,
         S("a1234567890123456789t"));
    test(S("abcdefghijklmnopqrst"), 1, 18, "12345678901234567890", 20,
         S("a12345678901234567890t"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "", 0, S("a"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345", 0, S("a"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345", 1, S("a1"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345", 2, S("a12"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345", 4, S("a1234"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345", 5, S("a12345"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "1234567890", 0, S("a"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "1234567890", 1, S("a1"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "1234567890", 5, S("a12345"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "1234567890", 9, S("a123456789"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "1234567890", 10, S("a1234567890"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345678901234567890", 0, S("a"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345678901234567890", 1, S("a1"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345678901234567890", 10,
         S("a1234567890"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345678901234567890", 19,
         S("a1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 1, 19, "12345678901234567890", 20,
         S("a12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "", 0, S("a"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345", 0, S("a"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345", 1, S("a1"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345", 2, S("a12"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345", 4, S("a1234"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345", 5, S("a12345"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "1234567890", 0, S("a"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "1234567890", 1, S("a1"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "1234567890", 5, S("a12345"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "1234567890", 9, S("a123456789"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "1234567890", 10, S("a1234567890"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345678901234567890", 0, S("a"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345678901234567890", 1, S("a1"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345678901234567890", 10,
         S("a1234567890"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345678901234567890", 19,
         S("a1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 1, 20, "12345678901234567890", 20,
         S("a12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345", 1,
         S("abcdefghij1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345", 2,
         S("abcdefghij12klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345", 4,
         S("abcdefghij1234klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345", 5,
         S("abcdefghij12345klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "1234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "1234567890", 1,
         S("abcdefghij1klmnopqrst"));
}

template <class S>
void test10() {
    test(S("abcdefghijklmnopqrst"), 10, 0, "1234567890", 5,
         S("abcdefghij12345klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "1234567890", 9,
         S("abcdefghij123456789klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "1234567890", 10,
         S("abcdefghij1234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345678901234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345678901234567890", 1,
         S("abcdefghij1klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345678901234567890", 10,
         S("abcdefghij1234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345678901234567890", 19,
         S("abcdefghij1234567890123456789klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 0, "12345678901234567890", 20,
         S("abcdefghij12345678901234567890klmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "", 0, S("abcdefghijlmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345", 0,
         S("abcdefghijlmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345", 1,
         S("abcdefghij1lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345", 2,
         S("abcdefghij12lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345", 4,
         S("abcdefghij1234lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345", 5,
         S("abcdefghij12345lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "1234567890", 0,
         S("abcdefghijlmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "1234567890", 1,
         S("abcdefghij1lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "1234567890", 5,
         S("abcdefghij12345lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "1234567890", 9,
         S("abcdefghij123456789lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "1234567890", 10,
         S("abcdefghij1234567890lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345678901234567890", 0,
         S("abcdefghijlmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345678901234567890", 1,
         S("abcdefghij1lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345678901234567890", 10,
         S("abcdefghij1234567890lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345678901234567890", 19,
         S("abcdefghij1234567890123456789lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 1, "12345678901234567890", 20,
         S("abcdefghij12345678901234567890lmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "", 0, S("abcdefghijpqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345", 0, S("abcdefghijpqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345", 1, S("abcdefghij1pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345", 2, S("abcdefghij12pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345", 4,
         S("abcdefghij1234pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345", 5,
         S("abcdefghij12345pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "1234567890", 0,
         S("abcdefghijpqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "1234567890", 1,
         S("abcdefghij1pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "1234567890", 5,
         S("abcdefghij12345pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "1234567890", 9,
         S("abcdefghij123456789pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "1234567890", 10,
         S("abcdefghij1234567890pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345678901234567890", 0,
         S("abcdefghijpqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345678901234567890", 1,
         S("abcdefghij1pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345678901234567890", 10,
         S("abcdefghij1234567890pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345678901234567890", 19,
         S("abcdefghij1234567890123456789pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 5, "12345678901234567890", 20,
         S("abcdefghij12345678901234567890pqrst"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "", 0, S("abcdefghijt"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345", 0, S("abcdefghijt"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345", 1, S("abcdefghij1t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345", 2, S("abcdefghij12t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345", 4, S("abcdefghij1234t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345", 5, S("abcdefghij12345t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "1234567890", 0, S("abcdefghijt"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "1234567890", 1, S("abcdefghij1t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "1234567890", 5,
         S("abcdefghij12345t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "1234567890", 9,
         S("abcdefghij123456789t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "1234567890", 10,
         S("abcdefghij1234567890t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345678901234567890", 0,
         S("abcdefghijt"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345678901234567890", 1,
         S("abcdefghij1t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345678901234567890", 10,
         S("abcdefghij1234567890t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345678901234567890", 19,
         S("abcdefghij1234567890123456789t"));
    test(S("abcdefghijklmnopqrst"), 10, 9, "12345678901234567890", 20,
         S("abcdefghij12345678901234567890t"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "", 0, S("abcdefghij"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345", 0, S("abcdefghij"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345", 1, S("abcdefghij1"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345", 2, S("abcdefghij12"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345", 4, S("abcdefghij1234"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345", 5, S("abcdefghij12345"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "1234567890", 1, S("abcdefghij1"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "1234567890", 5,
         S("abcdefghij12345"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "1234567890", 9,
         S("abcdefghij123456789"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "1234567890", 10,
         S("abcdefghij1234567890"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345678901234567890", 0,
         S("abcdefghij"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345678901234567890", 1,
         S("abcdefghij1"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345678901234567890", 10,
         S("abcdefghij1234567890"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345678901234567890", 19,
         S("abcdefghij1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 10, 10, "12345678901234567890", 20,
         S("abcdefghij12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "", 0, S("abcdefghij"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345", 0, S("abcdefghij"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345", 1, S("abcdefghij1"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345", 2, S("abcdefghij12"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345", 4, S("abcdefghij1234"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345", 5, S("abcdefghij12345"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "1234567890", 0, S("abcdefghij"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "1234567890", 1, S("abcdefghij1"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "1234567890", 5,
         S("abcdefghij12345"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "1234567890", 9,
         S("abcdefghij123456789"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "1234567890", 10,
         S("abcdefghij1234567890"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345678901234567890", 0,
         S("abcdefghij"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345678901234567890", 1,
         S("abcdefghij1"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345678901234567890", 10,
         S("abcdefghij1234567890"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345678901234567890", 19,
         S("abcdefghij1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 10, 11, "12345678901234567890", 20,
         S("abcdefghij12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345", 1,
         S("abcdefghijklmnopqrs1t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345", 2,
         S("abcdefghijklmnopqrs12t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345", 4,
         S("abcdefghijklmnopqrs1234t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345", 5,
         S("abcdefghijklmnopqrs12345t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "1234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "1234567890", 1,
         S("abcdefghijklmnopqrs1t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "1234567890", 5,
         S("abcdefghijklmnopqrs12345t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "1234567890", 9,
         S("abcdefghijklmnopqrs123456789t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "1234567890", 10,
         S("abcdefghijklmnopqrs1234567890t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345678901234567890", 0,
         S("abcdefghijklmnopqrst"));
}

template <class S>
void test11() {
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345678901234567890", 1,
         S("abcdefghijklmnopqrs1t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345678901234567890", 10,
         S("abcdefghijklmnopqrs1234567890t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345678901234567890", 19,
         S("abcdefghijklmnopqrs1234567890123456789t"));
    test(S("abcdefghijklmnopqrst"), 19, 0, "12345678901234567890", 20,
         S("abcdefghijklmnopqrs12345678901234567890t"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "", 0, S("abcdefghijklmnopqrs"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345", 0,
         S("abcdefghijklmnopqrs"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345", 1,
         S("abcdefghijklmnopqrs1"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345", 2,
         S("abcdefghijklmnopqrs12"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345", 4,
         S("abcdefghijklmnopqrs1234"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345", 5,
         S("abcdefghijklmnopqrs12345"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "1234567890", 0,
         S("abcdefghijklmnopqrs"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "1234567890", 1,
         S("abcdefghijklmnopqrs1"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "1234567890", 5,
         S("abcdefghijklmnopqrs12345"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "1234567890", 9,
         S("abcdefghijklmnopqrs123456789"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "1234567890", 10,
         S("abcdefghijklmnopqrs1234567890"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345678901234567890", 0,
         S("abcdefghijklmnopqrs"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345678901234567890", 1,
         S("abcdefghijklmnopqrs1"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345678901234567890", 10,
         S("abcdefghijklmnopqrs1234567890"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345678901234567890", 19,
         S("abcdefghijklmnopqrs1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 19, 1, "12345678901234567890", 20,
         S("abcdefghijklmnopqrs12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "", 0, S("abcdefghijklmnopqrs"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345", 0,
         S("abcdefghijklmnopqrs"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345", 1,
         S("abcdefghijklmnopqrs1"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345", 2,
         S("abcdefghijklmnopqrs12"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345", 4,
         S("abcdefghijklmnopqrs1234"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345", 5,
         S("abcdefghijklmnopqrs12345"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "1234567890", 0,
         S("abcdefghijklmnopqrs"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "1234567890", 1,
         S("abcdefghijklmnopqrs1"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "1234567890", 5,
         S("abcdefghijklmnopqrs12345"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "1234567890", 9,
         S("abcdefghijklmnopqrs123456789"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "1234567890", 10,
         S("abcdefghijklmnopqrs1234567890"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345678901234567890", 0,
         S("abcdefghijklmnopqrs"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345678901234567890", 1,
         S("abcdefghijklmnopqrs1"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345678901234567890", 10,
         S("abcdefghijklmnopqrs1234567890"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345678901234567890", 19,
         S("abcdefghijklmnopqrs1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 19, 2, "12345678901234567890", 20,
         S("abcdefghijklmnopqrs12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345", 1,
         S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345", 2,
         S("abcdefghijklmnopqrst12"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345", 4,
         S("abcdefghijklmnopqrst1234"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345", 5,
         S("abcdefghijklmnopqrst12345"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "1234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "1234567890", 1,
         S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "1234567890", 5,
         S("abcdefghijklmnopqrst12345"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "1234567890", 9,
         S("abcdefghijklmnopqrst123456789"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "1234567890", 10,
         S("abcdefghijklmnopqrst1234567890"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345678901234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345678901234567890", 1,
         S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345678901234567890", 10,
         S("abcdefghijklmnopqrst1234567890"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345678901234567890", 19,
         S("abcdefghijklmnopqrst1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 20, 0, "12345678901234567890", 20,
         S("abcdefghijklmnopqrst12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "", 0, S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345", 1,
         S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345", 2,
         S("abcdefghijklmnopqrst12"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345", 4,
         S("abcdefghijklmnopqrst1234"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345", 5,
         S("abcdefghijklmnopqrst12345"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "1234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "1234567890", 1,
         S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "1234567890", 5,
         S("abcdefghijklmnopqrst12345"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "1234567890", 9,
         S("abcdefghijklmnopqrst123456789"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "1234567890", 10,
         S("abcdefghijklmnopqrst1234567890"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345678901234567890", 0,
         S("abcdefghijklmnopqrst"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345678901234567890", 1,
         S("abcdefghijklmnopqrst1"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345678901234567890", 10,
         S("abcdefghijklmnopqrst1234567890"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345678901234567890", 19,
         S("abcdefghijklmnopqrst1234567890123456789"));
    test(S("abcdefghijklmnopqrst"), 20, 1, "12345678901234567890", 20,
         S("abcdefghijklmnopqrst12345678901234567890"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "", 0, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345", 0, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345", 1, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345", 2, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345", 4, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345", 5, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "1234567890", 0, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "1234567890", 1, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "1234567890", 5, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "1234567890", 9, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "1234567890", 10, S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345678901234567890", 0,
         S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345678901234567890", 1,
         S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345678901234567890", 10,
         S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345678901234567890", 19,
         S("can't happen"));
    test(S("abcdefghijklmnopqrst"), 21, 0, "12345678901234567890", 20,
         S("can't happen"));
}

int main() {
    {
        typedef std::string S;
        test0<S>();
        test1<S>();
        test2<S>();
        test3<S>();
        test4<S>();
        test5<S>();
        test6<S>();
        test7<S>();
        test8<S>();
        test9<S>();
        test10<S>();
        test11<S>();
    }
#if TEST_STD_VER >= 11
    {
        typedef std::basic_string<char, std::char_traits<char>,
                                  min_allocator<char>>
            S;
        test0<S>();
        test1<S>();
        test2<S>();
        test3<S>();
        test4<S>();
        test5<S>();
        test6<S>();
        test7<S>();
        test8<S>();
        test9<S>();
        test10<S>();
        test11<S>();
    }
#endif
}
