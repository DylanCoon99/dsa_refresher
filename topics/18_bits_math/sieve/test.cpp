#include <sieve.hpp>

#include <doctest.h>
#include <printing.hpp>

#include <vector>

namespace {
bool is_prime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d)
        if (x % d == 0) return false;
    return true;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(primesUpTo(10) == std::vector<int>{2, 3, 5, 7});
    CHECK(primesUpTo(2) == std::vector<int>{2});
    CHECK(primesUpTo(1).empty());
}

TEST_CASE("edge cases") {
    SUBCASE("n = 0 and n = 1") {
        CHECK(primesUpTo(0).empty());
        CHECK(primesUpTo(1).empty());
    }
    SUBCASE("n = 2 and n = 3") {
        CHECK(primesUpTo(2) == std::vector<int>{2});
        CHECK(primesUpTo(3) == std::vector<int>{2, 3});
    }
    SUBCASE("n is a composite just above a prime") { CHECK(primesUpTo(4) == std::vector<int>{2, 3}); }
    SUBCASE("n = 100 has 25 primes, the last being 97") {
        auto got = primesUpTo(100);
        REQUIRE(got.size() == 25);
        CHECK(got.front() == 2);
        CHECK(got.back() == 97);
    }
    SUBCASE("the bound is inclusive when n is prime") {
        auto got = primesUpTo(97);
        REQUIRE(!got.empty());
        CHECK(got.back() == 97);
        CHECK(got.size() == 25);
    }
}

TEST_CASE("against trial division for n up to 10^4") {
    // Checks n = 0..59, every 97th n, and n = 9991..10000. `expected` is the running list of primes <= n.
    std::vector<int> expected;
    for (int n = 0; n <= 10'000; ++n) {
        if (is_prime(n)) expected.push_back(n);
        if (n % 97 == 0 || n < 60 || n > 9'990) {
            CAPTURE(n);
            CHECK(primesUpTo(n) == expected);
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // pi(10^7) = 664579 and the largest prime below 10^7 is 9999991.
    auto got = primesUpTo(10'000'000);
    REQUIRE(got.size() == 664'579);
    CHECK(got.front() == 2);
    CHECK(got.back() == 9'999'991);
}
