#include <prefix_sum_2d.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <climits>
#include <vector>

namespace {
using Grid = std::vector<std::vector<int>>;

long long brute(const Grid& g, int r1, int c1, int r2, int c2) {
    long long s = 0;
    for (int r = r1; r <= r2; ++r)
        for (int c = c1; c <= c2; ++c) s += g[r][c];
    return s;
}

// Sum of the integers a..b.
long long range_total(long long a, long long b) { return (a + b) * (b - a + 1) / 2; }
}  // namespace

TEST_CASE("examples") {
    const Grid g = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
    PrefixSum2D ps(g);
    CHECK(ps.sumRegion(2, 1, 4, 3) == 8);
    CHECK(ps.sumRegion(1, 1, 2, 2) == 11);
    CHECK(ps.sumRegion(1, 2, 2, 4) == 12);
}

TEST_CASE("edge cases") {
    SUBCASE("1x1 grid") {
        PrefixSum2D ps({{5}});
        CHECK(ps.sumRegion(0, 0, 0, 0) == 5);
    }
    SUBCASE("1x1 grid with a negative value") {
        PrefixSum2D ps({{-7}});
        CHECK(ps.sumRegion(0, 0, 0, 0) == -7);
    }
    SUBCASE("full-grid query") {
        const Grid g = {{1, 2, 3}, {4, 5, 6}};
        PrefixSum2D ps(g);
        CHECK(ps.sumRegion(0, 0, 1, 2) == 21);
    }
    SUBCASE("single row and single column grids") {
        PrefixSum2D row({{1, -2, 3, -4}});
        CHECK(row.sumRegion(0, 1, 0, 3) == -3);
        PrefixSum2D col({{1}, {-2}, {3}, {-4}});
        CHECK(col.sumRegion(1, 0, 3, 0) == -3);
    }
    SUBCASE("single cell inside a larger grid") {
        const Grid g = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        PrefixSum2D ps(g);
        CHECK(ps.sumRegion(1, 1, 1, 1) == 5);
        CHECK(ps.sumRegion(2, 2, 2, 2) == 9);
        CHECK(ps.sumRegion(0, 2, 0, 2) == 3);
    }
    SUBCASE("rectangles touching the top-left border") {
        const Grid g = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        PrefixSum2D ps(g);
        CHECK(ps.sumRegion(0, 0, 0, 0) == 1);
        CHECK(ps.sumRegion(0, 0, 1, 1) == 12);
        CHECK(ps.sumRegion(0, 1, 2, 1) == 15);
        CHECK(ps.sumRegion(1, 0, 1, 2) == 15);
    }
    SUBCASE("values near INT_MAX overflow int") {
        const Grid g(2, std::vector<int>(2, INT_MAX));
        PrefixSum2D ps(g);
        CHECK(ps.sumRegion(0, 0, 1, 1) == 4LL * INT_MAX);
        CHECK(ps.sumRegion(0, 0, 0, 1) == 2LL * INT_MAX);
        CHECK(ps.sumRegion(1, 1, 1, 1) == INT_MAX);
    }
    SUBCASE("values near INT_MIN") {
        const Grid g(2, std::vector<int>(3, INT_MIN));
        PrefixSum2D ps(g);
        CHECK(ps.sumRegion(0, 0, 1, 2) == 6LL * INT_MIN);
    }
    SUBCASE("mixed extremes cancel") {
        const Grid g = {{INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}};
        PrefixSum2D ps(g);
        CHECK(ps.sumRegion(0, 0, 1, 1) == -2);
        CHECK(ps.sumRegion(0, 0, 0, 1) == -1);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int rows = rand_int(1, 8), cols = rand_int(1, 8);
        Grid g(rows);
        for (auto& row : g) row = rand_vec(cols, -100, 100);
        PrefixSum2D ps(g);
        for (int q = 0; q < 20; ++q) {
            const int r1 = rand_int(0, rows - 1), r2 = rand_int(r1, rows - 1);
            const int c1 = rand_int(0, cols - 1), c2 = rand_int(c1, cols - 1);
            CHECK(ps.sumRegion(r1, c1, r2, c2) == brute(g, r1, c1, r2, c2));
        }
    }
}

TEST_CASE("randomized with huge values") {
    for (int trial = 0; trial < 100; ++trial) {
        const int rows = rand_int(1, 6), cols = rand_int(1, 6);
        Grid g(rows);
        for (auto& row : g) row = rand_vec(cols, INT_MAX - 1000, INT_MAX);
        PrefixSum2D ps(g);
        const int r1 = rand_int(0, rows - 1), r2 = rand_int(r1, rows - 1);
        const int c1 = rand_int(0, cols - 1), c2 = rand_int(c1, cols - 1);
        CHECK(ps.sumRegion(r1, c1, r2, c2) == brute(g, r1, c1, r2, c2));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // grid[i][j] = K + i + j, so any rectangle sum has a closed form and totals reach ~10^12.
    // Queries are random, averaging ~10^5 cells each, so a per-query cell scan does ~10^10 adds.
    const int n = 1000;
    const long long K = 2'000'000;
    Grid g(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) g[i][j] = static_cast<int>(K + i + j);
    PrefixSum2D ps(g);
    long long mismatches = 0;
    long long biggest = 0;
    for (int q = 0; q < 100'000; ++q) {
        const int r1 = rand_int(0, n - 1), r2 = rand_int(r1, n - 1);
        const int c1 = rand_int(0, n - 1), c2 = rand_int(c1, n - 1);
        const long long h = r2 - r1 + 1, w = c2 - c1 + 1;
        const long long want = h * w * K + w * range_total(r1, r2) + h * range_total(c1, c2);
        const long long got = ps.sumRegion(r1, c1, r2, c2);
        if (got != want) ++mismatches;
        if (want > biggest) biggest = want;
    }
    CHECK(mismatches == 0);
    CHECK(biggest > INT_MAX);
}
