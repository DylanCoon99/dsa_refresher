#include <pacific_atlantic.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

namespace {
using Grid = std::vector<std::vector<int>>;
using Cells = std::vector<std::vector<int>>;

Cells normalize(Cells c) {
    std::sort(c.begin(), c.end());
    return c;
}

void check(const Grid& heights, const Cells& expected) {
    CHECK(normalize(pacificAtlantic(heights)) == normalize(expected));
}

// Brute force: from every cell, search downhill and note which borders are touched.
Cells brute(const Grid& h) {
    int rows = static_cast<int>(h.size()), cols = static_cast<int>(h[0].size());
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    Cells out;
    for (int sr = 0; sr < rows; ++sr)
        for (int sc = 0; sc < cols; ++sc) {
            std::vector<std::vector<char>> seen(rows, std::vector<char>(cols, 0));
            std::queue<std::pair<int, int>> q;
            q.push({sr, sc});
            seen[sr][sc] = 1;
            bool pac = false, atl = false;
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                if (r == 0 || c == 0) pac = true;
                if (r == rows - 1 || c == cols - 1) atl = true;
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nc < 0 || nr >= rows || nc >= cols || seen[nr][nc] || h[nr][nc] > h[r][c]) continue;
                    seen[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
            if (pac && atl) out.push_back({sr, sc});
        }
    return out;
}
}  // namespace

TEST_CASE("examples") {
    check({{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}},
          {{0, 4}, {1, 3}, {1, 4}, {2, 2}, {3, 0}, {3, 1}, {4, 0}});
    check({{1}}, {{0, 0}});
    check({{1, 1}, {1, 1}}, {{0, 0}, {0, 1}, {1, 0}, {1, 1}});
}

TEST_CASE("edge cases") {
    SUBCASE("1x1") { check({{7}}, {{0, 0}}); }
    SUBCASE("flat grid: every cell reaches both oceans") {
        check(Grid(3, std::vector<int>(4, 5)), brute(Grid(3, std::vector<int>(4, 5))));
        Cells all;
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 4; ++c) all.push_back({r, c});
        check(Grid(3, std::vector<int>(4, 5)), all);
    }
    SUBCASE("single row: every cell touches both the top and the bottom") {
        check({{3, 1, 4, 1, 5}}, {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}});
    }
    SUBCASE("single column") { check({{2}, {7}, {1}}, {{0, 0}, {1, 0}, {2, 0}}); }
    SUBCASE("a high peak in the middle drains to both oceans") {
        check({{1, 1, 1}, {1, 9, 1}, {1, 1, 1}}, brute({{1, 1, 1}, {1, 9, 1}, {1, 1, 1}}));
    }
    SUBCASE("a pit in the middle is not in the answer") {
        Grid g = {{5, 5, 5}, {5, 0, 5}, {5, 5, 5}};
        Cells got = normalize(pacificAtlantic(g));
        CHECK(std::find(got.begin(), got.end(), std::vector<int>{1, 1}) == got.end());
        CHECK(got == normalize(brute(g)));
    }
    SUBCASE("strictly increasing toward the bottom-right") {
        Grid g = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
        check(g, {{0, 2}, {1, 2}, {2, 0}, {2, 1}, {2, 2}});
    }
}

TEST_CASE("randomized vs per-cell search") {
    for (int trial = 0; trial < 200; ++trial) {
        int rows = rand_int(1, 6), cols = rand_int(1, 6);
        Grid g(rows, std::vector<int>(cols));
        for (auto& row : g)
            for (int& v : row) v = rand_int(0, 4);
        check(g, brute(g));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 300 x 300 with height r + c. Water can only flow toward smaller r + c, so every cell reaches
    // the top/left (Pacific), but only cells already on the bottom row or right column touch the
    // Atlantic. The answer is exactly those 299 + 300 = 599 cells. A per-cell search is
    // O((rows*cols)^2) and does not finish in time.
    const int n = 300;
    Grid g(n, std::vector<int>(n));
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c) g[r][c] = r + c;
    Cells expected;
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            if (r == n - 1 || c == n - 1) expected.push_back({r, c});
    Cells got = normalize(pacificAtlantic(g));
    bool same = got == normalize(expected);
    CHECK(same);
}
