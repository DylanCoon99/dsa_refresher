#include <fenwick_tree.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

TEST_CASE("examples") {
    FenwickTree f(5);
    f.add(0, 3);
    f.add(2, 4);
    f.add(4, -1);
    CHECK(f.prefixSum(2) == 7);
    CHECK(f.prefixSum(4) == 6);
    CHECK(f.rangeSum(1, 3) == 4);

    FenwickTree one(1);
    one.add(0, 9);
    CHECK(one.prefixSum(0) == 9);
    CHECK(one.prefixSum(-1) == 0);

    FenwickTree zeros(3);
    CHECK(zeros.rangeSum(0, 2) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 1") {
        FenwickTree f(1);
        f.add(0, 5);
        f.add(0, 7);
        CHECK(f.prefixSum(0) == 12);
        CHECK(f.rangeSum(0, 0) == 12);
        CHECK(f.prefixSum(-1) == 0);
    }
    SUBCASE("rangeSum over the whole array") {
        const int n = 10;
        FenwickTree f(n);
        long long total = 0;
        for (int i = 0; i < n; ++i) {
            f.add(i, i + 1);
            total += i + 1;
        }
        CHECK(total == 55);
        CHECK(f.rangeSum(0, n - 1) == 55);
        CHECK(f.prefixSum(n - 1) == 55);
    }
    SUBCASE("negative deltas") {
        FenwickTree f(6);
        f.add(1, -4);
        f.add(3, 10);
        f.add(3, -15);
        f.add(5, -1);
        CHECK(f.prefixSum(0) == 0);
        CHECK(f.prefixSum(1) == -4);
        CHECK(f.prefixSum(3) == -9);
        CHECK(f.rangeSum(2, 5) == -6);
        CHECK(f.rangeSum(0, 5) == -10);
    }
    SUBCASE("deltas near the limit accumulate in 64 bits") {
        FenwickTree f(4);
        for (int i = 0; i < 4; ++i) f.add(i, 1'000'000'000);
        f.add(0, 1'000'000'000);
        CHECK(f.prefixSum(3) == 5'000'000'000LL);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 20; ++trial) {
        const int n = rand_int(1, 60);
        FenwickTree f(n);
        std::vector<long long> arr(n, 0);
        bool ok = true;
        for (int op = 0; op < 500 && ok; ++op) {
            if (rand_int(0, 1) == 0) {
                int i = rand_int(0, n - 1);
                int d = rand_int(-1000, 1000);
                f.add(i, d);
                arr[i] += d;
            } else {
                int l = rand_int(0, n - 1);
                int r = rand_int(l, n - 1);
                long long want = 0;
                for (int k = l; k <= r; ++k) want += arr[k];
                long long wantPrefix = 0;
                for (int k = 0; k <= r; ++k) wantPrefix += arr[k];
                ok = f.rangeSum(l, r) == want && f.prefixSum(r) == wantPrefix;
            }
        }
        CHECK(ok);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // n = 10^6, 10^6 calls. Round k (k = 0..249999) does
    //   add(2k, k+1); add(2k+1, -1); prefixSum(2k+1); rangeSum(2k, 2k+1).
    // After round k the prefix over 0..2k+1 is (k+1)(k+2)/2 - (k+1) and the last pair sums to k.
    // Expected values are closed-form, so no brute force runs inside the timed region.
    const int n = 1'000'000;
    const int rounds = 250'000;
    FenwickTree f(n);
    bool ok = true;
    for (int k = 0; k < rounds && ok; ++k) {
        const long long K = k;
        f.add(2 * k, K + 1);
        f.add(2 * k + 1, -1);
        ok = f.prefixSum(2 * k + 1) == (K + 1) * (K + 2) / 2 - (K + 1) &&
             f.rangeSum(2 * k, 2 * k + 1) == K;
    }
    CHECK(ok);
    const long long R = rounds;
    CHECK(f.rangeSum(0, n - 1) == R * (R + 1) / 2 - R);
}
