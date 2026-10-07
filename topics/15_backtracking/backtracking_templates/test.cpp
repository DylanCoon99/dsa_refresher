#include <backtracking_templates.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
using Rows = std::vector<std::vector<int>>;

// Sort only the outer vector: used when the order inside each result matters.
Rows outer_sorted(Rows v) {
    std::sort(v.begin(), v.end());
    return v;
}

bool has_duplicates(Rows v) {
    std::sort(v.begin(), v.end());
    return std::adjacent_find(v.begin(), v.end()) != v.end();
}

long long choose(int n, int k) {
    long long r = 1;
    for (int i = 1; i <= k; ++i) r = r * (n - k + i) / i;
    return r;
}

long long factorial(int n) {
    long long r = 1;
    for (int i = 2; i <= n; ++i) r *= i;
    return r;
}

// Bitmask brute force; elements appear in their original relative order.
Rows brute_subsets(const std::vector<int>& items) {
    const int n = static_cast<int>(items.size());
    Rows out;
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::vector<int> s;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) s.push_back(items[i]);
        out.push_back(s);
    }
    return out;
}

Rows brute_permutations(std::vector<int> items) {
    std::sort(items.begin(), items.end());
    Rows out;
    do out.push_back(items);
    while (std::next_permutation(items.begin(), items.end()));
    return out;
}

// All size-k subsets of 1..n via bitmask, ascending inside.
Rows brute_combinations(int n, int k) {
    Rows out;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) != k) continue;
        std::vector<int> c;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) c.push_back(i + 1);
        out.push_back(c);
    }
    return out;
}

std::vector<int> distinct_items(int n) {
    std::vector<int> pool(201);
    std::iota(pool.begin(), pool.end(), -100);
    std::shuffle(pool.begin(), pool.end(), rng());
    pool.resize(n);
    return pool;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(outer_sorted(allSubsets({1, 2, 3})) ==
          Rows{{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}});
    CHECK(outer_sorted(allPermutations({1, 2, 3})) ==
          Rows{{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}});
    CHECK(outer_sorted(allCombinations(4, 2)) ==
          Rows{{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}});
}

TEST_CASE("edge cases") {
    SUBCASE("empty items") {
        CHECK(allSubsets({}) == Rows{{}});
        CHECK(allPermutations({}) == Rows{{}});
    }
    SUBCASE("single item") {
        CHECK(outer_sorted(allSubsets({7})) == Rows{{}, {7}});
        CHECK(allPermutations({7}) == Rows{{7}});
    }
    SUBCASE("k = 0") {
        CHECK(allCombinations(5, 0) == Rows{{}});
        CHECK(allCombinations(0, 0) == Rows{{}});
    }
    SUBCASE("k = n gives one combination") { CHECK(allCombinations(4, 4) == Rows{{1, 2, 3, 4}}); }
    SUBCASE("k = 1") { CHECK(outer_sorted(allCombinations(3, 1)) == Rows{{1}, {2}, {3}}); }
    SUBCASE("subsets keep the items' relative order (items not sorted)") {
        CHECK(outer_sorted(allSubsets({3, -1, 2})) ==
              outer_sorted(Rows{{}, {3}, {-1}, {2}, {3, -1}, {3, 2}, {-1, 2}, {3, -1, 2}}));
    }
    SUBCASE("negative items in permutations") {
        CHECK(outer_sorted(allPermutations({-2, 0, 5})) ==
              Rows{{-2, 0, 5}, {-2, 5, 0}, {0, -2, 5}, {0, 5, -2}, {5, -2, 0}, {5, 0, -2}});
    }
}

TEST_CASE("counts and no duplicates for n up to 8") {
    for (int n = 0; n <= 8; ++n) {
        std::vector<int> items(n);
        std::iota(items.begin(), items.end(), 1);

        Rows subs = allSubsets(items);
        CHECK(subs.size() == (1u << n));
        CHECK_FALSE(has_duplicates(subs));

        Rows perms = allPermutations(items);
        CHECK(static_cast<long long>(perms.size()) == factorial(n));
        CHECK_FALSE(has_duplicates(perms));

        for (int k = 0; k <= n; ++k) {
            Rows combs = allCombinations(n, k);
            CHECK(static_cast<long long>(combs.size()) == choose(n, k));
            CHECK_FALSE(has_duplicates(combs));
        }
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 80; ++trial) {
        const int n = rand_int(0, 7);
        std::vector<int> items = distinct_items(n);

        // Subsets: order inside each subset is the items' order, so only the outer vector is sorted.
        Rows subs = allSubsets(items);
        CHECK_FALSE(has_duplicates(subs));
        CHECK(outer_sorted(subs) == outer_sorted(brute_subsets(items)));

        // Permutations: inner order matters, outer is sorted.
        Rows perms = allPermutations(items);
        CHECK_FALSE(has_duplicates(perms));
        CHECK(outer_sorted(perms) == outer_sorted(brute_permutations(items)));

        const int m = rand_int(0, 8);
        const int k = rand_int(0, m);
        Rows combs = allCombinations(m, k);
        CHECK_FALSE(has_duplicates(combs));
        CHECK(outer_sorted(combs) == outer_sorted(brute_combinations(m, k)));
    }
}
