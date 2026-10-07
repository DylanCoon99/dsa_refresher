#include <range_sum_mutable.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

TEST_CASE("examples") {
    NumArray a({1, 3, 5});
    CHECK(a.sumRange(0, 2) == 9);
    a.update(1, 2);
    CHECK(a.sumRange(0, 2) == 8);

    NumArray one({4});
    CHECK(one.sumRange(0, 0) == 4);
}

TEST_CASE("edge cases") {
    SUBCASE("update to the same value changes nothing") {
        NumArray a({2, 7, 1});
        a.update(1, 7);
        a.update(1, 7);
        CHECK(a.sumRange(0, 2) == 10);
        CHECK(a.sumRange(1, 1) == 7);
    }
    SUBCASE("update the first and last positions") {
        NumArray a({1, 2, 3, 4, 5});
        a.update(0, 10);
        a.update(4, -10);
        CHECK(a.sumRange(0, 4) == 9);
        CHECK(a.sumRange(0, 0) == 10);
        CHECK(a.sumRange(4, 4) == -10);
        CHECK(a.sumRange(1, 3) == 9);
    }
    SUBCASE("n = 1 with updates") {
        NumArray a({0});
        a.update(0, 5);
        CHECK(a.sumRange(0, 0) == 5);
        a.update(0, -5);
        CHECK(a.sumRange(0, 0) == -5);
    }
    SUBCASE("negatives") {
        NumArray a({-1, -2, -3});
        CHECK(a.sumRange(0, 2) == -6);
        a.update(1, 4);
        CHECK(a.sumRange(0, 2) == 0);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 20; ++trial) {
        const int n = rand_int(1, 40);
        std::vector<int> arr = rand_vec(n, -100, 100);
        NumArray a(arr);
        bool ok = true;
        for (int op = 0; op < 500 && ok; ++op) {
            if (rand_int(0, 1) == 0) {
                int i = rand_int(0, n - 1);
                int v = rand_int(-100, 100);
                a.update(i, v);
                arr[i] = v;
            } else {
                int l = rand_int(0, n - 1);
                int r = rand_int(l, n - 1);
                int want = 0;
                for (int k = l; k <= r; ++k) want += arr[k];
                ok = a.sumRange(l, r) == want;
            }
        }
        CHECK(ok);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // n = 10^5, all 1s; 10^5 alternating calls: round j (0..49999) does update(2j, 5), then sumRange(j, n-1).
    // Positions 0, 2, ..., 2j hold 5 after the update; those at index >= j number j - ceil(j/2) + 1,
    // so the answer is (n - j) + 4 * (j - (j+1)/2 + 1). Closed form, nothing brute-forced in the timed region.
    const int n = 100'000;
    NumArray a(std::vector<int>(n, 1));
    bool ok = true;
    for (int j = 0; j < 50'000 && ok; ++j) {
        a.update(2 * j, 5);
        ok = a.sumRange(j, n - 1) == (n - j) + 4 * (j - (j + 1) / 2 + 1);
    }
    CHECK(ok);
}
