#include <top_k_frequent.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <map>
#include <vector>

namespace {
std::vector<int> sorted(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    return v;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(sorted(topKFrequent({1, 1, 1, 2, 2, 3}, 2)) == std::vector<int>{1, 2});
    CHECK(sorted(topKFrequent({5}, 1)) == std::vector<int>{5});
    CHECK(sorted(topKFrequent({4, 4, 4, 6, 6, 9}, 3)) == std::vector<int>{4, 6, 9});
}

TEST_CASE("edge cases") {
    SUBCASE("k equals the number of distinct values") {
        CHECK(sorted(topKFrequent({3, 1, 2, 3, 1, 3}, 3)) == std::vector<int>{1, 2, 3});
    }
    SUBCASE("negative values") {
        CHECK(sorted(topKFrequent({-1, -1, -2, -2, -2, 7}, 2)) == std::vector<int>{-2, -1});
        CHECK(sorted(topKFrequent({-5, -5, -5, 0, 0, 9}, 1)) == std::vector<int>{-5});
    }
    SUBCASE("extreme values") {
        const int lo = -2147483647 - 1, hi = 2147483647;
        CHECK(sorted(topKFrequent({lo, lo, hi, 0}, 1)) == std::vector<int>{lo});
    }
    SUBCASE("a single value repeated") { CHECK(sorted(topKFrequent({2, 2, 2, 2}, 1)) == std::vector<int>{2}); }
    SUBCASE("the most frequent value is not the first or the largest") {
        CHECK(sorted(topKFrequent({1, 2, 3, 3, 3, 2, 3, 0}, 1)) == std::vector<int>{3});
    }
}

TEST_CASE("randomized vs brute force") {
    int checked = 0;
    for (int trial = 0; trial < 500; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(1, 30), -6, 6);
        std::map<int, int> cnt;
        for (int x : nums) ++cnt[x];
        std::vector<std::pair<int, int>> byFreq;  // (count, value)
        for (auto& kv : cnt) byFreq.push_back({kv.second, kv.first});
        std::sort(byFreq.begin(), byFreq.end(), [](auto& a, auto& b) { return a.first > b.first; });
        int k = rand_int(1, static_cast<int>(byFreq.size()));
        // Only keep inputs whose answer is unique.
        if (k < static_cast<int>(byFreq.size()) && byFreq[k - 1].first == byFreq[k].first) continue;
        std::vector<int> want;
        for (int i = 0; i < k; ++i) want.push_back(byFreq[i].second);
        CHECK(sorted(topKFrequent(nums, k)) == sorted(want));
        ++checked;
    }
    CHECK(checked > 50);
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Value v (1..~446) appears v times, so counts are all distinct: 1+2+...+446 = 99 681 elements.
    std::vector<int> nums;
    for (int v = 1; v <= 446; ++v)
        for (int c = 0; c < v; ++c) nums.push_back(v);
    std::shuffle(nums.begin(), nums.end(), rng());
    CHECK(sorted(topKFrequent(nums, 3)) == std::vector<int>{444, 445, 446});
}
