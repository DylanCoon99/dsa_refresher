#include <lcs.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <string>

namespace {
using Fn = int (*)(const std::string&, const std::string&);
struct Impl {
    const char* name;
    Fn fn;
};
const Impl kImpls[] = {{"memo", lcsMemo}, {"tab", lcsTab}};

bool is_subsequence(const std::string& s, const std::string& t) {
    std::size_t k = 0;
    for (char c : t)
        if (k < s.size() && s[k] == c) ++k;
    return k == s.size();
}

// Try every subsequence of a (2^|a| masks) and keep the longest one that is also a subsequence of b.
int brute(const std::string& a, const std::string& b) {
    const int n = static_cast<int>(a.size());
    int best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::string s;
        for (int i = 0; i < n; ++i)
            if (mask >> i & 1) s += a[i];
        if (static_cast<int>(s.size()) > best && is_subsequence(s, b)) best = static_cast<int>(s.size());
    }
    return best;
}

std::string alternating(const std::string& pair, int n) {
    std::string s;
    for (int i = 0; i < n; ++i) s += pair[i % 2];
    return s;
}
}  // namespace

TEST_CASE("examples") {
    for (const Impl& m : kImpls) {
        INFO(m.name);
        CHECK(m.fn("abcde", "ace") == 3);
        CHECK(m.fn("abc", "abc") == 3);
        CHECK(m.fn("abc", "def") == 0);
    }
}

TEST_CASE("edge cases") {
    for (const Impl& m : kImpls) {
        INFO(m.name);
        SUBCASE("an empty string") {
            CHECK(m.fn("", "") == 0);
            CHECK(m.fn("", "abc") == 0);
            CHECK(m.fn("abc", "") == 0);
        }
        SUBCASE("identical strings") {
            CHECK(m.fn("dynamic", "dynamic") == 7);
            CHECK(m.fn("aaaa", "aaaa") == 4);
        }
        SUBCASE("no common characters") { CHECK(m.fn("aabb", "cccd") == 0); }
        SUBCASE("one string inside the other") {
            CHECK(m.fn("ace", "abcde") == 3);
            CHECK(m.fn("a", "bbbab") == 1);
        }
        SUBCASE("repeated letters") {
            CHECK(m.fn("aaaa", "aa") == 2);
            CHECK(m.fn("abab", "baba") == 3);
        }
        SUBCASE("reversed string") { CHECK(m.fn("abc", "cba") == 1); }
    }
}

TEST_CASE("randomized vs brute force (length <= 10)") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string a = rand_string(rand_int(0, 10), 'a', 'a' + rand_int(1, 4));
        const std::string b = rand_string(rand_int(0, 10), 'a', 'a' + rand_int(1, 4));
        const int expected = brute(a, b);
        for (const Impl& m : kImpls) {
            INFO(m.name << ": a=" << a << " b=" << b);
            CHECK(m.fn(a, b) == expected);
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // a^k c^k against b^k c^k: the only common characters are the c's, so the LCS is k. The a-vs-b
    // part never matches, which makes the cache-free recursion explore about C(2k, k) states.
    CHECK(lcsTab(std::string(500, 'a') + std::string(500, 'c'), std::string(500, 'b') + std::string(500, 'c')) == 500);
    CHECK(lcsMemo(std::string(150, 'a') + std::string(150, 'c'), std::string(150, 'b') + std::string(150, 'c')) == 150);
    // (ab)^k against (ba)^k: both have length 2k. Dropping the first char of the first string and the
    // last char of the second leaves the same 2k-1 characters, and the strings differ, so the LCS is 2k-1.
    CHECK(lcsTab(alternating("ab", 1000), alternating("ba", 1000)) == 999);
    CHECK(lcsMemo(alternating("ab", 300), alternating("ba", 300)) == 299);
}
