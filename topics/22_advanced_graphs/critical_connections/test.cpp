#include <critical_connections.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

namespace {
using Conns = std::vector<std::vector<int>>;

// Orient each pair as {min, max}, then sort the list, so any valid answer compares equal.
Conns normalize(Conns c) {
    for (auto& e : c)
        if (e.size() == 2 && e[0] > e[1]) std::swap(e[0], e[1]);
    std::sort(c.begin(), c.end());
    return c;
}

// Components among all n servers using every connection except index `skip`.
int components(int n, const Conns& conns, int skip) {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    auto find = [&](int x) {
        while (p[x] != x) x = p[x] = p[p[x]];
        return x;
    };
    for (int i = 0; i < static_cast<int>(conns.size()); ++i)
        if (i != skip) p[find(conns[i][0])] = find(conns[i][1]);
    int c = 0;
    for (int v = 0; v < n; ++v)
        if (find(v) == v) ++c;
    return c;
}

// Brute force: a connection is critical if removing it increases the component count.
Conns bruteForce(int n, const Conns& conns) {
    int base = components(n, conns, -1);
    Conns out;
    for (int i = 0; i < static_cast<int>(conns.size()); ++i)
        if (components(n, conns, i) > base) out.push_back(conns[i]);
    return normalize(out);
}

// Random connected simple graph on n vertices with m edges (n-1 <= m <= n(n-1)/2).
Conns randomConnected(int n, int m) {
    Conns edges;
    std::set<std::pair<int, int>> seen;
    auto add = [&](int a, int b) {
        if (a > b) std::swap(a, b);
        if (a == b || !seen.insert({a, b}).second) return false;
        edges.push_back({a, b});
        return true;
    };
    for (int v = 1; v < n; ++v) add(rand_int(0, v - 1), v);  // a random spanning tree
    while (static_cast<int>(edges.size()) < m) add(rand_int(0, n - 1), rand_int(0, n - 1));
    return edges;
}
}  // namespace

TEST_CASE("examples") {
    // A triangle 0-1-2 with a tail 1-3: only the tail edge is critical.
    CHECK(normalize(criticalConnections(4, {{0, 1}, {1, 2}, {2, 0}, {1, 3}})) == Conns{{1, 3}});
    // A path: every edge is critical.
    CHECK(normalize(criticalConnections(4, {{0, 1}, {1, 2}, {2, 3}})) == Conns{{0, 1}, {1, 2}, {2, 3}});
}

TEST_CASE("edge cases") {
    SUBCASE("n = 2 with a single connection") {
        CHECK(normalize(criticalConnections(2, {{0, 1}})) == Conns{{0, 1}});
        CHECK(normalize(criticalConnections(2, {{1, 0}})) == Conns{{0, 1}});
    }
    SUBCASE("a triangle has no critical connection") {
        CHECK(criticalConnections(3, {{0, 1}, {1, 2}, {2, 0}}).empty());
    }
    SUBCASE("two triangles joined by one edge") {
        Conns c = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 3}, {2, 3}};
        CHECK(normalize(criticalConnections(6, c)) == Conns{{2, 3}});
    }
    SUBCASE("a long cycle with a pendant vertex on each side") {
        Conns c = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, {0, 5}, {3, 6}};
        CHECK(normalize(criticalConnections(7, c)) == Conns{{0, 5}, {3, 6}});
    }
    SUBCASE("the answer may list either orientation of a pair") {
        CHECK(normalize(criticalConnections(3, {{2, 1}, {1, 0}})) == Conns{{0, 1}, {1, 2}});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(2, 12);
        int maxM = n * (n - 1) / 2;
        int m = rand_int(n - 1, std::min(maxM, n + 5));
        Conns edges = randomConnected(n, m);
        std::shuffle(edges.begin(), edges.end(), rng());
        for (auto& e : edges)
            if (rand_int(0, 1)) std::swap(e[0], e[1]);
        INFO("trial " << trial << ", n = " << n << ", m = " << m);
        CHECK(normalize(criticalConnections(n, edges)) == bruteForce(n, edges));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 2*10^4 servers, 6*10^4 connections, all distinct. A tree of blocks: single vertices, or groups of
    // 3..30 vertices wired as a cycle plus distinct extra chords (no connection inside a group is critical).
    // Groups are joined by single connections, mostly in a long chain; those are exactly the critical ones.
    const int n = 20'000, target = 60'000;
    std::vector<std::vector<int>> units;
    for (int next = 0; next < n;) {
        int s = rand_int(0, 9) < 4 ? 1 : rand_int(3, 30);
        s = std::min(s, n - next);
        if (s == 2) s = 1;  // a 2-vertex group would need a repeated connection
        std::vector<int> u(s);
        std::iota(u.begin(), u.end(), next);
        units.push_back(u);
        next += s;
    }
    Conns edges;
    std::set<std::pair<int, int>> seen;
    auto add = [&](int a, int b) {
        if (a > b) std::swap(a, b);
        if (a == b || !seen.insert({a, b}).second) return false;
        edges.push_back({a, b});
        return true;
    };
    std::vector<int> multi;
    for (int i = 0; i < static_cast<int>(units.size()); ++i) {
        const auto& u = units[i];
        int k = static_cast<int>(u.size());
        if (k >= 3) {
            for (int j = 0; j < k; ++j) add(u[j], u[(j + 1) % k]);
            multi.push_back(i);
        }
    }
    Conns critical;
    for (int i = 1; i < static_cast<int>(units.size()); ++i) {
        int parent = (i % 3 == 0) ? rand_int(0, i - 1) : i - 1;
        int a = units[parent][rand_int(0, static_cast<int>(units[parent].size()) - 1)];
        int b = units[i][rand_int(0, static_cast<int>(units[i].size()) - 1)];
        REQUIRE(add(a, b));
        critical.push_back({a, b});
    }
    int guard = 0;
    while (static_cast<int>(edges.size()) < target && ++guard < 10'000'000) {
        const auto& u = units[multi[rand_int(0, static_cast<int>(multi.size()) - 1)]];
        add(u[rand_int(0, static_cast<int>(u.size()) - 1)], u[rand_int(0, static_cast<int>(u.size()) - 1)]);
    }
    REQUIRE(static_cast<int>(edges.size()) == target);

    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(), perm.end(), rng());
    for (auto& e : edges) e = {perm[e[0]], perm[e[1]]};
    for (auto& e : critical) e = {perm[e[0]], perm[e[1]]};
    std::shuffle(edges.begin(), edges.end(), rng());
    Conns expected = normalize(critical);

    Conns got = normalize(criticalConnections(n, edges));
    CHECK(got.size() == expected.size());
    bool same = got == expected;
    CHECK(same);
}
