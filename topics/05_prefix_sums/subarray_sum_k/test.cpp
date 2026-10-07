#include <subarray_sum_k.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
int brute(const std::vector<int>& nums, int k) {
    const int n = static_cast<int>(nums.size());
    int count = 0;
    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        for (int j = i; j < n; ++j) {
            sum += nums[j];
            if (sum == k) ++count;
        }
    }
    return count;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(subarraySum({1, 1, 1}, 2) == 2);
    CHECK(subarraySum({1, 2, 3}, 3) == 2);
    CHECK(subarraySum({1, -1, 0}, 0) == 3);
}

TEST_CASE("edge cases") {
    SUBCASE("single element, match and no match") {
        CHECK(subarraySum({5}, 5) == 1);
        CHECK(subarraySum({5}, 4) == 0);
        CHECK(subarraySum({-5}, -5) == 1);
    }
    SUBCASE("k = 0 with all zeros counts every subarray") {
        CHECK(subarraySum({0, 0, 0}, 0) == 6);
        CHECK(subarraySum({0}, 0) == 1);
        CHECK(subarraySum({0, 0, 0, 0}, 0) == 10);
    }
    SUBCASE("zeros with nonzero k") {
        CHECK(subarraySum({0, 0, 3, 0}, 3) == 6);
    }
    SUBCASE("negative numbers") {
        CHECK(subarraySum({-1, -1, 1}, 0) == 1);
        CHECK(subarraySum({3, 4, 7, 2, -3, 1, 4, 2}, 7) == 4);
        CHECK(subarraySum({-1, -2, -3}, -3) == 2);
    }
    SUBCASE("negative k") {
        CHECK(subarraySum({1, -2, 1, -2}, -1) == 3);
    }
    SUBCASE("a subarray starting at index 0 (needs the empty prefix)") {
        CHECK(subarraySum({2, 3, 4}, 5) == 1);
        CHECK(subarraySum({7, 1, 1}, 7) == 1);
    }
    SUBCASE("whole array is the only match") {
        CHECK(subarraySum({1, 2, 3}, 6) == 1);
    }
    SUBCASE("no match") {
        CHECK(subarraySum({1, 2, 3}, 100) == 0);
    }
    SUBCASE("overlapping matches are all counted") {
        CHECK(subarraySum({1, -1, 1, -1}, 0) == 4);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        const int n = rand_int(1, 30);
        std::vector<int> nums = rand_vec(n, -5, 5);
        const int k = rand_int(-8, 8);
        CHECK(subarraySum(nums, k) == brute(nums, k));
    }
}

TEST_CASE("randomized, zero-heavy") {
    for (int trial = 0; trial < 200; ++trial) {
        const int n = rand_int(1, 30);
        std::vector<int> nums = rand_vec(n, -1, 1);
        const int k = rand_int(-2, 2);
        CHECK(subarraySum(nums, k) == brute(nums, k));
    }
}

TEST_CASE("randomized at the maximum constraint values") {
    for (int trial = 0; trial < 50; ++trial) {
        const int n = rand_int(1, 60);
        std::vector<int> nums = rand_vec(n, -1000, 1000);
        const int k = rand_int(-3000, 3000);
        CHECK(subarraySum(nums, k) == brute(nums, k));
    }
}
