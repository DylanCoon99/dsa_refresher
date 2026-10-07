#include <min_window_substring.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <random>
#include <string>

namespace {
bool covers(const std::string& w, const std::string& t) {
    int cnt[128] = {};
    for (char c : w) ++cnt[static_cast<unsigned char>(c)];
    for (char c : t)
        if (--cnt[static_cast<unsigned char>(c)] < 0) return false;
    return true;
}

// Length of the shortest covering window, or -1 if none (full enumeration).
int brute_len(const std::string& s, const std::string& t) {
    int best = -1;
    const int n = static_cast<int>(s.size());
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (covers(s.substr(i, j - i + 1), t) && (best == -1 || j - i + 1 < best)) best = j - i + 1;
    return best;
}

// Several shortest windows may tie, so validate the contract instead of one exact string.
void check_min_window(const std::string& s, const std::string& t) {
    CAPTURE(s);
    CAPTURE(t);
    const std::string got = minWindow(s, t);
    const int expected = brute_len(s, t);
    if (expected == -1) {
        CHECK(got == "");
        return;
    }
    REQUIRE(static_cast<int>(got.size()) == expected);
    CHECK(s.find(got) != std::string::npos);
    CHECK(covers(got, t));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(minWindow("ADOBECODEBANC", "ABC") == "BANC");
    CHECK(minWindow("a", "a") == "a");
    CHECK(minWindow("a", "aa") == "");
}

TEST_CASE("edge cases") {
    SUBCASE("t has duplicate characters") {
        CHECK(minWindow("aa", "aa") == "aa");
        CHECK(minWindow("abaab", "aa") == "aa");
        check_min_window("bbaac", "aab");
    }
    SUBCASE("t longer than s") { CHECK(minWindow("ab", "abc") == ""); }
    SUBCASE("t has a character s lacks") { CHECK(minWindow("abcdef", "xyz") == ""); }
    SUBCASE("whole string is the window") { CHECK(minWindow("abc", "cba") == "abc"); }
    SUBCASE("window at the very start and the very end") {
        CHECK(minWindow("abcxxxx", "abc") == "abc");
        CHECK(minWindow("xxxxabc", "abc") == "abc");
    }
    SUBCASE("case-sensitive") { CHECK(minWindow("aAbB", "AB") == "AbB"); }
    SUBCASE("single character t") { CHECK(minWindow("xxyxx", "y") == "y"); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(rand_int(1, 25), 'a', 'd');
        const std::string t = rand_string(rand_int(1, 6), 'a', 'd');
        check_min_window(s, t);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // |s| = 10^5 of lowercase filler (a..x). |t| = 50 uppercase letters with repeats.
    // t's letters appear spread over 5000 characters near the start, and again as one compact
    // shuffled 50-character block at index 60000. That block is the only window of length 50.
    const int n = 100'000, m = 50;
    std::mt19937 gen(8080);
    std::string s(n, 'a');
    for (char& c : s) c = static_cast<char>('a' + gen() % 24u);
    std::string t(m, 'A');
    for (char& c : t) c = static_cast<char>('A' + gen() % 10u);
    for (int i = 0; i < m; ++i) s[10'000 + 100 * i] = t[i];
    std::string block = t;
    std::shuffle(block.begin(), block.end(), gen);
    s.replace(60'000, m, block);
    CHECK(minWindow(s, t) == block);
}
