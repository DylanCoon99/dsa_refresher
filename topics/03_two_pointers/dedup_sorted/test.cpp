#include <dedup_sorted.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
// Only the first k entries are part of the contract.
void check_dedup(std::vector<int> nums) {
    std::vector<int> expected = nums;
    expected.erase(std::unique(expected.begin(), expected.end()), expected.end());
    const int k = removeDuplicates(nums);
    REQUIRE(k == static_cast<int>(expected.size()));
    REQUIRE(nums.size() >= expected.size());
    CHECK(std::vector<int>(nums.begin(), nums.begin() + k) == expected);
}
}  // namespace

TEST_CASE("examples") {
    std::vector<int> a = {1, 1, 2};
    REQUIRE(removeDuplicates(a) == 2);
    CHECK(std::vector<int>(a.begin(), a.begin() + 2) == std::vector<int>{1, 2});

    std::vector<int> b = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    REQUIRE(removeDuplicates(b) == 5);
    CHECK(std::vector<int>(b.begin(), b.begin() + 5) == std::vector<int>{0, 1, 2, 3, 4});

    std::vector<int> c;
    CHECK(removeDuplicates(c) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { check_dedup({}); }
    SUBCASE("single element") { check_dedup({7}); }
    SUBCASE("all equal") { check_dedup({5, 5, 5, 5, 5}); }
    SUBCASE("already unique") { check_dedup({-3, -1, 0, 2, 9}); }
    SUBCASE("negatives with duplicates") { check_dedup({-4, -4, -2, -2, -2, 0, 0}); }
    SUBCASE("two elements, equal") { check_dedup({1, 1}); }
    SUBCASE("duplicates only at the end") { check_dedup({1, 2, 3, 3, 3}); }
}

TEST_CASE("randomized vs std::unique") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(0, 40), -10, 10);
        std::sort(nums.begin(), nums.end());
        check_dedup(nums);
    }
}
