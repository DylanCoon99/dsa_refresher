#include <min_effort_path.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <cstdlib>
#include <vector>

namespace {
using Grid = std::vector<std::vector<int>>;

// Brute force: DFS over every simple route, tracking the largest step; keep the best.
void dfs(const Grid& g, std::vector<std::vector<bool>>& seen, int r, int c, int worst, int& best) {
    int rows = static_cast<int>(g.size()), cols = static_cast<int>(g[0].size());
    if (r == rows - 1 && c == cols - 1) {
        best = std::min(best, worst);
        return;
    }
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || seen[nr][nc]) continue;
        seen[nr][nc] = true;
        dfs(g, seen, nr, nc, std::max(worst, std::abs(g[nr][nc] - g[r][c])), best);
        seen[nr][nc] = false;
    }
}

int brute(const Grid& g) {
    std::vector<std::vector<bool>> seen(g.size(), std::vector<bool>(g[0].size(), false));
    seen[0][0] = true;
    int best = 1'000'000'000;
    dfs(g, seen, 0, 0, 0, best);
    return best;
}

// Independent reference for the large random grid: binary search on the allowed step, BFS to check.
int binarySearchBfs(const Grid& g) {
    int rows = static_cast<int>(g.size()), cols = static_cast<int>(g[0].size());
    auto reachable = [&](int limit) {
        std::vector<std::vector<bool>> seen(rows, std::vector<bool>(cols, false));
        std::vector<std::pair<int, int>> stack{{0, 0}};
        seen[0][0] = true;
        const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (!stack.empty()) {
            auto [r, c] = stack.back();
            stack.pop_back();
            if (r == rows - 1 && c == cols - 1) return true;
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || seen[nr][nc]) continue;
                if (std::abs(g[nr][nc] - g[r][c]) > limit) continue;
                seen[nr][nc] = true;
                stack.push_back({nr, nc});
            }
        }
        return false;
    };
    int lo = 0, hi = 1'000'000;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (reachable(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(minimumEffortPath({{1, 2, 2}, {3, 8, 2}, {5, 3, 5}}) == 2);
    CHECK(minimumEffortPath({{1, 2, 3}, {3, 8, 4}, {5, 3, 5}}) == 1);
    CHECK(minimumEffortPath({{7}}) == 0);
}

TEST_CASE("single cell") {
    CHECK(minimumEffortPath({{1}}) == 0);
    CHECK(minimumEffortPath({{1'000'000}}) == 0);
}

TEST_CASE("single row and single column") {
    CHECK(minimumEffortPath({{1, 5, 2, 9}}) == 7);
    CHECK(minimumEffortPath({{1}, {5}, {2}}) == 4);
    CHECK(minimumEffortPath({{4, 4, 4, 4, 4}}) == 0);
    CHECK(minimumEffortPath({{3, 1}}) == 2);
}

TEST_CASE("equal heights") {
    CHECK(minimumEffortPath({{5, 5, 5}, {5, 5, 5}, {5, 5, 5}}) == 0);
    // Equal heights along a detour: the corridor of 7s costs 0 even though it is longer.
    CHECK(minimumEffortPath({{7, 7, 7}, {1, 1, 7}, {9, 9, 7}}) == 0);
}

TEST_CASE("a longer route has the smaller effort") {
    // The direct way down the middle jumps from 1 to 10; going around keeps every step at 1.
    Grid g{{1, 2, 3}, {9, 10, 4}, {8, 9, 5}};
    CHECK(minimumEffortPath(g) == 1);
    // Going straight costs 9 on the first step; the detour along the top costs 1.
    CHECK(minimumEffortPath({{1, 2}, {10, 3}}) == 1);
}

TEST_CASE("heights at the extremes") {
    CHECK(minimumEffortPath({{1, 1'000'000}}) == 999'999);
    CHECK(minimumEffortPath({{1'000'000, 1}, {1, 1'000'000}}) == 999'999);
}

TEST_CASE("randomized vs path enumeration") {
    for (int trial = 0; trial < 200; ++trial) {
        int rows = rand_int(1, 4), cols = rand_int(1, 4);
        Grid g(rows, std::vector<int>(cols));
        int hi = rand_int(1, 4) == 1 ? 1'000'000 : 10;
        for (auto& row : g)
            for (auto& x : row) x = rand_int(1, hi);
        REQUIRE(minimumEffortPath(g) == brute(g));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 100 x 100 serpentine corridor. Corridor cells hold 1, 2, 3, ... in path order (rows 0, 2, ..., 98
    // joined by one connector cell in each odd row, then all of row 99); every other cell is 10^6.
    // Any step between two corridor cells that are not consecutive on the path differs by at least 2, and
    // any step from the corridor into a wall differs by about 10^6, so only the path itself has effort 1.
    const int n = 100;
    Grid g(n, std::vector<int>(n, 1'000'000));
    int next = 1;
    for (int r = 0; r < n - 1; r += 2) {
        bool leftToRight = (r / 2) % 2 == 0;
        for (int i = 0; i < n; ++i) g[r][leftToRight ? i : n - 1 - i] = next++;
        if (r + 2 < n - 1) g[r + 1][leftToRight ? n - 1 : 0] = next++;
    }
    // Row 98 runs right to left and ends at column 0; row 99 continues from there.
    g[98 + 1][0] = next++;
    for (int c = 1; c < n; ++c) g[99][c] = next++;
    CHECK(minimumEffortPath(g) == 1);

    // A random 100 x 100 grid, checked against binary search + flood fill.
    Grid h(n, std::vector<int>(n));
    for (auto& row : h)
        for (auto& x : row) x = rand_int(1, 1'000'000);
    int expected = binarySearchBfs(h);
    CHECK(expected > 0);
    CHECK(minimumEffortPath(h) == expected);
}
