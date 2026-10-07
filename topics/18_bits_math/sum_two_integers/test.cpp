#include <sum_two_integers.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <climits>

TEST_CASE("examples") {
    CHECK(getSum(1, 2) == 3);
    CHECK(getSum(-1, 1) == 0);
    CHECK(getSum(INT_MAX, INT_MIN) == -1);
}

TEST_CASE("edge cases") {
    SUBCASE("zeros") {
        CHECK(getSum(0, 0) == 0);
        CHECK(getSum(0, 5) == 5);
        CHECK(getSum(-7, 0) == -7);
    }
    SUBCASE("both negative") {
        CHECK(getSum(-2, -3) == -5);
        CHECK(getSum(-100, -23) == -123);
    }
    SUBCASE("mixed signs") {
        CHECK(getSum(5, -3) == 2);
        CHECK(getSum(-5, 3) == -2);
        CHECK(getSum(3, -5) == -2);
        CHECK(getSum(20, -20) == 0);
    }
    SUBCASE("-1 and 1") {
        CHECK(getSum(-1, 1) == 0);
        CHECK(getSum(1, -1) == 0);
    }
    SUBCASE("INT_MAX + INT_MIN is -1") {
        CHECK(getSum(INT_MAX, INT_MIN) == -1);
        CHECK(getSum(INT_MIN, INT_MAX) == -1);
    }
    SUBCASE("sums at the edges of int that do not overflow") {
        CHECK(getSum(INT_MAX, 0) == INT_MAX);
        CHECK(getSum(INT_MAX - 1, 1) == INT_MAX);
        CHECK(getSum(INT_MIN, 0) == INT_MIN);
        CHECK(getSum(INT_MIN + 1, -1) == INT_MIN);
        CHECK(getSum(INT_MIN, 1) == INT_MIN + 1);
    }
    SUBCASE("long carry chains") {
        CHECK(getSum(0x7FFFFFFF, 0) == 0x7FFFFFFF);
        CHECK(getSum(0x3FFFFFFF, 1) == 0x40000000);
        CHECK(getSum(-1, -1) == -2);
    }
}

TEST_CASE("randomized vs the + operator") {
    for (int trial = 0; trial < 500; ++trial) {
        int a = rand_int(-1'000'000'000, 1'000'000'000);
        int b = rand_int(-1'000'000'000, 1'000'000'000);
        if (trial % 4 == 0) {
            a = rand_int(-100, 100);
            b = rand_int(-100, 100);
        }
        CAPTURE(a);
        CAPTURE(b);
        CHECK(getSum(a, b) == a + b);  // |a + b| <= 2e9 < 2^31, so no overflow
    }
}
