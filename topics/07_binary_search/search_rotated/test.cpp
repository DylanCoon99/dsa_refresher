#include <search_rotated.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
std::vector<int> rotate_right(std::vector<int> v, int r) {
    std::rotate(v.begin(), v.end() - r, v.end());
    return v;
}
int brute(const std::vector<int>& v, int target) {
    for (int i = 0; i < static_cast<int>(v.size()); ++i)
        if (v[i] == target) return i;
    return -1;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(search({4, 5, 6, 7, 0, 1, 2}, 0) == 4);
    CHECK(search({4, 5, 6, 7, 0, 1, 2}, 3) == -1);
    CHECK(search({1}, 0) == -1);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 1") {
        CHECK(search({1}, 1) == 0);
        CHECK(search({1}, 2) == -1);
    }
    SUBCASE("n = 2 both orders") {
        CHECK(search({1, 3}, 3) == 1);
        CHECK(search({3, 1}, 3) == 0);
        CHECK(search({3, 1}, 1) == 1);
        CHECK(search({3, 1}, 2) == -1);
    }
    SUBCASE("every rotation of {0..9} against every target in -1..10") {
        std::vector<int> base;
        for (int i = 0; i < 10; ++i) base.push_back(i);
        for (int r = 0; r < 10; ++r) {
            const std::vector<int> nums = rotate_right(base, r);
            for (int target = -1; target <= 10; ++target) {
                CAPTURE(r);
                CAPTURE(target);
                CHECK(search(nums, target) == brute(nums, target));
            }
        }
    }
    SUBCASE("negative values") {
        CHECK(search({-2, 0, 3, -9, -5}, -9) == 3);
        CHECK(search({-2, 0, 3, -9, -5}, -5) == 4);
        CHECK(search({-2, 0, 3, -9, -5}, -2) == 0);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 50);
        std::vector<int> base;
        int v = rand_int(-60, 0);
        for (int i = 0; i < n; ++i) {
            base.push_back(v);
            v += rand_int(1, 3);
        }
        const std::vector<int> nums = rotate_right(base, rand_int(0, n - 1));
        const int target = rand_int(-65, v + 3);
        CHECK(search(nums, target) == brute(nums, target));
    }
}
