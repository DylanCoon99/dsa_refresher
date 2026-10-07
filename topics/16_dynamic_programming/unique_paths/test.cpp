#include <unique_paths.hpp>

#include <doctest.h>

namespace {
// Plain recursion over the first move: obviously correct, exponential, fine for small grids.
int brute(int m, int n) {
    if (m == 1 || n == 1) return 1;
    return brute(m - 1, n) + brute(m, n - 1);
}
}  // namespace

TEST_CASE("examples") {
    CHECK(uniquePaths(3, 7) == 28);
    CHECK(uniquePaths(3, 2) == 3);
    CHECK(uniquePaths(1, 5) == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("1 x 1") { CHECK(uniquePaths(1, 1) == 1); }
    SUBCASE("a single row or column") {
        CHECK(uniquePaths(1, 100) == 1);
        CHECK(uniquePaths(100, 1) == 1);
        CHECK(uniquePaths(1, 2) == 1);
    }
    SUBCASE("2 x N has N paths") {
        CHECK(uniquePaths(2, 9) == 9);
        CHECK(uniquePaths(9, 2) == 9);
    }
    SUBCASE("symmetric in m and n") { CHECK(uniquePaths(7, 3) == uniquePaths(3, 7)); }
    SUBCASE("23 x 12 = C(33, 11) fits in int") {
        CHECK(uniquePaths(23, 12) == 193536720);
        CHECK(uniquePaths(12, 23) == 193536720);
    }
}

TEST_CASE("every grid up to 9 x 9 vs brute force") {
    for (int m = 1; m <= 9; ++m)
        for (int n = 1; n <= 9; ++n) {
            INFO("m = " << m << ", n = " << n);
            CHECK(uniquePaths(m, n) == brute(m, n));
        }
}
