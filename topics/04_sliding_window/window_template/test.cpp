#include <window_template.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <random>
#include <string>
#include <unordered_map>

namespace {
using Freq = std::unordered_map<char, int>;

// The three monotone predicates used throughout. They ignore zero-count keys.
const auto at_most_two_distinct = [](const Freq& f, int) {
    int distinct = 0;
    for (const auto& kv : f)
        if (kv.second > 0) ++distinct;
    return distinct <= 2;
};
const auto no_repeats = [](const Freq& f, int) {
    for (const auto& kv : f)
        if (kv.second > 1) return false;
    return true;
};
const auto one_change_from_uniform = [](const Freq& f, int len) {
    int maxfreq = 0;
    for (const auto& kv : f) maxfreq = std::max(maxfreq, kv.second);
    return len - maxfreq <= 1;
};

// Obviously-correct reference: build every substring's frequency map from scratch.
template <typename Valid>
int brute(const std::string& s, Valid is_valid) {
    int best = 0;
    const int n = static_cast<int>(s.size());
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j) {
            Freq f;
            for (int k = i; k <= j; ++k) ++f[s[k]];
            if (is_valid(f, j - i + 1)) best = std::max(best, j - i + 1);
        }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(longestValidWindow("eceba", at_most_two_distinct) == 3);
    CHECK(longestValidWindow("abcabcbb", no_repeats) == 3);
    CHECK(longestValidWindow("aaabb", one_change_from_uniform) == 4);
}

TEST_CASE("edge cases") {
    SUBCASE("empty string") {
        CHECK(longestValidWindow("", at_most_two_distinct) == 0);
        CHECK(longestValidWindow("", no_repeats) == 0);
        CHECK(longestValidWindow("", one_change_from_uniform) == 0);
    }
    SUBCASE("single character") {
        CHECK(longestValidWindow("a", at_most_two_distinct) == 1);
        CHECK(longestValidWindow("a", no_repeats) == 1);
    }
    SUBCASE("whole string valid") { CHECK(longestValidWindow("abab", at_most_two_distinct) == 4); }
    SUBCASE("all the same character") {
        CHECK(longestValidWindow("aaaa", no_repeats) == 1);
        CHECK(longestValidWindow("aaaa", at_most_two_distinct) == 4);
    }
    SUBCASE("only one-character windows are valid") {
        CHECK(longestValidWindow("aaaa", [](const Freq&, int len) { return len <= 1; }) == 1);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(rand_int(0, 25), 'a', 'c');
        CAPTURE(s);
        CHECK(longestValidWindow(s, at_most_two_distinct) == brute(s, at_most_two_distinct));
        CHECK(longestValidWindow(s, no_repeats) == brute(s, no_repeats));
        CHECK(longestValidWindow(s, one_change_from_uniform) == brute(s, one_change_from_uniform));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 characters: random letters c..z around a 50000-long random a/b block that starts and ends
    // with "ab". Only a/b windows have <= 2 distinct characters for long, so the answer is the block
    // itself; re-scanning every window from scratch is O(n^2).
    const int n = 100'000, block = 50'000, start = 20'000;
    std::mt19937 gen(777);
    std::string s(n, 'c');
    for (char& c : s) c = static_cast<char>('c' + gen() % 24u);
    for (int i = start; i < start + block; ++i) s[i] = static_cast<char>('a' + gen() % 2u);
    s[start] = 'a';
    s[start + 1] = 'b';
    s[start + block - 2] = 'a';
    s[start + block - 1] = 'b';
    CHECK(longestValidWindow(s, at_most_two_distinct) == block);
}
