#include <single_number.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <map>
#include <vector>

TEST_CASE("examples") {
    CHECK(singleNumber({2, 2, 1}) == 1);
    CHECK(singleNumber({4, 1, 2, 1, 2}) == 4);
    CHECK(singleNumber({-7}) == -7);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 1") {
        CHECK(singleNumber({5}) == 5);
        CHECK(singleNumber({0}) == 0);
    }
    SUBCASE("the single value is 0") { CHECK(singleNumber({3, 0, 3}) == 0); }
    SUBCASE("negatives") {
        CHECK(singleNumber({-1, -1, -2}) == -2);
        CHECK(singleNumber({-3, 4, -3}) == 4);
        CHECK(singleNumber({-5, -9, -5, -9, -100}) == -100);
    }
    SUBCASE("INT_MIN as the single number") {
        CHECK(singleNumber({INT_MIN}) == INT_MIN);
        CHECK(singleNumber({7, INT_MIN, 7}) == INT_MIN);
        CHECK(singleNumber({INT_MAX, INT_MIN, INT_MAX}) == INT_MIN);
    }
    SUBCASE("INT_MAX as the single number") { CHECK(singleNumber({INT_MIN, INT_MAX, INT_MIN}) == INT_MAX); }
    SUBCASE("the pair is split far apart") { CHECK(singleNumber({1, 2, 3, 4, 5, 1, 2, 3, 4}) == 5); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int pairs = rand_int(0, 20);
        std::vector<int> nums;
        for (int i = 0; i < pairs; ++i) {
            int v = rand_int(-30, 30);
            nums.push_back(v);
            nums.push_back(v);
        }
        // Pair values are in [-30, 30]; the single value is outside it, so it really appears once.
        int single = rand_int(100, 1000) * (trial % 2 == 0 ? 1 : -1);
        nums.push_back(single);
        std::shuffle(nums.begin(), nums.end(), rng());
        std::map<int, int> count;
        for (int x : nums) ++count[x];
        // Brute force: the only value whose count is 1.
        int expected = 0;
        for (auto& [v, c] : count)
            if (c == 1) expected = v;
        CAPTURE(nums);
        CHECK(singleNumber(nums) == expected);
    }
}
