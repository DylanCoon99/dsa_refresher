#include <find_min_rotated.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
// Move the last r elements to the front.
std::vector<int> rotate_right(std::vector<int> v, int r) {
    std::rotate(v.begin(), v.end() - r, v.end());
    return v;
}
std::vector<int> ascending(int n, int start = 0, int step = 1) {
    std::vector<int> v;
    for (int i = 0; i < n; ++i) v.push_back(start + i * step);
    return v;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(findMin({3, 4, 5, 1, 2}) == 1);
    CHECK(findMin({4, 5, 6, 7, 0, 1, 2}) == 0);
    CHECK(findMin({11, 13, 15, 17}) == 11);
}

TEST_CASE("edge cases") {
    SUBCASE("not rotated") {
        CHECK(findMin({1, 2, 3, 4, 5}) == 1);
        CHECK(findMin({-9, -4, 0, 2, 8, 100}) == -9);
    }
    SUBCASE("rotated by n - 1") {
        CHECK(findMin({2, 3, 4, 5, 1}) == 1);
        CHECK(findMin({10, 20, 30, 40, 50, 5}) == 5);
    }
    SUBCASE("n = 1") {
        CHECK(findMin({42}) == 42);
        CHECK(findMin({-3}) == -3);
    }
    SUBCASE("n = 2 both orders") {
        CHECK(findMin({1, 2}) == 1);
        CHECK(findMin({2, 1}) == 1);
    }
    SUBCASE("n = 3 every rotation") {
        CHECK(findMin({1, 2, 3}) == 1);
        CHECK(findMin({3, 1, 2}) == 1);
        CHECK(findMin({2, 3, 1}) == 1);
    }
    SUBCASE("every rotation of several lengths") {
        for (int n = 1; n <= 40; ++n)
            for (int r = 0; r < n; ++r) CHECK(findMin(rotate_right(ascending(n, -20), r)) == -20);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 60);
        const std::vector<int> base = ascending(n, rand_int(-100, 100), rand_int(1, 5));
        const std::vector<int> nums = rotate_right(base, rand_int(0, n - 1));
        CHECK(findMin(nums) == *std::min_element(nums.begin(), nums.end()));
    }
}
