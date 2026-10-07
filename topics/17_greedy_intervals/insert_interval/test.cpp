#include <insert_interval.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

using Intervals = std::vector<std::vector<int>>;

namespace {
// Closed intervals on a tiny range. Cell 2x stands for the point x and cell 2x+1 for the gap after it,
// so touching intervals share a cell and merge, while a gap of one leaves a cell uncovered.
// Maximal runs of covered cells are the merged intervals.
Intervals brute(const Intervals& in, const std::vector<int>& add, int range) {
    std::vector<bool> cov(2 * range + 2, false);
    auto mark = [&](const std::vector<int>& iv) {
        for (int c = 2 * iv[0]; c <= 2 * iv[1]; ++c) cov[c] = true;
    };
    for (const auto& iv : in) mark(iv);
    mark(add);
    Intervals out;
    for (int c = 0; c < static_cast<int>(cov.size()); ++c) {
        if (!cov[c]) continue;
        int e = c;
        while (e + 1 < static_cast<int>(cov.size()) && cov[e + 1]) ++e;
        out.push_back({c / 2, e / 2});
        c = e;
    }
    return out;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(insert({{1, 3}, {6, 9}}, {2, 5}) == Intervals{{1, 5}, {6, 9}});
    CHECK(insert({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8}) == Intervals{{1, 2}, {3, 10}, {12, 16}});
    CHECK(insert({}, {5, 7}) == Intervals{{5, 7}});
}

TEST_CASE("edge cases") {
    SUBCASE("empty list") { CHECK(insert({}, {1, 1}) == Intervals{{1, 1}}); }
    SUBCASE("inserted before all") {
        CHECK(insert({{5, 6}, {8, 9}}, {1, 2}) == Intervals{{1, 2}, {5, 6}, {8, 9}});
    }
    SUBCASE("inserted after all") {
        CHECK(insert({{1, 2}, {4, 5}}, {7, 8}) == Intervals{{1, 2}, {4, 5}, {7, 8}});
    }
    SUBCASE("inserted in a gap between intervals") {
        CHECK(insert({{1, 2}, {8, 9}}, {4, 5}) == Intervals{{1, 2}, {4, 5}, {8, 9}});
    }
    SUBCASE("swallowing everything") {
        CHECK(insert({{2, 3}, {5, 6}, {8, 9}}, {0, 20}) == Intervals{{0, 20}});
        CHECK(insert({{2, 3}}, {2, 3}) == Intervals{{2, 3}});
    }
    SUBCASE("touching on the left merges (closed)") {
        CHECK(insert({{1, 3}, {6, 9}}, {3, 4}) == Intervals{{1, 4}, {6, 9}});
    }
    SUBCASE("touching on the right merges (closed)") {
        CHECK(insert({{1, 3}, {6, 9}}, {4, 6}) == Intervals{{1, 3}, {4, 9}});
    }
    SUBCASE("touching both neighbours merges all three") {
        CHECK(insert({{1, 3}, {6, 9}}, {3, 6}) == Intervals{{1, 9}});
    }
    SUBCASE("a gap of one keeps intervals apart") {
        CHECK(insert({{1, 3}, {6, 9}}, {4, 5}) == Intervals{{1, 3}, {4, 5}, {6, 9}});
    }
    SUBCASE("new interval inside an existing one") { CHECK(insert({{1, 10}}, {3, 4}) == Intervals{{1, 10}}); }
    SUBCASE("single-point new interval") {
        CHECK(insert({{1, 3}, {5, 7}}, {4, 4}) == Intervals{{1, 3}, {4, 4}, {5, 7}});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        // Sorted intervals separated by gaps of at least 1 (so none touch).
        Intervals in;
        int cur = rand_int(0, 2);
        const int n = rand_int(0, 6);
        for (int i = 0; i < n; ++i) {
            const int s = cur + rand_int(1, 3);
            const int e = s + rand_int(0, 3);
            in.push_back({s, e});
            cur = e;
        }
        int a = rand_int(0, cur + 4), b = rand_int(0, cur + 4);
        if (a > b) std::swap(a, b);
        INFO("trial " << trial);
        CHECK(insert(in, {a, b}) == brute(in, {a, b}, cur + 5));
    }
}
