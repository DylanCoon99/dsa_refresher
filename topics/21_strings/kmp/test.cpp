#include <kmp.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <string>
#include <vector>

namespace {
std::vector<int> naiveSearch(const std::string& t, const std::string& p) {
    std::vector<int> out;
    if (p.empty() || p.size() > t.size()) return out;
    for (std::size_t i = 0; i + p.size() <= t.size(); ++i)
        if (t.compare(i, p.size(), p) == 0) out.push_back(static_cast<int>(i));
    return out;
}

std::vector<int> naivePi(const std::string& s) {
    std::vector<int> pi(s.size(), 0);
    for (std::size_t i = 0; i < s.size(); ++i)
        for (std::size_t k = i; k >= 1; --k)  // candidate border length k < i + 1
            if (s.compare(0, k, s, i + 1 - k, k) == 0) {
                pi[i] = static_cast<int>(k);
                break;
            }
    return pi;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(prefixFunction("aabaaab") == std::vector<int>{0, 1, 0, 1, 2, 2, 3});
    CHECK(kmpSearch("aaaa", "aa") == std::vector<int>{0, 1, 2});
    CHECK(kmpSearch("abc", "abcd") == std::vector<int>{});
}

TEST_CASE("prefix function") {
    SUBCASE("empty and single character") {
        CHECK(prefixFunction("") == std::vector<int>{});
        CHECK(prefixFunction("a") == std::vector<int>{0});
    }
    SUBCASE("no borders") {
        CHECK(prefixFunction("abcd") == std::vector<int>{0, 0, 0, 0});
    }
    SUBCASE("all the same character") {
        CHECK(prefixFunction("aaaaa") == std::vector<int>{0, 1, 2, 3, 4});
    }
    SUBCASE("falls back more than one step") {
        CHECK(prefixFunction("abcabcd") == std::vector<int>{0, 0, 0, 1, 2, 3, 0});
        CHECK(prefixFunction("aabaabaaa") == std::vector<int>{0, 1, 0, 1, 2, 3, 4, 5, 2});
    }
}

TEST_CASE("search edge cases") {
    SUBCASE("empty pattern returns nothing") {
        CHECK(kmpSearch("abc", "") == std::vector<int>{});
        CHECK(kmpSearch("", "") == std::vector<int>{});
    }
    SUBCASE("empty text") {
        CHECK(kmpSearch("", "a") == std::vector<int>{});
    }
    SUBCASE("pattern equals text") {
        CHECK(kmpSearch("abcab", "abcab") == std::vector<int>{0});
    }
    SUBCASE("pattern longer than text") {
        CHECK(kmpSearch("ab", "abab") == std::vector<int>{});
    }
    SUBCASE("overlapping matches") {
        CHECK(kmpSearch("aaaa", "aa") == std::vector<int>{0, 1, 2});
        CHECK(kmpSearch("abababa", "aba") == std::vector<int>{0, 2, 4});
    }
    SUBCASE("a match at the very end and a near miss before it") {
        CHECK(kmpSearch("aabaaabaaac", "aaac") == std::vector<int>{7});
    }
    SUBCASE("no match") {
        CHECK(kmpSearch("abcabc", "abd") == std::vector<int>{});
    }
}

TEST_CASE("randomized vs naive") {
    for (int trial = 0; trial < 500; ++trial) {
        const std::string text = rand_string(rand_int(0, 40), 'a', 'b');
        const std::string pat = rand_string(rand_int(0, 6), 'a', 'b');
        INFO("text=" << text << " pattern=" << pat);
        CHECK(kmpSearch(text, pat) == naiveSearch(text, pat));
        CHECK(prefixFunction(text) == naivePi(text));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // text = a^1000000. Naive matching does ~10^9 comparisons for either pattern below.
    const int n = 1'000'000;
    const std::string text(n, 'a');

    SUBCASE("a pattern that never matches") {
        const std::string pat = std::string(999, 'a') + "b";
        CHECK(kmpSearch(text, pat) == std::vector<int>{});
    }
    SUBCASE("a pattern that matches at every position") {
        const std::string pat(999, 'a');
        const std::vector<int> got = kmpSearch(text, pat);
        REQUIRE(got.size() == static_cast<std::size_t>(n - 999 + 1));
        int bad = -1;
        for (int i = 0; i < static_cast<int>(got.size()); ++i)
            if (got[i] != i) { bad = i; break; }
        CHECK_MESSAGE(bad == -1, "first wrong entry at index " << bad);
    }
    SUBCASE("prefix function of a^1000000") {
        const std::vector<int> pi = prefixFunction(text);
        REQUIRE(pi.size() == static_cast<std::size_t>(n));
        int bad = -1;
        for (int i = 0; i < n; ++i)
            if (pi[i] != i) { bad = i; break; }
        CHECK_MESSAGE(bad == -1, "first wrong entry at index " << bad);
    }
}
