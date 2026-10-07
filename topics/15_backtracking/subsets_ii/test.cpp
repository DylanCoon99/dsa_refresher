#include <subsets_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <set>
#include <vector>

namespace {
using Rows = std::vector<std::vector<int>>;

// The order inside a subset does not matter: sort each subset, then the outer vector.
Rows normalized(Rows v) {
    for (auto& s : v) std::sort(s.begin(), s.end());
    std::sort(v.begin(), v.end());
    return v;
}

bool has_duplicates(const Rows& v) {
    Rows n = normalized(v);
    return std::adjacent_find(n.begin(), n.end()) != n.end();
}

// Every bitmask, each subset sorted, collected in a set so repeats collapse.
Rows brute(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::set<std::vector<int>> seen;
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::vector<int> s;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) s.push_back(nums[i]);
        std::sort(s.begin(), s.end());
        seen.insert(s);
    }
    return Rows(seen.begin(), seen.end());
}

void check_subsets(const std::vector<int>& nums) {
    Rows got = subsetsWithDup(nums);
    CHECK_FALSE(has_duplicates(got));
    CHECK(normalized(got) == brute(nums));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(normalized(subsetsWithDup({1, 2, 2})) == Rows{{}, {1}, {1, 2}, {1, 2, 2}, {2}, {2, 2}});
    CHECK(normalized(subsetsWithDup({2, 2, 2})) == Rows{{}, {2}, {2, 2}, {2, 2, 2}});
    CHECK(normalized(subsetsWithDup({0})) == Rows{{}, {0}});
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(subsetsWithDup({}) == Rows{{}}); }
    SUBCASE("all equal") {
        Rows got = subsetsWithDup({2, 2, 2});
        CHECK(got.size() == 4);
        CHECK_FALSE(has_duplicates(got));
    }
    SUBCASE("a mix, unsorted input") {
        // 4,1,4,1,-2: counts 4 x2, 1 x2, -2 x1 -> 3 * 3 * 2 = 18 distinct subsets
        std::vector<int> nums = {4, 1, 4, 1, -2};
        Rows got = subsetsWithDup(nums);
        CHECK(got.size() == 18);
        CHECK_FALSE(has_duplicates(got));
        CHECK(normalized(got) == brute(nums));
    }
    SUBCASE("no duplicates in the output") {
        Rows got = subsetsWithDup({1, 1, 2, 2, 3, 3});
        CHECK(got.size() == 27);  // 3 * 3 * 3
        CHECK_FALSE(has_duplicates(got));
    }
    SUBCASE("all distinct") { check_subsets({3, -1, 2, 7}); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(0, 10), -3, 3);
        check_subsets(nums);
    }
}
