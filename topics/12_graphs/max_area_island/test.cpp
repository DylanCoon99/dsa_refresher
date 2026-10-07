#include <max_area_island.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
using Grid = std::vector<std::vector<int>>;

// Reference: label propagation until stable, then count cells per label.
int brute(const Grid& g) {
    int rows = static_cast<int>(g.size()), cols = static_cast<int>(g[0].size());
    std::vector<std::vector<int>> label(rows, std::vector<int>(cols, -1));
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (g[r][c] == 1) label[r][c] = r * cols + c;
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    for (bool changed = true; changed;) {
        changed = false;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c) {
                if (label[r][c] < 0) continue;
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
    std::vector<int> count(rows * cols, 0);
    int best = 0;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (label[r][c] >= 0) best = std::max(best, ++count[label[r][c]]);
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(maxAreaOfIsland({{0, 1, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 1}}) == 3);
    CHECK(maxAreaOfIsland({{1, 1, 0, 1, 1}, {1, 0, 0, 0, 1}, {0, 0, 0, 0, 0}, {1, 1, 1, 1, 0}}) == 4);
    CHECK(maxAreaOfIsland({{0, 0, 0}, {0, 0, 0}}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("no land") { CHECK(maxAreaOfIsland(Grid(3, std::vector<int>(3, 0))) == 0); }
    SUBCASE("a single cell") {
        CHECK(maxAreaOfIsland({{1}}) == 1);
        CHECK(maxAreaOfIsland({{0}}) == 0);
        CHECK(maxAreaOfIsland({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}) == 1);
    }
    SUBCASE("two islands of equal size") { CHECK(maxAreaOfIsland({{1, 1, 0, 1, 1}, {0, 0, 0, 0, 0}}) == 2); }
    SUBCASE("all land") { CHECK(maxAreaOfIsland(Grid(4, std::vector<int>(5, 1))) == 20); }
    SUBCASE("diagonal cells are not connected") { CHECK(maxAreaOfIsland({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}) == 1); }
    SUBCASE("1xN and Nx1") {
        CHECK(maxAreaOfIsland({{1, 1, 0, 1, 1, 1}}) == 3);
        CHECK(maxAreaOfIsland({{1}, {1}, {1}, {0}, {1}}) == 3);
    }
    SUBCASE("a winding island larger than the straight ones") {
        CHECK(maxAreaOfIsland({{1, 1, 1, 1}, {0, 0, 0, 1}, {1, 1, 0, 1}, {0, 0, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 0}, {1, 1, 0, 0}}) == 11);
    }
}

TEST_CASE("randomized vs label propagation") {
    for (int trial = 0; trial < 300; ++trial) {
        int rows = rand_int(1, 8), cols = rand_int(1, 8);
        Grid g(rows, std::vector<int>(cols));
        for (auto& row : g)
            for (int& c : row) c = rand_int(0, 99) < 50 ? 1 : 0;
        CHECK(maxAreaOfIsland(g) == brute(g));
    }
}
