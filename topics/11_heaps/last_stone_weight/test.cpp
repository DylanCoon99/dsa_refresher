#include <last_stone_weight.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
// Obviously-correct simulation: sort every round and smash the two largest.
int brute(std::vector<int> stones) {
    while (stones.size() > 1) {
        std::sort(stones.begin(), stones.end());
        int y = stones.back();
        stones.pop_back();
        int x = stones.back();
        stones.pop_back();
        if (y != x) stones.push_back(y - x);
    }
    return stones.empty() ? 0 : stones[0];
}
}  // namespace

TEST_CASE("examples") {
    CHECK(lastStoneWeight({2, 7, 4, 1, 8, 1}) == 1);
    CHECK(lastStoneWeight({5}) == 5);
    CHECK(lastStoneWeight({3, 3}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("single stone") { CHECK(lastStoneWeight({1000}) == 1000); }
    SUBCASE("two equal stones vanish") { CHECK(lastStoneWeight({7, 7}) == 0); }
    SUBCASE("two unequal stones") { CHECK(lastStoneWeight({9, 4}) == 5); }
    SUBCASE("everything cancels") { CHECK(lastStoneWeight({1, 1, 2, 2, 5, 5}) == 0); }
    SUBCASE("all equal, odd count") { CHECK(lastStoneWeight({4, 4, 4}) == 4); }
    SUBCASE("difference becomes the heaviest again") { CHECK(lastStoneWeight({10, 9, 1, 1}) == 1); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 500; ++trial) {
        std::vector<int> stones = rand_vec(rand_int(1, 30), 1, rand_int(1, 1000));
        CHECK(lastStoneWeight(stones) == brute(stones));
    }
}
