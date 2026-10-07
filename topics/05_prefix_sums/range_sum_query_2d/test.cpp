#include <range_sum_query_2d.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
using Matrix = std::vector<std::vector<int>>;

int brute(const Matrix& m, int r1, int c1, int r2, int c2) {
    int s = 0;
    for (int r = r1; r <= r2; ++r)
        for (int c = c1; c <= c2; ++c) s += m[r][c];
    return s;
}
}  // namespace

TEST_CASE("examples") {
    NumMatrix nm({{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}});
    CHECK(nm.sumRegion(2, 1, 4, 3) == 8);
    CHECK(nm.sumRegion(1, 1, 2, 2) == 11);
    CHECK(nm.sumRegion(1, 2, 2, 4) == 12);
}

TEST_CASE("edge cases") {
    SUBCASE("1x1 matrix") {
        NumMatrix nm({{-3}});
        CHECK(nm.sumRegion(0, 0, 0, 0) == -3);
    }
    SUBCASE("1x1 matrix, positive") {
        NumMatrix nm({{9}});
        CHECK(nm.sumRegion(0, 0, 0, 0) == 9);
    }
    SUBCASE("whole matrix") {
        NumMatrix nm({{1, 2, 3}, {4, 5, 6}});
        CHECK(nm.sumRegion(0, 0, 1, 2) == 21);
    }
    SUBCASE("single row and single column") {
        NumMatrix row({{1, -2, 3, -4}});
        CHECK(row.sumRegion(0, 0, 0, 3) == -2);
        CHECK(row.sumRegion(0, 2, 0, 3) == -1);
        NumMatrix col({{1}, {-2}, {3}, {-4}});
        CHECK(col.sumRegion(0, 0, 3, 0) == -2);
        CHECK(col.sumRegion(2, 0, 3, 0) == -1);
    }
    SUBCASE("single cell in the interior and in each corner") {
        NumMatrix nm({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        CHECK(nm.sumRegion(1, 1, 1, 1) == 5);
        CHECK(nm.sumRegion(0, 0, 0, 0) == 1);
        CHECK(nm.sumRegion(0, 2, 0, 2) == 3);
        CHECK(nm.sumRegion(2, 0, 2, 0) == 7);
        CHECK(nm.sumRegion(2, 2, 2, 2) == 9);
    }
    SUBCASE("regions on the top and left borders") {
        NumMatrix nm({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        CHECK(nm.sumRegion(0, 0, 0, 2) == 6);
        CHECK(nm.sumRegion(0, 0, 2, 0) == 12);
        CHECK(nm.sumRegion(0, 1, 1, 2) == 16);
    }
    SUBCASE("negative values") {
        NumMatrix nm({{-1, -2}, {-3, -4}});
        CHECK(nm.sumRegion(0, 0, 1, 1) == -10);
        CHECK(nm.sumRegion(1, 0, 1, 1) == -7);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int rows = rand_int(1, 8), cols = rand_int(1, 8);
        Matrix m(rows);
        for (auto& row : m) row = rand_vec(cols, -10'000, 10'000);
        NumMatrix nm(m);
        for (int q = 0; q < 20; ++q) {
            const int r1 = rand_int(0, rows - 1), r2 = rand_int(r1, rows - 1);
            const int c1 = rand_int(0, cols - 1), c2 = rand_int(c1, cols - 1);
            CHECK(nm.sumRegion(r1, c1, r2, c2) == brute(m, r1, c1, r2, c2));
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Queries start near the top-left and end near the bottom-right, so a per-query cell scan
    // touches ~3.6·10^4 cells each: ~3.6·10^9 adds in total.
    const int n = 200;
    Matrix m(n, std::vector<int>(n));
    Matrix pre(n + 1, std::vector<int>(n + 1, 0));  // independent check of the answers
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            m[i][j] = (i * 131 + j * 71) % 2001 - 1000;
            pre[i + 1][j + 1] = m[i][j] + pre[i][j + 1] + pre[i + 1][j] - pre[i][j];
        }
    NumMatrix nm(m);
    long long mismatches = 0;
    for (int q = 0; q < 100'000; ++q) {
        const int r1 = rand_int(0, 20), r2 = rand_int(n - 21, n - 1);
        const int c1 = rand_int(0, 20), c2 = rand_int(n - 21, n - 1);
        const int want = pre[r2 + 1][c2 + 1] - pre[r1][c2 + 1] - pre[r2 + 1][c1] + pre[r1][c1];
        if (nm.sumRegion(r1, c1, r2, c2) != want) ++mismatches;
    }
    CHECK(mismatches == 0);
    CHECK(nm.sumRegion(0, 0, n - 1, n - 1) == pre[n][n]);
    CHECK(pre[n][n] != 0);
}
