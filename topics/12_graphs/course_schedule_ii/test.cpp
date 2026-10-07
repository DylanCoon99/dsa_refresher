#include <course_schedule_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
using Prereqs = std::vector<std::vector<int>>;

// True when `order` lists every course once and puts each prerequisite before its course.
bool validOrder(int n, const Prereqs& prereqs, const std::vector<int>& order) {
    if (static_cast<int>(order.size()) != n) return false;
    std::vector<int> pos(n, -1);
    for (int i = 0; i < n; ++i) {
        if (order[i] < 0 || order[i] >= n || pos[order[i]] != -1) return false;
        pos[order[i]] = i;
    }
    for (const auto& p : prereqs)
        if (pos[p[1]] >= pos[p[0]]) return false;
    return true;
}

void checkPossible(int n, const Prereqs& prereqs) { CHECK(validOrder(n, prereqs, findOrder(n, prereqs))); }
void checkImpossible(int n, const Prereqs& prereqs) { CHECK(findOrder(n, prereqs).empty()); }

bool brute(int n, const Prereqs& prereqs) {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    do {
        if (validOrder(n, prereqs, p)) return true;
    } while (std::next_permutation(p.begin(), p.end()));
    return false;
}
}  // namespace

TEST_CASE("examples") {
    checkPossible(2, {{1, 0}});
    CHECK(findOrder(2, {{1, 0}}) == std::vector<int>{0, 1});
    checkPossible(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}});
    checkImpossible(2, {{1, 0}, {0, 1}});
}

TEST_CASE("edge cases") {
    SUBCASE("no prerequisites: isolated courses are all included") { checkPossible(5, {}); }
    SUBCASE("single course") { CHECK(findOrder(1, {}) == std::vector<int>{0}); }
    SUBCASE("some courses isolated, some constrained") { checkPossible(6, {{1, 0}, {1, 4}}); }
    SUBCASE("cycle -> empty") { checkImpossible(3, {{1, 0}, {2, 1}, {0, 2}}); }
    SUBCASE("self-dependency -> empty") {
        checkImpossible(1, {{0, 0}});
        checkImpossible(3, {{1, 0}, {2, 2}});
    }
    SUBCASE("cycle in one component, the rest fine") { checkImpossible(6, {{1, 0}, {3, 2}, {4, 3}, {2, 4}}); }
    SUBCASE("prerequisites against the label order") { checkPossible(4, {{0, 1}, {1, 2}, {2, 3}}); }
    SUBCASE("repeated prerequisites") { checkPossible(3, {{1, 0}, {1, 0}, {2, 1}}); }
    SUBCASE("a chain has exactly one valid order") {
        CHECK(findOrder(4, {{0, 1}, {1, 2}, {2, 3}}) == std::vector<int>{3, 2, 1, 0});
    }
}

TEST_CASE("randomized vs permutation brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(1, 7), m = rand_int(0, 9);
        Prereqs prereqs;
        for (int i = 0; i < m; ++i) prereqs.push_back({rand_int(0, n - 1), rand_int(0, n - 1)});
        auto got = findOrder(n, prereqs);
        if (brute(n, prereqs)) {
            CHECK(validOrder(n, prereqs, got));
        } else {
            CHECK(got.empty());
        }
    }
}
