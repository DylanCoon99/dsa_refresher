#include <subsets.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
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

Rows brute(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    Rows out;
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::vector<int> s;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) s.push_back(nums[i]);
        out.push_back(s);
    }
    return out;
}

void check_subsets(const std::vector<int>& nums) {
    Rows got = subsets(nums);
    CHECK_FALSE(has_duplicates(got));
    CHECK(normalized(got) == normalized(brute(nums)));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(normalized(subsets({1, 2, 3})) ==
          Rows{{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}});
    CHECK(normalized(subsets({0})) == Rows{{}, {0}});
    CHECK(subsets({}) == Rows{{}});
}

TEST_CASE("edge cases") {
    SUBCASE("n = 0") { CHECK(subsets({}) == Rows{{}}); }
    SUBCASE("n = 1") { CHECK(normalized(subsets({5})) == Rows{{}, {5}}); }
    SUBCASE("negatives") {
        CHECK(normalized(subsets({-3, -1, 2})) ==
              Rows{{}, {-3}, {-3, -1}, {-3, -1, 2}, {-3, 2}, {-1}, {-1, 2}, {2}});
    }
    SUBCASE("n = 10 gives 1024 distinct subsets") {
        std::vector<int> nums(10);
        std::iota(nums.begin(), nums.end(), -5);
        Rows got = subsets(nums);
        CHECK(got.size() == 1024);
        CHECK_FALSE(has_duplicates(got));
        check_subsets(nums);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 200; ++trial) {
        std::vector<int> pool(21);
        std::iota(pool.begin(), pool.end(), -10);
        std::shuffle(pool.begin(), pool.end(), rng());
        pool.resize(rand_int(0, 9));
        check_subsets(pool);
    }
}
