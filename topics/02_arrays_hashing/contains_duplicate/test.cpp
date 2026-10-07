#include <contains_duplicate.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

TEST_CASE("examples") {
    CHECK(containsDuplicate({1, 2, 3, 1}) == true);
    CHECK(containsDuplicate({1, 2, 3, 4}) == false);
    CHECK(containsDuplicate({7}) == false);
}

TEST_CASE("edge cases") {
    SUBCASE("single element") { CHECK(containsDuplicate({0}) == false); }
    SUBCASE("INT_MIN and INT_MAX together, distinct") { CHECK(containsDuplicate({INT_MIN, INT_MAX}) == false); }
    SUBCASE("INT_MIN and INT_MAX with a repeated INT_MAX") {
        CHECK(containsDuplicate({INT_MIN, INT_MAX, 0, INT_MAX}) == true);
    }
    SUBCASE("duplicate at the far ends") { CHECK(containsDuplicate({5, 1, 2, 3, 4, 5}) == true); }
    SUBCASE("all equal") { CHECK(containsDuplicate({4, 4, 4, 4}) == true); }
    SUBCASE("negatives") {
        CHECK(containsDuplicate({-1, -2, -3}) == false);
        CHECK(containsDuplicate({-1, -2, -1}) == true);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(1, 30), -40, 40);
        bool want = false;
        for (std::size_t i = 0; i < nums.size(); ++i)
            for (std::size_t j = i + 1; j < nums.size(); ++j)
                if (nums[i] == nums[j]) want = true;
        CHECK(containsDuplicate(nums) == want);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 distinct values: an O(n^2) pair scan does ~5·10^9 comparisons.
    const int n = 100'000;
    std::vector<int> nums;
    for (int k = 0; k < n; ++k) nums.push_back(k * 7 - 300'000);
    std::shuffle(nums.begin(), nums.end(), rng());
    CHECK(containsDuplicate(nums) == false);
}
