#include <jump_game_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
// dp[j] = fewest jumps to reach j, or -1; O(n * max) and obviously correct.
int brute(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::vector<int> dp(n, -1);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] < 0) continue;
        for (int j = i + 1; j <= i + nums[i] && j < n; ++j)
            if (dp[j] < 0 || dp[i] + 1 < dp[j]) dp[j] = dp[i] + 1;
    }
    return dp[n - 1];
}
}  // namespace

TEST_CASE("examples") {
    CHECK(jump({2, 3, 1, 1, 4}) == 2);
    CHECK(jump({2, 3, 0, 1, 4}) == 2);
    CHECK(jump({5}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("single element") {
        CHECK(jump({0}) == 0);
        CHECK(jump({9}) == 0);
    }
    SUBCASE("reaches the end in one jump") {
        CHECK(jump({1, 0}) == 1);
        CHECK(jump({4, 1, 1, 1, 1}) == 1);
        CHECK(jump({10, 0, 0}) == 1);
    }
    SUBCASE("all ones need n - 1 jumps") { CHECK(jump({1, 1, 1, 1, 1}) == 4); }
    SUBCASE("the farthest first jump is not always best") {
        // From 0 you can land on index 1 (value 1) or index 2 (value 10): index 2 is the better launch.
        CHECK(jump({2, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0}) == 2);
    }
    SUBCASE("a mid-range jump is the right one") {
        // 0 -> 1 (value 4) reaches index 5, the end.
        CHECK(jump({3, 4, 1, 1, 1, 1}) == 2);
    }
    SUBCASE("zeros that are never landed on") { CHECK(jump({4, 0, 0, 0, 5, 0}) == 2); }
}

TEST_CASE("randomized vs brute force") {
    int checked = 0;
    for (int trial = 0; trial < 600 && checked < 300; ++trial) {
        const int n = rand_int(1, 12);
        const std::vector<int> v = rand_vec(n, 0, 4);
        const int expected = brute(v);
        if (expected < 0) continue;  // the contract only covers reachable inputs
        ++checked;
        INFO("trial " << trial);
        CHECK(jump(v) == expected);
    }
    CHECK(checked >= 200);
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Every index can jump 10^4: each jump covers exactly 10^4 more indices, so the last index
    // (distance 99999) needs ceil(99999 / 10^4) = 10 jumps.
    CHECK(jump(std::vector<int>(100000, 10000)) == 10);
}
