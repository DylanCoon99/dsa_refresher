#include <trie.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

TEST_CASE("examples") {
    Trie t;
    t.insert("apple");
    CHECK(t.search("apple"));
    CHECK_FALSE(t.search("app"));
    CHECK(t.startsWith("app"));
    t.insert("app");
    CHECK(t.search("app"));
}

TEST_CASE("edge cases") {
    SUBCASE("a prefix is not a word until it is inserted") {
        Trie t;
        t.insert("car");
        CHECK(t.search("car"));
        CHECK_FALSE(t.search("ca"));
        CHECK_FALSE(t.search("c"));
        CHECK(t.startsWith("ca"));
        CHECK(t.startsWith("c"));
        CHECK(t.startsWith("car"));
        t.insert("ca");
        CHECK(t.search("ca"));
        CHECK(t.search("car"));
    }
    SUBCASE("a longer string than any word is neither a word nor a prefix") {
        Trie t;
        t.insert("car");
        CHECK_FALSE(t.search("cart"));
        CHECK_FALSE(t.startsWith("cart"));
        CHECK_FALSE(t.search("cat"));
        CHECK_FALSE(t.startsWith("cat"));
    }
    SUBCASE("startsWith of the empty prefix, after an insert") {
        Trie t;
        t.insert("z");
        CHECK(t.startsWith(""));
        CHECK_FALSE(t.search(""));
    }
    SUBCASE("inserting the same word twice") {
        Trie t;
        t.insert("dog");
        t.insert("dog");
        CHECK(t.search("dog"));
        CHECK(t.startsWith("do"));
        CHECK_FALSE(t.search("do"));
    }
    SUBCASE("the empty word") {
        Trie t;
        t.insert("abc");
        CHECK_FALSE(t.search(""));
        t.insert("");
        CHECK(t.search(""));
        CHECK(t.search("abc"));
        CHECK(t.startsWith(""));
        Trie only_empty;
        only_empty.insert("");
        CHECK(only_empty.search(""));
        CHECK(only_empty.startsWith(""));
        CHECK_FALSE(only_empty.search("a"));
        CHECK_FALSE(only_empty.startsWith("a"));
    }
    SUBCASE("single letters and the full alphabet") {
        Trie t;
        t.insert("a");
        t.insert("z");
        CHECK(t.search("a"));
        CHECK(t.search("z"));
        CHECK_FALSE(t.search("m"));
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
        t.insert(alphabet);
        CHECK(t.search(alphabet));
        CHECK(t.startsWith(alphabet.substr(0, 25)));
        CHECK_FALSE(t.search(alphabet.substr(0, 25)));
    }
    SUBCASE("words sharing prefixes") {
        Trie t;
        for (const char* w : {"tea", "ten", "to", "inn", "in", "i"}) t.insert(w);
        for (const char* w : {"tea", "ten", "to", "inn", "in", "i"}) CHECK(t.search(w));
        for (const char* w : {"t", "te", "inne", "tex", "o", ""}) CHECK_FALSE(t.search(w));
        CHECK(t.startsWith("te"));
        CHECK(t.startsWith("inn"));
        CHECK_FALSE(t.startsWith("tb"));
    }
}

TEST_CASE("create and destroy many tries") {
    // The destructor must free every node exactly once; ASan reports a double free as CRASH.
    for (int round = 0; round < 100; ++round) {
        Trie t;
        std::vector<std::string> words;
        for (int k = 0; k < 20; ++k) words.push_back(rand_string(rand_int(0, 8), 'a', 'z'));
        for (const std::string& w : words) t.insert(w);
        for (const std::string& w : words) CHECK(t.search(w));
    }
    // Heap-allocated, too.
    for (int round = 0; round < 100; ++round) {
        Trie* t = new Trie();
        t->insert("abc");
        t->insert("abd");
        CHECK(t->startsWith("ab"));
        delete t;
    }
}

TEST_CASE("randomized vs std::set") {
    Trie t;
    std::set<std::string> words;
    auto has_prefix = [&](const std::string& p) {
        for (const std::string& w : words)
            if (w.rfind(p, 0) == 0) return true;
        return false;
    };
    for (int op = 0; op < 10'000; ++op) {
        std::string s = rand_string(rand_int(0, 5), 'a', 'c');
        switch (rand_int(0, 2)) {
            case 0:
                t.insert(s);
                words.insert(s);
                break;
            case 1:
                CHECK(t.search(s) == (words.count(s) == 1));
                break;
            default:
                if (s.empty() && words.empty()) break;  // startsWith("") on an empty trie is unspecified
                CHECK(t.startsWith(s) == has_prefix(s));
                break;
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 random words of length 20 over {a,b}, then 10^5 queries (each asked as both search and
    // startsWith). A linear scan over the words would be about 10^10 character comparisons.
    // Expected answers do not use the trie: a word is a 20-bit number, and a prefix of length k with
    // bits x is the heap-style code (1 << k) | x. Tables over those codes say which strings are
    // words and which are prefixes of some word.
    const int n = 100'000, len = 20;
    auto to_string = [&](unsigned bits, int k) {  // the first k letters of a 20-bit word
        std::string s(static_cast<std::size_t>(k), 'a');
        for (int i = 0; i < k; ++i)
            if ((bits >> (len - 1 - i)) & 1u) s[static_cast<std::size_t>(i)] = 'b';
        return s;
    };
    // To keep the trie a reasonable size (a fixed-array node is 26 pointers), the first 10 letters of
    // every word come from a pool of 128 random patterns; the last 10 letters are random.
    std::vector<unsigned> pool(128);
    for (unsigned& p : pool) p = static_cast<unsigned>(rand_int(0, 1023));
    auto random_word = [&]() {
        return (pool[static_cast<std::size_t>(rand_int(0, 127))] << 10) | static_cast<unsigned>(rand_int(0, 1023));
    };
    std::vector<unsigned> word_bits(n);
    std::vector<char> is_word(1u << (len + 1), 0), is_prefix(1u << (len + 1), 0);
    for (unsigned& w : word_bits) {
        w = random_word();
        is_word[(1u << len) | w] = 1;
        for (unsigned code = (1u << len) | w; code != 0 && !is_prefix[code]; code >>= 1) is_prefix[code] = 1;
    }

    std::vector<std::string> queries;
    std::vector<char> want_search, want_prefix;
    for (int k = 0; k < n; ++k) {
        unsigned bits = random_word();
        int qlen = len;
        if (k % 3 == 0) bits = word_bits[static_cast<std::size_t>(rand_int(0, n - 1))];             // an inserted word
        else if (k % 3 == 1) {                                                                       // a prefix of one
            bits = word_bits[static_cast<std::size_t>(rand_int(0, n - 1))];
            qlen = rand_int(1, len - 1);
        }                                                                                            // else: a fresh random word, present or not
        unsigned code = (1u << qlen) | (bits >> (len - qlen));
        queries.push_back(to_string(bits, qlen));
        want_search.push_back(qlen == len && is_word[code]);
        want_prefix.push_back(is_prefix[code]);
    }

    Trie t;
    for (unsigned w : word_bits) t.insert(to_string(w, len));
    int bad_search = 0, bad_prefix = 0;
    for (std::size_t k = 0; k < queries.size(); ++k) {
        if (t.search(queries[k]) != static_cast<bool>(want_search[k])) ++bad_search;
        if (t.startsWith(queries[k]) != static_cast<bool>(want_prefix[k])) ++bad_prefix;
    }
    CHECK(bad_search == 0);
    CHECK(bad_prefix == 0);
}
