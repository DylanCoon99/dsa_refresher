#include <corporate_flight_bookings.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
using Bookings = std::vector<std::vector<int>>;

// Seat by seat, flight by flight.
std::vector<int> brute(const Bookings& bookings, int n) {
    std::vector<int> answer(n, 0);
    for (const auto& b : bookings)
        for (int f = b[0]; f <= b[1]; ++f) answer[f - 1] += b[2];
    return answer;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(corpFlightBookings({{1, 2, 10}, {2, 3, 20}, {2, 5, 25}}, 5) == std::vector<int>{10, 55, 45, 25, 25});
    CHECK(corpFlightBookings({{1, 2, 10}, {2, 2, 15}}, 2) == std::vector<int>{10, 25});
    CHECK(corpFlightBookings({{1, 1, 4}}, 3) == std::vector<int>{4, 0, 0});
}

TEST_CASE("edge cases") {
    SUBCASE("a single booking covering all flights") {
        CHECK(corpFlightBookings({{1, 4, 7}}, 4) == std::vector<int>{7, 7, 7, 7});
    }
    SUBCASE("overlapping bookings") {
        CHECK(corpFlightBookings({{1, 3, 5}, {2, 4, 6}, {3, 5, 7}}, 5) == std::vector<int>{5, 11, 18, 13, 7});
    }
    SUBCASE("identical bookings stack") {
        CHECK(corpFlightBookings({{2, 3, 4}, {2, 3, 4}, {2, 3, 4}}, 4) == std::vector<int>{0, 12, 12, 0});
    }
    SUBCASE("booking at the last flight") {
        CHECK(corpFlightBookings({{5, 5, 9}}, 5) == std::vector<int>{0, 0, 0, 0, 9});
        CHECK(corpFlightBookings({{3, 5, 2}}, 5) == std::vector<int>{0, 0, 2, 2, 2});
    }
    SUBCASE("booking at the first flight only") {
        CHECK(corpFlightBookings({{1, 1, 3}}, 4) == std::vector<int>{3, 0, 0, 0});
    }
    SUBCASE("a single flight") {
        CHECK(corpFlightBookings({{1, 1, 8}, {1, 1, 2}}, 1) == std::vector<int>{10});
    }
    SUBCASE("no bookings") {
        CHECK(corpFlightBookings({}, 3) == std::vector<int>{0, 0, 0});
    }
    SUBCASE("adjacent, non-overlapping bookings") {
        CHECK(corpFlightBookings({{1, 2, 1}, {3, 4, 2}}, 4) == std::vector<int>{1, 1, 2, 2});
    }
    SUBCASE("bookings given out of order") {
        CHECK(corpFlightBookings({{4, 4, 1}, {1, 4, 2}, {2, 3, 5}}, 4) == std::vector<int>{2, 7, 7, 3});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 15);
        const int m = rand_int(0, 12);
        Bookings bookings;
        for (int i = 0; i < m; ++i) {
            const int first = rand_int(1, n), last = rand_int(first, n);
            bookings.push_back({first, last, rand_int(1, 10'000)});
        }
        CHECK(corpFlightBookings(bookings, n) == brute(bookings, n));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Every booking covers all flights, so seat-by-seat filling does 10^5 * 10^5 = 10^10 additions.
    // Each flight ends up with the total of all seats, which is known in closed form.
    const int n = 100'000;
    Bookings bookings;
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        const int seats = 1 + i % 10;
        bookings.push_back({1, n, seats});
        total += seats;
    }
    std::vector<int> got = corpFlightBookings(bookings, n);
    REQUIRE(got.size() == static_cast<std::size_t>(n));
    CHECK(total == 550'000);
    long long wrong = 0;
    for (int v : got)
        if (v != total) ++wrong;
    CHECK(wrong == 0);
}
