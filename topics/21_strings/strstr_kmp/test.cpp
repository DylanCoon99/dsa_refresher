#include <strstr_kmp.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <string>

namespace {
int naiveStr(const std::string& h, const std::string& n) {
    if (n.empty()) return 0;
    if (n.size() > h.size()) return -1;
    for (std::size_t i = 0; i + n.size() <= h.size(); ++i)
        if (h.compare(i, n.size(), n) == 0) return static_cast<int>(i);
    return -1;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(strStr("sadbutsad", "sad") == 0);
    CHECK(strStr("leetcode", "leeto") == -1);
    CHECK(strStr("abc", "c") == 2);
}

TEST_CASE("edge cases") {
    SUBCASE("needle equals haystack") {
        CHECK(strStr("abcab", "abcab") == 0);
        CHECK(strStr("a", "a") == 0);
    }
    SUBCASE("needle longer than haystack") {
        CHECK(strStr("ab", "abc") == -1);
        CHECK(strStr("", "a") == -1);
    }
    SUBCASE("empty needle") {
        CHECK(strStr("abc", "") == 0);
        CHECK(strStr("", "") == 0);
    }
    SUBCASE("match at the end") {
        CHECK(strStr("aaaaab", "aab") == 3);
        CHECK(strStr("mississippi", "pi") == 9);
    }
    SUBCASE("near misses before the real match") {
        CHECK(strStr("aabaaabaaac", "aaac") == 7);
        CHECK(strStr("abababc", "ababc") == 2);
    }
    SUBCASE("first of several matches") {
        CHECK(strStr("abababab", "bab") == 1);
    }
    SUBCASE("absent") {
        CHECK(strStr("abcabc", "abd") == -1);
    }
}

TEST_CASE("randomized vs naive") {
    for (int trial = 0; trial < 500; ++trial) {
        const std::string h = rand_string(rand_int(0, 30), 'a', 'b');
        const std::string n = rand_string(rand_int(0, 6), 'a', 'b');
        INFO("haystack=" << h << " needle=" << n);
        CHECK(strStr(h, n) == naiveStr(h, n));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Naive matching does ~10^9 comparisons on both inputs.
    const int n = 1'000'000;
    SUBCASE("no match: a^1000000 against a^999 b") {
        CHECK(strStr(std::string(n, 'a'), std::string(999, 'a') + "b") == -1);
    }
    SUBCASE("match only at the very end: a^1000000 b against a^999 b") {
        const std::string h = std::string(n, 'a') + "b";
        CHECK(strStr(h, std::string(999, 'a') + "b") == n - 999);
    }
}
