#include <char_replacement.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <random>
#include <string>

namespace {
// O(n^2 * 26): count every substring's letters from scratch.
int brute(const std::string& s, int k) {
    int best = 0;
    const int n = static_cast<int>(s.size());
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j) {
            int cnt[26] = {};
            for (int p = i; p <= j; ++p) ++cnt[s[p] - 'A'];
            const int mx = *std::max_element(cnt, cnt + 26);
            if ((j - i + 1) - mx <= k) best = std::max(best, j - i + 1);
        }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(characterReplacement("ABAB", 2) == 4);
    CHECK(characterReplacement("AABABBA", 1) == 4);
    CHECK(characterReplacement("ABC", 0) == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("single character") {
        CHECK(characterReplacement("A", 0) == 1);
        CHECK(characterReplacement("A", 1) == 1);
    }
    SUBCASE("k = 0 is the longest run") {
        CHECK(characterReplacement("AABBBCCDDDDE", 0) == 4);
        CHECK(characterReplacement("ABCDEF", 0) == 1);
    }
    SUBCASE("k >= n makes the whole string valid") {
        CHECK(characterReplacement("ABCDE", 5) == 5);
        CHECK(characterReplacement("ABCDE", 3) == 4);
        CHECK(characterReplacement("AB", 2) == 2);
    }
    SUBCASE("all the same letter") { CHECK(characterReplacement("ZZZZ", 2) == 4); }
    SUBCASE("best window is at the end") { CHECK(characterReplacement("ABCDXXXY", 1) == 4); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 30);
        const std::string s = rand_string(n, 'A', rand_int(0, 1) ? 'C' : 'F');
        const int k = rand_int(0, n);
        CAPTURE(s);
        CAPTURE(k);
        CHECK(characterReplacement(s, k) == brute(s, k));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 letters: B..Z at random, except a run of 40000 'A' in the middle. With k = 5000 the run
    // plus 5000 of its (non-A) neighbours is the best window, 45000 long; no other letter reaches that.
    const int n = 100'000, k = 5000;
    std::mt19937 gen(99);
    std::string s(n, 'B');
    for (char& c : s) c = static_cast<char>('B' + gen() % 25u);
    std::fill(s.begin() + 30'000, s.begin() + 70'000, 'A');
    CHECK(characterReplacement(s, k) == 45'000);
}
