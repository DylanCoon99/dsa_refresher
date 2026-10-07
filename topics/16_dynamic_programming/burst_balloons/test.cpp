#include <burst_balloons.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
// Try every bursting order (permutation of indices) and simulate it on a shrinking list.
int brute(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    int best = 0;
    do {
        std::vector<int> alive(nums);
        std::vector<int> ids(n);
        std::iota(ids.begin(), ids.end(), 0);
        int total = 0;
        for (int burst : order) {
            const int pos = static_cast<int>(std::find(ids.begin(), ids.end(), burst) - ids.begin());
            const int left = pos > 0 ? alive[pos - 1] : 1;
            const int right = pos + 1 < static_cast<int>(alive.size()) ? alive[pos + 1] : 1;
            total += left * alive[pos] * right;
            alive.erase(alive.begin() + pos);
            ids.erase(ids.begin() + pos);
        }
        best = std::max(best, total);
    } while (std::next_permutation(order.begin(), order.end()));
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(maxCoins({3, 1, 5, 8}) == 167);
    CHECK(maxCoins({1, 5}) == 10);
    CHECK(maxCoins({7}) == 7);
}

TEST_CASE("edge cases") {
    SUBCASE("a single balloon") {
        CHECK(maxCoins({7}) == 7);
        CHECK(maxCoins({0}) == 0);
    }
    SUBCASE("zeros") {
        CHECK(maxCoins({0, 0, 0}) == 0);
        CHECK(maxCoins({0, 5}) == 5);
        CHECK(maxCoins({5, 0, 5}) == 30);
    }
    SUBCASE("two balloons") { CHECK(maxCoins({2, 3}) == 9); }
    SUBCASE("all ones: every burst earns 1*1*1 = 1") {
        CHECK(maxCoins({1, 1, 1, 1}) == 4);
        CHECK(maxCoins(std::vector<int>(30, 1)) == 30);
    }
    SUBCASE("a large value in the middle") { CHECK(maxCoins({1, 9, 1}) == 27); }
}

TEST_CASE("randomized vs brute force over all orders (n <= 7)") {
    for (int trial = 0; trial < 150; ++trial) {
        std::vector<int> v = rand_vec(rand_int(1, 7), 0, 9);
        INFO(v);
        CHECK(maxCoins(v) == brute(v));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 100, then 298 zeros, then 100. Bursting a zero earns nothing and bursting an end 100 while a zero
    // still neighbours it also earns nothing, so burst the zeros first (0 coins), then the two 100s:
    // 1*100*100 = 10000 and 1*100*1 = 100.
    std::vector<int> v(300, 0);
    v.front() = 100;
    v.back() = 100;
    CHECK(maxCoins(v) == 10100);
}
