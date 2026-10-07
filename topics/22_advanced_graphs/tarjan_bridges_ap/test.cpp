#include <tarjan_bridges_ap.hpp>

#include <doctest.h>
#include <graph.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

namespace {
using Edges = std::vector<std::pair<int, int>>;
using Pairs = std::vector<std::pair<int, int>>;

// Undirected graph from an edge list; a repeated edge appears twice in each endpoint's list.
Graph build(int n, const Edges& edges) {
    Graph g(n);
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return g;
}

Pairs sortedBridges(int n, const Graph& g) {
    Pairs b = findBridges(n, g);
    std::sort(b.begin(), b.end());
    return b;
}
std::vector<int> sortedAPs(int n, const Graph& g) {
    auto a = findArticulationPoints(n, g);
    std::sort(a.begin(), a.end());
    return a;
}

// Number of connected components among the vertices not in `deadV`, ignoring edge index `deadE`.
int components(int n, const Edges& edges, int deadE, int deadV) {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    auto find = [&](int x) {
        while (p[x] != x) x = p[x] = p[p[x]];
        return x;
    };
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        if (i == deadE) continue;
        auto [u, v] = edges[i];
        if (u == deadV || v == deadV) continue;
        p[find(u)] = find(v);
    }
    int c = 0;
    for (int v = 0; v < n; ++v)
        if (v != deadV && find(v) == v) ++c;
    return c;
}

// Brute force: an edge is a bridge if deleting it adds a component; a vertex is an articulation
// point if deleting it (and its edges) leaves more components among the other vertices.
void bruteForce(int n, const Edges& edges, Pairs& bridges, std::vector<int>& aps) {
    int base = components(n, edges, -1, -1);
    for (int i = 0; i < static_cast<int>(edges.size()); ++i)
        if (components(n, edges, i, -1) > base)
            bridges.push_back({std::min(edges[i].first, edges[i].second), std::max(edges[i].first, edges[i].second)});
    std::sort(bridges.begin(), bridges.end());
    for (int v = 0; v < n; ++v)
        if (components(n, edges, -1, v) > base) aps.push_back(v);
}

void expectBoth(int n, const Edges& edges, Pairs bridges, std::vector<int> aps) {
    std::sort(bridges.begin(), bridges.end());
    std::sort(aps.begin(), aps.end());
    Graph g = build(n, edges);
    CHECK(sortedBridges(n, g) == bridges);
    CHECK(sortedAPs(n, g) == aps);
}
}  // namespace

TEST_CASE("examples") {
    // Two triangles joined by the edge 2-3: that edge is the only bridge, its endpoints the only cut vertices.
    expectBoth(6, {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 3}, {2, 3}}, {{2, 3}}, {2, 3});
    // A path 0-1-2-3: every edge is a bridge, the inner vertices are cut vertices.
    expectBoth(4, {{0, 1}, {1, 2}, {2, 3}}, {{0, 1}, {1, 2}, {2, 3}}, {1, 2});
}

TEST_CASE("edge cases") {
    SUBCASE("no vertices, one vertex, no edges") {
        expectBoth(0, {}, {}, {});
        expectBoth(1, {}, {}, {});
        expectBoth(3, {}, {}, {});
    }
    SUBCASE("a single edge: a bridge, but neither endpoint is a cut vertex") {
        expectBoth(2, {{0, 1}}, {{0, 1}}, {});
    }
    SUBCASE("a tree: every edge is a bridge") {
        // star centered at 0 with a tail: 0-1, 0-2, 0-3, 3-4, 4-5
        expectBoth(6, {{0, 1}, {0, 2}, {0, 3}, {3, 4}, {4, 5}}, {{0, 1}, {0, 2}, {0, 3}, {3, 4}, {4, 5}}, {0, 3, 4});
    }
    SUBCASE("the pair is reported as (min, max) even when given as (max, min)") {
        expectBoth(3, {{2, 1}, {1, 0}}, {{1, 2}, {0, 1}}, {1});
    }
    SUBCASE("a cycle has no bridges and no cut vertices") {
        expectBoth(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}, {}, {});
    }
    SUBCASE("two cycles joined by an edge") {
        expectBoth(7, {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 4}, {3, 4}}, {{3, 4}}, {3, 4});
    }
    SUBCASE("two cycles sharing one vertex: no bridge, one cut vertex") {
        expectBoth(5, {{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}, {4, 2}}, {}, {2});
    }
    SUBCASE("a disconnected graph") {
        // component A: path 0-1-2; component B: triangle 3-4-5; vertex 6 isolated; component C: edge 7-8
        expectBoth(9, {{0, 1}, {1, 2}, {3, 4}, {4, 5}, {5, 3}, {7, 8}}, {{0, 1}, {1, 2}, {7, 8}}, {1});
    }
    SUBCASE("parallel edges: a doubled edge is not a bridge") {
        // 0 = 1 (two edges) then 1 - 2: only 1-2 is a bridge, and vertex 1 is the only cut vertex.
        expectBoth(3, {{0, 1}, {0, 1}, {1, 2}}, {{1, 2}}, {1});
        // The same graph with the edges listed in a different order.
        expectBoth(3, {{1, 2}, {1, 0}, {0, 1}}, {{1, 2}}, {1});
    }
    SUBCASE("a doubled edge on a path makes that edge safe") {
        expectBoth(4, {{0, 1}, {1, 2}, {1, 2}, {2, 3}}, {{0, 1}, {2, 3}}, {1, 2});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        int n = rand_int(1, 12);
        int m = n >= 2 ? rand_int(0, 16) : 0;
        Edges edges;
        for (int i = 0; i < m; ++i) {
            int u = rand_int(0, n - 1), v = rand_int(0, n - 1);
            if (u == v) continue;  // no self-loops; repeated edges are allowed
            edges.push_back({u, v});
        }
        Pairs bb;
        std::vector<int> ba;
        bruteForce(n, edges, bb, ba);
        Graph g = build(n, edges);
        INFO("trial " << trial << ", n = " << n << ", m = " << edges.size());
        CHECK(sortedBridges(n, g) == bb);
        CHECK(sortedAPs(n, g) == ba);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 2*10^4 vertices, 6*10^4 edges. Built as a tree of "blocks": a single vertex, or 2+ vertices
    // that are 2-edge-connected and 2-vertex-connected (a doubled edge, or a cycle plus extra
    // chords, some repeated). Blocks are joined by single edges, mostly in a long chain, so the
    // bridges and cut vertices are known from the construction. Labels and edge order are shuffled.
    const int n = 20'000, target = 60'000;
    std::vector<std::vector<int>> units;
    for (int next = 0; next < n;) {
        int s = rand_int(0, 9) < 4 ? 1 : rand_int(2, 8);
        s = std::min(s, n - next);
        std::vector<int> u(s);
        std::iota(u.begin(), u.end(), next);
        units.push_back(u);
        next += s;
    }
    Edges edges;
    std::vector<int> bridgeDeg(n, 0), blockSize(n, 1);
    std::vector<int> multi;  // indices of units with >= 2 vertices
    for (int i = 0; i < static_cast<int>(units.size()); ++i) {
        const auto& u = units[i];
        int k = static_cast<int>(u.size());
        for (int v : u) blockSize[v] = k;
        if (k == 2) {
            edges.push_back({u[0], u[1]});
            edges.push_back({u[0], u[1]});
        } else if (k >= 3) {
            for (int j = 0; j < k; ++j) edges.push_back({u[j], u[(j + 1) % k]});
        }
        if (k >= 2) multi.push_back(i);
    }
    Pairs bridges;
    for (int i = 1; i < static_cast<int>(units.size()); ++i) {
        int parent = (i % 3 == 0) ? rand_int(0, i - 1) : i - 1;
        int a = units[parent][rand_int(0, static_cast<int>(units[parent].size()) - 1)];
        int b = units[i][rand_int(0, static_cast<int>(units[i].size()) - 1)];
        edges.push_back({a, b});
        bridges.push_back({a, b});
        ++bridgeDeg[a];
        ++bridgeDeg[b];
    }
    while (static_cast<int>(edges.size()) < target) {
        const auto& u = units[multi[rand_int(0, static_cast<int>(multi.size()) - 1)]];
        int a = u[rand_int(0, static_cast<int>(u.size()) - 1)], b = u[rand_int(0, static_cast<int>(u.size()) - 1)];
        if (a != b) edges.push_back({a, b});
    }
    // A vertex's removal leaves (its bridge subtrees) + (the rest of its block, if any) components.
    std::vector<int> aps;
    for (int v = 0; v < n; ++v)
        if (bridgeDeg[v] + (blockSize[v] >= 2 ? 1 : 0) >= 2) aps.push_back(v);

    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(), perm.end(), rng());
    for (auto& e : edges) e = {perm[e.first], perm[e.second]};
    std::shuffle(edges.begin(), edges.end(), rng());
    for (auto& b : bridges) {
        b = {perm[b.first], perm[b.second]};
        if (b.first > b.second) std::swap(b.first, b.second);
    }
    for (auto& v : aps) v = perm[v];
    std::sort(bridges.begin(), bridges.end());
    std::sort(aps.begin(), aps.end());

    REQUIRE(static_cast<int>(edges.size()) == target);
    Graph g = build(n, edges);
    Pairs gotB = sortedBridges(n, g);
    std::vector<int> gotA = sortedAPs(n, g);
    CHECK(gotB.size() == bridges.size());
    CHECK(gotA.size() == aps.size());
    bool sameB = gotB == bridges;
    bool sameA = gotA == aps;
    CHECK(sameB);
    CHECK(sameA);
}
