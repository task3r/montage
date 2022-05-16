//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <string>

// template <typename T>
//    int compare(size_type pos1, size_type n1, const T& t,
//                size_type pos2, size_type n2=npos) const;
//
//  Mostly we're testing string_view here

#include <cassert>
#include <stdexcept>
#include <string>

#include "min_allocator.h"
#include "test_macros.h"

int sign(int x) {
    if (x == 0) return 0;
    if (x < 0) return -1;
    return 1;
}

template <class S, class SV>
void test(const S& s, typename S::size_type pos1, typename S::size_type n1,
          SV sv, typename S::size_type pos2, typename S::size_type n2, int x) {
    static_assert((!std::is_same<S, SV>::value), "");
    if (pos1 <= s.size() && pos2 <= sv.size())
        assert(sign(s.compare(pos1, n1, sv, pos2, n2)) == sign(x));
#ifndef TEST_HAS_NO_EXCEPTIONS
    else {
        try {
            TEST_IGNORE_NODISCARD s.compare(pos1, n1, sv, pos2, n2);
            assert(false);
        } catch (const std::out_of_range&) {
            assert(pos1 > s.size() || pos2 > sv.size());
        }
    }
#endif
}

template <class S, class SV>
void test_npos(const S& s, typename S::size_type pos1, typename S::size_type n1,
               SV sv, typename S::size_type pos2, int x) {
    static_assert((!std::is_same<S, SV>::value), "");
    if (pos1 <= s.size() && pos2 <= sv.size())
        assert(sign(s.compare(pos1, n1, sv, pos2)) == sign(x));
#ifndef TEST_HAS_NO_EXCEPTIONS
    else {
        try {
            TEST_IGNORE_NODISCARD s.compare(pos1, n1, sv, pos2);
            assert(false);
        } catch (const std::out_of_range&) {
            assert(pos1 > s.size() || pos2 > sv.size());
        }
    }
#endif
}

template <class S, class SV>
void test0() {
    test(S(""), 0, 0, SV(""), 0, 0, 0);
    test(S(""), 0, 0, SV(""), 0, 1, 0);
    test(S(""), 0, 0, SV(""), 1, 0, 0);
    test(S(""), 0, 0, SV("abcde"), 0, 0, 0);
    test(S(""), 0, 0, SV("abcde"), 0, 1, -1);
    test(S(""), 0, 0, SV("abcde"), 0, 2, -2);
    test(S(""), 0, 0, SV("abcde"), 0, 4, -4);
    test(S(""), 0, 0, SV("abcde"), 0, 5, -5);
    test(S(""), 0, 0, SV("abcde"), 0, 6, -5);
    test(S(""), 0, 0, SV("abcde"), 1, 0, 0);
    test(S(""), 0, 0, SV("abcde"), 1, 1, -1);
    test(S(""), 0, 0, SV("abcde"), 1, 2, -2);
    test(S(""), 0, 0, SV("abcde"), 1, 3, -3);
    test(S(""), 0, 0, SV("abcde"), 1, 4, -4);
    test(S(""), 0, 0, SV("abcde"), 1, 5, -4);
    test(S(""), 0, 0, SV("abcde"), 2, 0, 0);
    test(S(""), 0, 0, SV("abcde"), 2, 1, -1);
    test(S(""), 0, 0, SV("abcde"), 2, 2, -2);
    test(S(""), 0, 0, SV("abcde"), 2, 3, -3);
    test(S(""), 0, 0, SV("abcde"), 2, 4, -3);
    test(S(""), 0, 0, SV("abcde"), 4, 0, 0);
    test(S(""), 0, 0, SV("abcde"), 4, 1, -1);
    test(S(""), 0, 0, SV("abcde"), 4, 2, -1);
    test(S(""), 0, 0, SV("abcde"), 5, 0, 0);
    test(S(""), 0, 0, SV("abcde"), 5, 1, 0);
    test(S(""), 0, 0, SV("abcde"), 6, 0, 0);
    test(S(""), 0, 0, SV("abcdefghij"), 0, 0, 0);
    test(S(""), 0, 0, SV("abcdefghij"), 0, 1, -1);
    test(S(""), 0, 0, SV("abcdefghij"), 0, 5, -5);
    test(S(""), 0, 0, SV("abcdefghij"), 0, 9, -9);
    test(S(""), 0, 0, SV("abcdefghij"), 0, 10, -10);
    test(S(""), 0, 0, SV("abcdefghij"), 0, 11, -10);
    test(S(""), 0, 0, SV("abcdefghij"), 1, 0, 0);
    test(S(""), 0, 0, SV("abcdefghij"), 1, 1, -1);
    test(S(""), 0, 0, SV("abcdefghij"), 1, 4, -4);
    test(S(""), 0, 0, SV("abcdefghij"), 1, 8, -8);
    test(S(""), 0, 0, SV("abcdefghij"), 1, 9, -9);
    test(S(""), 0, 0, SV("abcdefghij"), 1, 10, -9);
    test(S(""), 0, 0, SV("abcdefghij"), 5, 0, 0);
    test(S(""), 0, 0, SV("abcdefghij"), 5, 1, -1);
    test(S(""), 0, 0, SV("abcdefghij"), 5, 2, -2);
    test(S(""), 0, 0, SV("abcdefghij"), 5, 4, -4);
    test(S(""), 0, 0, SV("abcdefghij"), 5, 5, -5);
    test(S(""), 0, 0, SV("abcdefghij"), 5, 6, -5);
    test(S(""), 0, 0, SV("abcdefghij"), 9, 0, 0);
    test(S(""), 0, 0, SV("abcdefghij"), 9, 1, -1);
    test(S(""), 0, 0, SV("abcdefghij"), 9, 2, -1);
    test(S(""), 0, 0, SV("abcdefghij"), 10, 0, 0);
    test(S(""), 0, 0, SV("abcdefghij"), 10, 1, 0);
    test(S(""), 0, 0, SV("abcdefghij"), 11, 0, 0);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S(""), 0, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S(""), 0, 1, SV(""), 0, 0, 0);
    test(S(""), 0, 1, SV(""), 0, 1, 0);
    test(S(""), 0, 1, SV(""), 1, 0, 0);
    test(S(""), 0, 1, SV("abcde"), 0, 0, 0);
    test(S(""), 0, 1, SV("abcde"), 0, 1, -1);
    test(S(""), 0, 1, SV("abcde"), 0, 2, -2);
    test(S(""), 0, 1, SV("abcde"), 0, 4, -4);
    test(S(""), 0, 1, SV("abcde"), 0, 5, -5);
    test(S(""), 0, 1, SV("abcde"), 0, 6, -5);
    test(S(""), 0, 1, SV("abcde"), 1, 0, 0);
    test(S(""), 0, 1, SV("abcde"), 1, 1, -1);
    test(S(""), 0, 1, SV("abcde"), 1, 2, -2);
    test(S(""), 0, 1, SV("abcde"), 1, 3, -3);
    test(S(""), 0, 1, SV("abcde"), 1, 4, -4);
    test(S(""), 0, 1, SV("abcde"), 1, 5, -4);
    test(S(""), 0, 1, SV("abcde"), 2, 0, 0);
    test(S(""), 0, 1, SV("abcde"), 2, 1, -1);
    test(S(""), 0, 1, SV("abcde"), 2, 2, -2);
    test(S(""), 0, 1, SV("abcde"), 2, 3, -3);
    test(S(""), 0, 1, SV("abcde"), 2, 4, -3);
    test(S(""), 0, 1, SV("abcde"), 4, 0, 0);
    test(S(""), 0, 1, SV("abcde"), 4, 1, -1);
    test(S(""), 0, 1, SV("abcde"), 4, 2, -1);
    test(S(""), 0, 1, SV("abcde"), 5, 0, 0);
    test(S(""), 0, 1, SV("abcde"), 5, 1, 0);
    test(S(""), 0, 1, SV("abcde"), 6, 0, 0);
}

template <class S, class SV>
void test1() {
    test(S(""), 0, 1, SV("abcdefghij"), 0, 0, 0);
    test(S(""), 0, 1, SV("abcdefghij"), 0, 1, -1);
    test(S(""), 0, 1, SV("abcdefghij"), 0, 5, -5);
    test(S(""), 0, 1, SV("abcdefghij"), 0, 9, -9);
    test(S(""), 0, 1, SV("abcdefghij"), 0, 10, -10);
    test(S(""), 0, 1, SV("abcdefghij"), 0, 11, -10);
    test(S(""), 0, 1, SV("abcdefghij"), 1, 0, 0);
    test(S(""), 0, 1, SV("abcdefghij"), 1, 1, -1);
    test(S(""), 0, 1, SV("abcdefghij"), 1, 4, -4);
    test(S(""), 0, 1, SV("abcdefghij"), 1, 8, -8);
    test(S(""), 0, 1, SV("abcdefghij"), 1, 9, -9);
    test(S(""), 0, 1, SV("abcdefghij"), 1, 10, -9);
    test(S(""), 0, 1, SV("abcdefghij"), 5, 0, 0);
    test(S(""), 0, 1, SV("abcdefghij"), 5, 1, -1);
    test(S(""), 0, 1, SV("abcdefghij"), 5, 2, -2);
    test(S(""), 0, 1, SV("abcdefghij"), 5, 4, -4);
    test(S(""), 0, 1, SV("abcdefghij"), 5, 5, -5);
    test(S(""), 0, 1, SV("abcdefghij"), 5, 6, -5);
    test(S(""), 0, 1, SV("abcdefghij"), 9, 0, 0);
    test(S(""), 0, 1, SV("abcdefghij"), 9, 1, -1);
    test(S(""), 0, 1, SV("abcdefghij"), 9, 2, -1);
    test(S(""), 0, 1, SV("abcdefghij"), 10, 0, 0);
    test(S(""), 0, 1, SV("abcdefghij"), 10, 1, 0);
    test(S(""), 0, 1, SV("abcdefghij"), 11, 0, 0);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S(""), 0, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S(""), 1, 0, SV(""), 0, 0, 0);
    test(S(""), 1, 0, SV(""), 0, 1, 0);
    test(S(""), 1, 0, SV(""), 1, 0, 0);
    test(S(""), 1, 0, SV("abcde"), 0, 0, 0);
    test(S(""), 1, 0, SV("abcde"), 0, 1, 0);
    test(S(""), 1, 0, SV("abcde"), 0, 2, 0);
    test(S(""), 1, 0, SV("abcde"), 0, 4, 0);
    test(S(""), 1, 0, SV("abcde"), 0, 5, 0);
    test(S(""), 1, 0, SV("abcde"), 0, 6, 0);
    test(S(""), 1, 0, SV("abcde"), 1, 0, 0);
    test(S(""), 1, 0, SV("abcde"), 1, 1, 0);
    test(S(""), 1, 0, SV("abcde"), 1, 2, 0);
    test(S(""), 1, 0, SV("abcde"), 1, 3, 0);
    test(S(""), 1, 0, SV("abcde"), 1, 4, 0);
    test(S(""), 1, 0, SV("abcde"), 1, 5, 0);
    test(S(""), 1, 0, SV("abcde"), 2, 0, 0);
    test(S(""), 1, 0, SV("abcde"), 2, 1, 0);
    test(S(""), 1, 0, SV("abcde"), 2, 2, 0);
    test(S(""), 1, 0, SV("abcde"), 2, 3, 0);
    test(S(""), 1, 0, SV("abcde"), 2, 4, 0);
    test(S(""), 1, 0, SV("abcde"), 4, 0, 0);
    test(S(""), 1, 0, SV("abcde"), 4, 1, 0);
    test(S(""), 1, 0, SV("abcde"), 4, 2, 0);
    test(S(""), 1, 0, SV("abcde"), 5, 0, 0);
    test(S(""), 1, 0, SV("abcde"), 5, 1, 0);
    test(S(""), 1, 0, SV("abcde"), 6, 0, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 0, 0, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 0, 1, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 0, 5, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 0, 9, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 0, 10, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 0, 11, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 1, 0, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 1, 1, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 1, 4, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 1, 8, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 1, 9, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 1, 10, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 5, 0, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 5, 1, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 5, 2, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 5, 4, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 5, 5, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 5, 6, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 9, 0, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 9, 1, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 9, 2, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 10, 0, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 10, 1, 0);
    test(S(""), 1, 0, SV("abcdefghij"), 11, 0, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 0, 1, 0);
}

template <class S, class SV>
void test2() {
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 0, 10, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 0, 19, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 0, 20, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 0, 21, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 1, 1, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 1, 9, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 1, 18, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 1, 19, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 1, 20, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 10, 1, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 10, 5, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 10, 9, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 10, 10, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 10, 11, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 19, 1, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 19, 2, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S(""), 1, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 0, 0, SV(""), 0, 0, 0);
    test(S("abcde"), 0, 0, SV(""), 0, 1, 0);
    test(S("abcde"), 0, 0, SV(""), 1, 0, 0);
    test(S("abcde"), 0, 0, SV("abcde"), 0, 0, 0);
    test(S("abcde"), 0, 0, SV("abcde"), 0, 1, -1);
    test(S("abcde"), 0, 0, SV("abcde"), 0, 2, -2);
    test(S("abcde"), 0, 0, SV("abcde"), 0, 4, -4);
    test(S("abcde"), 0, 0, SV("abcde"), 0, 5, -5);
    test(S("abcde"), 0, 0, SV("abcde"), 0, 6, -5);
    test(S("abcde"), 0, 0, SV("abcde"), 1, 0, 0);
    test(S("abcde"), 0, 0, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 0, 0, SV("abcde"), 1, 2, -2);
    test(S("abcde"), 0, 0, SV("abcde"), 1, 3, -3);
    test(S("abcde"), 0, 0, SV("abcde"), 1, 4, -4);
    test(S("abcde"), 0, 0, SV("abcde"), 1, 5, -4);
    test(S("abcde"), 0, 0, SV("abcde"), 2, 0, 0);
    test(S("abcde"), 0, 0, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 0, 0, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 0, 0, SV("abcde"), 2, 3, -3);
    test(S("abcde"), 0, 0, SV("abcde"), 2, 4, -3);
    test(S("abcde"), 0, 0, SV("abcde"), 4, 0, 0);
    test(S("abcde"), 0, 0, SV("abcde"), 4, 1, -1);
    test(S("abcde"), 0, 0, SV("abcde"), 4, 2, -1);
    test(S("abcde"), 0, 0, SV("abcde"), 5, 0, 0);
    test(S("abcde"), 0, 0, SV("abcde"), 5, 1, 0);
    test(S("abcde"), 0, 0, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcde"), 0, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcde"), 0, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 0, 1, SV(""), 0, 0, 1);
    test(S("abcde"), 0, 1, SV(""), 0, 1, 1);
    test(S("abcde"), 0, 1, SV(""), 1, 0, 0);
    test(S("abcde"), 0, 1, SV("abcde"), 0, 0, 1);
}

template <class S, class SV>
void test3() {
    test(S("abcde"), 0, 1, SV("abcde"), 0, 1, 0);
    test(S("abcde"), 0, 1, SV("abcde"), 0, 2, -1);
    test(S("abcde"), 0, 1, SV("abcde"), 0, 4, -3);
    test(S("abcde"), 0, 1, SV("abcde"), 0, 5, -4);
    test(S("abcde"), 0, 1, SV("abcde"), 0, 6, -4);
    test(S("abcde"), 0, 1, SV("abcde"), 1, 0, 1);
    test(S("abcde"), 0, 1, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 0, 1, SV("abcde"), 1, 2, -1);
    test(S("abcde"), 0, 1, SV("abcde"), 1, 3, -1);
    test(S("abcde"), 0, 1, SV("abcde"), 1, 4, -1);
    test(S("abcde"), 0, 1, SV("abcde"), 1, 5, -1);
    test(S("abcde"), 0, 1, SV("abcde"), 2, 0, 1);
    test(S("abcde"), 0, 1, SV("abcde"), 2, 1, -2);
    test(S("abcde"), 0, 1, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 0, 1, SV("abcde"), 2, 3, -2);
    test(S("abcde"), 0, 1, SV("abcde"), 2, 4, -2);
    test(S("abcde"), 0, 1, SV("abcde"), 4, 0, 1);
    test(S("abcde"), 0, 1, SV("abcde"), 4, 1, -4);
    test(S("abcde"), 0, 1, SV("abcde"), 4, 2, -4);
    test(S("abcde"), 0, 1, SV("abcde"), 5, 0, 1);
    test(S("abcde"), 0, 1, SV("abcde"), 5, 1, 1);
    test(S("abcde"), 0, 1, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 0, 1, 0);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 0, 5, -4);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 0, 9, -8);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 0, 10, -9);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 0, 11, -9);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 1, 4, -1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 1, 8, -1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 1, 9, -1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 1, 10, -1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 5, 1, -5);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 5, 2, -5);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 5, 4, -5);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 9, 1, -9);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 9, 2, -9);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcde"), 0, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 1, 0);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 10, -9);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 19, -18);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 20, -19);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 21, -19);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcde"), 0, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 0, 2, SV(""), 0, 0, 2);
    test(S("abcde"), 0, 2, SV(""), 0, 1, 2);
    test(S("abcde"), 0, 2, SV(""), 1, 0, 0);
    test(S("abcde"), 0, 2, SV("abcde"), 0, 0, 2);
    test(S("abcde"), 0, 2, SV("abcde"), 0, 1, 1);
    test(S("abcde"), 0, 2, SV("abcde"), 0, 2, 0);
    test(S("abcde"), 0, 2, SV("abcde"), 0, 4, -2);
    test(S("abcde"), 0, 2, SV("abcde"), 0, 5, -3);
    test(S("abcde"), 0, 2, SV("abcde"), 0, 6, -3);
    test(S("abcde"), 0, 2, SV("abcde"), 1, 0, 2);
    test(S("abcde"), 0, 2, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 0, 2, SV("abcde"), 1, 2, -1);
    test(S("abcde"), 0, 2, SV("abcde"), 1, 3, -1);
    test(S("abcde"), 0, 2, SV("abcde"), 1, 4, -1);
    test(S("abcde"), 0, 2, SV("abcde"), 1, 5, -1);
    test(S("abcde"), 0, 2, SV("abcde"), 2, 0, 2);
    test(S("abcde"), 0, 2, SV("abcde"), 2, 1, -2);
    test(S("abcde"), 0, 2, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 0, 2, SV("abcde"), 2, 3, -2);
    test(S("abcde"), 0, 2, SV("abcde"), 2, 4, -2);
    test(S("abcde"), 0, 2, SV("abcde"), 4, 0, 2);
    test(S("abcde"), 0, 2, SV("abcde"), 4, 1, -4);
    test(S("abcde"), 0, 2, SV("abcde"), 4, 2, -4);
    test(S("abcde"), 0, 2, SV("abcde"), 5, 0, 2);
    test(S("abcde"), 0, 2, SV("abcde"), 5, 1, 2);
    test(S("abcde"), 0, 2, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 0, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 0, 1, 1);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 0, 5, -3);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 0, 9, -7);
}

template <class S, class SV>
void test4() {
    test(S("abcde"), 0, 2, SV("abcdefghij"), 0, 10, -8);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 0, 11, -8);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 1, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 1, 4, -1);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 1, 8, -1);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 1, 9, -1);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 1, 10, -1);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 5, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 5, 1, -5);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 5, 2, -5);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 5, 4, -5);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 9, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 9, 1, -9);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 9, 2, -9);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 10, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 10, 1, 2);
    test(S("abcde"), 0, 2, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 0, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 0, 10, -8);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 0, 19, -17);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 0, 20, -18);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 0, 21, -18);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 1, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 10, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 19, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 20, 0, 2);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 20, 1, 2);
    test(S("abcde"), 0, 2, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 0, 4, SV(""), 0, 0, 4);
    test(S("abcde"), 0, 4, SV(""), 0, 1, 4);
    test(S("abcde"), 0, 4, SV(""), 1, 0, 0);
    test(S("abcde"), 0, 4, SV("abcde"), 0, 0, 4);
    test(S("abcde"), 0, 4, SV("abcde"), 0, 1, 3);
    test(S("abcde"), 0, 4, SV("abcde"), 0, 2, 2);
    test(S("abcde"), 0, 4, SV("abcde"), 0, 4, 0);
    test(S("abcde"), 0, 4, SV("abcde"), 0, 5, -1);
    test(S("abcde"), 0, 4, SV("abcde"), 0, 6, -1);
    test(S("abcde"), 0, 4, SV("abcde"), 1, 0, 4);
    test(S("abcde"), 0, 4, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 0, 4, SV("abcde"), 1, 2, -1);
    test(S("abcde"), 0, 4, SV("abcde"), 1, 3, -1);
    test(S("abcde"), 0, 4, SV("abcde"), 1, 4, -1);
    test(S("abcde"), 0, 4, SV("abcde"), 1, 5, -1);
    test(S("abcde"), 0, 4, SV("abcde"), 2, 0, 4);
    test(S("abcde"), 0, 4, SV("abcde"), 2, 1, -2);
    test(S("abcde"), 0, 4, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 0, 4, SV("abcde"), 2, 3, -2);
    test(S("abcde"), 0, 4, SV("abcde"), 2, 4, -2);
    test(S("abcde"), 0, 4, SV("abcde"), 4, 0, 4);
    test(S("abcde"), 0, 4, SV("abcde"), 4, 1, -4);
    test(S("abcde"), 0, 4, SV("abcde"), 4, 2, -4);
    test(S("abcde"), 0, 4, SV("abcde"), 5, 0, 4);
    test(S("abcde"), 0, 4, SV("abcde"), 5, 1, 4);
    test(S("abcde"), 0, 4, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 0, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 0, 1, 3);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 0, 5, -1);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 0, 9, -5);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 0, 10, -6);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 0, 11, -6);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 1, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 1, 4, -1);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 1, 8, -1);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 1, 9, -1);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 1, 10, -1);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 5, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 5, 1, -5);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 5, 2, -5);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 5, 4, -5);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 9, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 9, 1, -9);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 9, 2, -9);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 10, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 10, 1, 4);
    test(S("abcde"), 0, 4, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 0, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 0, 1, 3);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 0, 10, -6);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 0, 19, -15);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 0, 20, -16);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 0, 21, -16);
}

template <class S, class SV>
void test5() {
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 1, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 10, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 19, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 20, 0, 4);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 20, 1, 4);
    test(S("abcde"), 0, 4, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 0, 5, SV(""), 0, 0, 5);
    test(S("abcde"), 0, 5, SV(""), 0, 1, 5);
    test(S("abcde"), 0, 5, SV(""), 1, 0, 0);
    test(S("abcde"), 0, 5, SV("abcde"), 0, 0, 5);
    test(S("abcde"), 0, 5, SV("abcde"), 0, 1, 4);
    test(S("abcde"), 0, 5, SV("abcde"), 0, 2, 3);
    test(S("abcde"), 0, 5, SV("abcde"), 0, 4, 1);
    test(S("abcde"), 0, 5, SV("abcde"), 0, 5, 0);
    test(S("abcde"), 0, 5, SV("abcde"), 0, 6, 0);
    test(S("abcde"), 0, 5, SV("abcde"), 1, 0, 5);
    test(S("abcde"), 0, 5, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 0, 5, SV("abcde"), 1, 2, -1);
    test(S("abcde"), 0, 5, SV("abcde"), 1, 3, -1);
    test(S("abcde"), 0, 5, SV("abcde"), 1, 4, -1);
    test(S("abcde"), 0, 5, SV("abcde"), 1, 5, -1);
    test(S("abcde"), 0, 5, SV("abcde"), 2, 0, 5);
    test(S("abcde"), 0, 5, SV("abcde"), 2, 1, -2);
    test(S("abcde"), 0, 5, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 0, 5, SV("abcde"), 2, 3, -2);
    test(S("abcde"), 0, 5, SV("abcde"), 2, 4, -2);
    test(S("abcde"), 0, 5, SV("abcde"), 4, 0, 5);
    test(S("abcde"), 0, 5, SV("abcde"), 4, 1, -4);
    test(S("abcde"), 0, 5, SV("abcde"), 4, 2, -4);
    test(S("abcde"), 0, 5, SV("abcde"), 5, 0, 5);
    test(S("abcde"), 0, 5, SV("abcde"), 5, 1, 5);
    test(S("abcde"), 0, 5, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 0, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 0, 1, 4);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 0, 5, 0);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 0, 9, -4);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 0, 10, -5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 0, 11, -5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 1, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 1, 4, -1);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 1, 8, -1);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 1, 9, -1);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 1, 10, -1);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 5, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 5, 1, -5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 5, 2, -5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 5, 4, -5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 9, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 9, 1, -9);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 9, 2, -9);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 10, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 10, 1, 5);
    test(S("abcde"), 0, 5, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 1, 4);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 10, -5);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 19, -14);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 20, -15);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 21, -15);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 19, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 20, 0, 5);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 20, 1, 5);
    test(S("abcde"), 0, 5, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 0, 6, SV(""), 0, 0, 5);
    test(S("abcde"), 0, 6, SV(""), 0, 1, 5);
    test(S("abcde"), 0, 6, SV(""), 1, 0, 0);
    test(S("abcde"), 0, 6, SV("abcde"), 0, 0, 5);
    test(S("abcde"), 0, 6, SV("abcde"), 0, 1, 4);
    test(S("abcde"), 0, 6, SV("abcde"), 0, 2, 3);
    test(S("abcde"), 0, 6, SV("abcde"), 0, 4, 1);
    test(S("abcde"), 0, 6, SV("abcde"), 0, 5, 0);
}

template <class S, class SV>
void test6() {
    test(S("abcde"), 0, 6, SV("abcde"), 0, 6, 0);
    test(S("abcde"), 0, 6, SV("abcde"), 1, 0, 5);
    test(S("abcde"), 0, 6, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 0, 6, SV("abcde"), 1, 2, -1);
    test(S("abcde"), 0, 6, SV("abcde"), 1, 3, -1);
    test(S("abcde"), 0, 6, SV("abcde"), 1, 4, -1);
    test(S("abcde"), 0, 6, SV("abcde"), 1, 5, -1);
    test(S("abcde"), 0, 6, SV("abcde"), 2, 0, 5);
    test(S("abcde"), 0, 6, SV("abcde"), 2, 1, -2);
    test(S("abcde"), 0, 6, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 0, 6, SV("abcde"), 2, 3, -2);
    test(S("abcde"), 0, 6, SV("abcde"), 2, 4, -2);
    test(S("abcde"), 0, 6, SV("abcde"), 4, 0, 5);
    test(S("abcde"), 0, 6, SV("abcde"), 4, 1, -4);
    test(S("abcde"), 0, 6, SV("abcde"), 4, 2, -4);
    test(S("abcde"), 0, 6, SV("abcde"), 5, 0, 5);
    test(S("abcde"), 0, 6, SV("abcde"), 5, 1, 5);
    test(S("abcde"), 0, 6, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 0, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 0, 1, 4);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 0, 5, 0);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 0, 9, -4);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 0, 10, -5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 0, 11, -5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 1, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 1, 4, -1);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 1, 8, -1);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 1, 9, -1);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 1, 10, -1);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 5, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 5, 1, -5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 5, 2, -5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 5, 4, -5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 9, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 9, 1, -9);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 9, 2, -9);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 10, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 10, 1, 5);
    test(S("abcde"), 0, 6, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 0, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 0, 1, 4);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 0, 10, -5);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 0, 19, -14);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 0, 20, -15);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 0, 21, -15);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 1, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 10, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 19, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 20, 0, 5);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 20, 1, 5);
    test(S("abcde"), 0, 6, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 1, 0, SV(""), 0, 0, 0);
    test(S("abcde"), 1, 0, SV(""), 0, 1, 0);
    test(S("abcde"), 1, 0, SV(""), 1, 0, 0);
    test(S("abcde"), 1, 0, SV("abcde"), 0, 0, 0);
    test(S("abcde"), 1, 0, SV("abcde"), 0, 1, -1);
    test(S("abcde"), 1, 0, SV("abcde"), 0, 2, -2);
    test(S("abcde"), 1, 0, SV("abcde"), 0, 4, -4);
    test(S("abcde"), 1, 0, SV("abcde"), 0, 5, -5);
    test(S("abcde"), 1, 0, SV("abcde"), 0, 6, -5);
    test(S("abcde"), 1, 0, SV("abcde"), 1, 0, 0);
    test(S("abcde"), 1, 0, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 1, 0, SV("abcde"), 1, 2, -2);
    test(S("abcde"), 1, 0, SV("abcde"), 1, 3, -3);
    test(S("abcde"), 1, 0, SV("abcde"), 1, 4, -4);
    test(S("abcde"), 1, 0, SV("abcde"), 1, 5, -4);
    test(S("abcde"), 1, 0, SV("abcde"), 2, 0, 0);
    test(S("abcde"), 1, 0, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 1, 0, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 1, 0, SV("abcde"), 2, 3, -3);
    test(S("abcde"), 1, 0, SV("abcde"), 2, 4, -3);
    test(S("abcde"), 1, 0, SV("abcde"), 4, 0, 0);
    test(S("abcde"), 1, 0, SV("abcde"), 4, 1, -1);
    test(S("abcde"), 1, 0, SV("abcde"), 4, 2, -1);
    test(S("abcde"), 1, 0, SV("abcde"), 5, 0, 0);
    test(S("abcde"), 1, 0, SV("abcde"), 5, 1, 0);
    test(S("abcde"), 1, 0, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 1, 1, -1);
}

template <class S, class SV>
void test7() {
    test(S("abcde"), 1, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcde"), 1, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcde"), 1, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 1, 1, SV(""), 0, 0, 1);
    test(S("abcde"), 1, 1, SV(""), 0, 1, 1);
    test(S("abcde"), 1, 1, SV(""), 1, 0, 0);
    test(S("abcde"), 1, 1, SV("abcde"), 0, 0, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 0, 1, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 0, 2, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 0, 4, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 0, 5, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 0, 6, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 1, 0, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 1, 1, 0);
    test(S("abcde"), 1, 1, SV("abcde"), 1, 2, -1);
    test(S("abcde"), 1, 1, SV("abcde"), 1, 3, -2);
    test(S("abcde"), 1, 1, SV("abcde"), 1, 4, -3);
    test(S("abcde"), 1, 1, SV("abcde"), 1, 5, -3);
    test(S("abcde"), 1, 1, SV("abcde"), 2, 0, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 1, 1, SV("abcde"), 2, 2, -1);
    test(S("abcde"), 1, 1, SV("abcde"), 2, 3, -1);
    test(S("abcde"), 1, 1, SV("abcde"), 2, 4, -1);
    test(S("abcde"), 1, 1, SV("abcde"), 4, 0, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 4, 1, -3);
    test(S("abcde"), 1, 1, SV("abcde"), 4, 2, -3);
    test(S("abcde"), 1, 1, SV("abcde"), 5, 0, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 5, 1, 1);
    test(S("abcde"), 1, 1, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 0, 1, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 0, 5, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 0, 9, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 0, 10, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 0, 11, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 1, 1, 0);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 1, 4, -3);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 1, 8, -7);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 1, 9, -8);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 1, 10, -8);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 5, 1, -4);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 5, 2, -4);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 5, 5, -4);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 5, 6, -4);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 9, 1, -8);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 9, 2, -8);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcde"), 1, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 1, 0);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 9, -8);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 18, -17);
}

template <class S, class SV>
void test8() {
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 19, -18);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 20, -18);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcde"), 1, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 1, 2, SV(""), 0, 0, 2);
    test(S("abcde"), 1, 2, SV(""), 0, 1, 2);
    test(S("abcde"), 1, 2, SV(""), 1, 0, 0);
    test(S("abcde"), 1, 2, SV("abcde"), 0, 0, 2);
    test(S("abcde"), 1, 2, SV("abcde"), 0, 1, 1);
    test(S("abcde"), 1, 2, SV("abcde"), 0, 2, 1);
    test(S("abcde"), 1, 2, SV("abcde"), 0, 4, 1);
    test(S("abcde"), 1, 2, SV("abcde"), 0, 5, 1);
    test(S("abcde"), 1, 2, SV("abcde"), 0, 6, 1);
    test(S("abcde"), 1, 2, SV("abcde"), 1, 0, 2);
    test(S("abcde"), 1, 2, SV("abcde"), 1, 1, 1);
    test(S("abcde"), 1, 2, SV("abcde"), 1, 2, 0);
    test(S("abcde"), 1, 2, SV("abcde"), 1, 3, -1);
    test(S("abcde"), 1, 2, SV("abcde"), 1, 4, -2);
    test(S("abcde"), 1, 2, SV("abcde"), 1, 5, -2);
    test(S("abcde"), 1, 2, SV("abcde"), 2, 0, 2);
    test(S("abcde"), 1, 2, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 1, 2, SV("abcde"), 2, 2, -1);
    test(S("abcde"), 1, 2, SV("abcde"), 2, 3, -1);
    test(S("abcde"), 1, 2, SV("abcde"), 2, 4, -1);
    test(S("abcde"), 1, 2, SV("abcde"), 4, 0, 2);
    test(S("abcde"), 1, 2, SV("abcde"), 4, 1, -3);
    test(S("abcde"), 1, 2, SV("abcde"), 4, 2, -3);
    test(S("abcde"), 1, 2, SV("abcde"), 5, 0, 2);
    test(S("abcde"), 1, 2, SV("abcde"), 5, 1, 2);
    test(S("abcde"), 1, 2, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 0, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 0, 1, 1);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 0, 5, 1);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 0, 9, 1);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 0, 10, 1);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 0, 11, 1);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 1, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 1, 1, 1);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 1, 4, -2);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 1, 8, -6);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 1, 9, -7);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 1, 10, -7);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 5, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 5, 1, -4);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 5, 2, -4);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 5, 5, -4);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 5, 6, -4);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 9, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 9, 1, -8);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 9, 2, -8);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 10, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 10, 1, 2);
    test(S("abcde"), 1, 2, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 0, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 1, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 1, 1, 1);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 1, 9, -7);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 1, 18, -16);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 1, 19, -17);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 1, 20, -17);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 10, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 19, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 20, 0, 2);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 20, 1, 2);
    test(S("abcde"), 1, 2, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 1, 3, SV(""), 0, 0, 3);
    test(S("abcde"), 1, 3, SV(""), 0, 1, 3);
    test(S("abcde"), 1, 3, SV(""), 1, 0, 0);
    test(S("abcde"), 1, 3, SV("abcde"), 0, 0, 3);
    test(S("abcde"), 1, 3, SV("abcde"), 0, 1, 1);
    test(S("abcde"), 1, 3, SV("abcde"), 0, 2, 1);
    test(S("abcde"), 1, 3, SV("abcde"), 0, 4, 1);
    test(S("abcde"), 1, 3, SV("abcde"), 0, 5, 1);
    test(S("abcde"), 1, 3, SV("abcde"), 0, 6, 1);
    test(S("abcde"), 1, 3, SV("abcde"), 1, 0, 3);
    test(S("abcde"), 1, 3, SV("abcde"), 1, 1, 2);
    test(S("abcde"), 1, 3, SV("abcde"), 1, 2, 1);
}

template <class S, class SV>
void test9() {
    test(S("abcde"), 1, 3, SV("abcde"), 1, 3, 0);
    test(S("abcde"), 1, 3, SV("abcde"), 1, 4, -1);
    test(S("abcde"), 1, 3, SV("abcde"), 1, 5, -1);
    test(S("abcde"), 1, 3, SV("abcde"), 2, 0, 3);
    test(S("abcde"), 1, 3, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 1, 3, SV("abcde"), 2, 2, -1);
    test(S("abcde"), 1, 3, SV("abcde"), 2, 3, -1);
    test(S("abcde"), 1, 3, SV("abcde"), 2, 4, -1);
    test(S("abcde"), 1, 3, SV("abcde"), 4, 0, 3);
    test(S("abcde"), 1, 3, SV("abcde"), 4, 1, -3);
    test(S("abcde"), 1, 3, SV("abcde"), 4, 2, -3);
    test(S("abcde"), 1, 3, SV("abcde"), 5, 0, 3);
    test(S("abcde"), 1, 3, SV("abcde"), 5, 1, 3);
    test(S("abcde"), 1, 3, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 0, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 0, 1, 1);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 0, 5, 1);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 0, 9, 1);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 0, 10, 1);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 0, 11, 1);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 1, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 1, 1, 2);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 1, 4, -1);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 1, 8, -5);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 1, 9, -6);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 1, 10, -6);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 5, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 5, 1, -4);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 5, 2, -4);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 5, 5, -4);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 5, 6, -4);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 9, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 9, 1, -8);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 9, 2, -8);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 10, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 10, 1, 3);
    test(S("abcde"), 1, 3, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 0, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 1, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 1, 1, 2);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 1, 9, -6);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 1, 18, -15);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 1, 19, -16);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 1, 20, -16);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 10, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 19, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 20, 0, 3);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 20, 1, 3);
    test(S("abcde"), 1, 3, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 1, 4, SV(""), 0, 0, 4);
    test(S("abcde"), 1, 4, SV(""), 0, 1, 4);
    test(S("abcde"), 1, 4, SV(""), 1, 0, 0);
    test(S("abcde"), 1, 4, SV("abcde"), 0, 0, 4);
    test(S("abcde"), 1, 4, SV("abcde"), 0, 1, 1);
    test(S("abcde"), 1, 4, SV("abcde"), 0, 2, 1);
    test(S("abcde"), 1, 4, SV("abcde"), 0, 4, 1);
    test(S("abcde"), 1, 4, SV("abcde"), 0, 5, 1);
    test(S("abcde"), 1, 4, SV("abcde"), 0, 6, 1);
    test(S("abcde"), 1, 4, SV("abcde"), 1, 0, 4);
    test(S("abcde"), 1, 4, SV("abcde"), 1, 1, 3);
    test(S("abcde"), 1, 4, SV("abcde"), 1, 2, 2);
    test(S("abcde"), 1, 4, SV("abcde"), 1, 3, 1);
    test(S("abcde"), 1, 4, SV("abcde"), 1, 4, 0);
    test(S("abcde"), 1, 4, SV("abcde"), 1, 5, 0);
    test(S("abcde"), 1, 4, SV("abcde"), 2, 0, 4);
    test(S("abcde"), 1, 4, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 1, 4, SV("abcde"), 2, 2, -1);
    test(S("abcde"), 1, 4, SV("abcde"), 2, 3, -1);
    test(S("abcde"), 1, 4, SV("abcde"), 2, 4, -1);
    test(S("abcde"), 1, 4, SV("abcde"), 4, 0, 4);
    test(S("abcde"), 1, 4, SV("abcde"), 4, 1, -3);
    test(S("abcde"), 1, 4, SV("abcde"), 4, 2, -3);
    test(S("abcde"), 1, 4, SV("abcde"), 5, 0, 4);
    test(S("abcde"), 1, 4, SV("abcde"), 5, 1, 4);
    test(S("abcde"), 1, 4, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 0, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 0, 1, 1);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 0, 5, 1);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 0, 9, 1);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 0, 10, 1);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 0, 11, 1);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 1, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 1, 1, 3);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 1, 4, 0);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 1, 8, -4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 1, 9, -5);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 1, 10, -5);
}

template <class S, class SV>
void test10() {
    test(S("abcde"), 1, 4, SV("abcdefghij"), 5, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 5, 1, -4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 5, 2, -4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 5, 5, -4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 5, 6, -4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 9, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 9, 1, -8);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 9, 2, -8);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 10, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 10, 1, 4);
    test(S("abcde"), 1, 4, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 1, 3);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 9, -5);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 18, -14);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 19, -15);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 20, -15);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 19, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 20, 0, 4);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 20, 1, 4);
    test(S("abcde"), 1, 4, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 1, 5, SV(""), 0, 0, 4);
    test(S("abcde"), 1, 5, SV(""), 0, 1, 4);
    test(S("abcde"), 1, 5, SV(""), 1, 0, 0);
    test(S("abcde"), 1, 5, SV("abcde"), 0, 0, 4);
    test(S("abcde"), 1, 5, SV("abcde"), 0, 1, 1);
    test(S("abcde"), 1, 5, SV("abcde"), 0, 2, 1);
    test(S("abcde"), 1, 5, SV("abcde"), 0, 4, 1);
    test(S("abcde"), 1, 5, SV("abcde"), 0, 5, 1);
    test(S("abcde"), 1, 5, SV("abcde"), 0, 6, 1);
    test(S("abcde"), 1, 5, SV("abcde"), 1, 0, 4);
    test(S("abcde"), 1, 5, SV("abcde"), 1, 1, 3);
    test(S("abcde"), 1, 5, SV("abcde"), 1, 2, 2);
    test(S("abcde"), 1, 5, SV("abcde"), 1, 3, 1);
    test(S("abcde"), 1, 5, SV("abcde"), 1, 4, 0);
    test(S("abcde"), 1, 5, SV("abcde"), 1, 5, 0);
    test(S("abcde"), 1, 5, SV("abcde"), 2, 0, 4);
    test(S("abcde"), 1, 5, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 1, 5, SV("abcde"), 2, 2, -1);
    test(S("abcde"), 1, 5, SV("abcde"), 2, 3, -1);
    test(S("abcde"), 1, 5, SV("abcde"), 2, 4, -1);
    test(S("abcde"), 1, 5, SV("abcde"), 4, 0, 4);
    test(S("abcde"), 1, 5, SV("abcde"), 4, 1, -3);
    test(S("abcde"), 1, 5, SV("abcde"), 4, 2, -3);
    test(S("abcde"), 1, 5, SV("abcde"), 5, 0, 4);
    test(S("abcde"), 1, 5, SV("abcde"), 5, 1, 4);
    test(S("abcde"), 1, 5, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 0, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 0, 1, 1);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 0, 5, 1);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 0, 9, 1);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 0, 10, 1);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 0, 11, 1);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 1, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 1, 1, 3);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 1, 4, 0);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 1, 8, -4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 1, 9, -5);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 1, 10, -5);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 5, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 5, 1, -4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 5, 2, -4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 5, 5, -4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 5, 6, -4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 9, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 9, 1, -8);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 9, 2, -8);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 10, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 10, 1, 4);
    test(S("abcde"), 1, 5, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 0, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 1, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 1, 1, 3);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 1, 9, -5);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 1, 18, -14);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 1, 19, -15);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 1, 20, -15);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 10, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 10, 1, -9);
}

template <class S, class SV>
void test11() {
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 19, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 20, 0, 4);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 20, 1, 4);
    test(S("abcde"), 1, 5, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 2, 0, SV(""), 0, 0, 0);
    test(S("abcde"), 2, 0, SV(""), 0, 1, 0);
    test(S("abcde"), 2, 0, SV(""), 1, 0, 0);
    test(S("abcde"), 2, 0, SV("abcde"), 0, 0, 0);
    test(S("abcde"), 2, 0, SV("abcde"), 0, 1, -1);
    test(S("abcde"), 2, 0, SV("abcde"), 0, 2, -2);
    test(S("abcde"), 2, 0, SV("abcde"), 0, 4, -4);
    test(S("abcde"), 2, 0, SV("abcde"), 0, 5, -5);
    test(S("abcde"), 2, 0, SV("abcde"), 0, 6, -5);
    test(S("abcde"), 2, 0, SV("abcde"), 1, 0, 0);
    test(S("abcde"), 2, 0, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 2, 0, SV("abcde"), 1, 2, -2);
    test(S("abcde"), 2, 0, SV("abcde"), 1, 3, -3);
    test(S("abcde"), 2, 0, SV("abcde"), 1, 4, -4);
    test(S("abcde"), 2, 0, SV("abcde"), 1, 5, -4);
    test(S("abcde"), 2, 0, SV("abcde"), 2, 0, 0);
    test(S("abcde"), 2, 0, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 2, 0, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 2, 0, SV("abcde"), 2, 3, -3);
    test(S("abcde"), 2, 0, SV("abcde"), 2, 4, -3);
    test(S("abcde"), 2, 0, SV("abcde"), 4, 0, 0);
    test(S("abcde"), 2, 0, SV("abcde"), 4, 1, -1);
    test(S("abcde"), 2, 0, SV("abcde"), 4, 2, -1);
    test(S("abcde"), 2, 0, SV("abcde"), 5, 0, 0);
    test(S("abcde"), 2, 0, SV("abcde"), 5, 1, 0);
    test(S("abcde"), 2, 0, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcde"), 2, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcde"), 2, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 2, 1, SV(""), 0, 0, 1);
    test(S("abcde"), 2, 1, SV(""), 0, 1, 1);
    test(S("abcde"), 2, 1, SV(""), 1, 0, 0);
    test(S("abcde"), 2, 1, SV("abcde"), 0, 0, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 0, 1, 2);
    test(S("abcde"), 2, 1, SV("abcde"), 0, 2, 2);
    test(S("abcde"), 2, 1, SV("abcde"), 0, 4, 2);
    test(S("abcde"), 2, 1, SV("abcde"), 0, 5, 2);
    test(S("abcde"), 2, 1, SV("abcde"), 0, 6, 2);
    test(S("abcde"), 2, 1, SV("abcde"), 1, 0, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 1, 1, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 1, 2, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 1, 3, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 1, 4, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 1, 5, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 2, 0, 1);
}

template <class S, class SV>
void test12() {
    test(S("abcde"), 2, 1, SV("abcde"), 2, 1, 0);
    test(S("abcde"), 2, 1, SV("abcde"), 2, 2, -1);
    test(S("abcde"), 2, 1, SV("abcde"), 2, 3, -2);
    test(S("abcde"), 2, 1, SV("abcde"), 2, 4, -2);
    test(S("abcde"), 2, 1, SV("abcde"), 4, 0, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 4, 1, -2);
    test(S("abcde"), 2, 1, SV("abcde"), 4, 2, -2);
    test(S("abcde"), 2, 1, SV("abcde"), 5, 0, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 5, 1, 1);
    test(S("abcde"), 2, 1, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 0, 1, 2);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 0, 5, 2);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 0, 9, 2);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 0, 10, 2);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 0, 11, 2);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 1, 1, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 1, 4, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 1, 8, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 1, 9, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 1, 10, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 5, 1, -3);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 5, 2, -3);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 5, 4, -3);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 5, 5, -3);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 5, 6, -3);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 9, 1, -7);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 9, 2, -7);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcde"), 2, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 0, 1, 2);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 0, 10, 2);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 0, 19, 2);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 0, 20, 2);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 0, 21, 2);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 1, 1, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 1, 9, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 1, 18, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 1, 19, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 1, 20, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 10, 1, -8);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 10, 5, -8);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 10, 9, -8);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 10, 10, -8);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 10, 11, -8);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 19, 1, -17);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 19, 2, -17);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcde"), 2, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 2, 2, SV(""), 0, 0, 2);
    test(S("abcde"), 2, 2, SV(""), 0, 1, 2);
    test(S("abcde"), 2, 2, SV(""), 1, 0, 0);
    test(S("abcde"), 2, 2, SV("abcde"), 0, 0, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 0, 1, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 0, 2, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 0, 4, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 0, 5, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 0, 6, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 1, 0, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 1, 1, 1);
    test(S("abcde"), 2, 2, SV("abcde"), 1, 2, 1);
    test(S("abcde"), 2, 2, SV("abcde"), 1, 3, 1);
    test(S("abcde"), 2, 2, SV("abcde"), 1, 4, 1);
    test(S("abcde"), 2, 2, SV("abcde"), 1, 5, 1);
    test(S("abcde"), 2, 2, SV("abcde"), 2, 0, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 2, 1, 1);
    test(S("abcde"), 2, 2, SV("abcde"), 2, 2, 0);
    test(S("abcde"), 2, 2, SV("abcde"), 2, 3, -1);
    test(S("abcde"), 2, 2, SV("abcde"), 2, 4, -1);
    test(S("abcde"), 2, 2, SV("abcde"), 4, 0, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 4, 1, -2);
    test(S("abcde"), 2, 2, SV("abcde"), 4, 2, -2);
    test(S("abcde"), 2, 2, SV("abcde"), 5, 0, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 5, 1, 2);
    test(S("abcde"), 2, 2, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 0, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 0, 1, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 0, 5, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 0, 9, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 0, 10, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 0, 11, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 1, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 1, 1, 1);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 1, 4, 1);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 1, 8, 1);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 1, 9, 1);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 1, 10, 1);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 5, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 5, 1, -3);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 5, 2, -3);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 5, 4, -3);
}

template <class S, class SV>
void test13() {
    test(S("abcde"), 2, 2, SV("abcdefghij"), 5, 5, -3);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 5, 6, -3);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 9, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 9, 1, -7);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 9, 2, -7);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 10, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 10, 1, 2);
    test(S("abcde"), 2, 2, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 0, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 0, 1, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 0, 10, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 0, 19, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 0, 20, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 0, 21, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 1, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 1, 1, 1);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 1, 9, 1);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 1, 18, 1);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 1, 19, 1);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 1, 20, 1);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 10, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 10, 1, -8);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 10, 5, -8);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 10, 9, -8);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 10, 10, -8);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 10, 11, -8);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 19, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 19, 1, -17);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 19, 2, -17);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 20, 0, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 20, 1, 2);
    test(S("abcde"), 2, 2, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 2, 3, SV(""), 0, 0, 3);
    test(S("abcde"), 2, 3, SV(""), 0, 1, 3);
    test(S("abcde"), 2, 3, SV(""), 1, 0, 0);
    test(S("abcde"), 2, 3, SV("abcde"), 0, 0, 3);
    test(S("abcde"), 2, 3, SV("abcde"), 0, 1, 2);
    test(S("abcde"), 2, 3, SV("abcde"), 0, 2, 2);
    test(S("abcde"), 2, 3, SV("abcde"), 0, 4, 2);
    test(S("abcde"), 2, 3, SV("abcde"), 0, 5, 2);
    test(S("abcde"), 2, 3, SV("abcde"), 0, 6, 2);
    test(S("abcde"), 2, 3, SV("abcde"), 1, 0, 3);
    test(S("abcde"), 2, 3, SV("abcde"), 1, 1, 1);
    test(S("abcde"), 2, 3, SV("abcde"), 1, 2, 1);
    test(S("abcde"), 2, 3, SV("abcde"), 1, 3, 1);
    test(S("abcde"), 2, 3, SV("abcde"), 1, 4, 1);
    test(S("abcde"), 2, 3, SV("abcde"), 1, 5, 1);
    test(S("abcde"), 2, 3, SV("abcde"), 2, 0, 3);
    test(S("abcde"), 2, 3, SV("abcde"), 2, 1, 2);
    test(S("abcde"), 2, 3, SV("abcde"), 2, 2, 1);
    test(S("abcde"), 2, 3, SV("abcde"), 2, 3, 0);
    test(S("abcde"), 2, 3, SV("abcde"), 2, 4, 0);
    test(S("abcde"), 2, 3, SV("abcde"), 4, 0, 3);
    test(S("abcde"), 2, 3, SV("abcde"), 4, 1, -2);
    test(S("abcde"), 2, 3, SV("abcde"), 4, 2, -2);
    test(S("abcde"), 2, 3, SV("abcde"), 5, 0, 3);
    test(S("abcde"), 2, 3, SV("abcde"), 5, 1, 3);
    test(S("abcde"), 2, 3, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 0, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 0, 1, 2);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 0, 5, 2);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 0, 9, 2);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 0, 10, 2);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 0, 11, 2);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 1, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 1, 1, 1);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 1, 4, 1);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 1, 8, 1);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 1, 9, 1);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 1, 10, 1);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 5, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 5, 1, -3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 5, 2, -3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 5, 4, -3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 5, 5, -3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 5, 6, -3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 9, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 9, 1, -7);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 9, 2, -7);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 10, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 10, 1, 3);
    test(S("abcde"), 2, 3, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 0, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 0, 1, 2);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 0, 10, 2);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 0, 19, 2);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 0, 20, 2);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 0, 21, 2);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 1, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 1, 1, 1);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 1, 9, 1);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 1, 18, 1);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 1, 19, 1);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 1, 20, 1);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 10, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 10, 1, -8);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 10, 5, -8);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 10, 9, -8);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 10, 10, -8);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 10, 11, -8);
}

template <class S, class SV>
void test14() {
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 19, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 19, 1, -17);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 19, 2, -17);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 20, 0, 3);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 20, 1, 3);
    test(S("abcde"), 2, 3, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 2, 4, SV(""), 0, 0, 3);
    test(S("abcde"), 2, 4, SV(""), 0, 1, 3);
    test(S("abcde"), 2, 4, SV(""), 1, 0, 0);
    test(S("abcde"), 2, 4, SV("abcde"), 0, 0, 3);
    test(S("abcde"), 2, 4, SV("abcde"), 0, 1, 2);
    test(S("abcde"), 2, 4, SV("abcde"), 0, 2, 2);
    test(S("abcde"), 2, 4, SV("abcde"), 0, 4, 2);
    test(S("abcde"), 2, 4, SV("abcde"), 0, 5, 2);
    test(S("abcde"), 2, 4, SV("abcde"), 0, 6, 2);
    test(S("abcde"), 2, 4, SV("abcde"), 1, 0, 3);
    test(S("abcde"), 2, 4, SV("abcde"), 1, 1, 1);
    test(S("abcde"), 2, 4, SV("abcde"), 1, 2, 1);
    test(S("abcde"), 2, 4, SV("abcde"), 1, 3, 1);
    test(S("abcde"), 2, 4, SV("abcde"), 1, 4, 1);
    test(S("abcde"), 2, 4, SV("abcde"), 1, 5, 1);
    test(S("abcde"), 2, 4, SV("abcde"), 2, 0, 3);
    test(S("abcde"), 2, 4, SV("abcde"), 2, 1, 2);
    test(S("abcde"), 2, 4, SV("abcde"), 2, 2, 1);
    test(S("abcde"), 2, 4, SV("abcde"), 2, 3, 0);
    test(S("abcde"), 2, 4, SV("abcde"), 2, 4, 0);
    test(S("abcde"), 2, 4, SV("abcde"), 4, 0, 3);
    test(S("abcde"), 2, 4, SV("abcde"), 4, 1, -2);
    test(S("abcde"), 2, 4, SV("abcde"), 4, 2, -2);
    test(S("abcde"), 2, 4, SV("abcde"), 5, 0, 3);
    test(S("abcde"), 2, 4, SV("abcde"), 5, 1, 3);
    test(S("abcde"), 2, 4, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 0, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 0, 1, 2);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 0, 5, 2);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 0, 9, 2);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 0, 10, 2);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 0, 11, 2);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 1, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 1, 1, 1);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 1, 4, 1);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 1, 8, 1);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 1, 9, 1);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 1, 10, 1);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 5, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 5, 1, -3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 5, 2, -3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 5, 4, -3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 5, 5, -3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 5, 6, -3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 9, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 9, 1, -7);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 9, 2, -7);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 10, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 10, 1, 3);
    test(S("abcde"), 2, 4, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 0, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 0, 1, 2);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 0, 10, 2);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 0, 19, 2);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 0, 20, 2);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 0, 21, 2);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 1, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 1, 1, 1);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 1, 9, 1);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 1, 18, 1);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 1, 19, 1);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 1, 20, 1);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 10, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 10, 1, -8);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 10, 5, -8);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 10, 9, -8);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 10, 10, -8);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 10, 11, -8);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 19, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 19, 1, -17);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 19, 2, -17);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 20, 0, 3);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 20, 1, 3);
    test(S("abcde"), 2, 4, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 4, 0, SV(""), 0, 0, 0);
    test(S("abcde"), 4, 0, SV(""), 0, 1, 0);
    test(S("abcde"), 4, 0, SV(""), 1, 0, 0);
    test(S("abcde"), 4, 0, SV("abcde"), 0, 0, 0);
    test(S("abcde"), 4, 0, SV("abcde"), 0, 1, -1);
    test(S("abcde"), 4, 0, SV("abcde"), 0, 2, -2);
    test(S("abcde"), 4, 0, SV("abcde"), 0, 4, -4);
    test(S("abcde"), 4, 0, SV("abcde"), 0, 5, -5);
    test(S("abcde"), 4, 0, SV("abcde"), 0, 6, -5);
    test(S("abcde"), 4, 0, SV("abcde"), 1, 0, 0);
    test(S("abcde"), 4, 0, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 4, 0, SV("abcde"), 1, 2, -2);
    test(S("abcde"), 4, 0, SV("abcde"), 1, 3, -3);
    test(S("abcde"), 4, 0, SV("abcde"), 1, 4, -4);
    test(S("abcde"), 4, 0, SV("abcde"), 1, 5, -4);
    test(S("abcde"), 4, 0, SV("abcde"), 2, 0, 0);
    test(S("abcde"), 4, 0, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 4, 0, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 4, 0, SV("abcde"), 2, 3, -3);
    test(S("abcde"), 4, 0, SV("abcde"), 2, 4, -3);
}

template <class S, class SV>
void test15() {
    test(S("abcde"), 4, 0, SV("abcde"), 4, 0, 0);
    test(S("abcde"), 4, 0, SV("abcde"), 4, 1, -1);
    test(S("abcde"), 4, 0, SV("abcde"), 4, 2, -1);
    test(S("abcde"), 4, 0, SV("abcde"), 5, 0, 0);
    test(S("abcde"), 4, 0, SV("abcde"), 5, 1, 0);
    test(S("abcde"), 4, 0, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcde"), 4, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcde"), 4, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 4, 1, SV(""), 0, 0, 1);
    test(S("abcde"), 4, 1, SV(""), 0, 1, 1);
    test(S("abcde"), 4, 1, SV(""), 1, 0, 0);
    test(S("abcde"), 4, 1, SV("abcde"), 0, 0, 1);
    test(S("abcde"), 4, 1, SV("abcde"), 0, 1, 4);
    test(S("abcde"), 4, 1, SV("abcde"), 0, 2, 4);
    test(S("abcde"), 4, 1, SV("abcde"), 0, 4, 4);
    test(S("abcde"), 4, 1, SV("abcde"), 0, 5, 4);
    test(S("abcde"), 4, 1, SV("abcde"), 0, 6, 4);
    test(S("abcde"), 4, 1, SV("abcde"), 1, 0, 1);
    test(S("abcde"), 4, 1, SV("abcde"), 1, 1, 3);
    test(S("abcde"), 4, 1, SV("abcde"), 1, 2, 3);
    test(S("abcde"), 4, 1, SV("abcde"), 1, 3, 3);
    test(S("abcde"), 4, 1, SV("abcde"), 1, 4, 3);
    test(S("abcde"), 4, 1, SV("abcde"), 1, 5, 3);
    test(S("abcde"), 4, 1, SV("abcde"), 2, 0, 1);
    test(S("abcde"), 4, 1, SV("abcde"), 2, 1, 2);
    test(S("abcde"), 4, 1, SV("abcde"), 2, 2, 2);
    test(S("abcde"), 4, 1, SV("abcde"), 2, 3, 2);
    test(S("abcde"), 4, 1, SV("abcde"), 2, 4, 2);
    test(S("abcde"), 4, 1, SV("abcde"), 4, 0, 1);
    test(S("abcde"), 4, 1, SV("abcde"), 4, 1, 0);
    test(S("abcde"), 4, 1, SV("abcde"), 4, 2, 0);
    test(S("abcde"), 4, 1, SV("abcde"), 5, 0, 1);
    test(S("abcde"), 4, 1, SV("abcde"), 5, 1, 1);
    test(S("abcde"), 4, 1, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 0, 1, 4);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 0, 5, 4);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 0, 9, 4);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 0, 10, 4);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 0, 11, 4);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 1, 1, 3);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 1, 4, 3);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 1, 8, 3);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 1, 9, 3);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 1, 10, 3);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 5, 1, -1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 5, 2, -1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 5, 4, -1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 5, 5, -1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 5, 6, -1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 9, 1, -5);
}

template <class S, class SV>
void test16() {
    test(S("abcde"), 4, 1, SV("abcdefghij"), 9, 2, -5);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcde"), 4, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 0, 1, 4);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 0, 10, 4);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 0, 19, 4);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 0, 20, 4);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 0, 21, 4);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 1, 1, 3);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 1, 9, 3);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 1, 18, 3);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 1, 19, 3);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 1, 20, 3);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 10, 1, -6);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 10, 5, -6);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 10, 9, -6);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 10, 10, -6);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 10, 11, -6);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 19, 1, -15);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 19, 2, -15);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcde"), 4, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 4, 2, SV(""), 0, 0, 1);
    test(S("abcde"), 4, 2, SV(""), 0, 1, 1);
    test(S("abcde"), 4, 2, SV(""), 1, 0, 0);
    test(S("abcde"), 4, 2, SV("abcde"), 0, 0, 1);
    test(S("abcde"), 4, 2, SV("abcde"), 0, 1, 4);
    test(S("abcde"), 4, 2, SV("abcde"), 0, 2, 4);
    test(S("abcde"), 4, 2, SV("abcde"), 0, 4, 4);
    test(S("abcde"), 4, 2, SV("abcde"), 0, 5, 4);
    test(S("abcde"), 4, 2, SV("abcde"), 0, 6, 4);
    test(S("abcde"), 4, 2, SV("abcde"), 1, 0, 1);
    test(S("abcde"), 4, 2, SV("abcde"), 1, 1, 3);
    test(S("abcde"), 4, 2, SV("abcde"), 1, 2, 3);
    test(S("abcde"), 4, 2, SV("abcde"), 1, 3, 3);
    test(S("abcde"), 4, 2, SV("abcde"), 1, 4, 3);
    test(S("abcde"), 4, 2, SV("abcde"), 1, 5, 3);
    test(S("abcde"), 4, 2, SV("abcde"), 2, 0, 1);
    test(S("abcde"), 4, 2, SV("abcde"), 2, 1, 2);
    test(S("abcde"), 4, 2, SV("abcde"), 2, 2, 2);
    test(S("abcde"), 4, 2, SV("abcde"), 2, 3, 2);
    test(S("abcde"), 4, 2, SV("abcde"), 2, 4, 2);
    test(S("abcde"), 4, 2, SV("abcde"), 4, 0, 1);
    test(S("abcde"), 4, 2, SV("abcde"), 4, 1, 0);
    test(S("abcde"), 4, 2, SV("abcde"), 4, 2, 0);
    test(S("abcde"), 4, 2, SV("abcde"), 5, 0, 1);
    test(S("abcde"), 4, 2, SV("abcde"), 5, 1, 1);
    test(S("abcde"), 4, 2, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 0, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 0, 1, 4);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 0, 5, 4);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 0, 9, 4);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 0, 10, 4);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 0, 11, 4);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 1, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 1, 1, 3);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 1, 4, 3);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 1, 8, 3);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 1, 9, 3);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 1, 10, 3);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 5, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 5, 1, -1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 5, 2, -1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 5, 4, -1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 5, 5, -1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 5, 6, -1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 9, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 9, 1, -5);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 9, 2, -5);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 10, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 10, 1, 1);
    test(S("abcde"), 4, 2, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 0, 1, 4);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 0, 10, 4);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 0, 19, 4);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 0, 20, 4);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 0, 21, 4);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 1, 1, 3);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 1, 9, 3);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 1, 18, 3);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 1, 19, 3);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 1, 20, 3);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 10, 1, -6);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 10, 5, -6);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 10, 9, -6);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 10, 10, -6);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 10, 11, -6);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 19, 1, -15);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 19, 2, -15);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 20, 0, 1);
}

template <class S, class SV>
void test17() {
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcde"), 4, 2, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 5, 0, SV(""), 0, 0, 0);
    test(S("abcde"), 5, 0, SV(""), 0, 1, 0);
    test(S("abcde"), 5, 0, SV(""), 1, 0, 0);
    test(S("abcde"), 5, 0, SV("abcde"), 0, 0, 0);
    test(S("abcde"), 5, 0, SV("abcde"), 0, 1, -1);
    test(S("abcde"), 5, 0, SV("abcde"), 0, 2, -2);
    test(S("abcde"), 5, 0, SV("abcde"), 0, 4, -4);
    test(S("abcde"), 5, 0, SV("abcde"), 0, 5, -5);
    test(S("abcde"), 5, 0, SV("abcde"), 0, 6, -5);
    test(S("abcde"), 5, 0, SV("abcde"), 1, 0, 0);
    test(S("abcde"), 5, 0, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 5, 0, SV("abcde"), 1, 2, -2);
    test(S("abcde"), 5, 0, SV("abcde"), 1, 3, -3);
    test(S("abcde"), 5, 0, SV("abcde"), 1, 4, -4);
    test(S("abcde"), 5, 0, SV("abcde"), 1, 5, -4);
    test(S("abcde"), 5, 0, SV("abcde"), 2, 0, 0);
    test(S("abcde"), 5, 0, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 5, 0, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 5, 0, SV("abcde"), 2, 3, -3);
    test(S("abcde"), 5, 0, SV("abcde"), 2, 4, -3);
    test(S("abcde"), 5, 0, SV("abcde"), 4, 0, 0);
    test(S("abcde"), 5, 0, SV("abcde"), 4, 1, -1);
    test(S("abcde"), 5, 0, SV("abcde"), 4, 2, -1);
    test(S("abcde"), 5, 0, SV("abcde"), 5, 0, 0);
    test(S("abcde"), 5, 0, SV("abcde"), 5, 1, 0);
    test(S("abcde"), 5, 0, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcde"), 5, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcde"), 5, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 5, 1, SV(""), 0, 0, 0);
    test(S("abcde"), 5, 1, SV(""), 0, 1, 0);
    test(S("abcde"), 5, 1, SV(""), 1, 0, 0);
    test(S("abcde"), 5, 1, SV("abcde"), 0, 0, 0);
    test(S("abcde"), 5, 1, SV("abcde"), 0, 1, -1);
    test(S("abcde"), 5, 1, SV("abcde"), 0, 2, -2);
    test(S("abcde"), 5, 1, SV("abcde"), 0, 4, -4);
    test(S("abcde"), 5, 1, SV("abcde"), 0, 5, -5);
    test(S("abcde"), 5, 1, SV("abcde"), 0, 6, -5);
    test(S("abcde"), 5, 1, SV("abcde"), 1, 0, 0);
    test(S("abcde"), 5, 1, SV("abcde"), 1, 1, -1);
    test(S("abcde"), 5, 1, SV("abcde"), 1, 2, -2);
    test(S("abcde"), 5, 1, SV("abcde"), 1, 3, -3);
    test(S("abcde"), 5, 1, SV("abcde"), 1, 4, -4);
    test(S("abcde"), 5, 1, SV("abcde"), 1, 5, -4);
    test(S("abcde"), 5, 1, SV("abcde"), 2, 0, 0);
    test(S("abcde"), 5, 1, SV("abcde"), 2, 1, -1);
    test(S("abcde"), 5, 1, SV("abcde"), 2, 2, -2);
    test(S("abcde"), 5, 1, SV("abcde"), 2, 3, -3);
    test(S("abcde"), 5, 1, SV("abcde"), 2, 4, -3);
    test(S("abcde"), 5, 1, SV("abcde"), 4, 0, 0);
    test(S("abcde"), 5, 1, SV("abcde"), 4, 1, -1);
    test(S("abcde"), 5, 1, SV("abcde"), 4, 2, -1);
    test(S("abcde"), 5, 1, SV("abcde"), 5, 0, 0);
}

template <class S, class SV>
void test18() {
    test(S("abcde"), 5, 1, SV("abcde"), 5, 1, 0);
    test(S("abcde"), 5, 1, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 0, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 0, 1, -1);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 0, 5, -5);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 0, 9, -9);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 0, 10, -10);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 0, 11, -10);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 1, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 1, 1, -1);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 1, 4, -4);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 1, 8, -8);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 1, 9, -9);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 1, 10, -9);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 5, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 5, 1, -1);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 5, 2, -2);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 5, 4, -4);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 5, 5, -5);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 5, 6, -5);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 9, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 9, 1, -1);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 9, 2, -1);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 10, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 10, 1, 0);
    test(S("abcde"), 5, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcde"), 5, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcde"), 6, 0, SV(""), 0, 0, 0);
    test(S("abcde"), 6, 0, SV(""), 0, 1, 0);
    test(S("abcde"), 6, 0, SV(""), 1, 0, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 0, 0, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 0, 1, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 0, 2, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 0, 4, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 0, 5, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 0, 6, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 1, 0, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 1, 1, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 1, 2, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 1, 3, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 1, 4, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 1, 5, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 2, 0, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 2, 1, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 2, 2, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 2, 3, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 2, 4, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 4, 0, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 4, 1, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 4, 2, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 5, 0, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 5, 1, 0);
    test(S("abcde"), 6, 0, SV("abcde"), 6, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 0, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 0, 5, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 0, 9, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 0, 10, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 0, 11, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 1, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 1, 4, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 1, 8, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 1, 9, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 1, 10, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 5, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 5, 2, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 5, 4, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 5, 5, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 5, 6, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 9, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 9, 2, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghij"), 11, 0, 0);
}

template <class S, class SV>
void test19() {
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 0, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 0, 10, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 0, 19, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 0, 20, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 0, 21, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 1, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 1, 9, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 1, 18, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 1, 19, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 1, 20, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 10, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 10, 5, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 10, 9, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 10, 10, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 10, 11, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 19, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 19, 2, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcde"), 6, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 0, 0, SV(""), 0, 0, 0);
    test(S("abcdefghij"), 0, 0, SV(""), 0, 1, 0);
    test(S("abcdefghij"), 0, 0, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghij"), 0, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghij"), 0, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 0, 1, SV(""), 0, 0, 1);
    test(S("abcdefghij"), 0, 1, SV(""), 0, 1, 1);
}

template <class S, class SV>
void test20() {
    test(S("abcdefghij"), 0, 1, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 0, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 0, 1, 0);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 0, 2, -1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 0, 4, -3);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 0, 5, -4);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 0, 6, -4);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 1, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 1, 2, -1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 1, 3, -1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 1, 4, -1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 1, 5, -1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 2, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 2, 1, -2);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 2, 3, -2);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 2, 4, -2);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 4, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 4, 1, -4);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 4, 2, -4);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 5, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 5, 1, 1);
    test(S("abcdefghij"), 0, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 0, 1, 0);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 0, 5, -4);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 0, 9, -8);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 0, 10, -9);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 0, 11, -9);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 1, 0);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 10, -9);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 19, -18);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 20, -19);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 21, -19);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcdefghij"), 0, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 0, 5, SV(""), 0, 0, 5);
    test(S("abcdefghij"), 0, 5, SV(""), 0, 1, 5);
    test(S("abcdefghij"), 0, 5, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 0, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 0, 1, 4);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 0, 2, 3);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 0, 4, 1);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 0, 5, 0);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 0, 6, 0);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 1, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 1, 2, -1);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 1, 3, -1);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 1, 4, -1);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 1, 5, -1);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 2, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 2, 1, -2);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 2, 3, -2);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 2, 4, -2);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 4, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 4, 1, -4);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 4, 2, -4);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 5, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 5, 1, 5);
    test(S("abcdefghij"), 0, 5, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 0, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 0, 1, 4);
}

template <class S, class SV>
void test21() {
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 0, 5, 0);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 0, 9, -4);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 0, 10, -5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 0, 11, -5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 1, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 5, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 9, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 10, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 10, 1, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 1, 4);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 10, -5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 19, -14);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 20, -15);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 0, 21, -15);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 19, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 20, 0, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 20, 1, 5);
    test(S("abcdefghij"), 0, 5, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 0, 9, SV(""), 0, 0, 9);
    test(S("abcdefghij"), 0, 9, SV(""), 0, 1, 9);
    test(S("abcdefghij"), 0, 9, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 0, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 0, 1, 8);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 0, 2, 7);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 0, 4, 5);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 0, 5, 4);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 0, 6, 4);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 1, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 1, 2, -1);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 1, 3, -1);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 1, 4, -1);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 1, 5, -1);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 2, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 2, 1, -2);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 2, 3, -2);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 2, 4, -2);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 4, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 4, 1, -4);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 4, 2, -4);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 5, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 5, 1, 9);
    test(S("abcdefghij"), 0, 9, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 0, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 0, 1, 8);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 0, 5, 4);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 0, 9, 0);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 0, 10, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 0, 11, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 1, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 5, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 9, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 10, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 10, 1, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 0, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 0, 1, 8);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 0, 10, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 0, 19, -10);
}

template <class S, class SV>
void test22() {
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 0, 20, -11);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 0, 21, -11);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 1, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 10, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 19, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 20, 0, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 20, 1, 9);
    test(S("abcdefghij"), 0, 9, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 0, 10, SV(""), 0, 0, 10);
    test(S("abcdefghij"), 0, 10, SV(""), 0, 1, 10);
    test(S("abcdefghij"), 0, 10, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 0, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 0, 1, 9);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 0, 2, 8);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 0, 4, 6);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 0, 5, 5);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 0, 6, 5);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 1, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 1, 2, -1);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 1, 3, -1);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 1, 4, -1);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 1, 5, -1);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 2, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 2, 1, -2);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 2, 3, -2);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 2, 4, -2);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 4, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 4, 1, -4);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 4, 2, -4);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 5, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 5, 1, 10);
    test(S("abcdefghij"), 0, 10, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 0, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 0, 1, 9);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 0, 5, 5);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 0, 10, 0);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 0, 11, 0);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 1, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 5, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 9, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 10, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 10, 1, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 1, 9);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 10, 0);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 19, -9);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 20, -10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 21, -10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 19, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 20, 0, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 20, 1, 10);
    test(S("abcdefghij"), 0, 10, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 0, 11, SV(""), 0, 0, 10);
    test(S("abcdefghij"), 0, 11, SV(""), 0, 1, 10);
    test(S("abcdefghij"), 0, 11, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 0, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 0, 1, 9);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 0, 2, 8);
}

template <class S, class SV>
void test23() {
    test(S("abcdefghij"), 0, 11, SV("abcde"), 0, 4, 6);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 0, 5, 5);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 0, 6, 5);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 1, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 1, 2, -1);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 1, 3, -1);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 1, 4, -1);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 1, 5, -1);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 2, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 2, 1, -2);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 2, 3, -2);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 2, 4, -2);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 4, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 4, 1, -4);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 4, 2, -4);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 5, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 5, 1, 10);
    test(S("abcdefghij"), 0, 11, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 0, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 0, 1, 9);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 0, 5, 5);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 0, 10, 0);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 0, 11, 0);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 1, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 5, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 9, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 10, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 10, 1, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 0, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 0, 1, 9);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 0, 10, 0);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 0, 19, -9);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 0, 20, -10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 0, 21, -10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 1, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 1, 18, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 1, 19, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 1, 20, -1);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 10, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 10, 1, -10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 10, 5, -10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 10, 9, -10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 19, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 19, 1, -19);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 19, 2, -19);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 20, 0, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 20, 1, 10);
    test(S("abcdefghij"), 0, 11, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 1, 0, SV(""), 0, 0, 0);
    test(S("abcdefghij"), 1, 0, SV(""), 0, 1, 0);
    test(S("abcdefghij"), 1, 0, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghij"), 1, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 0, 11, -10);
}

template <class S, class SV>
void test24() {
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghij"), 1, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 1, 1, SV(""), 0, 0, 1);
    test(S("abcdefghij"), 1, 1, SV(""), 0, 1, 1);
    test(S("abcdefghij"), 1, 1, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 0, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 0, 1, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 0, 2, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 0, 4, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 0, 5, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 0, 6, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 1, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 1, 1, 0);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 1, 2, -1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 1, 3, -2);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 1, 4, -3);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 1, 5, -3);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 2, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 2, 2, -1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 2, 3, -1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 2, 4, -1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 4, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 4, 1, -3);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 4, 2, -3);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 5, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 5, 1, 1);
    test(S("abcdefghij"), 1, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 1, 1, 0);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 1, 4, -3);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 1, 8, -7);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 1, 9, -8);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 1, 10, -8);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 1, 0);
}

template <class S, class SV>
void test25() {
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 9, -8);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 18, -17);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 19, -18);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 20, -18);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcdefghij"), 1, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 1, 4, SV(""), 0, 0, 4);
    test(S("abcdefghij"), 1, 4, SV(""), 0, 1, 4);
    test(S("abcdefghij"), 1, 4, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 0, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 0, 1, 1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 0, 2, 1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 0, 4, 1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 0, 5, 1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 0, 6, 1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 1, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 1, 1, 3);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 1, 2, 2);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 1, 3, 1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 1, 4, 0);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 1, 5, 0);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 2, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 2, 2, -1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 2, 3, -1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 2, 4, -1);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 4, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 4, 1, -3);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 4, 2, -3);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 5, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 5, 1, 4);
    test(S("abcdefghij"), 1, 4, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 0, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 1, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 1, 1, 3);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 1, 4, 0);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 1, 8, -4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 1, 9, -5);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 1, 10, -5);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 5, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 9, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 10, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 10, 1, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 1, 3);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 9, -5);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 18, -14);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 19, -15);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 1, 20, -15);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 19, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 20, 0, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 20, 1, 4);
    test(S("abcdefghij"), 1, 4, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 1, 8, SV(""), 0, 0, 8);
    test(S("abcdefghij"), 1, 8, SV(""), 0, 1, 8);
    test(S("abcdefghij"), 1, 8, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 0, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 0, 1, 1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 0, 2, 1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 0, 4, 1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 0, 5, 1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 0, 6, 1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 1, 0, 8);
}

template <class S, class SV>
void test26() {
    test(S("abcdefghij"), 1, 8, SV("abcde"), 1, 1, 7);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 1, 2, 6);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 1, 3, 5);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 1, 4, 4);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 1, 5, 4);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 2, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 2, 2, -1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 2, 3, -1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 2, 4, -1);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 4, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 4, 1, -3);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 4, 2, -3);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 5, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 5, 1, 8);
    test(S("abcdefghij"), 1, 8, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 0, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 1, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 1, 1, 7);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 1, 4, 4);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 1, 8, 0);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 5, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 9, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 10, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 10, 1, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 0, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 1, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 1, 1, 7);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 1, 18, -10);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 1, 19, -11);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 1, 20, -11);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 10, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 19, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 20, 0, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 20, 1, 8);
    test(S("abcdefghij"), 1, 8, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 1, 9, SV(""), 0, 0, 9);
    test(S("abcdefghij"), 1, 9, SV(""), 0, 1, 9);
    test(S("abcdefghij"), 1, 9, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 0, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 0, 1, 1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 0, 2, 1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 0, 4, 1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 0, 5, 1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 0, 6, 1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 1, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 1, 1, 8);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 1, 2, 7);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 1, 3, 6);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 1, 4, 5);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 1, 5, 5);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 2, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 2, 2, -1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 2, 3, -1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 2, 4, -1);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 4, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 4, 1, -3);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 4, 2, -3);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 5, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 5, 1, 9);
    test(S("abcdefghij"), 1, 9, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 0, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 1, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 1, 1, 8);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 1, 4, 5);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 1, 8, 1);
}

template <class S, class SV>
void test27() {
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 1, 9, 0);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 1, 10, 0);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 5, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 9, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 10, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 10, 1, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 1, 8);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 9, 0);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 18, -9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 19, -10);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 20, -10);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 19, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 20, 0, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 20, 1, 9);
    test(S("abcdefghij"), 1, 9, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 1, 10, SV(""), 0, 0, 9);
    test(S("abcdefghij"), 1, 10, SV(""), 0, 1, 9);
    test(S("abcdefghij"), 1, 10, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 0, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 0, 1, 1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 0, 2, 1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 0, 4, 1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 0, 5, 1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 0, 6, 1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 1, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 1, 1, 8);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 1, 2, 7);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 1, 3, 6);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 1, 4, 5);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 1, 5, 5);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 2, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 2, 2, -1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 2, 3, -1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 2, 4, -1);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 4, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 4, 1, -3);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 4, 2, -3);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 5, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 5, 1, 9);
    test(S("abcdefghij"), 1, 10, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 0, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 1, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 1, 1, 8);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 1, 4, 5);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 1, 8, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 1, 9, 0);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 1, 10, 0);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 5, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 9, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 10, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 10, 1, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 0, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 1, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 1, 1, 8);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 1, 9, 0);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 1, 18, -9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 1, 19, -10);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 1, 20, -10);
}

template <class S, class SV>
void test28() {
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 10, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 10, 1, -9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 10, 5, -9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 10, 10, -9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 10, 11, -9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 19, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 19, 1, -18);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 19, 2, -18);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 20, 0, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 20, 1, 9);
    test(S("abcdefghij"), 1, 10, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 5, 0, SV(""), 0, 0, 0);
    test(S("abcdefghij"), 5, 0, SV(""), 0, 1, 0);
    test(S("abcdefghij"), 5, 0, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghij"), 5, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghij"), 5, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 5, 1, SV(""), 0, 0, 1);
    test(S("abcdefghij"), 5, 1, SV(""), 0, 1, 1);
    test(S("abcdefghij"), 5, 1, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 0, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 0, 1, 5);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 0, 2, 5);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 0, 4, 5);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 0, 5, 5);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 0, 6, 5);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 1, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 1, 1, 4);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 1, 2, 4);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 1, 3, 4);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 1, 4, 4);
}

template <class S, class SV>
void test29() {
    test(S("abcdefghij"), 5, 1, SV("abcde"), 1, 5, 4);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 2, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 2, 1, 3);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 2, 2, 3);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 2, 3, 3);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 2, 4, 3);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 4, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 4, 1, 1);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 4, 2, 1);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 5, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 5, 1, 1);
    test(S("abcdefghij"), 5, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 0, 1, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 0, 5, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 0, 9, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 0, 10, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 0, 11, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 1, 1, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 1, 4, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 1, 8, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 1, 9, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 1, 10, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 5, 1, 0);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 5, 2, -1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 5, 4, -3);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 9, 1, -4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 9, 2, -4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 1, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 10, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 19, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 20, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 0, 21, 5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 1, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 9, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 18, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 19, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 1, 20, 4);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 1, -5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 9, -5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 10, -5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 10, 11, -5);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 19, 1, -14);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 19, 2, -14);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcdefghij"), 5, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 5, 2, SV(""), 0, 0, 2);
    test(S("abcdefghij"), 5, 2, SV(""), 0, 1, 2);
    test(S("abcdefghij"), 5, 2, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 0, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 0, 1, 5);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 0, 2, 5);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 0, 4, 5);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 0, 5, 5);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 0, 6, 5);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 1, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 1, 1, 4);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 1, 2, 4);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 1, 3, 4);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 1, 4, 4);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 1, 5, 4);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 2, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 2, 1, 3);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 2, 2, 3);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 2, 3, 3);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 2, 4, 3);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 4, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 4, 1, 1);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 4, 2, 1);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 5, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 5, 1, 2);
    test(S("abcdefghij"), 5, 2, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 0, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 0, 1, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 0, 5, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 0, 9, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 0, 10, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 0, 11, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 1, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 1, 1, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 1, 4, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 1, 8, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 1, 9, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 1, 10, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 5, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 5, 1, 1);
}

template <class S, class SV>
void test30() {
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 5, 2, 0);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 5, 4, -2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 5, 5, -3);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 5, 6, -3);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 9, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 9, 1, -4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 9, 2, -4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 10, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 10, 1, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 0, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 0, 1, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 0, 10, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 0, 19, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 0, 20, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 0, 21, 5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 1, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 1, 1, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 1, 9, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 1, 18, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 1, 19, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 1, 20, 4);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 10, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 10, 1, -5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 10, 9, -5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 10, 10, -5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 10, 11, -5);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 19, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 19, 1, -14);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 19, 2, -14);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 20, 0, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 20, 1, 2);
    test(S("abcdefghij"), 5, 2, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 5, 4, SV(""), 0, 0, 4);
    test(S("abcdefghij"), 5, 4, SV(""), 0, 1, 4);
    test(S("abcdefghij"), 5, 4, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 0, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 0, 1, 5);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 0, 2, 5);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 0, 4, 5);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 0, 5, 5);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 0, 6, 5);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 1, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 1, 1, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 1, 2, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 1, 3, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 1, 4, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 1, 5, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 2, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 2, 1, 3);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 2, 2, 3);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 2, 3, 3);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 2, 4, 3);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 4, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 4, 1, 1);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 4, 2, 1);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 5, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 5, 1, 4);
    test(S("abcdefghij"), 5, 4, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 0, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 0, 1, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 0, 5, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 0, 9, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 0, 10, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 0, 11, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 1, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 1, 1, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 1, 4, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 1, 8, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 1, 9, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 1, 10, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 5, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 5, 1, 3);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 5, 2, 2);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 5, 4, 0);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 5, 5, -1);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 5, 6, -1);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 9, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 9, 1, -4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 9, 2, -4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 10, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 10, 1, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 0, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 0, 1, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 0, 10, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 0, 19, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 0, 20, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 0, 21, 5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 1, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 1, 1, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 1, 9, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 1, 18, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 1, 19, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 1, 20, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 10, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 10, 1, -5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 10, 9, -5);
}

template <class S, class SV>
void test31() {
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 10, 10, -5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 10, 11, -5);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 19, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 19, 1, -14);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 19, 2, -14);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 20, 0, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 20, 1, 4);
    test(S("abcdefghij"), 5, 4, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 5, 5, SV(""), 0, 0, 5);
    test(S("abcdefghij"), 5, 5, SV(""), 0, 1, 5);
    test(S("abcdefghij"), 5, 5, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 0, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 0, 1, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 0, 2, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 0, 4, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 0, 5, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 0, 6, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 1, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 1, 1, 4);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 1, 2, 4);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 1, 3, 4);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 1, 4, 4);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 1, 5, 4);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 2, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 2, 1, 3);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 2, 2, 3);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 2, 3, 3);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 2, 4, 3);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 4, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 4, 1, 1);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 4, 2, 1);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 5, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 5, 1, 5);
    test(S("abcdefghij"), 5, 5, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 0, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 0, 1, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 0, 5, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 0, 9, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 0, 10, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 0, 11, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 1, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 1, 1, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 1, 4, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 1, 8, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 1, 9, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 1, 10, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 5, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 5, 1, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 5, 2, 3);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 5, 4, 1);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 5, 5, 0);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 5, 6, 0);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 9, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 9, 1, -4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 9, 2, -4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 10, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 10, 1, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 0, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 0, 1, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 0, 10, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 0, 19, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 0, 20, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 0, 21, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 1, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 1, 1, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 1, 9, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 1, 18, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 1, 19, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 1, 20, 4);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 10, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 10, 1, -5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 10, 9, -5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 10, 10, -5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 10, 11, -5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 19, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 19, 1, -14);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 19, 2, -14);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 20, 0, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 20, 1, 5);
    test(S("abcdefghij"), 5, 5, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 5, 6, SV(""), 0, 0, 5);
    test(S("abcdefghij"), 5, 6, SV(""), 0, 1, 5);
    test(S("abcdefghij"), 5, 6, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 0, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 0, 1, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 0, 2, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 0, 4, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 0, 5, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 0, 6, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 1, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 1, 1, 4);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 1, 2, 4);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 1, 3, 4);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 1, 4, 4);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 1, 5, 4);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 2, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 2, 1, 3);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 2, 2, 3);
}

template <class S, class SV>
void test32() {
    test(S("abcdefghij"), 5, 6, SV("abcde"), 2, 3, 3);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 2, 4, 3);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 4, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 4, 1, 1);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 4, 2, 1);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 5, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 5, 1, 5);
    test(S("abcdefghij"), 5, 6, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 0, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 0, 1, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 0, 5, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 0, 9, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 0, 10, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 0, 11, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 1, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 1, 1, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 1, 4, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 1, 8, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 1, 9, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 1, 10, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 5, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 5, 1, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 5, 2, 3);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 5, 4, 1);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 5, 5, 0);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 5, 6, 0);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 9, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 9, 1, -4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 9, 2, -4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 10, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 10, 1, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 0, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 0, 1, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 0, 10, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 0, 19, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 0, 20, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 0, 21, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 1, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 1, 1, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 1, 9, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 1, 18, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 1, 19, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 1, 20, 4);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 10, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 10, 1, -5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 10, 9, -5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 10, 10, -5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 10, 11, -5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 19, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 19, 1, -14);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 19, 2, -14);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 20, 0, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 20, 1, 5);
    test(S("abcdefghij"), 5, 6, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 9, 0, SV(""), 0, 0, 0);
    test(S("abcdefghij"), 9, 0, SV(""), 0, 1, 0);
    test(S("abcdefghij"), 9, 0, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghij"), 9, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 5, 6, -5);
}

template <class S, class SV>
void test33() {
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghij"), 9, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 9, 1, SV(""), 0, 0, 1);
    test(S("abcdefghij"), 9, 1, SV(""), 0, 1, 1);
    test(S("abcdefghij"), 9, 1, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 0, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 0, 1, 9);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 0, 2, 9);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 0, 4, 9);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 0, 5, 9);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 0, 6, 9);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 1, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 1, 1, 8);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 1, 2, 8);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 1, 3, 8);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 1, 4, 8);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 1, 5, 8);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 2, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 2, 1, 7);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 2, 2, 7);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 2, 3, 7);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 2, 4, 7);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 4, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 4, 1, 5);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 4, 2, 5);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 5, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 5, 1, 1);
    test(S("abcdefghij"), 9, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 0, 1, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 0, 5, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 0, 9, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 0, 10, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 0, 11, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 1, 1, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 1, 4, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 1, 8, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 1, 9, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 1, 10, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 5, 1, 4);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 5, 2, 4);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 5, 4, 4);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 5, 5, 4);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 5, 6, 4);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 9, 1, 0);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 9, 2, 0);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 0, 1, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 0, 10, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 0, 19, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 0, 20, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 0, 21, 9);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 1, 1, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 1, 9, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 1, 18, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 1, 19, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 1, 20, 8);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 10, 5, -1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 10, 9, -1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 10, 10, -1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 10, 11, -1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 19, 1, -10);
}

template <class S, class SV>
void test34() {
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 19, 2, -10);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcdefghij"), 9, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 9, 2, SV(""), 0, 0, 1);
    test(S("abcdefghij"), 9, 2, SV(""), 0, 1, 1);
    test(S("abcdefghij"), 9, 2, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 0, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 0, 1, 9);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 0, 2, 9);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 0, 4, 9);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 0, 5, 9);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 0, 6, 9);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 1, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 1, 1, 8);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 1, 2, 8);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 1, 3, 8);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 1, 4, 8);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 1, 5, 8);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 2, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 2, 1, 7);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 2, 2, 7);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 2, 3, 7);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 2, 4, 7);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 4, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 4, 1, 5);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 4, 2, 5);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 5, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 5, 1, 1);
    test(S("abcdefghij"), 9, 2, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 0, 1, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 0, 5, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 0, 9, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 0, 10, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 0, 11, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 1, 1, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 1, 4, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 1, 8, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 1, 9, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 1, 10, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 5, 1, 4);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 5, 2, 4);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 5, 4, 4);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 5, 5, 4);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 5, 6, 4);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 9, 1, 0);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 9, 2, 0);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 0, 1, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 0, 10, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 0, 19, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 0, 20, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 0, 21, 9);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 1, 1, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 1, 9, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 1, 18, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 1, 19, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 1, 20, 8);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 10, 5, -1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 10, 9, -1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 10, 10, -1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 10, 11, -1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 19, 1, -10);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 19, 2, -10);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcdefghij"), 9, 2, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 10, 0, SV(""), 0, 0, 0);
    test(S("abcdefghij"), 10, 0, SV(""), 0, 1, 0);
    test(S("abcdefghij"), 10, 0, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 4, 1, -1);
}

template <class S, class SV>
void test35() {
    test(S("abcdefghij"), 10, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghij"), 10, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghij"), 10, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 10, 1, SV(""), 0, 0, 0);
    test(S("abcdefghij"), 10, 1, SV(""), 0, 1, 0);
    test(S("abcdefghij"), 10, 1, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 0, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 0, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 0, 2, -2);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 0, 4, -4);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 0, 5, -5);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 0, 6, -5);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 1, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 1, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 1, 2, -2);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 1, 3, -3);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 1, 4, -4);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 1, 5, -4);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 2, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 2, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 2, 2, -2);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 2, 3, -3);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 2, 4, -3);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 4, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 4, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 4, 2, -1);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 5, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 5, 1, 0);
    test(S("abcdefghij"), 10, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 10, 0, 0);
}

template <class S, class SV>
void test36() {
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 10, -10);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 19, -19);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 20, -20);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 21, -20);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 18, -18);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 19, -19);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 20, -19);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 5, -5);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 9, -9);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 10, -10);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 11, -10);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 19, 1, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 19, 2, -1);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghij"), 10, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghij"), 11, 0, SV(""), 0, 0, 0);
    test(S("abcdefghij"), 11, 0, SV(""), 0, 1, 0);
    test(S("abcdefghij"), 11, 0, SV(""), 1, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 0, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 0, 2, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 0, 4, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 0, 5, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 0, 6, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 1, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 1, 2, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 1, 3, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 1, 4, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 1, 5, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 2, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 2, 2, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 2, 3, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 2, 4, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 4, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 4, 2, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 0, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 0, 5, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 0, 9, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 0, 10, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 0, 11, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 1, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 1, 4, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 1, 8, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 1, 9, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 1, 10, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 5, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 5, 2, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 5, 4, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 5, 5, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 5, 6, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 9, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 9, 2, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 0, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 0, 10, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 0, 19, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 0, 20, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 0, 21, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 1, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 1, 9, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 1, 18, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 1, 19, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 1, 20, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 10, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 10, 5, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 10, 9, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 10, 10, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 10, 11, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 19, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 19, 2, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghij"), 11, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
}

template <class S, class SV>
void test37() {
    test(S("abcdefghijklmnopqrst"), 0, 0, SV(""), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV(""), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 20,
         -20);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 0, 21,
         -20);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 18,
         -18);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 1, 20,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 5,
         -5);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 19, 2,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghijklmnopqrst"), 0, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV(""), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV(""), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 0, 2, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 0, 4, -3);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 0, 5, -4);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 0, 6, -4);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 1, 2, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 1, 3, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 1, 5, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 2, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 2, 1, -2);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 2, 3, -2);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 2, 4, -2);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 4, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 4, 1, -4);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 4, 2, -4);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 5, 1, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcde"), 6, 0, 0);
}

template <class S, class SV>
void test38() {
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 0, 5, -4);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 0, 9, -8);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 0, 10, -9);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 0, 11, -9);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 10,
         -9);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 19,
         -18);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 20,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 0, 21,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 9, -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 18,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 19,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 1, 20,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 1,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 5,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 9,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 1,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 19, 2,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcdefghijklmnopqrst"), 0, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV(""), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV(""), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 0, 1, 9);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 0, 2, 8);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 0, 4, 6);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 0, 5, 5);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 0, 6, 5);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 1, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 1, 2, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 1, 3, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 1, 5, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 2, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 2, 1, -2);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 2, 3, -2);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 2, 4, -2);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 4, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 4, 1, -4);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 4, 2, -4);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 5, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 5, 1, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 0, 1, 9);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 0, 5, 5);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 0, 10, 0);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 0, 11, 0);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 1, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 5, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 9, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 10, 0, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 10, 1, 10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 1, 9);
}

template <class S, class SV>
void test39() {
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 10,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 19,
         -9);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 20,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 0, 21,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 9,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 18,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 19,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 1, 20,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 1,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 5,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 9,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 19, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 19, 1,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 19, 2,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 20, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 20, 1,
         10);
    test(S("abcdefghijklmnopqrst"), 0, 10, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV(""), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV(""), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 0, 1, 18);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 0, 2, 17);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 0, 4, 15);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 0, 5, 14);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 0, 6, 14);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 1, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 1, 2, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 1, 3, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 1, 5, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 2, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 2, 1, -2);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 2, 3, -2);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 2, 4, -2);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 4, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 4, 1, -4);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 4, 2, -4);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 5, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 5, 1, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 0, 1, 18);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 0, 5, 14);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 0, 9, 10);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 0, 10, 9);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 0, 11, 9);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 1, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 5, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 9, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 10, 0, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 10, 1, 19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 0, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 0, 1,
         18);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 0, 10,
         9);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 0, 19,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 0, 20,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 0, 21,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 1, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 1, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 1, 9,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 1, 18,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 1, 19,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 1, 20,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 10, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 10, 1,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 10, 5,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 10, 9,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 19, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 19, 1,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 19, 2,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 20, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 20, 1,
         19);
    test(S("abcdefghijklmnopqrst"), 0, 19, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV(""), 0, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV(""), 0, 1, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 0, 0, 20);
}

template <class S, class SV>
void test40() {
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 0, 2, 18);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 0, 4, 16);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 0, 5, 15);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 0, 6, 15);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 1, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 1, 2, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 1, 3, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 1, 5, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 2, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 2, 1, -2);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 2, 3, -2);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 2, 4, -2);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 4, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 4, 1, -4);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 4, 2, -4);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 5, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 5, 1, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 0, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 0, 5, 15);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 0, 9, 11);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 0, 10, 10);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 0, 11, 10);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 1, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 5, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 9, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 10, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 10, 1, 20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 0, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 0, 1,
         19);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 0, 10,
         10);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 0, 19,
         1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 0, 20,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 0, 21,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 1, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 1, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 1, 9,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 1, 18,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 1, 19,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 1, 20,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 10, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 10, 1,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 10, 5,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 10, 9,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 19, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 19, 1,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 19, 2,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 20, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 20, 1,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 20, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV(""), 0, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV(""), 0, 1, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 0, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 0, 2, 18);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 0, 4, 16);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 0, 5, 15);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 0, 6, 15);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 1, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 1, 2, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 1, 3, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 1, 5, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 2, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 2, 1, -2);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 2, 3, -2);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 2, 4, -2);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 4, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 4, 1, -4);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 4, 2, -4);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 5, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 5, 1, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 0, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 0, 5, 15);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 0, 9, 11);
}

template <class S, class SV>
void test41() {
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 0, 10, 10);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 0, 11, 10);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 1, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 1, 4, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 1, 8, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 1, 9, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 1, 10, -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 5, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 5, 1, -5);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 5, 2, -5);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 5, 4, -5);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 9, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 9, 1, -9);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 9, 2, -9);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 10, 0, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 10, 1, 20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 0, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 0, 1,
         19);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 0, 10,
         10);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 0, 19,
         1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 0, 20,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 0, 21,
         0);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 1, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 1, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 1, 9,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 1, 18,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 1, 19,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 1, 20,
         -1);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 10, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 10, 1,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 10, 5,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 10, 9,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 19, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 19, 1,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 19, 2,
         -19);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 20, 0,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 20, 1,
         20);
    test(S("abcdefghijklmnopqrst"), 0, 21, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV(""), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV(""), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 20,
         -20);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 0, 21,
         -20);
}

template <class S, class SV>
void test42() {
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 9, -9);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 18,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 1, 20,
         -19);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 5,
         -5);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 19, 2,
         -1);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 20, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 20, 1, 0);
    test(S("abcdefghijklmnopqrst"), 1, 0, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV(""), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV(""), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 0, 2, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 0, 4, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 0, 6, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 1, 1, 0);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 1, 2, -1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 1, 3, -2);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 1, 4, -3);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 1, 5, -3);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 2, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 2, 2, -1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 2, 3, -1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 2, 4, -1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 4, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 4, 1, -3);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 4, 2, -3);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 5, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 1, 1, 0);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 1, 4, -3);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 1, 8, -7);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 1, 9, -8);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 1, 10, -8);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 1, 0);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 9, -8);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 18,
         -17);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 19,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 1, 20,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 5,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 10,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 10, 11,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 1,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 19, 2,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 20, 0, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 20, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 1, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV(""), 0, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV(""), 0, 1, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 0, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 0, 2, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 0, 4, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 0, 5, 1);
}

template <class S, class SV>
void test43() {
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 0, 6, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 1, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 1, 1, 8);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 1, 2, 7);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 1, 3, 6);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 1, 4, 5);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 1, 5, 5);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 2, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 2, 2, -1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 2, 3, -1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 2, 4, -1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 4, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 4, 1, -3);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 4, 2, -3);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 5, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 5, 1, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 0, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 1, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 1, 1, 8);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 1, 4, 5);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 1, 8, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 1, 9, 0);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 1, 10, 0);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 5, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 9, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 10, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 10, 1, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 10, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 19, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 20, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 0, 21, 1);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 1, 8);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 9, 0);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 18,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 19,
         -10);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 1, 20,
         -10);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 5,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 10,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 10, 11,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 19, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 19, 1,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 19, 2,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 20, 0, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 20, 1, 9);
    test(S("abcdefghijklmnopqrst"), 1, 9, SV("abcdefghijklmnopqrst"), 21, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV(""), 0, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV(""), 0, 1, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 0, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 0, 2, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 0, 4, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 0, 6, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 1, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 1, 1, 17);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 1, 2, 16);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 1, 3, 15);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 1, 4, 14);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 1, 5, 14);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 2, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 2, 2, -1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 2, 3, -1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 2, 4, -1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 4, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 4, 1, -3);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 4, 2, -3);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 5, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 5, 1, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 0, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 1, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 1, 1, 17);
}

template <class S, class SV>
void test44() {
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 1, 4, 14);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 1, 8, 10);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 1, 10, 9);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 5, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 9, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 10, 0, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 10, 1, 18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 0, 0,
         18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 0, 10,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 0, 19,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 0, 20,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 0, 21,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 1, 0,
         18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 1, 1,
         17);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 1, 18,
         0);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 1, 19,
         -1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 1, 20,
         -1);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 10, 0,
         18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 10, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 10, 5,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 10, 10,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 10, 11,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 19, 0,
         18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 19, 1,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 19, 2,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 20, 0,
         18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 20, 1,
         18);
    test(S("abcdefghijklmnopqrst"), 1, 18, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV(""), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV(""), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 0, 2, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 0, 4, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 0, 6, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 1, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 1, 1, 18);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 1, 2, 17);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 1, 3, 16);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 1, 4, 15);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 1, 5, 15);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 2, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 2, 2, -1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 2, 3, -1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 2, 4, -1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 4, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 4, 1, -3);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 4, 2, -3);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 5, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 5, 1, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 1, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 1, 1, 18);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 1, 4, 15);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 1, 8, 11);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 1, 9, 10);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 1, 10, 10);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 5, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 9, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 10, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 10, 1, 19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 0, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 0, 10,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 0, 19,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 0, 20,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 0, 21,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 1, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 1, 1,
         18);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 1, 9,
         10);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 1, 18,
         1);
}

template <class S, class SV>
void test45() {
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 1, 19,
         0);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 1, 20,
         0);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 10, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 10, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 10, 5,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 10, 10,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 10, 11,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 19, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 19, 1,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 19, 2,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 20, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 20, 1,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 19, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV(""), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV(""), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 0, 2, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 0, 4, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 0, 6, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 1, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 1, 1, 18);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 1, 2, 17);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 1, 3, 16);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 1, 4, 15);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 1, 5, 15);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 2, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 2, 2, -1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 2, 3, -1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 2, 4, -1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 4, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 4, 1, -3);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 4, 2, -3);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 5, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 5, 1, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 0, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 0, 5, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 0, 9, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 0, 10, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 0, 11, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 1, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 1, 1, 18);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 1, 4, 15);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 1, 8, 11);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 1, 9, 10);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 1, 10, 10);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 5, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 5, 1, -4);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 5, 2, -4);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 5, 5, -4);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 5, 6, -4);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 9, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 9, 1, -8);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 9, 2, -8);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 10, 0, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 10, 1, 19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 0, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 0, 10,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 0, 19,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 0, 20,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 0, 21,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 1, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 1, 1,
         18);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 1, 9,
         10);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 1, 18,
         1);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 1, 19,
         0);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 1, 20,
         0);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 10, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 10, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 10, 5,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 10, 10,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 10, 11,
         -9);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 19, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 19, 1,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 19, 2,
         -18);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 20, 0,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 20, 1,
         19);
    test(S("abcdefghijklmnopqrst"), 1, 20, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV(""), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV(""), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 1, 2, -2);
}

template <class S, class SV>
void test46() {
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 20,
         -20);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 0, 21,
         -20);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 18,
         -18);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 1, 20,
         -19);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 5,
         -5);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 19, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 19, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 19, 2,
         -1);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 20, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 20, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 0, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV(""), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV(""), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 0, 2, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 0, 4, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 0, 6, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 1, 2, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 1, 3, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 1, 5, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 2, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 2, 1, 8);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 2, 2, 8);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 2, 3, 8);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 2, 4, 8);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 4, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 4, 1, 6);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 4, 2, 6);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 5, 1, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 0, 9, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 0, 10, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 0, 11, 10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 1, 8, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 1, 10, 9);
}

template <class S, class SV>
void test47() {
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 5, 1, 5);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 5, 2, 5);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 5, 4, 5);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 5, 5, 5);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 5, 6, 5);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 9, 1, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 9, 2, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 1,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 10,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 19,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 20,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 0, 21,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 18,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 19,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 1, 20,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 5,
         -4);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 9,
         -8);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 10,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 10, 11,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 19, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 19, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 19, 2,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 20, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 20, 1,
         1);
    test(S("abcdefghijklmnopqrst"), 10, 1, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV(""), 0, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV(""), 0, 1, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 0, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 0, 2, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 0, 4, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 0, 6, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 1, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 1, 2, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 1, 3, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 1, 5, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 2, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 2, 1, 8);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 2, 2, 8);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 2, 3, 8);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 2, 4, 8);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 4, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 4, 1, 6);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 4, 2, 6);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 5, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 5, 1, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 0, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 0, 9, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 0, 10, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 0, 11, 10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 1, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 1, 8, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 1, 10, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 5, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 5, 1, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 5, 2, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 5, 4, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 5, 5, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 5, 6, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 9, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 9, 1, 1);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 9, 2, 1);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 10, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 10, 1, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 0, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 0, 1,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 0, 10,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 0, 19,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 0, 20,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 0, 21,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 1, 0, 5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 1, 18,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 1, 19,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 1, 20,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 10, 0,
         5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 10, 1,
         4);
}

template <class S, class SV>
void test48() {
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 10, 5,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 10, 9,
         -4);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 10, 10,
         -5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 10, 11,
         -5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 19, 0,
         5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 19, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 19, 2,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 20, 0,
         5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 20, 1,
         5);
    test(S("abcdefghijklmnopqrst"), 10, 5, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV(""), 0, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV(""), 0, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 0, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 0, 2, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 0, 4, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 0, 6, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 1, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 1, 2, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 1, 3, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 1, 5, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 2, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 2, 1, 8);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 2, 2, 8);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 2, 3, 8);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 2, 4, 8);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 4, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 4, 1, 6);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 4, 2, 6);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 5, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 5, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 0, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 0, 9, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 0, 10, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 0, 11, 10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 1, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 1, 8, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 1, 10, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 5, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 5, 1, 5);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 5, 2, 5);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 5, 4, 5);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 5, 5, 5);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 5, 6, 5);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 9, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 9, 1, 1);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 9, 2, 1);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 10, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 10, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 0, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 0, 1,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 0, 10,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 0, 19,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 0, 20,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 0, 21,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 1, 0, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 1, 18,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 1, 19,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 1, 20,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 10, 0,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 10, 1,
         8);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 10, 5,
         4);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 10, 9,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 10, 10,
         -1);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 10, 11,
         -1);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 19, 0,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 19, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 19, 2,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 20, 0,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 20, 1,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 9, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV(""), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV(""), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 0, 2, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 0, 4, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 0, 6, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 1, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 1, 2, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 1, 3, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 1, 5, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 2, 0, 10);
}

template <class S, class SV>
void test49() {
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 2, 1, 8);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 2, 2, 8);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 2, 3, 8);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 2, 4, 8);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 4, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 4, 1, 6);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 4, 2, 6);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 5, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 5, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 0, 9, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 0, 10, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 0, 11, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 1, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 1, 8, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 1, 10, 9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 5, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 5, 1, 5);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 5, 2, 5);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 5, 4, 5);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 5, 5, 5);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 5, 6, 5);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 9, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 9, 1, 1);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 9, 2, 1);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 10, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 10, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 0, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 0, 1,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 0, 10,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 0, 19,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 0, 20,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 0, 21,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 1, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 1, 1,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 1, 9,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 1, 18,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 1, 19,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 1, 20,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 10, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 10, 1,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 10, 5,
         5);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 10, 9,
         1);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 10, 10,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 10, 11,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 19, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 19, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 19, 2,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 20, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 20, 1,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 10, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV(""), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV(""), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 0, 2, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 0, 4, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 0, 6, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 1, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 1, 2, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 1, 3, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 1, 5, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 2, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 2, 1, 8);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 2, 2, 8);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 2, 3, 8);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 2, 4, 8);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 4, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 4, 1, 6);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 4, 2, 6);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 5, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 5, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 0, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 0, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 0, 5, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 0, 9, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 0, 10, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 0, 11, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 1, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 1, 1, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 1, 4, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 1, 8, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 1, 9, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 1, 10, 9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 5, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 5, 1, 5);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 5, 2, 5);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 5, 4, 5);
}

template <class S, class SV>
void test50() {
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 5, 5, 5);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 5, 6, 5);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 9, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 9, 1, 1);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 9, 2, 1);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 10, 0, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 10, 1, 10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 0, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 0, 1,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 0, 10,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 0, 19,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 0, 20,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 0, 21,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 1, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 1, 1,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 1, 9,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 1, 18,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 1, 19,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 1, 20,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 10, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 10, 1,
         9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 10, 5,
         5);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 10, 9,
         1);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 10, 10,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 10, 11,
         0);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 19, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 19, 1,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 19, 2,
         -9);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 20, 0,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 20, 1,
         10);
    test(S("abcdefghijklmnopqrst"), 10, 11, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV(""), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV(""), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 0, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 0, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 0, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 0, 20,
         -20);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 0, 21,
         -20);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 1, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 1, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 1, 18,
         -18);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 1, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 1, 20,
         -19);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 10, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 10, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 10, 5,
         -5);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
}

template <class S, class SV>
void test51() {
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 19, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 19, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 19, 2,
         -1);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 20, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 20, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 0, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV(""), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV(""), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 0, 2, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 0, 4, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 0, 5, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 0, 6, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 1, 1, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 1, 2, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 1, 3, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 1, 4, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 1, 5, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 2, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 2, 1, 17);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 2, 2, 17);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 2, 3, 17);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 2, 4, 17);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 4, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 4, 1, 15);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 4, 2, 15);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 5, 1, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 0, 5, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 0, 9, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 0, 10, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 0, 11, 19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 1, 1, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 1, 4, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 1, 8, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 1, 9, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 1, 10, 18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 5, 1, 14);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 5, 2, 14);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 5, 4, 14);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 5, 5, 14);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 5, 6, 14);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 9, 1, 10);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 9, 2, 10);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 0, 1,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 0, 10,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 0, 19,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 0, 20,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 0, 21,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 1, 1,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 1, 9,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 1, 18,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 1, 19,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 1, 20,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 10, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 10, 1,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 10, 5,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 10, 9,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 10, 10,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 10, 11,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 19, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 19, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 19, 2,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 20, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 20, 1,
         1);
    test(S("abcdefghijklmnopqrst"), 19, 1, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV(""), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV(""), 0, 1, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 0, 2, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 0, 4, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 0, 5, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 0, 6, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 1, 1, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 1, 2, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 1, 3, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 1, 4, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 1, 5, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 2, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 2, 1, 17);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 2, 2, 17);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 2, 3, 17);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 2, 4, 17);
}

template <class S, class SV>
void test52() {
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 4, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 4, 1, 15);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 4, 2, 15);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 5, 1, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 0, 1, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 0, 5, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 0, 9, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 0, 10, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 0, 11, 19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 1, 1, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 1, 4, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 1, 8, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 1, 9, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 1, 10, 18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 5, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 5, 1, 14);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 5, 2, 14);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 5, 4, 14);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 5, 5, 14);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 5, 6, 14);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 9, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 9, 1, 10);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 9, 2, 10);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 10, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 10, 1, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 0, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 0, 1,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 0, 10,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 0, 19,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 0, 20,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 0, 21,
         19);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 1, 0, 1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 1, 1,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 1, 9,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 1, 18,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 1, 19,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 1, 20,
         18);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 10, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 10, 1,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 10, 5,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 10, 9,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 10, 10,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 10, 11,
         9);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 19, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 19, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 19, 2,
         0);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 20, 0,
         1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 20, 1,
         1);
    test(S("abcdefghijklmnopqrst"), 19, 2, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV(""), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV(""), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 0, 2, -2);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 0, 4, -4);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 0, 6, -5);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 1, 2, -2);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 1, 3, -3);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 1, 5, -4);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 2, 3, -3);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 2, 4, -3);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 4, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 4, 2, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 9, 1, -1);
}

template <class S, class SV>
void test53() {
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 0, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 0, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 0, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 0, 20,
         -20);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 0, 21,
         -20);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 1, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 1, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 1, 18,
         -18);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 1, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 1, 20,
         -19);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 10, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 10, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 10, 5,
         -5);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 19, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 19, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 19, 2,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 20, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 20, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 0, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV(""), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV(""), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 0, 2, -2);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 0, 4, -4);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 0, 6, -5);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 1, 2, -2);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 1, 3, -3);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 1, 5, -4);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 2, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 2, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 2, 2, -2);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 2, 3, -3);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 2, 4, -3);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 4, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 4, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 4, 2, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 5, 1, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 0, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 0, 5, -5);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 0, 9, -9);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 0, 10, -10);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 0, 11, -10);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 1, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 1, 4, -4);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 1, 8, -8);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 1, 9, -9);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 1, 10, -9);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 5, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 5, 2, -2);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 5, 4, -4);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 5, 5, -5);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 5, 6, -5);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 9, 1, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 9, 2, -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 0, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 0, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 0, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 0, 20,
         -20);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 0, 21,
         -20);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 1, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 1, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 1, 18,
         -18);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 1, 19,
         -19);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 1, 20,
         -19);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 10, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 10, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 10, 5,
         -5);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 10, 9,
         -9);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 10, 10,
         -10);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 10, 11,
         -10);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 19, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 19, 1,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 19, 2,
         -1);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 20, 0,
         0);
}

template <class S, class SV>
void test54() {
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 20, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 20, 1, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV(""), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV(""), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV(""), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 0, 2, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 0, 4, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 0, 5, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 0, 6, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 1, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 1, 2, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 1, 3, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 1, 4, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 1, 5, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 2, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 2, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 2, 2, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 2, 3, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 2, 4, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 4, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 4, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 4, 2, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 5, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcde"), 6, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 0, 5, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 0, 9, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 0, 10, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 0, 11, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 1, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 1, 4, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 1, 8, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 1, 9, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 1, 10, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 5, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 5, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 5, 2, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 5, 4, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 5, 5, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 5, 6, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 9, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 9, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 9, 2, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 10, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 10, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghij"), 11, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 0, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 0, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 0, 10,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 0, 19,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 0, 20,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 0, 21,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 1, 0, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 1, 1, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 1, 9, 0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 1, 18,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 1, 19,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 1, 20,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 10, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 10, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 10, 5,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 10, 9,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 10, 10,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 10, 11,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 19, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 19, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 19, 2,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 20, 0,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 20, 1,
         0);
    test(S("abcdefghijklmnopqrst"), 21, 0, SV("abcdefghijklmnopqrst"), 21, 0,
         0);
}

template <class S, class SV>
void test55() {
    test_npos(S(""), 0, 0, SV(""), 0, 0);
    test_npos(S(""), 0, 0, SV("abcde"), 0, -5);
    test_npos(S("abcde"), 0, 0, SV("abcdefghij"), 0, -10);
    test_npos(S("abcde"), 0, 0, SV("abcdefghij"), 1, -9);
    test_npos(S("abcde"), 0, 0, SV("abcdefghij"), 5, -5);
}

int main() {
    {
        typedef std::string S;
        typedef std::string_view SV;
        test0<S, SV>();
        test1<S, SV>();
        test2<S, SV>();
        test3<S, SV>();
        test4<S, SV>();
        test5<S, SV>();
        test6<S, SV>();
        test7<S, SV>();
        test8<S, SV>();
        test9<S, SV>();
        test10<S, SV>();
        test11<S, SV>();
        test12<S, SV>();
        test13<S, SV>();
        test14<S, SV>();
        test15<S, SV>();
        test16<S, SV>();
        test17<S, SV>();
        test18<S, SV>();
        test19<S, SV>();
        test20<S, SV>();
        test21<S, SV>();
        test22<S, SV>();
        test23<S, SV>();
        test24<S, SV>();
        test25<S, SV>();
        test26<S, SV>();
        test27<S, SV>();
        test28<S, SV>();
        test29<S, SV>();
        test30<S, SV>();
        test31<S, SV>();
        test32<S, SV>();
        test33<S, SV>();
        test34<S, SV>();
        test35<S, SV>();
        test36<S, SV>();
        test37<S, SV>();
        test38<S, SV>();
        test39<S, SV>();
        test40<S, SV>();
        test41<S, SV>();
        test42<S, SV>();
        test43<S, SV>();
        test44<S, SV>();
        test45<S, SV>();
        test46<S, SV>();
        test47<S, SV>();
        test48<S, SV>();
        test49<S, SV>();
        test50<S, SV>();
        test51<S, SV>();
        test52<S, SV>();
        test53<S, SV>();
        test54<S, SV>();
        test55<S, SV>();
    }
#if TEST_STD_VER >= 11
    {
        typedef std::basic_string<char, std::char_traits<char>,
                                  min_allocator<char>>
            S;
        typedef std::basic_string_view<char, std::char_traits<char>> SV;
        test0<S, SV>();
        test1<S, SV>();
        test2<S, SV>();
        test3<S, SV>();
        test4<S, SV>();
        test5<S, SV>();
        test6<S, SV>();
        test7<S, SV>();
        test8<S, SV>();
        test9<S, SV>();
        test10<S, SV>();
        test11<S, SV>();
        test12<S, SV>();
        test13<S, SV>();
        test14<S, SV>();
        test15<S, SV>();
        test16<S, SV>();
        test17<S, SV>();
        test18<S, SV>();
        test19<S, SV>();
        test20<S, SV>();
        test21<S, SV>();
        test22<S, SV>();
        test23<S, SV>();
        test24<S, SV>();
        test25<S, SV>();
        test26<S, SV>();
        test27<S, SV>();
        test28<S, SV>();
        test29<S, SV>();
        test30<S, SV>();
        test31<S, SV>();
        test32<S, SV>();
        test33<S, SV>();
        test34<S, SV>();
        test35<S, SV>();
        test36<S, SV>();
        test37<S, SV>();
        test38<S, SV>();
        test39<S, SV>();
        test40<S, SV>();
        test41<S, SV>();
        test42<S, SV>();
        test43<S, SV>();
        test44<S, SV>();
        test45<S, SV>();
        test46<S, SV>();
        test47<S, SV>();
        test48<S, SV>();
        test49<S, SV>();
        test50<S, SV>();
        test51<S, SV>();
        test52<S, SV>();
        test53<S, SV>();
        test54<S, SV>();
        test55<S, SV>();
    }
#endif
    {
        typedef std::string S;
        typedef std::string_view SV;
        S s = "MNOP";
        SV sv = "CDEF";
        char arr[] = "MNOP";

        //  calls compare(pos, n1, const char *, 0)
        assert(s.compare(0, 4, "QRST", 0) > 0);

        //  calls compare(pos, n1, string("QRST"), 0, npos)
        assert(s.compare(0, 4, "QRST", 0, std::string::npos) < 0);

        //  calls compare(pos, n1, T, 0, npos)
        assert(s.compare(0, 4, sv, 0) > 0);

        //  calls compare(pos, n1, T, 0, npos)
        assert(s.compare(0, 4, sv, 0, std::string::npos) > 0);

        // calls compare(pos, n1, const char *, 0)
        assert(s.compare(0, 4, arr, 0) > 0);

        //  calls compare(size, size, string(arr), 0, npos)
        assert(s.compare(0, 4, arr, 0, std::string::npos) == 0);
    }
}
