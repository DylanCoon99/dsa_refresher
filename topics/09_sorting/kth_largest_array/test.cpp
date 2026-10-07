#include <kth_largest_array.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <functional>
#include <vector>

namespace {
// Run on a copy (the function may reorder its argument) and compare with a descending sort.
void check_kth(std::vector<int> nums, int k) {
    std::vector<int> desc = nums;
    std::sort(desc.begin(), desc.end(), std::greater<int>());
    REQUIRE(1 <= k);
    REQUIRE(k <= static_cast<int>(nums.size()));
    CHECK(findKthLargest(nums, k) == desc[static_cast<std::size_t>(k) - 1]);
}
}  // namespace

TEST_CASE("examples") {
    std::vector<int> a = {3, 2, 1, 5, 6, 4};
    CHECK(findKthLargest(a, 2) == 5);
    std::vector<int> b = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    CHECK(findKthLargest(b, 4) == 4);
    std::vector<int> c = {7};
    CHECK(findKthLargest(c, 1) == 7);
}

TEST_CASE("edge cases") {
    SUBCASE("k = 1 is the maximum") { check_kth({3, 9, 2, 9, 1}, 1); }
    SUBCASE("k = n is the minimum") { check_kth({3, 9, 2, 9, 1}, 5); }
    SUBCASE("duplicates") {
        check_kth({5, 5, 4}, 2);
        check_kth({5, 5, 4}, 3);
        check_kth({2, 2, 2, 2}, 3);
        check_kth({1, 2, 2, 3, 3, 3}, 4);
    }
    SUBCASE("negatives") { check_kth({-1, -5, 0, -3, 2}, 3); }
    SUBCASE("INT_MIN and INT_MAX") {
        check_kth({INT_MIN, INT_MAX, 0, INT_MIN, INT_MAX}, 1);
        check_kth({INT_MIN, INT_MAX, 0, INT_MIN, INT_MAX}, 3);
        check_kth({INT_MIN, INT_MAX, 0, INT_MIN, INT_MAX}, 5);
    }
    SUBCASE("sorted and reversed input") {
        check_kth({1, 2, 3, 4, 5, 6}, 2);
        check_kth({6, 5, 4, 3, 2, 1}, 5);
    }
}

TEST_CASE("randomized vs sort") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> nums = rand_vec(static_cast<std::size_t>(rand_int(1, 40)), -15, 15);
        check_kth(nums, rand_int(1, static_cast<int>(nums.size())));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^6 equal keys: a quickselect whose partition sends equal keys to one side removes one element
    // per pass (~10^12 steps). The all-equal answer (5) also differs from the stub's default return.
    std::vector<int> nums(1'000'000, 5);
    CHECK(findKthLargest(nums, 500'000) == 5);
}
