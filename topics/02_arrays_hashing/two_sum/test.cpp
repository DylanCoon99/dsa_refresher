#include <two_sum.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// Several pairs may be valid, so check the contract rather than one exact answer.
void check_pair(const std::vector<int>& nums, int target) {
    std::vector<int> got = twoSum(nums, target);
    REQUIRE(got.size() == 2);
    const int i = got[0], j = got[1];
    REQUIRE(0 <= i);
    REQUIRE(i < j);
    REQUIRE(j < static_cast<int>(nums.size()));
    CHECK(static_cast<long long>(nums[i]) + nums[j] == target);
}
}  // namespace

TEST_CASE("examples") {
    CHECK(twoSum({2, 7, 11, 15}, 9) == std::vector<int>{0, 1});
    CHECK(twoSum({3, 2, 4}, 6) == std::vector<int>{1, 2});
    CHECK(twoSum({3, 3}, 6) == std::vector<int>{0, 1});
}

TEST_CASE("edge cases") {
    SUBCASE("minimum size") { check_pair({1, 2}, 3); }
    SUBCASE("negatives and zero target") { check_pair({-3, 4, 3, 90}, 0); }
    SUBCASE("pair at the end") { check_pair({5, 6, 7, 1, 9}, 10); }
    SUBCASE("duplicates where only one copy is usable") { check_pair({4, 4, 1}, 5); }
    SUBCASE("extreme values") { check_pair({-1'000'000'000, 7, 1'000'000'000}, 0); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(2, 40), -50, 50);
        int i = rand_int(0, static_cast<int>(nums.size()) - 2);
        int j = rand_int(i + 1, static_cast<int>(nums.size()) - 1);
        check_pair(nums, nums[i] + nums[j]);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Evens 0, 2, 4, ... plus two odd values at the end: the only valid pair is the last two,
    // so an O(n^2) pair scan has to do ~2·10^10 checks.
    const int n = 200'000;
    std::vector<int> nums;
    for (int k = 0; k < n - 2; ++k) nums.push_back(2 * k);
    nums.push_back(500'000'001);
    nums.push_back(500'000'003);
    CHECK(twoSum(nums, 1'000'000'004) == std::vector<int>{n - 2, n - 1});
}
