#include <count_primes.hpp>

#include <doctest.h>
#include <random_utils.hpp>

namespace {
bool is_prime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d)
        if (x % d == 0) return false;
    return true;
}
int brute(int n) {
    int count = 0;
    for (int i = 2; i < n; ++i)
        if (is_prime(i)) ++count;
    return count;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(countPrimes(10) == 4);
    CHECK(countPrimes(2) == 0);
    CHECK(countPrimes(3) == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 0, 1, 2 give 0") {
        CHECK(countPrimes(0) == 0);
        CHECK(countPrimes(1) == 0);
        CHECK(countPrimes(2) == 0);
    }
    SUBCASE("n = 3 gives 1") { CHECK(countPrimes(3) == 1); }
    SUBCASE("the bound is exclusive when n is prime") {
        CHECK(countPrimes(5) == 2);  // 2, 3
        CHECK(countPrimes(6) == 3);  // 2, 3, 5
        CHECK(countPrimes(97) == 24);
        CHECK(countPrimes(98) == 25);
    }
    SUBCASE("n = 100 has 25 primes below it") { CHECK(countPrimes(100) == 25); }
}

TEST_CASE("randomized vs trial division") {
    for (int n = 0; n <= 60; ++n) {
        CAPTURE(n);
        CHECK(countPrimes(n) == brute(n));
    }
    for (int trial = 0; trial < 150; ++trial) {
        int n = rand_int(61, 3000);
        CAPTURE(n);
        CHECK(countPrimes(n) == brute(n));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // pi(1.5*10^7) = 970704, and 1.5*10^7 is not prime, so the count below n equals pi(n).
    CHECK(countPrimes(15'000'000) == 970'704);
}
