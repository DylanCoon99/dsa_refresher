#include <binary_search.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <climits>
#include <vector>

TEST_CASE("examples") {
    CHECK(search({-1, 0, 3, 5, 9, 12}, 9) == 4);
    CHECK(search({-1, 0, 3, 5, 9, 12}, 2) == -1);
    CHECK(search({5}, 5) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 1 hit") { CHECK(search({7}, 7) == 0); }
    SUBCASE("n = 1 miss") {
        CHECK(search({7}, 6) == -1);
        CHECK(search({7}, 8) == -1);
    }
    SUBCASE("target at both ends") {
        const std::vector<int> a = {1, 4, 6, 9, 11, 20, 30};
        CHECK(search(a, 1) == 0);
        CHECK(search(a, 30) == 6);
    }
    SUBCASE("targets outside the range") {
        const std::vector<int> a = {1, 4, 6, 9};
        CHECK(search(a, 0) == -1);
        CHECK(search(a, 10) == -1);
    }
    SUBCASE("INT_MIN and INT_MAX") {
        const std::vector<int> a = {INT_MIN, -1, 0, INT_MAX};
        CHECK(search(a, INT_MIN) == 0);
        CHECK(search(a, INT_MAX) == 3);
        CHECK(search(a, INT_MIN + 1) == -1);
        CHECK(search(a, INT_MAX - 1) == -1);
    }
    SUBCASE("every index of small arrays") {
        for (int n = 1; n <= 12; ++n) {
            std::vector<int> a;
            for (int i = 0; i < n; ++i) a.push_back(2 * i);
            for (int i = 0; i < n; ++i) CHECK(search(a, 2 * i) == i);
            for (int i = -1; i <= n; ++i) CHECK(search(a, 2 * i + 1) == -1);
        }
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> a;
        int v = rand_int(-30, 0);
        for (int i = rand_int(1, 25); i > 0; --i) {
            a.push_back(v);
            v += rand_int(1, 4);
        }
        const int target = rand_int(-35, 100);
        int expected = -1;
        for (int i = 0; i < static_cast<int>(a.size()); ++i)
            if (a[i] == target) expected = i;
        CHECK(search(a, target) == expected);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // nums[i] = 2i + 1 (all odd), queried with q in [0, 2n): odd q hits at index (q-1)/2, even q misses.
    // A linear scan per query is ~5·10^11 comparisons in total.
    const int n = 1'000'000;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) nums[i] = 2 * i + 1;
    long long mismatches = 0, hits = 0;
    for (long long k = 0; k < n; ++k) {
        const int q = static_cast<int>((k * 7919 + 13) % (2LL * n));
        const int expected = (q % 2 == 1) ? (q - 1) / 2 : -1;
        hits += expected >= 0;
        if (search(nums, q) != expected) ++mismatches;
    }
    CHECK(hits > 400'000);
    CHECK(mismatches == 0);
}
