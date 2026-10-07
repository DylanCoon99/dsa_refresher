#include <climbing_stairs.hpp>

#include <doctest.h>

namespace {
// Plain recursion over the last move: obviously correct, exponential, fine for small n.
long long brute(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    return brute(n - 1) + brute(n - 2);
}
}  // namespace

TEST_CASE("examples") {
    CHECK(climbStairs(2) == 2);
    CHECK(climbStairs(3) == 3);
    CHECK(climbStairs(4) == 5);
}

TEST_CASE("edge cases") {
    CHECK(climbStairs(1) == 1);
    CHECK(climbStairs(2) == 2);
    CHECK(climbStairs(10) == 89);
    SUBCASE("n = 45 is the largest that fits in int") { CHECK(climbStairs(45) == 1836311903); }
    SUBCASE("n = 44") { CHECK(climbStairs(44) == 1134903170); }
}

TEST_CASE("every n up to 25 vs brute force") {
    for (int n = 1; n <= 25; ++n) {
        INFO("n = " << n);
        CHECK(climbStairs(n) == brute(n));
    }
}
