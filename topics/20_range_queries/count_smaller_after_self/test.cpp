#include <count_smaller_after_self.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <climits>
#include <vector>

namespace {
std::vector<int> brute(const std::vector<int>& nums) {
    std::vector<int> out(nums.size(), 0);
    for (std::size_t i = 0; i < nums.size(); ++i)
        for (std::size_t j = i + 1; j < nums.size(); ++j)
            if (nums[j] < nums[i]) ++out[i];
    return out;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(countSmaller({5, 2, 6, 1}) == std::vector<int>{2, 1, 1, 0});
    CHECK(countSmaller({-1}) == std::vector<int>{0});
    CHECK(countSmaller({-1, -1}) == std::vector<int>{0, 0});
}

TEST_CASE("edge cases") {
    SUBCASE("equal values are not smaller") {
        CHECK(countSmaller({3, 3, 3, 3}) == std::vector<int>{0, 0, 0, 0});
        CHECK(countSmaller({2, 1, 2, 1}) == std::vector<int>{2, 0, 1, 0});
    }
    SUBCASE("negatives") {
        CHECK(countSmaller({-1, -3, -2, 0, -5}) == std::vector<int>{3, 1, 1, 1, 0});
    }
    SUBCASE("strictly decreasing and strictly increasing") {
        CHECK(countSmaller({4, 3, 2, 1}) == std::vector<int>{3, 2, 1, 0});
        CHECK(countSmaller({1, 2, 3, 4}) == std::vector<int>{0, 0, 0, 0});
    }
    SUBCASE("INT_MIN and INT_MAX") {
        CHECK(countSmaller({INT_MAX, INT_MIN, 0, INT_MIN, INT_MAX}) == std::vector<int>{3, 0, 1, 0, 0});
        CHECK(countSmaller({INT_MAX, INT_MIN}) == std::vector<int>{1, 0});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 40);
        std::vector<int> nums;
        switch (trial % 3) {
            case 0: nums = rand_vec(n, -5, 5); break;  // many ties
            case 1: nums = rand_vec(n, -1'000'000, 1'000'000); break;
            default:
                nums = rand_vec(n, 0, 3);
                for (int& x : nums) x = (x == 0) ? INT_MIN : (x == 1) ? INT_MAX : x;
        }
        CHECK(countSmaller(nums) == brute(nums));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // n = 10^5, strictly decreasing values spread across the whole int range:
    // a[i] = INT_MAX - 42949 * i, so counts[i] = n - 1 - i. That is also the worst case for the
    // O(n^2) scan (~5·10^9 comparisons), and the spread forces coordinate compression.
    const int n = 100'000;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) nums[i] = static_cast<int>(INT_MAX - 42949LL * i);
    std::vector<int> got = countSmaller(nums);
    REQUIRE(got.size() == static_cast<std::size_t>(n));
    bool ok = true;
    for (int i = 0; i < n && ok; ++i) ok = got[i] == n - 1 - i;
    CHECK(ok);
}
