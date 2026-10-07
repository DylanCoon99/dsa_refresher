#include <quickselect.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

namespace {
// Run quickselect on a copy (it may reorder its argument) and compare with the sorted array.
void check_select(std::vector<int> nums, std::size_t k) {
    std::vector<int> sorted = nums;
    std::sort(sorted.begin(), sorted.end());
    REQUIRE(k < nums.size());
    CHECK(quickselect(nums, k) == sorted[k]);
}
}  // namespace

TEST_CASE("examples") {
    std::vector<int> a = {7, 1, 5, 3};
    CHECK(quickselect(a, 0) == 1);
    std::vector<int> b = {7, 1, 5, 3};
    CHECK(quickselect(b, 3) == 7);
    std::vector<int> c = {2, 2, 9, 2, 5};
    CHECK(quickselect(c, 2) == 2);
}

TEST_CASE("edge cases") {
    SUBCASE("single element") { check_select({5}, 0); }
    SUBCASE("k = 0 is the minimum") { check_select({9, 4, 8, 1, 6}, 0); }
    SUBCASE("k = n - 1 is the maximum") { check_select({9, 4, 8, 1, 6}, 4); }
    SUBCASE("every k on a small array") {
        for (std::size_t k = 0; k < 6; ++k) check_select({3, 1, 4, 1, 5, 9}, k);
    }
    SUBCASE("duplicates") {
        check_select({4, 4, 4, 4}, 0);
        check_select({4, 4, 4, 4}, 3);
        check_select({1, 2, 2, 2, 3, 3}, 2);
        check_select({1, 2, 2, 2, 3, 3}, 4);
        check_select({5, 1, 5, 1, 5, 1}, 3);
    }
    SUBCASE("already sorted and reversed") {
        check_select({1, 2, 3, 4, 5, 6, 7}, 3);
        check_select({7, 6, 5, 4, 3, 2, 1}, 3);
    }
    SUBCASE("INT_MIN and INT_MAX") {
        check_select({INT_MAX, INT_MIN, 0, INT_MAX, INT_MIN}, 0);
        check_select({INT_MAX, INT_MIN, 0, INT_MAX, INT_MIN}, 2);
        check_select({INT_MAX, INT_MIN, 0, INT_MAX, INT_MIN}, 4);
    }
}

TEST_CASE("randomized vs sort") {
    for (int trial = 0; trial < 500; ++trial) {
        std::vector<int> nums = rand_vec(static_cast<std::size_t>(rand_int(1, 40)), -15, 15);
        const std::size_t k = static_cast<std::size_t>(rand_int(0, static_cast<int>(nums.size()) - 1));
        check_select(nums, k);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^6 equal keys: a two-way partition that sends all equal keys to one side removes one element
    // per pass (~10^12 steps in total). Three-way partitioning finishes in one pass.
    std::vector<int> nums(1'000'000, 7);
    CHECK(quickselect(nums, nums.size() / 2) == 7);
}
