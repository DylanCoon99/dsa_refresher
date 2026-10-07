#include <swim_rising_water.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
using Grid = std::vector<std::vector<int>>;

Grid randomPermutationGrid(int n) {
    std::vector<int> v(n * n);
    std::iota(v.begin(), v.end(), 0);
    std::shuffle(v.begin(), v.end(), rng());
    Grid g(n, std::vector<int>(n));
    for (int i = 0; i < n * n; ++i) g[i / n][i % n] = v[i];
    return g;
}

// Brute force: DFS over every simple route, tracking the highest cell; keep the smallest.
void dfs(const Grid& g, std::vector<std::vector<bool>>& seen, int r, int c, int worst, int& best) {
    int n = static_cast<int>(g.size());
    if (r == n - 1 && c == n - 1) {
        best = std::min(best, worst);
        return;
    }
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nc < 0 || nr >= n || nc >= n || seen[nr][nc]) continue;
        seen[nr][nc] = true;
        dfs(g, seen, nr, nc, std::max(worst, g[nr][nc]), best);
        seen[nr][nc] = false;
    }
}

int brute(const Grid& g) {
    int n = static_cast<int>(g.size());
    std::vector<std::vector<bool>> seen(n, std::vector<bool>(n, false));
    seen[0][0] = true;
    int best = 1'000'000'000;
    dfs(g, seen, 0, 0, g[0][0], best);
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(swimInWater({{0, 2}, {1, 3}}) == 3);
    CHECK(swimInWater({{0, 1, 2, 3, 4}, {24, 23, 22, 21, 5}, {12, 13, 14, 15, 16}, {11, 17, 18, 19, 20}, {10, 9, 8, 7, 6}}) ==
          16);
    CHECK(swimInWater({{0}}) == 0);
}

TEST_CASE("single cell") {
    CHECK(swimInWater({{0}}) == 0);
}

TEST_CASE("2x2 grids") {
    CHECK(swimInWater({{0, 1}, {2, 3}}) == 3);
    CHECK(swimInWater({{0, 3}, {1, 2}}) == 2);
    CHECK(swimInWater({{1, 0}, {3, 2}}) == 2);
    CHECK(swimInWater({{2, 1}, {3, 0}}) == 2);  // the end cell is low but the start is 2
}

TEST_CASE("the start is the highest cell") {
    CHECK(swimInWater({{3, 0}, {1, 2}}) == 3);
    CHECK(swimInWater({{8, 0, 1}, {2, 3, 4}, {5, 6, 7}}) == 8);
}

TEST_CASE("the end is the highest cell") {
    CHECK(swimInWater({{0, 1, 2}, {3, 4, 5}, {6, 7, 8}}) == 8);
}

TEST_CASE("a detour beats a high direct route") {
    // The direct way down the middle passes 8; the route around the edge peaks at 5.
    Grid g{{0, 1, 2}, {8, 7, 3}, {6, 5, 4}};
    CHECK(swimInWater(g) == 4);
    Grid h{{0, 8, 5}, {1, 7, 4}, {2, 3, 6}};
    CHECK(swimInWater(h) == 6);
}

TEST_CASE("randomized vs path enumeration") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 5);
        Grid g = randomPermutationGrid(n);
        REQUIRE(swimInWater(g) == brute(g));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 50 x 50 serpentine corridor: rows 0, 2, ..., 48 joined by one connector cell in each odd row, then the
    // last cell (49, 49) below the end of row 48. Corridor cells get 0, 1, 2, ... in path order (L = 1275
    // cells); every other cell gets a shuffled value from L .. 2499. The route along the corridor peaks at
    // L - 1 = 1274, and any route that leaves the corridor must cross a cell with value >= L, so the answer is 1274.
    const int n = 50;
    Grid g(n, std::vector<int>(n, -1));
    int next = 0;
    for (int r = 0; r < n; r += 2) {
        bool leftToRight = (r / 2) % 2 == 0;
        for (int i = 0; i < n; ++i) g[r][leftToRight ? i : n - 1 - i] = next++;
        if (r + 1 < n) g[r + 1][leftToRight ? n - 1 : 0] = next++;
    }
    const int corridor = next;
    std::vector<int> walls;
    for (int v = corridor; v < n * n; ++v) walls.push_back(v);
    std::shuffle(walls.begin(), walls.end(), rng());
    size_t w = 0;
    for (auto& row : g)
        for (auto& x : row)
            if (x == -1) x = walls[w++];
    REQUIRE(w == walls.size());
    REQUIRE(g[0][0] == 0);
    CHECK(swimInWater(g) == corridor - 1);
    CHECK(corridor == 1275);
}
