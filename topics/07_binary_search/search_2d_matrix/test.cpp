#include <search_2d_matrix.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <climits>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

TEST_CASE("examples") {
    const Matrix m = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    CHECK(searchMatrix(m, 3) == true);
    CHECK(searchMatrix(m, 13) == false);
    CHECK(searchMatrix({{4}}, 4) == true);
}

TEST_CASE("edge cases") {
    SUBCASE("1x1") {
        CHECK(searchMatrix({{4}}, 4) == true);
        CHECK(searchMatrix({{4}}, 3) == false);
        CHECK(searchMatrix({{4}}, 5) == false);
    }
    SUBCASE("single row") {
        const Matrix m = {{1, 3, 5, 7, 9}};
        for (int x : {1, 3, 5, 7, 9}) CHECK(searchMatrix(m, x) == true);
        for (int x : {0, 2, 4, 6, 8, 10}) CHECK(searchMatrix(m, x) == false);
    }
    SUBCASE("single column") {
        const Matrix m = {{1}, {3}, {5}, {7}, {9}};
        for (int x : {1, 3, 5, 7, 9}) CHECK(searchMatrix(m, x) == true);
        for (int x : {0, 2, 4, 6, 8, 10}) CHECK(searchMatrix(m, x) == false);
    }
    SUBCASE("target between rows") {
        const Matrix m = {{1, 3, 5}, {10, 12, 14}, {20, 22, 24}};
        CHECK(searchMatrix(m, 6) == false);   // after row 0's last
        CHECK(searchMatrix(m, 9) == false);   // before row 1's first
        CHECK(searchMatrix(m, 15) == false);
        CHECK(searchMatrix(m, 19) == false);
    }
    SUBCASE("first and last cells, and values outside the range") {
        const Matrix m = {{1, 3, 5}, {10, 12, 14}, {20, 22, 24}};
        CHECK(searchMatrix(m, 1) == true);
        CHECK(searchMatrix(m, 24) == true);
        CHECK(searchMatrix(m, 0) == false);
        CHECK(searchMatrix(m, 25) == false);
        CHECK(searchMatrix(m, INT_MIN) == false);
        CHECK(searchMatrix(m, INT_MAX) == false);
    }
    SUBCASE("every row boundary") {
        const Matrix m = {{1, 2}, {4, 5}, {7, 8}, {10, 11}};
        for (int x = 0; x <= 12; ++x) {
            const bool present = (x % 3 != 0) && x >= 1 && x <= 11;
            CHECK(searchMatrix(m, x) == present);
        }
    }
    SUBCASE("extreme values") {
        const Matrix m = {{INT_MIN, -5}, {0, INT_MAX}};
        CHECK(searchMatrix(m, INT_MIN) == true);
        CHECK(searchMatrix(m, INT_MAX) == true);
        CHECK(searchMatrix(m, 1) == false);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int rows = rand_int(1, 8), cols = rand_int(1, 8);
        Matrix m(rows, std::vector<int>(cols));
        int v = rand_int(-20, 0);
        for (auto& row : m) {
            for (int& cell : row) {
                cell = v;
                v += rand_int(0, 3);   // non-decreasing inside a row
            }
            v += 1;                    // strictly greater than the previous row's last
        }
        const int target = rand_int(-25, v + 5);
        bool expected = false;
        for (const auto& row : m)
            for (int cell : row)
                if (cell == target) expected = true;
        CHECK(searchMatrix(m, target) == expected);
    }
}
