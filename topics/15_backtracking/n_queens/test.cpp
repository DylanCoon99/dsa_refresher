#include <n_queens.hpp>

#include <doctest.h>
#include <printing.hpp>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

namespace {
using Boards = std::vector<std::vector<std::string>>;

Boards outer_sorted(Boards v) {
    std::sort(v.begin(), v.end());
    return v;
}

bool has_duplicates(Boards v) {
    std::sort(v.begin(), v.end());
    return std::adjacent_find(v.begin(), v.end()) != v.end();
}

// One queen per row, per column, per "/" diagonal and per "\" diagonal; only 'Q' and '.' characters.
bool valid_board(const std::vector<std::string>& b, int n) {
    if (static_cast<int>(b.size()) != n) return false;
    std::set<int> cols, d1, d2;
    for (int r = 0; r < n; ++r) {
        if (static_cast<int>(b[r].size()) != n) return false;
        int queens = 0;
        for (int c = 0; c < n; ++c) {
            if (b[r][c] != 'Q' && b[r][c] != '.') return false;
            if (b[r][c] == 'Q') {
                ++queens;
                if (!cols.insert(c).second) return false;
                if (!d1.insert(r + c).second) return false;
                if (!d2.insert(r - c).second) return false;
            }
        }
        if (queens != 1) return false;
    }
    return true;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(outer_sorted(solveNQueens(4)) ==
          Boards{{"..Q.", "Q...", "...Q", ".Q.."}, {".Q..", "...Q", "Q...", "..Q."}});
    CHECK(solveNQueens(1) == Boards{{"Q"}});
    CHECK(solveNQueens(3).empty());
}

TEST_CASE("edge cases") {
    SUBCASE("n = 1") { CHECK(solveNQueens(1) == Boards{{"Q"}}); }
    SUBCASE("n = 2 and n = 3 have no placement") {
        CHECK(solveNQueens(2).empty());
        CHECK(solveNQueens(3).empty());
    }
}

TEST_CASE("solution counts, validity and no duplicates for n = 1..9") {
    const std::size_t expected[] = {1, 0, 0, 2, 10, 4, 40, 92, 352};
    for (int n = 1; n <= 9; ++n) {
        CAPTURE(n);
        Boards got = solveNQueens(n);
        CHECK(got.size() == expected[n - 1]);
        CHECK_FALSE(has_duplicates(got));
        bool all_valid = true;
        for (const auto& b : got) all_valid = all_valid && valid_board(b, n);
        CHECK(all_valid);
    }
}
