#include <decode_ways.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <string>

namespace {
// Enumerate every way to cut s (a bitmask over the n-1 gaps), then check each piece is 1..26 with no
// leading zero. Pieces longer than 2 digits can never be valid, so they are rejected.
int brute(const std::string& s) {
    const int n = static_cast<int>(s.size());
    int count = 0;
    for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
        bool ok = true;
        int start = 0;
        for (int i = 1; i <= n && ok; ++i) {
            if (i < n && !(mask >> (i - 1) & 1)) continue;  // no cut before position i
            const std::string piece = s.substr(start, i - start);
            start = i;
            if (piece.size() > 2 || piece[0] == '0' || std::stoi(piece) > 26) ok = false;
        }
        if (ok) ++count;
    }
    return count;
}

// The number of decodings of n ones is the (n+1)-th Fibonacci number (F1 = F2 = 1).
long long fib(int k) {
    long long a = 0, b = 1;
    for (int i = 0; i < k; ++i) {
        long long t = a + b;
        a = b;
        b = t;
    }
    return a;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(numDecodings("12") == 2);
    CHECK(numDecodings("226") == 3);
    CHECK(numDecodings("06") == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("zeros") {
        CHECK(numDecodings("0") == 0);
        CHECK(numDecodings("06") == 0);
        CHECK(numDecodings("10") == 1);
        CHECK(numDecodings("100") == 0);
        CHECK(numDecodings("230") == 0);
        CHECK(numDecodings("301") == 0);
        CHECK(numDecodings("2101") == 1);
        CHECK(numDecodings("1001") == 0);
    }
    SUBCASE("two-digit numbers above 26 are not letters") {
        CHECK(numDecodings("27") == 1);
        CHECK(numDecodings("2727") == 1);
        CHECK(numDecodings("26") == 2);
    }
    SUBCASE("single characters") {
        CHECK(numDecodings("1") == 1);
        CHECK(numDecodings("9") == 1);
    }
    SUBCASE("mixed") {
        CHECK(numDecodings("11106") == 2);
        CHECK(numDecodings("123456") == 3);
    }
    SUBCASE("a run of ones follows the Fibonacci numbers") {
        for (int n = 1; n <= 30; ++n) {
            INFO("n = " << n);
            CHECK(numDecodings(std::string(n, '1')) == fib(n + 1));
        }
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        // Mostly 0, 1 and 2 (the digits that make two-digit pieces interesting), sometimes larger.
        std::string s;
        const int len = rand_int(1, 12);
        for (int i = 0; i < len; ++i) s += static_cast<char>('0' + (rand_int(0, 4) == 0 ? rand_int(3, 9) : rand_int(0, 2)));
        INFO("s = " << s);
        CHECK(numDecodings(s) == brute(s));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 45 ones: fib(46) = 1836311903 decodings (fits in int), but ~1.8e9 calls without a cache.
    CHECK(numDecodings(std::string(45, '1')) == 1836311903);
    // 60 ones then "00": the final 0 can never be decoded, so the answer is 0, but a cache-free recursion
    // only discovers that at the end of each of its ~fib(60) paths. The intermediate counts (up to
    // fib(61), about 2.5e12) overflow int, so a signed 32-bit table crashes here under UBSan.
    CHECK(numDecodings(std::string(60, '1') + "00") == 0);
}
