#include <word_search_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

namespace {
using Board = std::vector<std::vector<char>>;

std::vector<std::string> sorted(std::vector<std::string> v) {
    std::sort(v.begin(), v.end());
    return v;
}

// Obviously-correct reference: one DFS per word.
bool brute_dfs(const Board& b, std::vector<std::vector<char>>& used, const std::string& w, std::size_t k, int r, int c) {
    if (r < 0 || c < 0 || r >= static_cast<int>(b.size()) || c >= static_cast<int>(b[0].size())) return false;
    if (used[r][c] || b[r][c] != w[k]) return false;
    if (k + 1 == w.size()) return true;
    used[r][c] = 1;
    bool ok = brute_dfs(b, used, w, k + 1, r + 1, c) || brute_dfs(b, used, w, k + 1, r - 1, c) ||
              brute_dfs(b, used, w, k + 1, r, c + 1) || brute_dfs(b, used, w, k + 1, r, c - 1);
    used[r][c] = 0;
    return ok;
}
std::vector<std::string> brute_find(const Board& b, const std::vector<std::string>& words) {
    std::set<std::string> out;
    for (const std::string& w : words) {
        std::vector<std::vector<char>> used(b.size(), std::vector<char>(b[0].size(), 0));
        for (int r = 0; r < static_cast<int>(b.size()); ++r)
            for (int c = 0; c < static_cast<int>(b[0].size()); ++c)
                if (brute_dfs(b, used, w, 0, r, c)) out.insert(w);
    }
    return {out.begin(), out.end()};
}
}  // namespace

TEST_CASE("examples") {
    Board b1 = {{'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'}, {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}};
    CHECK(sorted(findWords(b1, {"oath", "pea", "eat", "rain"})) == std::vector<std::string>{"eat", "oath"});
    CHECK(findWords({{'a', 'b'}, {'c', 'd'}}, {"abcb"}).empty());
    CHECK(sorted(findWords({{'a'}}, {"a", "aa"})) == std::vector<std::string>{"a"});
}

TEST_CASE("edge cases") {
    SUBCASE("1x1 board") {
        CHECK(sorted(findWords({{'a'}}, {"a"})) == std::vector<std::string>{"a"});
        CHECK(findWords({{'a'}}, {"b"}).empty());
        CHECK(findWords({{'a'}}, {"aa", "ab"}).empty());
    }
    SUBCASE("the same word reachable two ways appears once") {
        // "ab" can start at (0,0) or (1,1) and end at either b.
        Board b = {{'a', 'b'}, {'b', 'a'}};
        CHECK(sorted(findWords(b, {"ab"})) == std::vector<std::string>{"ab"});
    }
    SUBCASE("duplicate entries in the word list are reported once") {
        Board b = {{'a', 'b'}};
        CHECK(sorted(findWords(b, {"ab", "ab", "ba", "ba", "ab"})) == std::vector<std::string>{"ab", "ba"});
    }
    SUBCASE("a word needing a reused cell is absent") {
        CHECK(findWords({{'a', 'b'}}, {"aba"}).empty());
        CHECK(findWords({{'a', 'a'}}, {"aaa"}).empty());
        CHECK(findWords({{'a', 'b'}, {'c', 'd'}}, {"abcb", "abdc", "acdb", "abca"}).size() == 2);
    }
    SUBCASE("cells are reusable across different words") {
        CHECK(sorted(findWords({{'a', 'b'}}, {"ab", "ba", "a", "b"})) ==
              std::vector<std::string>{"a", "ab", "b", "ba"});
    }
    SUBCASE("no diagonal moves") {
        CHECK(findWords({{'a', 'x'}, {'x', 'b'}}, {"ab"}).empty());
    }
    SUBCASE("a word and its own prefix are both found") {
        Board b = {{'a', 'p', 'p', 'l', 'e'}};
        CHECK(sorted(findWords(b, {"app", "apple", "appl"})) == std::vector<std::string>{"app", "appl", "apple"});
    }
    SUBCASE("a long word that fits only along a snake path") {
        Board b = {{'a', 'b', 'c'}, {'f', 'e', 'd'}, {'g', 'h', 'i'}};
        CHECK(sorted(findWords(b, {"abcdefghi", "abcfehgid", "abcdihgfe"})) ==
              std::vector<std::string>{"abcdefghi", "abcdihgfe"});
    }
    SUBCASE("word longer than the number of cells") {
        CHECK(findWords({{'a', 'b'}}, {"abab"}).empty());
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int rows = rand_int(1, 4), cols = rand_int(1, 4);
        Board b(rows, std::vector<char>(cols));
        for (auto& row : b)
            for (char& c : row) c = static_cast<char>(rand_int('a', 'b'));
        std::vector<std::string> words;
        for (int k = rand_int(1, 12); k > 0; --k) words.push_back(rand_string(rand_int(1, 6), 'a', 'b'));
        CHECK(sorted(findWords(b, words)) == brute_find(b, words));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 12x12 board of random letters from {a,b,c}, 3*10^4 random words of length 1-10 over {a,b,c}.
    // Letters are skewed towards 'a' (70% a, 20% b, 10% c) so that many paths survive several
    // letters; searching the board once per word then repeats a lot of work (about 4 s for the
    // per-word DFS in Debug+ASan), while one shared trie walk does not.
    // Expected answer: enumerate every simple path of length <= 10 on the board once, marking the
    // base-4 code of its letters (letter+1 per digit, so codes of different strings never
    // collide), then look each distinct word up in that table.
    const int R = 12, C = 12, maxLen = 10;
    auto skewed_letter = [] {  // 'a' 70%, 'b' 20%, 'c' 10%
        const int x = rand_int(0, 9);
        return x < 7 ? 'a' : (x < 9 ? 'b' : 'c');
    };
    Board b(R, std::vector<char>(C));
    for (auto& row : b)
        for (char& c : row) c = skewed_letter();
    std::vector<std::string> words;
    for (int k = 0; k < 30'000; ++k) {
        std::string w(static_cast<std::size_t>(rand_int(1, maxLen)), 'a');
        for (char& c : w) c = skewed_letter();
        words.push_back(w);
    }

    std::vector<char> reachable(1 << (2 * maxLen), 0);
    std::vector<std::vector<char>> used(R, std::vector<char>(C, 0));
    struct Walk {
        const Board& b;
        std::vector<std::vector<char>>& used;
        std::vector<char>& reachable;
        void go(int r, int c, int len, int code) {
            if (r < 0 || c < 0 || r >= R || c >= C || used[r][c]) return;
            code = code * 4 + (b[r][c] - 'a' + 1);
            reachable[code] = 1;
            if (len == maxLen) return;
            used[r][c] = 1;
            go(r + 1, c, len + 1, code);
            go(r - 1, c, len + 1, code);
            go(r, c + 1, len + 1, code);
            go(r, c - 1, len + 1, code);
            used[r][c] = 0;
        }
    } walk{b, used, reachable};
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c) walk.go(r, c, 1, 0);

    std::set<std::string> want;
    for (const std::string& w : words) {
        int code = 0;
        for (char ch : w) code = code * 4 + (ch - 'a' + 1);
        if (reachable[code]) want.insert(w);
    }
    REQUIRE(want.size() > 100);  // the instance is meaningful: many words are present

    std::vector<std::string> got = findWords(b, words);
    CHECK(sorted(got) == std::vector<std::string>(want.begin(), want.end()));
}
