#include <word_dictionary.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <string>
#include <vector>

namespace {
// Obviously-correct reference: scan every word.
bool brute_match(const std::string& word, const std::string& pattern) {
    if (word.size() != pattern.size()) return false;
    for (std::size_t i = 0; i < word.size(); ++i)
        if (pattern[i] != '.' && pattern[i] != word[i]) return false;
    return true;
}
bool brute_search(const std::vector<std::string>& words, const std::string& pattern) {
    for (const std::string& w : words)
        if (brute_match(w, pattern)) return true;
    return false;
}
}  // namespace

TEST_CASE("examples") {
    WordDictionary d;
    d.addWord("bad");
    d.addWord("dad");
    d.addWord("mad");
    CHECK_FALSE(d.search("pad"));
    CHECK(d.search("bad"));
    CHECK(d.search(".ad"));
    CHECK(d.search("b.."));
}

TEST_CASE("edge cases") {
    SUBCASE("empty dictionary") {
        WordDictionary d;
        CHECK_FALSE(d.search("a"));
        CHECK_FALSE(d.search("."));
    }
    SUBCASE("all dots") {
        WordDictionary d;
        d.addWord("abc");
        CHECK(d.search("..."));
        CHECK_FALSE(d.search(".."));
        CHECK_FALSE(d.search("...."));
        d.addWord("z");
        CHECK(d.search("."));
    }
    SUBCASE("dots longer than any word") {
        WordDictionary d;
        d.addWord("ab");
        d.addWord("abc");
        CHECK_FALSE(d.search("...."));
        CHECK_FALSE(d.search("....."));
        CHECK_FALSE(d.search("ab..."));
    }
    SUBCASE("a dot at the end") {
        WordDictionary d;
        d.addWord("cat");
        CHECK(d.search("ca."));
        CHECK_FALSE(d.search("ba."));
        CHECK_FALSE(d.search("c."));
        CHECK_FALSE(d.search("cat."));
    }
    SUBCASE("a dot at the start") {
        WordDictionary d;
        d.addWord("cat");
        CHECK(d.search(".at"));
        CHECK_FALSE(d.search(".ar"));
    }
    SUBCASE("mixed literals and dots") {
        WordDictionary d;
        d.addWord("abcde");
        d.addWord("abxde");
        d.addWord("zzzzz");
        CHECK(d.search("a.c.e"));
        CHECK(d.search(".b.d."));
        CHECK(d.search("a..de"));
        CHECK_FALSE(d.search("a.c.f"));
        CHECK_FALSE(d.search("a.cxe"));
        CHECK(d.search("zz.zz"));
        CHECK_FALSE(d.search("zy.zz"));
    }
    SUBCASE("the right branch is found after a wrong one") {
        // '.' must try every child, not just the first.
        WordDictionary d;
        d.addWord("aab");
        d.addWord("abb");
        d.addWord("acc");
        CHECK(d.search(".cc"));
        CHECK(d.search("a.c"));
        CHECK_FALSE(d.search(".ca"));
        CHECK(d.search(".bb"));
    }
    SUBCASE("a stored prefix is not a match for a longer pattern, or the reverse") {
        WordDictionary d;
        d.addWord("app");
        d.addWord("apple");
        CHECK(d.search("app"));
        CHECK(d.search("a.p.e"));
        CHECK_FALSE(d.search("appl"));
        CHECK_FALSE(d.search("a.pl"));
        CHECK_FALSE(d.search("ap"));
    }
    SUBCASE("adding twice and single-letter words") {
        WordDictionary d;
        d.addWord("a");
        d.addWord("a");
        CHECK(d.search("a"));
        CHECK(d.search("."));
        CHECK_FALSE(d.search("b"));
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        WordDictionary d;
        std::vector<std::string> words;
        const int n = rand_int(0, 12);
        for (int k = 0; k < n; ++k) {
            words.push_back(rand_string(rand_int(1, 5), 'a', 'c'));
            d.addWord(words.back());
        }
        for (int q = 0; q < 30; ++q) {
            std::string p = rand_string(rand_int(1, 6), 'a', 'c');
            for (char& c : p)
                if (rand_int(0, 2) == 0) c = '.';
            CHECK(d.search(p) == brute_search(words, p));
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^4 random words of length 3-5 over 'a'..'y', then 10^4 patterns of length 3-5 with a
    // mix of dots. The expected answer is known by construction (no dictionary scan):
    //  - "hit" patterns are an added word with some positions replaced by '.', so they match;
    //  - "miss" patterns put the letter 'z' (never in any word) at position 0 or 1.
    // Scanning every word for every pattern costs about 10^8 length checks plus character compares.
    const int n = 10'000;
    std::vector<std::string> words;
    WordDictionary d;
    for (int k = 0; k < n; ++k) {
        words.push_back(rand_string(rand_int(3, 5), 'a', 'y'));
        d.addWord(words.back());
    }
    std::vector<std::string> patterns;
    std::vector<char> want;
    for (int k = 0; k < n; ++k) {
        std::string p;
        if (k % 2 == 0) {
            p = words[rand_int(0, n - 1)];
            for (char& c : p)
                if (rand_int(0, 1) == 0) c = '.';
            want.push_back(1);
        } else {
            p = std::string(static_cast<std::size_t>(rand_int(3, 5)), '.');
            p[static_cast<std::size_t>(rand_int(0, 1))] = 'z';
            want.push_back(0);
        }
        patterns.push_back(p);
    }
    int bad = 0;
    for (int k = 0; k < n; ++k)
        if (d.search(patterns[static_cast<std::size_t>(k)]) != static_cast<bool>(want[static_cast<std::size_t>(k)])) ++bad;
    CHECK(bad == 0);
}
