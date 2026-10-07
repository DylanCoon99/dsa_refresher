#include <graph_traversal.hpp>

#include <doctest.h>
#include <graph.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <cstdlib>
#include <string>
#include <vector>

namespace {
using Grid = std::vector<std::string>;
using Dist = std::vector<std::vector<int>>;

// Test-side references: BFS using the order list itself as the queue, and plain recursive DFS
// (the random graphs here are small, so recursion depth is not a concern).
std::vector<int> refBfs(const Graph& g, int s) {
    std::vector<char> seen(g.size(), 0);
    std::vector<int> order{s};
    seen[s] = 1;
    for (std::size_t i = 0; i < order.size(); ++i) {
        for (int w : g[order[i]]) {
            if (!seen[w]) {
                seen[w] = 1;
                order.push_back(w);
            }
        }
    }
    return order;
}

void refDfs(const Graph& g, int v, std::vector<char>& seen, std::vector<int>& order) {
    seen[v] = 1;
    order.push_back(v);
    for (int w : g[v]) {
        if (!seen[w]) refDfs(g, w, seen, order);
    }
}

std::vector<int> refDfsOrder(const Graph& g, int s) {
    std::vector<char> seen(g.size(), 0);
    std::vector<int> order;
    refDfs(g, s, seen, order);
    return order;
}

void checkBoth(const Graph& g, int s, const std::vector<int>& bfs, const std::vector<int>& dfs) {
    CHECK(bfsOrder(g, s) == bfs);
    CHECK(dfsOrder(g, s) == dfs);
}
}  // namespace

TEST_CASE("examples") {
    // 0 -> 1, 2;  1 -> 3;  2 -> 3;  3 -> (none)
    Graph g = {{1, 2}, {3}, {3}, {}};
    checkBoth(g, 0, {0, 1, 2, 3}, {0, 1, 3, 2});

    // A branching tree: BFS goes level by level, DFS goes deep first.
    Graph t = {{1, 2}, {3, 4}, {5}, {}, {}, {}};
    checkBoth(t, 0, {0, 1, 2, 3, 4, 5}, {0, 1, 3, 4, 2, 5});

    Grid grid = {"..#", "...", "#.."};
    CHECK(gridDistances(grid, 0, 0) == Dist{{0, 1, -1}, {1, 2, 3}, {-1, 3, 4}});
    CHECK(countRegions({"..#", "#.#", "..#"}) == 1);
    CHECK(countRegions({".#.", "###", ".#."}) == 4);
}

TEST_CASE("graph edge cases") {
    SUBCASE("disconnected graph lists only reachable vertices") {
        Graph g = {{1}, {0}, {3}, {2}, {}};
        checkBoth(g, 0, {0, 1}, {0, 1});
        checkBoth(g, 2, {2, 3}, {2, 3});
    }
    SUBCASE("self-loop") {
        Graph g = {{0, 1}, {1, 2}, {}};
        checkBoth(g, 0, {0, 1, 2}, {0, 1, 2});
    }
    SUBCASE("start is isolated") {
        Graph g = {{}, {2}, {1}};
        checkBoth(g, 0, {0}, {0});
    }
    SUBCASE("single vertex") {
        Graph g = {{}};
        checkBoth(g, 0, {0}, {0});
    }
    SUBCASE("cycle") {
        Graph g = {{1}, {2}, {0}};
        checkBoth(g, 1, {1, 2, 0}, {1, 2, 0});
    }
    SUBCASE("diamond with a back edge") {
        Graph g = {{2, 1}, {3}, {3}, {0}};
        checkBoth(g, 0, {0, 2, 1, 3}, {0, 2, 3, 1});
    }
    SUBCASE("repeated (parallel) edges") {
        Graph g = {{1, 1, 2}, {2, 2}, {}};
        checkBoth(g, 0, {0, 1, 2}, {0, 1, 2});
    }
}

TEST_CASE("grid edge cases") {
    SUBCASE("1x1 open grid") {
        CHECK(gridDistances({"."}, 0, 0) == Dist{{0}});
        CHECK(countRegions({"."}) == 1);
    }
    SUBCASE("1x1 wall") { CHECK(countRegions({"#"}) == 0); }
    SUBCASE("start surrounded by walls") {
        Grid g = {"###", "#.#", "###"};
        CHECK(gridDistances(g, 1, 1) == Dist{{-1, -1, -1}, {-1, 0, -1}, {-1, -1, -1}});
        Grid h = {"#.#", ".#.", "#.#"};
        CHECK(countRegions(h) == 4);
    }
    SUBCASE("unreachable open cells are -1") {
        Grid g = {".#.", ".#.", ".#."};
        CHECK(gridDistances(g, 0, 0) == Dist{{0, -1, -1}, {1, -1, -1}, {2, -1, -1}});
    }
    SUBCASE("path must go around walls") {
        Grid g = {"...", ".#.", "..."};
        CHECK(gridDistances(g, 0, 0) == Dist{{0, 1, 2}, {1, -1, 3}, {2, 3, 4}});
    }
    SUBCASE("diagonal cells are not connected") {
        CHECK(countRegions({".#", "#."}) == 2);
        CHECK(gridDistances({".#", "#."}, 0, 0) == Dist{{0, -1}, {-1, -1}});
    }
    SUBCASE("single row and single column") {
        CHECK(gridDistances({"..#.."}, 0, 1) == Dist{{1, 0, -1, -1, -1}});
        CHECK(gridDistances({".", ".", "#", "."}, 1, 0) == Dist{{1}, {0}, {-1}, {-1}});
        CHECK(countRegions({"..#.."}) == 2);
    }
}

TEST_CASE("randomized graphs vs reference BFS/DFS") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 12), m = rand_int(0, 25);
        Graph g(n);
        for (int i = 0; i < m; ++i) {
            int u = rand_int(0, n - 1), v = rand_int(0, n - 1);  // may be self-loops or repeats
            g[u].push_back(v);
            if (rand_int(0, 1)) g[v].push_back(u);
        }
        int s = rand_int(0, n - 1);
        CHECK(bfsOrder(g, s) == refBfs(g, s));
        CHECK(dfsOrder(g, s) == refDfsOrder(g, s));
    }
}

TEST_CASE("randomized grids vs relaxation reference") {
    for (int trial = 0; trial < 100; ++trial) {
        int rows = rand_int(1, 7), cols = rand_int(1, 7);
        Grid g(rows, std::string(cols, '.'));
        for (auto& row : g)
            for (char& c : row)
                if (rand_int(0, 99) < 30) c = '#';
        int sr = rand_int(0, rows - 1), sc = rand_int(0, cols - 1);
        g[sr][sc] = '.';
        // Reference: Bellman-Ford style relaxation until nothing changes.
        Dist want(rows, std::vector<int>(cols, -1));
        want[sr][sc] = 0;
        for (bool changed = true; changed;) {
            changed = false;
            for (int r = 0; r < rows; ++r)
                for (int c = 0; c < cols; ++c) {
                    if (g[r][c] != '.') continue;
                    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || want[nr][nc] < 0) continue;
                        if (want[r][c] < 0 || want[nr][nc] + 1 < want[r][c]) {
                            want[r][c] = want[nr][nc] + 1;
                            changed = true;
                        }
                    }
                }
        }
        CHECK(gridDistances(g, sr, sc) == want);
        // Regions: label propagation (each open cell takes the smallest index in its region).
        std::vector<std::vector<int>> label(rows, std::vector<int>(cols, -1));
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (g[r][c] == '.') label[r][c] = r * cols + c;
        for (bool changed = true; changed;) {
            changed = false;
            for (int r = 0; r < rows; ++r)
                for (int c = 0; c < cols; ++c) {
                    if (label[r][c] < 0) continue;
                    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || label[nr][nc] < 0) continue;
                        if (label[nr][nc] < label[r][c]) {
                            label[r][c] = label[nr][nc];
                            changed = true;
                        }
                    }
                }
        }
        int regions = 0;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (label[r][c] == r * cols + c) ++regions;
        CHECK(countRegions(g) == regions);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 300 x 300 fully open grid. From (150, 77) the distance to (r, c) is |r-150| + |c-77|, and the
    // whole grid is a single region. A per-cell BFS (O((rows*cols)^2)) does not finish in time.
    const int n = 300, sr = 150, sc = 77;
    Grid g(n, std::string(n, '.'));
    Dist want(n, std::vector<int>(n));
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c) want[r][c] = std::abs(r - sr) + std::abs(c - sc);
    Dist got = gridDistances(g, sr, sc);
    bool same = got == want;
    CHECK(same);
    CHECK(countRegions(g) == 1);
}
