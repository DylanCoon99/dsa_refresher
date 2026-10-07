#include <range_sum_query.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <numeric>
#include <vector>

namespace {
int brute(const std::vector<int>& v, int l, int r) { return std::accumulate(v.begin() + l, v.begin() + r + 1, 0); }
}  // namespace

TEST_CASE("examples") {
    NumArray a({-2, 0, 3, -5, 2, -1});
    CHECK(a.sumRange(0, 2) == 1);
    CHECK(a.sumRange(2, 5) == -1);
    CHECK(a.sumRange(0, 5) == -3);
}

TEST_CASE("edge cases") {
    SUBCASE("single element") {
        NumArray a({7});
        CHECK(a.sumRange(0, 0) == 7);
    }
    SUBCASE("single negative element") {
        NumArray a({-4});
        CHECK(a.sumRange(0, 0) == -4);
    }
    SUBCASE("full range") {
        NumArray a({1, 2, 3, 4});
        CHECK(a.sumRange(0, 3) == 10);
    }
    SUBCASE("first and last element alone") {
        NumArray a({5, -1, 8});
        CHECK(a.sumRange(0, 0) == 5);
        CHECK(a.sumRange(2, 2) == 8);
    }
    SUBCASE("queries repeat and may come in any order") {
        NumArray a({3, 1, 4, 1, 5, 9, 2, 6});
        CHECK(a.sumRange(4, 7) == 22);
        CHECK(a.sumRange(0, 1) == 4);
        CHECK(a.sumRange(4, 7) == 22);
        CHECK(a.sumRange(3, 3) == 1);
    }
    SUBCASE("all zeros and all equal values") {
        NumArray z({0, 0, 0});
        CHECK(z.sumRange(0, 2) == 0);
        NumArray e({2, 2, 2, 2});
        CHECK(e.sumRange(1, 3) == 6);
    }
    SUBCASE("values at the constraint limits") {
        NumArray a({10'000, -10'000, 10'000, 10'000});
        CHECK(a.sumRange(0, 3) == 20'000);
        CHECK(a.sumRange(1, 1) == -10'000);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 30);
        std::vector<int> v = rand_vec(n, -10'000, 10'000);
        NumArray a(v);
        for (int q = 0; q < 20; ++q) {
            const int l = rand_int(0, n - 1), r = rand_int(l, n - 1);
            CHECK(a.sumRange(l, r) == brute(v, l, r));
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Queries start near the front and end near the back, so a per-query loop does ~10^10 adds.
    const int n = 100'000;
    std::vector<int> v(n), pre(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        v[i] = (i * 7919) % 2001 - 1000;
        pre[i + 1] = pre[i] + v[i];  // independent check of the answers (|sum| <= 10^8)
    }
    NumArray a(v);
    long long mismatches = 0;
    for (int q = 0; q < 100'000; ++q) {
        const int l = rand_int(0, 100), r = rand_int(n - 101, n - 1);
        if (a.sumRange(l, r) != pre[r + 1] - pre[l]) ++mismatches;
    }
    CHECK(mismatches == 0);
    CHECK(a.sumRange(0, n - 1) == pre[n]);
    CHECK(pre[n] != 0);
}
