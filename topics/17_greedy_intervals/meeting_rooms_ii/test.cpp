#include <meeting_rooms_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

using Intervals = std::vector<std::vector<int>>;

namespace {
// The maximum number of simultaneous meetings is reached at some start point; count the half-open
// meetings [s, e) containing each start.
int brute(const Intervals& v) {
    int best = 0;
    for (const auto& p : v) {
        int cnt = 0;
        for (const auto& q : v)
            if (q[0] <= p[0] && p[0] < q[1]) ++cnt;
        best = std::max(best, cnt);
    }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(minMeetingRooms({{0, 30}, {5, 10}, {15, 20}}) == 2);
    CHECK(minMeetingRooms({{7, 10}, {2, 4}}) == 1);
    CHECK(minMeetingRooms({{1, 5}, {2, 6}, {3, 7}}) == 3);
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(minMeetingRooms({}) == 0); }
    SUBCASE("single meeting") { CHECK(minMeetingRooms({{3, 8}}) == 1); }
    SUBCASE("touching meetings share a room") {
        CHECK(minMeetingRooms({{1, 2}, {2, 3}, {3, 4}}) == 1);
        CHECK(minMeetingRooms({{3, 4}, {1, 3}}) == 1);
    }
    SUBCASE("all overlapping needs n rooms") {
        CHECK(minMeetingRooms({{1, 10}, {2, 9}, {3, 8}, {4, 7}, {5, 6}}) == 5);
        CHECK(minMeetingRooms(Intervals(6, {2, 5})) == 6);
    }
    SUBCASE("a gap of one lets a room be reused") { CHECK(minMeetingRooms({{1, 2}, {3, 4}}) == 1); }
    SUBCASE("unsorted input") { CHECK(minMeetingRooms({{15, 20}, {0, 30}, {5, 10}}) == 2); }
    SUBCASE("end and start at the same time with another meeting running") {
        // At time 4: {1,4} ends, {4,8} starts, {2,6} continues -> 2 rooms, not 3.
        CHECK(minMeetingRooms({{1, 4}, {4, 8}, {2, 6}}) == 2);
    }
    SUBCASE("large coordinates") { CHECK(minMeetingRooms({{0, 1000000000}, {999999999, 1000000000}}) == 2); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const int n = rand_int(1, 10);
        Intervals in;
        for (int i = 0; i < n; ++i) {
            const int a = rand_int(0, 15);
            in.push_back({a, a + rand_int(1, 6)});
        }
        INFO("trial " << trial);
        CHECK(minMeetingRooms(in) == brute(in));
    }
}
