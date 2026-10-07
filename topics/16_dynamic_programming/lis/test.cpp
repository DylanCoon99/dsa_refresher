#include <lis.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
// O(n^2) DP: len[i] = longest strictly increasing subsequence ending at i.
int brute(const std::vector<int>& v) {
    std::vector<int> len(v.size(), 1);
    int best = 0;
    for (std::size_t i = 0; i < v.size(); ++i) {
        for (std::size_t j = 0; j < i; ++j)
            if (v[j] < v[i]) len[i] = std::max(len[i], len[j] + 1);
        best = std::max(best, len[i]);
    }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(lengthOfLIS({10, 9, 2, 5, 3, 7, 101, 18}) == 4);
    CHECK(lengthOfLIS({0, 1, 0, 3, 2, 3}) == 4);
    CHECK(lengthOfLIS({7, 7, 7, 7}) == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("a single element") { CHECK(lengthOfLIS({5}) == 1); }
    SUBCASE("duplicates do not count: strictly increasing") {
        CHECK(lengthOfLIS({7, 7, 7}) == 1);
        CHECK(lengthOfLIS({1, 2, 2, 3}) == 3);
        CHECK(lengthOfLIS({2, 2, 3, 3, 4, 4}) == 3);
    }
    SUBCASE("strictly decreasing") { CHECK(lengthOfLIS({9, 7, 5, 3, 1}) == 1); }
    SUBCASE("strictly increasing") { CHECK(lengthOfLIS({1, 2, 3, 4, 5}) == 5); }
    SUBCASE("negative values") {
        CHECK(lengthOfLIS({-3, -1, -2, 0, -5, 4}) == 4);
        CHECK(lengthOfLIS({-10000, 10000}) == 2);
    }
    SUBCASE("the longest run is not the one starting first") {
        CHECK(lengthOfLIS({4, 5, 6, 1, 2, 3, 4, 5}) == 5);
    }
}

TEST_CASE("randomized vs O(n^2) brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        std::vector<int> v = rand_vec(rand_int(1, 40), -10, 10);  // narrow range: many duplicates
        INFO(v);
        CHECK(lengthOfLIS(v) == brute(v));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    const int n = 100000;
    SUBCASE("repeating ramp 0..999: strictly increasing needs distinct values, so the answer is 1000") {
        std::vector<int> v(n);
        for (int i = 0; i < n; ++i) v[i] = i % 1000;
        CHECK(lengthOfLIS(v) == 1000);
    }
    SUBCASE("fully increasing") {
        std::vector<int> v(n);
        for (int i = 0; i < n; ++i) v[i] = i - 50000;
        CHECK(lengthOfLIS(v) == n);
    }
}
