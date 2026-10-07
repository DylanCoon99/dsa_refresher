#include <course_schedule.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
using Prereqs = std::vector<std::vector<int>>;

// Brute force: some ordering of all courses must put every prerequisite first.
bool brute(int n, const Prereqs& prereqs) {
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    do {
        std::vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[order[i]] = i;
        bool ok = true;
        for (const auto& p : prereqs)
            if (pos[p[1]] >= pos[p[0]]) ok = false;
        if (ok) return true;
    } while (std::next_permutation(order.begin(), order.end()));
    return false;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(canFinish(2, {{1, 0}}) == true);
    CHECK(canFinish(2, {{1, 0}, {0, 1}}) == false);
    CHECK(canFinish(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}) == true);
}

TEST_CASE("edge cases") {
    SUBCASE("no prerequisites") {
        CHECK(canFinish(1, {}) == true);
        CHECK(canFinish(5, {}) == true);
    }
    SUBCASE("2-cycle") { CHECK(canFinish(2, {{0, 1}, {1, 0}}) == false); }
    SUBCASE("self-dependency") {
        CHECK(canFinish(1, {{0, 0}}) == false);
        CHECK(canFinish(3, {{1, 0}, {2, 2}}) == false);
    }
    SUBCASE("long chain") { CHECK(canFinish(6, {{1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}}) == true); }
    SUBCASE("long cycle") { CHECK(canFinish(5, {{1, 0}, {2, 1}, {3, 2}, {4, 3}, {0, 4}}) == false); }
    SUBCASE("cycle in a component away from course 0") { CHECK(canFinish(5, {{1, 0}, {3, 4}, {4, 3}}) == false); }
    SUBCASE("repeated prerequisites") { CHECK(canFinish(2, {{1, 0}, {1, 0}}) == true); }
    SUBCASE("diamond") { CHECK(canFinish(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}) == true); }
}

TEST_CASE("randomized vs permutation brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(1, 7), m = rand_int(0, 9);
        Prereqs prereqs;
        for (int i = 0; i < m; ++i) prereqs.push_back({rand_int(0, n - 1), rand_int(0, n - 1)});
        CHECK(canFinish(n, prereqs) == brute(n, prereqs));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 courses in a chain (shuffled labels): perm[i+1] requires perm[i].
    const int n = 100'000;
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(), perm.end(), rng());
    Prereqs chain;
    for (int i = 0; i + 1 < n; ++i) chain.push_back({perm[i + 1], perm[i]});
    CHECK(canFinish(n, chain) == true);
    // Close the chain into one big cycle: perm[0] now requires perm[n-1].
    chain.push_back({perm[0], perm[n - 1]});
    CHECK(canFinish(n, chain) == false);
}
