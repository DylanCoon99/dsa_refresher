#include <merge_intervals.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

using Intervals = std::vector<std::vector<int>>;

namespace {
// Closed intervals on a tiny range. Cell 2x stands for the point x and cell 2x+1 for the gap after it,
// so {1,4} covers cells 2..8 and {4,5} covers 8..10 (they share cell 8 and merge), while {1,4} and
// {5,6} leave cell 9 uncovered (they stay separate). Maximal runs of covered cells are the answer.
Intervals brute(const Intervals& in, int range) {
    std::vector<bool> cov(2 * range + 2, false);
    for (const auto& iv : in)
        for (int c = 2 * iv[0]; c <= 2 * iv[1]; ++c) cov[c] = true;
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
    CHECK(merge({{1, 3}, {2, 6}, {8, 10}, {15, 18}}) == Intervals{{1, 6}, {8, 10}, {15, 18}});
    CHECK(merge({{1, 4}, {4, 5}}) == Intervals{{1, 5}});
    CHECK(merge({{8, 10}, {1, 3}, {2, 4}}) == Intervals{{1, 4}, {8, 10}});
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(merge({}) == Intervals{}); }
    SUBCASE("single interval") { CHECK(merge({{3, 7}}) == Intervals{{3, 7}}); }
    SUBCASE("single point interval") { CHECK(merge({{5, 5}}) == Intervals{{5, 5}}); }
    SUBCASE("touching merges (closed)") {
        CHECK(merge({{1, 4}, {4, 5}}) == Intervals{{1, 5}});
        CHECK(merge({{4, 5}, {1, 4}}) == Intervals{{1, 5}});
    }
    SUBCASE("a gap of one keeps them apart") { CHECK(merge({{1, 4}, {5, 6}}) == Intervals{{1, 4}, {5, 6}}); }
    SUBCASE("containment") {
        CHECK(merge({{1, 10}, {2, 3}, {4, 5}}) == Intervals{{1, 10}});
        CHECK(merge({{2, 3}, {1, 10}}) == Intervals{{1, 10}});
    }
    SUBCASE("unsorted input") {
        CHECK(merge({{15, 18}, {2, 6}, {8, 10}, {1, 3}}) == Intervals{{1, 6}, {8, 10}, {15, 18}});
    }
    SUBCASE("duplicates") { CHECK(merge({{2, 4}, {2, 4}, {2, 4}}) == Intervals{{2, 4}}); }
    SUBCASE("same start, different ends") { CHECK(merge({{1, 2}, {1, 9}, {1, 5}}) == Intervals{{1, 9}}); }
    SUBCASE("a later interval ends before the current one") {
        CHECK(merge({{1, 10}, {2, 4}, {5, 7}, {12, 13}}) == Intervals{{1, 10}, {12, 13}});
    }
    SUBCASE("large coordinates") {
        CHECK(merge({{1000000000, 1000000000}, {0, 0}}) == Intervals{{0, 0}, {1000000000, 1000000000}});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int range = 25;
        const int n = rand_int(1, 8);
        Intervals in;
        for (int i = 0; i < n; ++i) {
            int a = rand_int(0, range), b = rand_int(0, range);
            if (a > b) std::swap(a, b);
            in.push_back({a, b});
        }
        INFO("trial " << trial);
        CHECK(merge(in) == brute(in, range));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 intervals in total, shuffled:
    //  - a chain {2i, 2i+2} for i < n/2: each touches the next, so they merge into one {0, n};
    //  - n/2 pairwise disjoint intervals {200000 + 3j, 200000 + 3j + 1}, which stay as they are.
    const int n = 100000;
    Intervals in, expected;
    for (int i = 0; i < n / 2; ++i) in.push_back({2 * i, 2 * i + 2});
    expected.push_back({0, n});
    for (int j = 0; j < n / 2; ++j) {
        in.push_back({200000 + 3 * j, 200000 + 3 * j + 1});
        expected.push_back({200000 + 3 * j, 200000 + 3 * j + 1});
    }
    std::shuffle(in.begin(), in.end(), rng());
    CHECK(merge(in) == expected);
}
