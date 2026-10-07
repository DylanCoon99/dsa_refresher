#include <segment_tree.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

TEST_CASE("examples") {
    SegmentTree t({2, 4, 6, 8});
    CHECK(t.query(0, 3) == 20);
    CHECK(t.query(1, 2) == 10);
    t.update(1, 10);
    CHECK(t.query(0, 3) == 26);
    CHECK(t.query(1, 1) == 10);

    SegmentTree one({5});
    CHECK(one.query(0, 0) == 5);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 1") {
        SegmentTree t({7});
        CHECK(t.query(0, 0) == 7);
        t.update(0, -3);
        CHECK(t.query(0, 0) == -3);
    }
    SUBCASE("n = 7 (not a power of two): every range") {
        const std::vector<long long> v = {3, -1, 4, -1, 5, -9, 2};
        SegmentTree t(v);
        bool ok = true;
        for (int l = 0; l < 7; ++l) {
            long long want = 0;
            for (int r = l; r < 7; ++r) {
                want += v[r];
                ok = ok && t.query(l, r) == want;
            }
        }
        CHECK(ok);
    }
    SUBCASE("n = 7: update then every prefix") {
        SegmentTree t({1, 1, 1, 1, 1, 1, 1});
        t.update(6, 100);
        t.update(0, -50);
        CHECK(t.query(0, 6) == 55);
        CHECK(t.query(0, 0) == -50);
        CHECK(t.query(5, 6) == 101);
    }
    SUBCASE("update assigns rather than adds") {
        SegmentTree t({5, 5, 5});
        t.update(1, 5);
        CHECK(t.query(0, 2) == 15);
        t.update(1, 5);
        t.update(1, 2);
        CHECK(t.query(1, 1) == 2);
        CHECK(t.query(0, 2) == 12);
    }
    SUBCASE("extreme values accumulate in 64 bits") {
        SegmentTree t({1'000'000'000, 1'000'000'000, 1'000'000'000});
        CHECK(t.query(0, 2) == 3'000'000'000LL);
        t.update(2, -1'000'000'000);
        CHECK(t.query(0, 2) == 1'000'000'000);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 20; ++trial) {
        const int n = rand_int(1, 40);
        std::vector<long long> arr(n);
        for (auto& x : arr) x = rand_int(-1000, 1000);
        SegmentTree t(arr);
        bool ok = true;
        for (int op = 0; op < 500 && ok; ++op) {
            if (rand_int(0, 1) == 0) {
                int i = rand_int(0, n - 1);
                int v = rand_int(-1000, 1000);
                t.update(i, v);
                arr[i] = v;
            } else {
                int l = rand_int(0, n - 1);
                int r = rand_int(l, n - 1);
                long long want = 0;
                for (int k = l; k <= r; ++k) want += arr[k];
                ok = t.query(l, r) == want;
            }
        }
        CHECK(ok);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // n = 10^5 starting from all 1s; 10^5 calls = 25000 rounds of
    //   update(p, 3); query(p, n-1); query(0, n-1); query(0, p)   with p = 4j.
    // After round j, positions 0, 4, ..., 4j hold 3 and the rest hold 1, so the answers are closed-form.
    const int n = 100'000;
    SegmentTree t(std::vector<long long>(n, 1));
    bool ok = true;
    for (int j = 0; j < 25'000 && ok; ++j) {
        const long long p = 4LL * j;
        t.update(static_cast<int>(p), 3);
        ok = t.query(static_cast<int>(p), n - 1) == (n - p) + 2 &&
             t.query(0, n - 1) == n + 2 * (j + 1) &&
             t.query(0, static_cast<int>(p)) == (p + 1) + 2 * (j + 1);
    }
    CHECK(ok);
}
