#include <num_islands.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
using Grid = std::vector<std::vector<char>>;

// Reference: label propagation until stable (each land cell holds the smallest index in its island).
int brute(const Grid& g) {
    int rows = static_cast<int>(g.size()), cols = static_cast<int>(g[0].size());
    std::vector<std::vector<int>> label(rows, std::vector<int>(cols, -1));
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (g[r][c] == '1') label[r][c] = r * cols + c;
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
    int count = 0;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (label[r][c] == r * cols + c) ++count;
    return count;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(numIslands({{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}}) == 1);
    CHECK(numIslands({{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}}) == 3);
}

TEST_CASE("edge cases") {
    SUBCASE("all water") { CHECK(numIslands(Grid(3, std::vector<char>(4, '0'))) == 0); }
    SUBCASE("all land") { CHECK(numIslands(Grid(3, std::vector<char>(4, '1'))) == 1); }
    SUBCASE("1x1") {
        CHECK(numIslands({{'1'}}) == 1);
        CHECK(numIslands({{'0'}}) == 0);
    }
    SUBCASE("diagonal cells are not connected") {
        CHECK(numIslands({{'1', '0'}, {'0', '1'}}) == 2);
        CHECK(numIslands({{'1', '0', '0'}, {'0', '1', '0'}, {'0', '0', '1'}}) == 3);
    }
    SUBCASE("1xN") {
        CHECK(numIslands({{'1', '1', '0', '1', '0', '1', '1'}}) == 3);
        CHECK(numIslands({{'1', '1', '1'}}) == 1);
    }
    SUBCASE("Nx1") {
        CHECK(numIslands({{'1'}, {'0'}, {'1'}, {'1'}, {'0'}}) == 2);
        CHECK(numIslands({{'0'}, {'0'}}) == 0);
    }
    SUBCASE("a spiral is one island") {
        CHECK(numIslands({{'1', '1', '1', '1', '1'}, {'0', '0', '0', '0', '1'}, {'1', '1', '1', '0', '1'}, {'1', '0', '0', '0', '1'}, {'1', '1', '1', '1', '1'}}) == 1);
    }
    SUBCASE("checkerboard") {
        Grid g(4, std::vector<char>(4, '0'));
        for (int r = 0; r < 4; ++r)
            for (int c = 0; c < 4; ++c) g[r][c] = ((r + c) % 2 == 0) ? '1' : '0';
        CHECK(numIslands(g) == 8);
    }
}

TEST_CASE("randomized vs label propagation") {
    for (int trial = 0; trial < 300; ++trial) {
        int rows = rand_int(1, 8), cols = rand_int(1, 8);
        Grid g(rows, std::vector<char>(cols));
        for (auto& row : g)
            for (char& c : row) c = rand_int(0, 99) < 45 ? '1' : '0';
        CHECK(numIslands(g) == brute(g));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 300 x 300, all land: one island. Recursive DFS on this grid is 90000 calls deep and may
    // overflow the stack; a per-cell flood fill (O((rows*cols)^2)) does not finish in time.
    Grid g(300, std::vector<char>(300, '1'));
    CHECK(numIslands(g) == 1);
}
