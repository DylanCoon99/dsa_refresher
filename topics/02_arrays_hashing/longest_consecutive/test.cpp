#include <longest_consecutive.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <numeric>
#include <vector>

TEST_CASE("examples") {
    CHECK(longestConsecutive({100, 4, 200, 1, 3, 2}) == 4);
    CHECK(longestConsecutive({1, 2, 2, 3}) == 3);
    CHECK(longestConsecutive({}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(longestConsecutive({}) == 0); }
    SUBCASE("single element") { CHECK(longestConsecutive({42}) == 1); }
    SUBCASE("all equal") { CHECK(longestConsecutive({5, 5, 5}) == 1); }
    SUBCASE("duplicates inside a run") { CHECK(longestConsecutive({1, 2, 2, 3}) == 3); }
    SUBCASE("a run crossing zero") { CHECK(longestConsecutive({-2, 1, 0, -1, 5}) == 4); }
    SUBCASE("no two values adjacent") { CHECK(longestConsecutive({10, 20, 30}) == 1); }
    SUBCASE("INT_MAX next to INT_MAX - 1") {
        CHECK(longestConsecutive({INT_MAX, INT_MAX - 1}) == 2);
        CHECK(longestConsecutive({INT_MAX, 7, INT_MAX - 1, INT_MAX - 2}) == 3);
    }
    SUBCASE("INT_MIN next to INT_MIN + 1") {
        CHECK(longestConsecutive({INT_MIN + 1, INT_MIN, 0}) == 2);
    }
    SUBCASE("INT_MIN and INT_MAX far apart") { CHECK(longestConsecutive({INT_MIN, INT_MAX}) == 1); }
    SUBCASE("two runs, the longer one is later") { CHECK(longestConsecutive({1, 2, 10, 11, 12, 13}) == 4); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(0, 20), -15, 15);
        // Sort + unique, then scan for the longest run of +1 steps.
        std::vector<int> s = nums;
        std::sort(s.begin(), s.end());
        s.erase(std::unique(s.begin(), s.end()), s.end());
        int best = 0, cur = 0;
        for (std::size_t i = 0; i < s.size(); ++i) {
            cur = (i > 0 && s[i] == s[i - 1] + 1) ? cur + 1 : 1;
            best = std::max(best, cur);
        }
        CHECK(longestConsecutive(nums) == best);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // One shuffled run of 10^5 values. Walking upward from every element (no start-of-run check)
    // does ~5·10^9 set lookups.
    const int n = 100'000;
    std::vector<int> nums(n);
    std::iota(nums.begin(), nums.end(), -50'000);
    std::shuffle(nums.begin(), nums.end(), rng());
    CHECK(longestConsecutive(nums) == n);
}
