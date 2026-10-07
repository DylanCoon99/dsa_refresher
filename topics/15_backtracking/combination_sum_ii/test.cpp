#include <combination_sum_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
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

// Bitmask brute force: every subset of positions with the right sum, sorted, in a set.
Rows brute(const std::vector<int>& cands, int target) {
    const int n = static_cast<int>(cands.size());
    std::set<std::vector<int>> seen;
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::vector<int> s;
        int sum = 0;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) {
                s.push_back(cands[i]);
                sum += cands[i];
            }
        if (sum == target) {
            std::sort(s.begin(), s.end());
            seen.insert(s);
        }
    }
    return Rows(seen.begin(), seen.end());
}
}  // namespace

TEST_CASE("examples") {
    CHECK(normalized(combinationSum2({10, 1, 2, 7, 6, 1, 5}, 8)) ==
          Rows{{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}});
    CHECK(normalized(combinationSum2({2, 5, 2, 1, 2}, 5)) == Rows{{1, 2, 2}, {5}});
    CHECK(normalized(combinationSum2({1, 1, 1, 1}, 2)) == Rows{{1, 1}});
}

TEST_CASE("edge cases") {
    SUBCASE("four equal values, target 2 gives one combination") {
        Rows got = combinationSum2({1, 1, 1, 1}, 2);
        CHECK(got == Rows{{1, 1}});
    }
    SUBCASE("no solution") {
        CHECK(combinationSum2({2, 4, 6}, 7).empty());
        CHECK(combinationSum2({1, 1}, 3).empty());
    }
    SUBCASE("a candidate used only once even though reuse would reach the target") {
        CHECK(combinationSum2({3}, 6).empty());
    }
    SUBCASE("target equals one candidate, duplicated") {
        CHECK(normalized(combinationSum2({4, 4, 2}, 4)) == Rows{{4}});
    }
    SUBCASE("no duplicates in the output") {
        Rows got = combinationSum2({1, 1, 2, 2, 3, 3, 4}, 6);
        CHECK_FALSE(has_duplicates(got));
        CHECK(normalized(got) == brute({1, 1, 2, 2, 3, 3, 4}, 6));
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> cands = rand_vec(rand_int(1, 12), 1, 6);
        const int target = rand_int(1, 15);
        Rows got = combinationSum2(cands, target);
        CHECK_FALSE(has_duplicates(got));
        CHECK(normalized(got) == brute(cands, target));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 100 copies of 1, target 30: the only combination is thirty 1s. Without skipping equal values at a
    // level, the search generates C(100, 30) ~ 3·10^25 position-subsets.
    std::vector<int> cands(100, 1);
    Rows got = combinationSum2(cands, 30);
    REQUIRE(got.size() == 1);
    CHECK(got[0] == std::vector<int>(30, 1));
}
