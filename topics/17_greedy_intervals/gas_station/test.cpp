#include <gas_station.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// All stations from which a full circle succeeds, by direct simulation (O(n^2)).
std::vector<int> valid_starts(const std::vector<int>& gas, const std::vector<int>& cost) {
    const int n = static_cast<int>(gas.size());
    std::vector<int> res;
    for (int s = 0; s < n; ++s) {
        long long tank = 0;
        bool ok = true;
        for (int k = 0; k < n && ok; ++k) {
            const int i = (s + k) % n;
            tank += gas[i];
            tank -= cost[i];
            if (tank < 0) ok = false;
        }
        if (ok) res.push_back(s);
    }
    return res;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(canCompleteCircuit({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}) == 3);
    CHECK(canCompleteCircuit({2, 3, 4}, {3, 4, 3}) == -1);
    CHECK(canCompleteCircuit({5}, {4}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("single station, enough gas") {
        CHECK(canCompleteCircuit({3}, {3}) == 0);
        CHECK(canCompleteCircuit({9}, {1}) == 0);
    }
    SUBCASE("single station, not enough gas") { CHECK(canCompleteCircuit({2}, {3}) == -1); }
    SUBCASE("total gas below total cost") {
        CHECK(canCompleteCircuit({1, 1, 1}, {1, 1, 2}) == -1);
        CHECK(canCompleteCircuit({0, 0}, {0, 1}) == -1);
    }
    SUBCASE("the start is the last index") {
        CHECK(canCompleteCircuit({0, 0, 5}, {2, 3, 0}) == 2);
        CHECK(canCompleteCircuit({1, 1, 1, 8}, {3, 3, 3, 1}) == 3);
    }
    SUBCASE("the start is the first index") { CHECK(canCompleteCircuit({6, 0, 0}, {1, 2, 3}) == 0); }
    SUBCASE("a rich station after a poor stretch") {
        // Starting at 0 or 1 runs dry; 2 collects 10 first.
        CHECK(canCompleteCircuit({1, 1, 10, 1}, {2, 2, 2, 2}) == 2);
    }
    SUBCASE("arriving with exactly zero fuel is allowed") { CHECK(canCompleteCircuit({2, 0}, {1, 1}) == 0); }
}

TEST_CASE("randomized vs brute force") {
    int unique_cases = 0;
    for (int trial = 0; trial < 3000 && unique_cases < 300; ++trial) {
        const int n = rand_int(1, 8);
        const std::vector<int> gas = rand_vec(n, 0, 5);
        const std::vector<int> cost = rand_vec(n, 0, 5);
        const std::vector<int> starts = valid_starts(gas, cost);
        if (starts.size() > 1) continue;  // the contract promises at most one valid start
        ++unique_cases;
        INFO("trial " << trial);
        CHECK(canCompleteCircuit(gas, cost) == (starts.empty() ? -1 : starts[0]));
    }
    CHECK(unique_cases >= 200);
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Station n-1 gives 1 gas and costs 0; station n-2 gives 0 and costs 1; every other station gives
    // 1 and costs 1 (net 0). Starting at n-1 the tank is 1 through the net-0 stations and ends at 0 after
    // station n-2, so it works. Any start s < n-2 coasts through net-0 stations with an empty tank
    // and runs dry at station n-2; starting at n-2 fails at once. So n-1 is the only valid start.
    const int n = 100000;
    std::vector<int> gas(n, 1), cost(n, 1);
    gas[n - 1] = 1;
    cost[n - 1] = 0;
    gas[n - 2] = 0;
    cost[n - 2] = 1;
    CHECK(canCompleteCircuit(gas, cost) == n - 1);
}
