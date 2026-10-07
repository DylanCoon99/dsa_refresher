#include <bounds.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

namespace {
std::size_t std_lower(const std::vector<int>& a, int x) {
    return static_cast<std::size_t>(std::lower_bound(a.begin(), a.end(), x) - a.begin());
}
std::size_t std_upper(const std::vector<int>& a, int x) {
    return static_cast<std::size_t>(std::upper_bound(a.begin(), a.end(), x) - a.begin());
}
void check_both(const std::vector<int>& a, int x) {
    CHECK(lowerBound(a, x) == std_lower(a, x));
    CHECK(upperBound(a, x) == std_upper(a, x));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(lowerBound({1, 2, 2, 2, 5}, 2) == 1);
    CHECK(upperBound({1, 2, 2, 2, 5}, 2) == 4);
    CHECK(lowerBound({1, 2, 2, 2, 5}, 3) == 4);
    CHECK(upperBound({1, 2, 2, 2, 5}, 3) == 4);
    CHECK(lowerBound({}, 7) == 0);
    CHECK(upperBound({}, 7) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("empty array") { check_both({}, 0); }
    SUBCASE("x below the minimum") {
        check_both({3, 5, 7}, 2);
        CHECK(lowerBound({3, 5, 7}, 2) == 0);
        CHECK(upperBound({3, 5, 7}, 2) == 0);
    }
    SUBCASE("x above the maximum") {
        check_both({3, 5, 7}, 8);
        CHECK(lowerBound({3, 5, 7}, 8) == 3);
        CHECK(upperBound({3, 5, 7}, 8) == 3);
    }
    SUBCASE("all equal") {
        const std::vector<int> a(9, 4);
        check_both(a, 4);
        check_both(a, 3);
        check_both(a, 5);
        CHECK(lowerBound(a, 4) == 0);
        CHECK(upperBound(a, 4) == 9);
    }
    SUBCASE("single element") {
        check_both({6}, 5);
        check_both({6}, 6);
        check_both({6}, 7);
    }
    SUBCASE("INT_MIN and INT_MAX queries") {
        const std::vector<int> a = {-5, 0, 0, 12, 99};
        check_both(a, INT_MIN);
        check_both(a, INT_MAX);
        CHECK(lowerBound(a, INT_MIN) == 0);
        CHECK(upperBound(a, INT_MAX) == 5);
    }
    SUBCASE("INT_MIN and INT_MAX stored in the array") {
        const std::vector<int> a = {INT_MIN, INT_MIN, 0, INT_MAX, INT_MAX};
        for (int x : {INT_MIN, INT_MIN + 1, -1, 0, 1, INT_MAX - 1, INT_MAX}) check_both(a, x);
        CHECK(lowerBound(a, INT_MIN) == 0);
        CHECK(upperBound(a, INT_MIN) == 2);
        CHECK(lowerBound(a, INT_MAX) == 3);
        CHECK(upperBound(a, INT_MAX) == 5);
    }
}

TEST_CASE("randomized vs std::lower_bound / std::upper_bound") {
    for (int trial = 0; trial < 2000; ++trial) {
        std::vector<int> a = rand_vec(rand_int(0, 30), -15, 15);
        std::sort(a.begin(), a.end());
        check_both(a, rand_int(-18, 18));
    }
}
