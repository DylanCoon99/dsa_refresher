#include <my_calendar_i.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <utility>
#include <vector>

TEST_CASE("examples") {
    MyCalendar a;
    CHECK(a.book(10, 20) == true);
    CHECK(a.book(15, 25) == false);
    CHECK(a.book(20, 30) == true);

    MyCalendar b;
    CHECK(b.book(5, 10) == true);
    CHECK(b.book(5, 10) == false);

    MyCalendar c;
    CHECK(c.book(0, 100) == true);
    CHECK(c.book(40, 50) == false);
}

TEST_CASE("edge cases") {
    SUBCASE("touching bookings succeed on both sides") {
        MyCalendar c;
        CHECK(c.book(10, 20) == true);
        CHECK(c.book(20, 30) == true);
        CHECK(c.book(0, 10) == true);
    }
    SUBCASE("nested bookings fail") {
        MyCalendar c;
        CHECK(c.book(10, 50) == true);
        CHECK(c.book(20, 30) == false);  // new inside old
        CHECK(c.book(10, 11) == false);  // shares the start
        CHECK(c.book(49, 50) == false);  // shares the end
    }
    SUBCASE("a new booking that contains an old one fails") {
        MyCalendar c;
        CHECK(c.book(20, 30) == true);
        CHECK(c.book(10, 40) == false);
    }
    SUBCASE("an identical booking fails") {
        MyCalendar c;
        CHECK(c.book(3, 4) == true);
        CHECK(c.book(3, 4) == false);
    }
    SUBCASE("partial overlaps fail on either side") {
        MyCalendar c;
        CHECK(c.book(10, 20) == true);
        CHECK(c.book(5, 11) == false);
        CHECK(c.book(19, 25) == false);
    }
    SUBCASE("a failed booking reserves nothing") {
        MyCalendar c;
        CHECK(c.book(10, 20) == true);
        CHECK(c.book(15, 25) == false);
        CHECK(c.book(20, 30) == true);
        CHECK(c.book(0, 10) == true);
    }
    SUBCASE("large coordinates") {
        MyCalendar c;
        CHECK(c.book(0, 1'000'000'000) == true);
        CHECK(c.book(999'999'999, 1'000'000'000) == false);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        MyCalendar cal;
        std::vector<std::pair<int, int>> stored;
        bool ok = true;
        for (int op = 0; op < 30 && ok; ++op) {
            int s = rand_int(0, 40);
            int e = rand_int(s + 1, 45);
            bool want = true;
            for (const auto& [a, b] : stored)
                if (s < b && a < e) want = false;
            if (want) stored.emplace_back(s, e);
            ok = cal.book(s, e) == want;
        }
        CHECK(ok);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 pairwise-disjoint bookings, slot k = [1000k, 1000k + len_k) with 1 <= len_k <= 1000,
    // made in shuffled order: every one must succeed. Then 1000 bookings of [1000k, 1000k + 1),
    // one inside each of 1000 slots, must all fail. A scan over all stored bookings is O(n^2).
    const int n = 100'000;
    std::vector<int> order(n), len(n);
    for (int k = 0; k < n; ++k) {
        order[k] = k;
        len[k] = rand_int(1, 1000);
    }
    std::shuffle(order.begin(), order.end(), rng());
    MyCalendar cal;
    bool allBooked = true;
    for (int idx = 0; idx < n && allBooked; ++idx) {
        int k = order[idx];
        allBooked = cal.book(1000 * k, 1000 * k + len[k]);
    }
    CHECK(allBooked);
    bool allRejected = true;
    for (int idx = 0; idx < 1000 && allRejected; ++idx) {
        int k = order[idx];
        allRejected = !cal.book(1000 * k, 1000 * k + 1);
    }
    CHECK(allRejected);
}
