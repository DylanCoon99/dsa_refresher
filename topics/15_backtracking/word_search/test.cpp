#include <word_search.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace {
using Board = std::vector<std::vector<char>>;

// Brute force: track every reachable (cell, visited-set) state after matching each prefix.
// Boards are small (at most 3x3), so the visited set fits in a bitmask.
bool brute(const Board& b, const std::string& w) {
    const int R = static_cast<int>(b.size()), C = static_cast<int>(b[0].size());
    std::set<std::pair<int, int>> states;  // (cell index, visited mask)
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c)
            if (b[r][c] == w[0]) states.insert({r * C + c, 1 << (r * C + c)});
    for (std::size_t i = 1; i < w.size() && !states.empty(); ++i) {
        std::set<std::pair<int, int>> next;
        for (auto [cell, mask] : states) {
            const int r = cell / C, c = cell % C;
            const int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                int id = nr * C + nc;
                if ((mask >> id & 1) || b[nr][nc] != w[i]) continue;
                next.insert({id, mask | (1 << id)});
            }
        }
        states = next;
    }
    return !states.empty();
}

const Board kClassic = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
}  // namespace

TEST_CASE("examples") {
    CHECK(exist(kClassic, "ABCCED"));
    CHECK(exist(kClassic, "SEE"));
    CHECK_FALSE(exist(kClassic, "ABCB"));
}

TEST_CASE("edge cases") {
    SUBCASE("single cell, matching") { CHECK(exist({{'A'}}, "A")); }
    SUBCASE("single cell, not matching") { CHECK_FALSE(exist({{'A'}}, "B")); }
    SUBCASE("word longer than the number of cells") {
        CHECK_FALSE(exist({{'A', 'A'}}, "AAA"));
        CHECK_FALSE(exist({{'A', 'A'}, {'A', 'A'}}, "AAAAA"));
    }
    SUBCASE("a cell may not be reused") {
        CHECK_FALSE(exist({{'A', 'B'}}, "ABA"));
        CHECK(exist({{'A', 'B'}}, "AB"));
        CHECK(exist({{'A', 'B'}}, "BA"));
    }
    SUBCASE("word uses every cell of a 1 x n board") { CHECK(exist({{'A', 'B', 'C', 'D'}}, "DCBA")); }
    SUBCASE("snake path through every cell") {
        Board snake = {{'A', 'B', 'C', 'D'}, {'H', 'G', 'F', 'E'}, {'I', 'J', 'K', 'L'}};
        CHECK(exist(snake, "ABCDEFGHIJKL"));
        CHECK_FALSE(exist(snake, "ABCDEFGHIJKM"));
        CHECK_FALSE(exist(snake, "ABCDGHIJKL"));  // D and G are not adjacent
    }
    SUBCASE("diagonal moves are not allowed") { CHECK_FALSE(exist({{'A', 'X'}, {'X', 'B'}}, "AB")); }
    SUBCASE("a path that needs a dead-end branch to be abandoned") {
        // Starting at the left A and going right dead-ends; the answer is the path from the right A.
        CHECK(exist({{'A', 'A', 'B'}}, "AAB"));
        CHECK_FALSE(exist({{'A', 'A', 'B'}}, "ABA"));
    }
    SUBCASE("all same letter, exact cell count") {
        Board all_a(3, std::vector<char>(3, 'A'));
        CHECK(exist(all_a, std::string(9, 'A')));
        CHECK_FALSE(exist(all_a, std::string(10, 'A')));
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        const int R = rand_int(1, 3), C = rand_int(1, 3);
        Board b(R, std::vector<char>(C));
        for (auto& row : b)
            for (char& ch : row) ch = static_cast<char>('A' + rand_int(0, 2));
        std::string w = rand_string(rand_int(1, 6), 'A', 'C');
        CHECK(exist(b, w) == brute(b, w));
    }
}
