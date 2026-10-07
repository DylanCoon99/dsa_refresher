#include <rotting_oranges.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
using Grid = std::vector<std::vector<int>>;

// Reference: simulate minute by minute on a copy.
int simulate(Grid g) {
    int rows = static_cast<int>(g.size()), cols = static_cast<int>(g[0].size());
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    int minutes = 0;
    for (;;) {
        Grid next = g;
        bool changed = false;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c) {
                if (g[r][c] != 1) continue;
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && g[nr][nc] == 2) {
                        next[r][c] = 2;
                        changed = true;
                        break;
                    }
                }
            }
        if (!changed) break;
        g = next;
        ++minutes;
    }
    for (const auto& row : g)
        for (int v : row)
            if (v == 1) return -1;
    return minutes;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(orangesRotting({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}) == 4);
    CHECK(orangesRotting({{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}) == -1);
    CHECK(orangesRotting({{0, 2}}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("no fresh oranges") {
        CHECK(orangesRotting({{0}}) == 0);
        CHECK(orangesRotting({{2, 2}, {0, 2}}) == 0);
    }
    SUBCASE("unreachable fresh orange") { CHECK(orangesRotting({{2, 0, 1}}) == -1); }
    SUBCASE("walled-off fresh orange while others rot") { CHECK(orangesRotting({{2, 1, 0, 1}}) == -1); }
    SUBCASE("no rotten orange but fresh present") {
        CHECK(orangesRotting({{1}}) == -1);
        CHECK(orangesRotting({{1, 1}, {0, 1}}) == -1);
    }
    SUBCASE("single fresh next to single rotten") { CHECK(orangesRotting({{2, 1}}) == 1); }
    SUBCASE("multi-source spread is simultaneous") {
        // Rotten at both ends of a row of 7 fresh: the middle rots after 4 minutes, not 7.
        CHECK(orangesRotting({{2, 1, 1, 1, 1, 1, 1, 1, 2}}) == 4);
        CHECK(orangesRotting({{2, 1, 1, 1, 1, 1, 2}}) == 3);
    }
    SUBCASE("rotten oranges in opposite corners") { CHECK(orangesRotting({{2, 1, 1}, {1, 1, 1}, {1, 1, 2}}) == 2); }
    SUBCASE("single column") { CHECK(orangesRotting({{1}, {1}, {2}, {1}, {1}, {1}}) == 3); }
}

TEST_CASE("randomized vs minute-by-minute simulation") {
    for (int trial = 0; trial < 300; ++trial) {
        int rows = rand_int(1, 6), cols = rand_int(1, 6);
        Grid g(rows, std::vector<int>(cols));
        for (auto& row : g)
            for (int& v : row) {
                int x = rand_int(0, 99);
                v = x < 20 ? 0 : (x < 85 ? 1 : 2);
            }
        CHECK(orangesRotting(g) == simulate(g));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 300 x 300 of fresh oranges with a rotten one in each corner. A fresh cell (r, c) rots after
    // min(r, 299-r) + min(c, 299-c) minutes (distance to the nearest corner), so the answer is the
    // largest such value: 149 + 149 = 298. A per-orange BFS is O((rows*cols)^2) and does not finish in time.
    const int n = 300;
    Grid g(n, std::vector<int>(n, 1));
    g[0][0] = g[0][n - 1] = g[n - 1][0] = g[n - 1][n - 1] = 2;
    CHECK(orangesRotting(g) == 298);
}
