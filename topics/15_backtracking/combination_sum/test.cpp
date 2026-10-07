#include <combination_sum.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

namespace {
using Rows = std::vector<std::vector<int>>;

// The order inside a combination does not matter: sort each, then the outer vector.
Rows normalized(Rows v) {
    for (auto& s : v) std::sort(s.begin(), s.end());
    std::sort(v.begin(), v.end());
    return v;
}

bool has_duplicates(const Rows& v) {
    Rows n = normalized(v);
    return std::adjacent_find(n.begin(), n.end()) != n.end();
}

// Brute force by DP over sums: ways[t] = every sorted multiset summing to t, built by adding
// one candidate to a multiset for t - c and re-sorting; a set collapses repeats.
Rows brute(const std::vector<int>& candidates, int target) {
    std::vector<std::set<std::vector<int>>> ways(target + 1);
    ways[0].insert(std::vector<int>{});
    for (int t = 1; t <= target; ++t)
        for (int c : candidates)
            if (c <= t)
                for (const auto& combo : ways[t - c]) {
                    std::vector<int> next = combo;
                    next.push_back(c);
                    std::sort(next.begin(), next.end());
                    ways[t].insert(next);
                }
    return Rows(ways[target].begin(), ways[target].end());
}

void check_sum(const std::vector<int>& candidates, int target) {
    Rows got = combinationSum(candidates, target);
    CHECK_FALSE(has_duplicates(got));
    CHECK(normalized(got) == brute(candidates, target));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(normalized(combinationSum({2, 3, 6, 7}, 7)) == Rows{{2, 2, 3}, {7}});
    CHECK(normalized(combinationSum({2, 3, 5}, 8)) == Rows{{2, 2, 2, 2}, {2, 3, 3}, {3, 5}});
    CHECK(combinationSum({5, 6}, 3).empty());
}

TEST_CASE("edge cases") {
    SUBCASE("target smaller than every candidate") { CHECK(combinationSum({4, 7, 9}, 3).empty()); }
    SUBCASE("target equal to a candidate") {
        CHECK(normalized(combinationSum({7, 11}, 7)) == Rows{{7}});
    }
    SUBCASE("no combination reaches the target") { CHECK(combinationSum({4, 6}, 9).empty()); }
    SUBCASE("only candidate 1: one combination of ten ones") {
        CHECK(combinationSum({1}, 10) == Rows{std::vector<int>(10, 1)});
    }
    SUBCASE("candidate 1 with others, target 10 (many results)") {
        std::vector<int> cands = {1, 2, 3, 4, 5};
        Rows got = combinationSum(cands, 10);
        CHECK(got.size() == 30);  // partitions of 10 into parts of size at most 5
        CHECK_FALSE(has_duplicates(got));
        CHECK(normalized(got) == brute(cands, 10));
    }
    SUBCASE("unsorted candidates") { check_sum({7, 2, 5, 3}, 12); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> pool(12);
        std::iota(pool.begin(), pool.end(), 1);
        std::shuffle(pool.begin(), pool.end(), rng());
        pool.resize(rand_int(1, 5));
        check_sum(pool, rand_int(1, 30));
    }
}
