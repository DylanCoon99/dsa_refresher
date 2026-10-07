#include <reconstruct_itinerary.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <string>
#include <vector>

namespace {
using Tickets = std::vector<std::vector<std::string>>;
using Route = std::vector<std::string>;

// Brute force: depth-first search that tries the unused tickets leaving the current airport in increasing
// order of destination, backtracking when stuck. The first complete route found is the smallest one.
bool search(const Tickets& t, std::vector<char>& used, const std::string& at, std::size_t count, Route& route) {
    if (count == t.size()) return true;
    std::vector<std::size_t> options;
    for (std::size_t i = 0; i < t.size(); ++i)
        if (!used[i] && t[i][0] == at) options.push_back(i);
    std::sort(options.begin(), options.end(), [&](std::size_t a, std::size_t b) { return t[a][1] < t[b][1]; });
    for (std::size_t i : options) {
        used[i] = 1;
        route.push_back(t[i][1]);
        if (search(t, used, t[i][1], count + 1, route)) return true;
        route.pop_back();
        used[i] = 0;
    }
    return false;
}

Route bruteForce(const Tickets& t) {
    std::vector<char> used(t.size(), 0);
    Route route{"JFK"};
    REQUIRE(search(t, used, "JFK", 0, route));
    return route;
}
}  // namespace

TEST_CASE("examples") {
    // JFK has two tickets out; ATL has two. The smallest route takes ATL first, then comes back through JFK.
    CHECK(findItinerary({{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}}) ==
          Route{"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"});
    // A simple chain.
    CHECK(findItinerary({{"JFK", "AAA"}, {"AAA", "BBB"}}) == Route{"JFK", "AAA", "BBB"});
}

TEST_CASE("edge cases") {
    SUBCASE("a single ticket") {
        CHECK(findItinerary({{"JFK", "LAX"}}) == Route{"JFK", "LAX"});
    }
    SUBCASE("dead-end trap: the alphabetically first move strands the other tickets") {
        // Going to KUL first would end the trip with NRT -> JFK unused.
        CHECK(findItinerary({{"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"}}) == Route{"JFK", "NRT", "JFK", "KUL"});
    }
    SUBCASE("duplicate tickets are separate tickets") {
        CHECK(findItinerary({{"JFK", "AAA"}, {"JFK", "AAA"}, {"AAA", "JFK"}}) == Route{"JFK", "AAA", "JFK", "AAA"});
    }
    SUBCASE("a ticket from an airport to itself") {
        CHECK(findItinerary({{"JFK", "JFK"}, {"JFK", "AAA"}}) == Route{"JFK", "JFK", "AAA"});
    }
    SUBCASE("a loop back to the start is flown before the smaller ending") {
        CHECK(findItinerary({{"JFK", "BBB"}, {"BBB", "JFK"}, {"JFK", "AAA"}}) == Route{"JFK", "BBB", "JFK", "AAA"});
    }
    SUBCASE("ticket order in the input does not matter") {
        Tickets t = {{"JFK", "NRT"}, {"NRT", "JFK"}, {"JFK", "KUL"}};
        Tickets r = {{"JFK", "KUL"}, {"NRT", "JFK"}, {"JFK", "NRT"}};
        CHECK(findItinerary(t) == Route{"JFK", "NRT", "JFK", "KUL"});
        CHECK(findItinerary(r) == Route{"JFK", "NRT", "JFK", "KUL"});
    }
}

TEST_CASE("randomized vs brute force") {
    const std::vector<std::string> names = {"JFK", "AAA", "BBB", "CCC", "DDD"};
    for (int trial = 0; trial < 400; ++trial) {
        // A random walk from JFK guarantees that at least one valid itinerary exists.
        int len = rand_int(1, 8);
        Tickets t;
        std::string at = "JFK";
        for (int i = 0; i < len; ++i) {
            std::string next = names[rand_int(0, static_cast<int>(names.size()) - 1)];
            t.push_back({at, next});
            at = next;
        }
        std::shuffle(t.begin(), t.end(), rng());
        Route expected = bruteForce(t);
        INFO("trial " << trial << ", tickets = " << t.size());
        CHECK(findItinerary(t) == expected);
    }
}
