#include <median_finder.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

TEST_CASE("examples") {
    MedianFinder a;
    a.addNum(1);
    a.addNum(2);
    CHECK(a.findMedian() == 1.5);
    a.addNum(3);
    CHECK(a.findMedian() == 2.0);

    MedianFinder b;
    b.addNum(5);
    CHECK(b.findMedian() == 5.0);
    b.addNum(-1);
    CHECK(b.findMedian() == 2.0);
}

TEST_CASE("edge cases") {
    SUBCASE("odd and even counts") {
        MedianFinder m;
        m.addNum(10);
        CHECK(m.findMedian() == 10.0);
        m.addNum(20);
        CHECK(m.findMedian() == 15.0);
        m.addNum(30);
        CHECK(m.findMedian() == 20.0);
        m.addNum(40);
        CHECK(m.findMedian() == 25.0);
        m.addNum(50);
        CHECK(m.findMedian() == 30.0);
    }
    SUBCASE("descending input") {
        MedianFinder m;
        for (int v : {9, 7, 5, 3, 1}) m.addNum(v);
        CHECK(m.findMedian() == 5.0);
        m.addNum(0);
        CHECK(m.findMedian() == 4.0);
    }
    SUBCASE("negatives") {
        MedianFinder m;
        m.addNum(-4);
        CHECK(m.findMedian() == -4.0);
        m.addNum(-3);
        CHECK(m.findMedian() == -3.5);
        m.addNum(-10);
        CHECK(m.findMedian() == -4.0);
    }
    SUBCASE("duplicates") {
        MedianFinder m;
        for (int i = 0; i < 5; ++i) m.addNum(7);
        CHECK(m.findMedian() == 7.0);
        m.addNum(8);
        CHECK(m.findMedian() == 7.0);
    }
    SUBCASE("INT_MAX + INT_MAX averages without int overflow") {
        MedianFinder m;
        m.addNum(INT_MAX);
        m.addNum(INT_MAX);
        CHECK(m.findMedian() == 2147483647.0);
    }
    SUBCASE("INT_MIN + INT_MIN and INT_MIN + INT_MAX") {
        MedianFinder m;
        m.addNum(INT_MIN);
        m.addNum(INT_MIN);
        CHECK(m.findMedian() == -2147483648.0);
        MedianFinder n;
        n.addNum(INT_MIN);
        n.addNum(INT_MAX);
        CHECK(n.findMedian() == -0.5);
    }
    SUBCASE("repeated queries do not change the answer") {
        MedianFinder m;
        m.addNum(1);
        m.addNum(4);
        CHECK(m.findMedian() == 2.5);
        CHECK(m.findMedian() == 2.5);
    }
}

TEST_CASE("randomized vs brute force") {
    // Model: a sorted vector with ordered insertion.
    std::vector<int> model;
    MedianFinder m;
    for (int op = 0; op < 10'000; ++op) {
        if (model.empty() || rand_int(0, 2) != 0) {
            int v = rand_int(-1000, 1000);
            m.addNum(v);
            model.insert(std::upper_bound(model.begin(), model.end(), v), v);
        }
        if (!model.empty() && rand_int(0, 1) == 0) {
            std::size_t n = model.size();
            double expected = n % 2 == 1
                                  ? static_cast<double>(model[n / 2])
                                  : (static_cast<double>(model[n / 2 - 1]) + static_cast<double>(model[n / 2])) / 2.0;
            REQUIRE(m.findMedian() == expected);
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 adds, each followed by a query. Values are added from the outside in: 1, N, 2, N-1, ...
    // so the median is known analytically. After 2m adds the collection is {1..m} + {N-m+1..N}
    // and the median is (N+1)/2; after 2m+1 adds the median is m+1. Sorting on each query is
    // O(n log n) per call; inserting into a sorted vector is not designed to be rejected.
    const int N = 100'000;
    MedianFinder mf;
    int wrong = 0;
    int lo = 1, hi = N;
    for (int i = 1; i <= N; ++i) {
        mf.addNum(i % 2 == 1 ? lo++ : hi--);
        double expected = i % 2 == 0 ? (N + 1) / 2.0 : static_cast<double>((i + 1) / 2);
        if (mf.findMedian() != expected) ++wrong;
    }
    CHECK(wrong == 0);
}
