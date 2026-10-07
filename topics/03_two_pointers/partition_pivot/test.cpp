#include <partition_pivot.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <cstddef>
#include <vector>

namespace {
// Property check: multiset preserved, prefix < pivot, suffix >= pivot, count correct.
void check_partition(const std::vector<int>& original, int pivot) {
    std::vector<int> nums = original;
    const std::size_t expected_count =
        static_cast<std::size_t>(std::count_if(original.begin(), original.end(), [&](int v) { return v < pivot; }));
    const std::size_t k = partitionAround(nums, pivot);
    REQUIRE(nums.size() == original.size());
    REQUIRE(k == expected_count);
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (i < k) {
            CHECK(nums[i] < pivot);
        } else {
            CHECK(nums[i] >= pivot);
        }
    }
    std::vector<int> a = nums, b = original;
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    CHECK(a == b);
}
}  // namespace

TEST_CASE("examples") {
    check_partition({3, 8, 1, 9, 2}, 5);
    check_partition({4, 4, 4}, 4);
    check_partition({1, 2, 3}, 10);
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { check_partition({}, 3); }
    SUBCASE("single element below") { check_partition({1}, 3); }
    SUBCASE("single element above") { check_partition({9}, 3); }
    SUBCASE("pivot smaller than every value") { check_partition({5, 7, 6, 9, 8}, 1); }
    SUBCASE("pivot larger than every value") { check_partition({5, 7, 6, 9, 8}, 100); }
    SUBCASE("pivot absent from the array") { check_partition({9, 1, 8, 2, 7, 3}, 5); }
    SUBCASE("pivot present several times") { check_partition({5, 1, 5, 9, 5, 2}, 5); }
    SUBCASE("already partitioned") { check_partition({1, 2, 3, 7, 8, 9}, 5); }
    SUBCASE("reverse partitioned") { check_partition({9, 8, 7, 3, 2, 1}, 5); }
    SUBCASE("negatives and extremes") { check_partition({-1'000'000'000, 1'000'000'000, 0, -5, 5}, 0); }
}

TEST_CASE("randomized property check") {
    for (int trial = 0; trial < 500; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(0, 30), -15, 15);
        check_partition(nums, rand_int(-17, 17));
    }
}
