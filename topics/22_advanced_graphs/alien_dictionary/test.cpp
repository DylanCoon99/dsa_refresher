#include <alien_dictionary.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

namespace {
using Words = std::vector<std::string>;

std::set<char> lettersOf(const Words& w) {
    std::set<char> s;
    for (const auto& x : w) s.insert(x.begin(), x.end());
    return s;
}

// Is `order` an arrangement of exactly the letters of `words` (each once) under which `words` is sorted?
bool consistent(const std::string& order, const Words& words) {
    std::set<char> letters = lettersOf(words);
    std::set<char> seen(order.begin(), order.end());
    if (seen.size() != order.size() || seen != letters) return false;  // duplicates, missing or extra letters
    auto rank = [&](char c) { return order.find(c); };
    for (std::size_t i = 0; i + 1 < words.size(); ++i) {
        const std::string &a = words[i], &b = words[i + 1];
        std::size_t k = 0;
        while (k < a.size() && k < b.size() && a[k] == b[k]) ++k;
        if (k == a.size() || k == b.size()) {
            if (a.size() > b.size()) return false;  // a longer word may not precede its own prefix
        } else if (rank(a[k]) >= rank(b[k])) {
            return false;
        }
    }
    return true;
}

// Brute force: try every arrangement of the letters.
bool anyOrderWorks(const Words& words) {
    std::set<char> letters = lettersOf(words);
    std::string p(letters.begin(), letters.end());
    do {
        if (consistent(p, words)) return true;
    } while (std::next_permutation(p.begin(), p.end()));
    return false;
}

void expectValid(const Words& words) {
    std::string got = alienOrder(words);
    INFO("got \"" << got << "\"");
    CHECK(consistent(got, words));
}
}  // namespace

TEST_CASE("examples") {
    expectValid({"wrt", "wrf", "er", "ett", "rftt"});  // t < f, w < e, r < t, e < r
    // The only consistent order here is "zx".
    CHECK(alienOrder({"z", "x"}) == "zx");
}

TEST_CASE("edge cases") {
    SUBCASE("inconsistent: a word precedes its own prefix") { CHECK(alienOrder({"abc", "ab"}) == ""); }
    SUBCASE("a prefix before the longer word is fine") { expectValid({"ab", "abc"}); }
    SUBCASE("inconsistent: a two-letter cycle") { CHECK(alienOrder({"z", "x", "z"}) == ""); }
    SUBCASE("inconsistent: a three-letter cycle") {
        // a < b, b < c, c < a from the three adjacent pairs.
        CHECK(alienOrder({"ab", "bc", "ca", "ab"}) == "");
    }
    SUBCASE("a single word: its letters in any order") {
        expectValid({"abcab"});
        CHECK(alienOrder({"abcab"}).size() == 3);
    }
    SUBCASE("a single one-letter word") { CHECK(alienOrder({"q"}) == "q"); }
    SUBCASE("equal adjacent words give no constraint") {
        expectValid({"aa", "aa"});
        CHECK(alienOrder({"zz", "zz"}).size() == 1);
    }
    SUBCASE("letters with no constraints are still included") {
        // Only a < b is known; c and d appear but nothing orders them.
        Words w = {"ab", "cd"};
        std::string got = alienOrder(w);
        INFO("got \"" << got << "\"");
        CHECK(got.size() == 4);
        CHECK(consistent(got, w));
    }
    SUBCASE("a letter that appears only in a later part of a word is included") {
        Words w = {"ac", "ad", "bxy"};
        std::string got = alienOrder(w);
        INFO("got \"" << got << "\"");
        CHECK(got.size() == 6);  // a, b, c, d, x, y
        CHECK(consistent(got, w));
    }
    SUBCASE("only the first difference between adjacent words counts") {
        // "ab" < "ba": a < b. The later letters of each word give no constraint of their own.
        Words w = {"abz", "bay"};
        expectValid(w);
    }
    SUBCASE("a chain of adjacent pairs forces a single order") {
        // a < b, b < c, c < d from three adjacent pairs; the only valid order is "abcd".
        CHECK(alienOrder({"a", "b", "c", "d"}) == "abcd");
    }
    SUBCASE("a long chain of constraints") {
        Words w = {"za", "yb", "xc", "wd"};
        std::string got = alienOrder(w);
        INFO("got \"" << got << "\"");
        CHECK(got.size() == 8);  // z < y < x < w are forced; a, b, c, d are free but must be present
        CHECK(consistent(got, w));
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int k = rand_int(1, 5);
        int count = rand_int(1, 6);
        Words w;
        for (int i = 0; i < count; ++i) w.push_back(rand_string(rand_int(1, 3), 'a', static_cast<char>('a' + k - 1)));
        INFO("trial " << trial);
        std::string got = alienOrder(w);
        if (anyOrderWorks(w)) {
            CHECK(consistent(got, w));
        } else {
            CHECK(got == "");
        }
    }
}

TEST_CASE("randomized sorted dictionaries are always solvable") {
    // Sort random words by a random hidden alphabet; the answer must then be a valid order.
    for (int trial = 0; trial < 200; ++trial) {
        int k = rand_int(2, 8);
        std::string alphabet;
        for (int i = 0; i < k; ++i) alphabet += static_cast<char>('a' + i);
        std::shuffle(alphabet.begin(), alphabet.end(), rng());
        auto rank = [&](char c) { return alphabet.find(c); };
        Words w;
        int count = rand_int(1, 12);
        for (int i = 0; i < count; ++i) w.push_back(rand_string(rand_int(1, 4), 'a', static_cast<char>('a' + k - 1)));
        std::stable_sort(w.begin(), w.end(), [&](const std::string& a, const std::string& b) {
            return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                                                [&](char x, char y) { return rank(x) < rank(y); });
        });
        std::string got = alienOrder(w);
        INFO("trial " << trial << ", hidden alphabet " << alphabet);
        CHECK(consistent(got, w));
    }
}
