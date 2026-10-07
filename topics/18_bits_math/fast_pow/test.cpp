#include <fast_pow.hpp>

#include <doctest.h>
#include <random_utils.hpp>

namespace {
// Obviously-correct reference for small exponents: multiply one factor at a time.
long long naive(long long base, int exp, long long mod) {
    long long b = ((base % mod) + mod) % mod;
    long long r = 1 % mod;
    for (int i = 0; i < exp; ++i) r = r * b % mod;
    return r;
}
constexpr long long P = 1'000'000'007;
}  // namespace

TEST_CASE("examples") {
    CHECK(modPow(2, 10, 1000) == 24);
    CHECK(modPow(-2, 3, 5) == 2);
    CHECK(modPow(7, 0, 1) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("exp 0 gives 1 when mod > 1") {
        CHECK(modPow(5, 0, 7) == 1);
        CHECK(modPow(0, 0, 7) == 1);
        CHECK(modPow(-4, 0, 2'000'000'000) == 1);
    }
    SUBCASE("mod 1 gives 0") {
        CHECK(modPow(5, 3, 1) == 0);
        CHECK(modPow(0, 0, 1) == 0);
        CHECK(modPow(-9, 1'000'000'000'000'000'000LL, 1) == 0);
    }
    SUBCASE("negative base") {
        CHECK(modPow(-3, 1, 7) == 4);
        CHECK(modPow(-3, 2, 7) == 2);
        CHECK(modPow(-1, 1'000'000'000'000'000'000LL, 13) == 1);
        CHECK(modPow(-1, 999'999'999'999'999'999LL, 13) == 12);
    }
    SUBCASE("base at least mod") {
        CHECK(modPow(10, 2, 7) == 2);
        CHECK(modPow(1'000'000'000'000LL, 3, 1000) == 0);
        CHECK(modPow(P + 5, 4, P) == 625);
    }
    SUBCASE("base 0 and base 1") {
        CHECK(modPow(0, 5, 11) == 0);
        CHECK(modPow(1, 1'000'000'000'000'000'000LL, 11) == 1);
    }
    SUBCASE("largest allowed mod: products near 4e18 must not overflow") {
        const long long M = 2'000'000'000;
        CHECK(modPow(M - 1, 2, M) == 1);
        CHECK(modPow(M - 1, 3, M) == M - 1);
        CHECK(modPow(-1, 999'999'999'999'999'999LL, M) == M - 1);
    }
    SUBCASE("Fermat: a^(p-1) == 1 for prime p = 1e9+7") {
        for (long long a : {2LL, 3LL, 10LL, 123456789LL, P - 1, P + 2, -5LL}) {
            CHECK(modPow(a, P - 1, P) == 1);
        }
        CHECK(modPow(P, P - 1, P) == 0);  // a multiple of p never reaches 1
    }
}

TEST_CASE("randomized vs naive loop") {
    for (int trial = 0; trial < 400; ++trial) {
        long long mod = rand_int(1, 2'000'000'000);
        if (trial % 3 == 0) mod = rand_int(1, 50);
        long long base = rand_int(-2'000'000'000, 2'000'000'000);
        int exp = rand_int(0, 1000);
        CAPTURE(base);
        CAPTURE(exp);
        CAPTURE(mod);
        CHECK(modPow(base, exp, mod) == naive(base, exp, mod));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // By Fermat, a^(k(p-1)) == 1 and a^(k(p-1)+1) == a (mod p) for a in 1..p-1, so the expected
    // values are known without computing any power. Both exponents are about 10^18.
    const long long E = 1'000'000'000'000'000'000LL;
    const long long exp1 = E - E % (P - 1);  // a multiple of p-1
    static_assert(E % (P - 1) != 0, "exp1 + 1 must stay below 1e18");
    const long long exp2 = exp1 + 1;
    for (long long a = 2; a <= 1001; ++a) {
        REQUIRE(modPow(a, exp1, P) == 1);
        REQUIRE(modPow(a, exp2, P) == a);
    }
}
