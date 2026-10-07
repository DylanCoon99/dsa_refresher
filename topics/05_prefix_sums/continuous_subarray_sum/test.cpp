#include <continuous_subarray_sum.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
bool brute(const std::vector<int>& nums, int k) {
    const int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; ++i) {
        long long sum = nums[i];
        for (int j = i + 1; j < n; ++j) {
            sum += nums[j];
            if (sum % k == 0) return true;
        }
    }
    return false;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(checkSubarraySum({23, 2, 4, 6, 7}, 6) == true);
    CHECK(checkSubarraySum({23, 2, 6, 4, 7}, 6) == true);
    CHECK(checkSubarraySum({23, 2, 6, 4, 7}, 13) == false);
}

TEST_CASE("edge cases") {
    SUBCASE("single element is never long enough") {
        CHECK(checkSubarraySum({0}, 1) == false);
        CHECK(checkSubarraySum({6}, 6) == false);
        CHECK(checkSubarraySum({0}, 5) == false);
    }
    SUBCASE("two zeros sum to 0, a multiple of k") {
        CHECK(checkSubarraySum({0, 0}, 1) == true);
        CHECK(checkSubarraySum({0, 0}, 7) == true);
    }
    SUBCASE("zeros inside, k = 3") {
        CHECK(checkSubarraySum({5, 0, 0, 0}, 3) == true);
    }
    SUBCASE("a lone zero next to a non-multiple does not count") {
        CHECK(checkSubarraySum({1, 0}, 2) == false);
        CHECK(checkSubarraySum({0, 1}, 2) == false);
    }
    SUBCASE("k = 1: every sum is a multiple") {
        CHECK(checkSubarraySum({1, 2}, 1) == true);
        CHECK(checkSubarraySum({3, 5, 7}, 1) == true);
    }
    SUBCASE("exactly two elements") {
        CHECK(checkSubarraySum({3, 3}, 6) == true);
        CHECK(checkSubarraySum({3, 4}, 6) == false);
    }
    SUBCASE("the qualifying block is the whole array") {
        CHECK(checkSubarraySum({1, 2, 3}, 6) == true);
        CHECK(checkSubarraySum({1, 2, 3}, 4) == false);
    }
    SUBCASE("a single multiple of k does not qualify by itself") {
        CHECK(checkSubarraySum({6, 1, 1}, 6) == false);
        CHECK(checkSubarraySum({1, 6, 1}, 6) == false);
    }
    SUBCASE("k larger than every possible sum") {
        CHECK(checkSubarraySum({1, 2, 3}, 100) == false);
    }
    SUBCASE("a sum of 0 is a multiple of every k") {
        CHECK(checkSubarraySum({4, 0, 0}, 1'000'000'007) == true);
    }
    SUBCASE("sums near the top of the int range") {
        CHECK(checkSubarraySum({1'000'000'000, 1'000'000'000}, 2'000'000'000) == true);
        CHECK(checkSubarraySum({1'000'000'000, 1'000'000'000}, 1'999'999'999) == false);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 500; ++trial) {
        const int n = rand_int(1, 12);
        std::vector<int> nums = rand_vec(n, 0, 9);
        const int k = rand_int(1, 15);
        CHECK(checkSubarraySum(nums, k) == brute(nums, k));
    }
}

TEST_CASE("randomized with larger k (mostly false)") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 10);
        std::vector<int> nums = rand_vec(n, 0, 100);
        const int k = rand_int(50, 1000);
        CHECK(checkSubarraySum(nums, k) == brute(nums, k));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // k = 10^9 and every prefix sum stays far below it, so no block of length >= 2 qualifies and
    // an O(n^2) scan must try all ~5·10^9 blocks. The second case has the only qualifying block at
    // the very end, so even a scan that exits early still has to look at nearly every block.
    const int n = 100'000;
    const int k = 1'000'000'000;
    std::vector<int> nums(n, 1);
    CHECK(checkSubarraySum(nums, k) == false);

    nums[n - 2] = k - 1;  // {k-1, 1} at the end sums to exactly k
    CHECK(checkSubarraySum(nums, k) == true);
}
