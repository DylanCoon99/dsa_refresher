#include <pow_x_n.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <cmath>

namespace {
// Relative closeness (absolute near 0).
bool close(double got, double want, double rel) {
    return std::fabs(got - want) <= rel * std::max(1.0, std::fabs(want));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(close(myPow(2.0, 10), 1024.0, 1e-12));
    CHECK(close(myPow(2.0, -2), 0.25, 1e-12));
    CHECK(myPow(5.0, 0) == 1.0);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 0") {
        CHECK(myPow(5.0, 0) == 1.0);
        CHECK(myPow(-3.5, 0) == 1.0);
        CHECK(myPow(0.0, 0) == 1.0);
    }
    SUBCASE("n = 1") { CHECK(myPow(-3.5, 1) == -3.5); }
    SUBCASE("a negative n") {
        CHECK(close(myPow(2.0, -3), 0.125, 1e-12));
        CHECK(close(myPow(4.0, -1), 0.25, 1e-12));
        CHECK(close(myPow(-2.0, -3), -0.125, 1e-12));
    }
    SUBCASE("a negative base") {
        CHECK(myPow(-2.0, 3) == -8.0);
        CHECK(myPow(-2.0, 4) == 16.0);
    }
    SUBCASE("n = INT_MIN (-n overflows int)") {
        CHECK(myPow(1.0, INT_MIN) == 1.0);
        CHECK(myPow(-1.0, INT_MIN) == 1.0);  // INT_MIN is even
        CHECK(myPow(2.0, INT_MIN) == 0.0);   // 2^-2147483648 underflows to 0
    }
    SUBCASE("n = INT_MAX with base +-1") {
        CHECK(myPow(1.0, INT_MAX) == 1.0);
        CHECK(myPow(-1.0, INT_MAX) == -1.0);  // INT_MAX is odd
    }
    SUBCASE("n = INT_MAX with base 0 and n = INT_MIN + 1 with base +-1") {
        CHECK(myPow(0.0, INT_MAX) == 0.0);
        CHECK(myPow(-1.0, INT_MIN + 1) == -1.0);
    }
    SUBCASE("base 0.5 with a large negative n is exactly a power of two") {
        CHECK(myPow(0.5, -1000) == std::ldexp(1.0, 1000));
    }
}

TEST_CASE("randomized vs std::pow within 1e-9 relative error") {
    for (int trial = 0; trial < 400; ++trial) {
        double x = rand_int(5, 15) / 10.0 + rand_int(0, 999) / 1e6;  // roughly 0.5 .. 1.5
        int n = rand_int(-1000, 1000);
        CAPTURE(x);
        CAPTURE(n);
        const double want = std::pow(x, n);
        // Skip cases where the exact result is outside the comfortable double range.
        if (!std::isfinite(want) || want == 0.0) continue;
        CHECK(close(myPow(x, n), want, 1e-9));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^6 calls at n = INT_MAX. Bases +-1 have exact answers (INT_MAX is odd); a loop that
    // multiplies n times would need about 2*10^9 steps per call.
    const int calls = 1'000'000;
    bool all_exact = true;
    for (int i = 0; i < calls; ++i) {
        const double x = (i % 2 == 0) ? 1.0 : -1.0;
        if (myPow(x, INT_MAX) != x) all_exact = false;
    }
    CHECK(all_exact);
    // x = 1 + 2^-30 is exactly representable and (1 + 2^-30)^INT_MAX is about e^2. Rounding error
    // grows with n, so the tolerance here is looser than for small n.
    const double x = 1.0 + std::ldexp(1.0, -30);
    CHECK(close(myPow(x, INT_MAX), std::pow(x, INT_MAX), 1e-5));
}
