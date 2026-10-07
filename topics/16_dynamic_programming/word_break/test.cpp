#include <word_break.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <string>
#include <vector>

namespace {
using Words = std::vector<std::string>;

// Plain recursion: try every dictionary word at the current position. Fine for tiny inputs.
bool brute(const std::string& s, std::size_t pos, const Words& dict) {
    if (pos == s.size()) return true;
    for (const std::string& w : dict)
        if (s.compare(pos, w.size(), w) == 0 && brute(s, pos + w.size(), dict)) return true;
    return false;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(wordBreak("leetcode", {"leet", "code"}));
    CHECK(wordBreak("applepenapple", {"apple", "pen"}));
    CHECK_FALSE(wordBreak("catsandog", {"cats", "dog", "sand", "and", "cat"}));
}

TEST_CASE("edge cases") {
    SUBCASE("a word is reused") {
        CHECK(wordBreak("aaaa", {"a"}));
        CHECK(wordBreak("abababab", {"ab"}));
    }
    SUBCASE("no split exists") {
        CHECK_FALSE(wordBreak("abc", {"a", "b"}));
        CHECK_FALSE(wordBreak("abc", {"ab", "bc"}));
        CHECK_FALSE(wordBreak("a", {"b"}));
    }
    SUBCASE("a greedy longest-prefix choice fails") {
        CHECK(wordBreak("cars", {"car", "ca", "rs"}));
        CHECK(wordBreak("aaaaaaa", {"aaaa", "aaa"}));
    }
    SUBCASE("the whole string is one word") { CHECK(wordBreak("hello", {"hello", "he"})); }
    SUBCASE("a dictionary word longer than s") { CHECK_FALSE(wordBreak("ab", {"abc"})); }
    SUBCASE("a split exists only with the shorter word first") {
        CHECK(wordBreak("abcd", {"ab", "abc", "cd"}));
    }
    SUBCASE("unused words do not matter") { CHECK(wordBreak("xyz", {"q", "xyz", "zz"})); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        const std::string s = rand_string(rand_int(1, 12), 'a', 'b');
        Words dict;
        const int words = rand_int(1, 4);
        for (int i = 0; i < words; ++i) dict.push_back(rand_string(rand_int(1, 4), 'a', 'b'));
        INFO("s = " << s << ", dict size " << dict.size());
        CHECK(wordBreak(s, dict) == brute(s, 0, dict));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Dictionary {"a", "aa", ..., "a" x 10}.
    Words dict;
    for (int len = 1; len <= 10; ++len) dict.push_back(std::string(len, 'a'));
    // 150 a's then a 'b': nothing matches the 'b', so the answer is false, but a cache-free recursion
    // tries every composition of 150 into parts of size 1..10 first (exponentially many).
    CHECK_FALSE(wordBreak(std::string(150, 'a') + "b", dict));
    // 150 a's alone can be split, so the answer is true.
    CHECK(wordBreak(std::string(150, 'a'), dict));
}
