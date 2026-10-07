#include <word_ladder.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <queue>
#include <set>
#include <string>
#include <vector>

namespace {
using Words = std::vector<std::string>;

bool oneApart(const std::string& a, const std::string& b) {
    int diff = 0;
    for (std::size_t i = 0; i < a.size(); ++i) diff += a[i] != b[i];
    return diff == 1;
}

// Brute force: BFS comparing each word with the whole list.
int brute(const std::string& begin, const std::string& end, const Words& list) {
    if (std::find(list.begin(), list.end(), end) == list.end()) return 0;
    std::set<std::string> seen{begin};
    std::queue<std::pair<std::string, int>> q;
    q.push({begin, 1});
    while (!q.empty()) {
        auto [w, len] = q.front();
        q.pop();
        if (w == end) return len;
        for (const auto& nb : list)
            if (oneApart(w, nb) && seen.insert(nb).second) q.push({nb, len + 1});
    }
    return 0;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(ladderLength("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}) == 5);
    CHECK(ladderLength("hit", "cog", {"hot", "dot", "dog", "lot", "log"}) == 0);
    CHECK(ladderLength("a", "c", {"a", "b", "c"}) == 2);
}

TEST_CASE("edge cases") {
    SUBCASE("endWord not in the list") {
        CHECK(ladderLength("hit", "hot", {"dot", "dog"}) == 0);
        CHECK(ladderLength("aa", "bb", {"ab", "ba"}) == 0);
    }
    SUBCASE("a single step") {
        CHECK(ladderLength("hit", "hot", {"hot"}) == 2);
        CHECK(ladderLength("abc", "abd", {"abd", "xyz"}) == 2);
    }
    SUBCASE("no path") {
        CHECK(ladderLength("aaa", "zzz", {"aab", "abb", "zzz", "zzy"}) == 0);
        CHECK(ladderLength("hit", "cog", {"cog", "cot"}) == 0);
    }
    SUBCASE("beginWord is not required to be in the list") {
        CHECK(ladderLength("hit", "hot", {"hot", "hat"}) == 2);
        CHECK(ladderLength("hit", "hot", {"hit", "hot"}) == 2);
    }
    SUBCASE("several routes, the shortest counts") {
        // Every route from aaa to bbb needs 3 changes (4 words); the x-words are a dead-end detour.
        CHECK(ladderLength("aaa", "bbb", {"aab", "abb", "bbb", "aba", "baa", "bba", "xaa", "xxa", "xxx", "bxx"}) == 4);
    }
    SUBCASE("single-letter words") { CHECK(ladderLength("a", "c", {"c"}) == 2); }
    SUBCASE("a long forced chain") {
        // Each word in the list differs from the next by one letter; no shortcut exists.
        CHECK(ladderLength("aaaa", "bbbb", {"baaa", "bbaa", "bbba", "bbbb"}) == 5);
    }
}

TEST_CASE("randomized vs all-pairs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int len = rand_int(1, 3), n = rand_int(1, 12);
        std::set<std::string> uniq;
        for (int i = 0; i < n; ++i) uniq.insert(rand_string(len, 'a', 'c'));
        Words list(uniq.begin(), uniq.end());
        std::string begin = rand_string(len, 'a', 'c'), end;
        do end = rand_string(len, 'a', 'c');
        while (end == begin);
        CHECK(ladderLength(begin, end, list) == brute(begin, end, list));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 5000 distinct words of length 5: every word whose letters at positions 0-3 come from
    // {a..e} and whose last letter comes from {a..h} (5*5*5*5*8 = 5000). In this set two words are
    // neighbors exactly when they differ in one position, so the ladder length from "zaaaa" (not in
    // the list) to "eeeeh" is 1 + the number of positions that differ: all 5, giving 6. An
    // all-pairs neighbor search (O(n^2 * L)) does not finish in time.
    Words list;
    for (char a = 'a'; a <= 'e'; ++a)
        for (char b = 'a'; b <= 'e'; ++b)
            for (char c = 'a'; c <= 'e'; ++c)
                for (char d = 'a'; d <= 'e'; ++d)
                    for (char e = 'a'; e <= 'h'; ++e) list.push_back({a, b, c, d, e});
    REQUIRE(list.size() == 5000);
    std::shuffle(list.begin(), list.end(), rng());
    CHECK(ladderLength("zaaaa", "eeeeh", list) == 6);
}
