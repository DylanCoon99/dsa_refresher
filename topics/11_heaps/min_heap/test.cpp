#include <min_heap.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <functional>
#include <queue>
#include <stdexcept>
#include <vector>

namespace {
// Pops everything and returns the values in pop order.
std::vector<int> drain(MinHeap& h) {
    std::vector<int> out;
    while (!h.empty()) out.push_back(h.pop());
    return out;
}
}  // namespace

TEST_CASE("examples") {
    MinHeap h;
    for (int v : {5, 2, 8, 1}) h.push(v);
    CHECK(h.top() == 1);
    CHECK(h.size() == 4);
    CHECK(drain(h) == std::vector<int>{1, 2, 5, 8});

    MinHeap g(std::vector<int>{9, 4, 7, 1});
    CHECK(g.size() == 4);
    CHECK(drain(g) == std::vector<int>{1, 4, 7, 9});
}

TEST_CASE("edge cases") {
    SUBCASE("empty heap throws") {
        MinHeap h;
        CHECK(h.empty());
        CHECK(h.size() == 0);
        CHECK_THROWS_AS(h.pop(), std::out_of_range);
        CHECK_THROWS_AS(h.top(), std::out_of_range);
    }
    SUBCASE("empty again after popping everything") {
        MinHeap h;
        h.push(3);
        h.push(1);
        CHECK(h.pop() == 1);
        CHECK(h.pop() == 3);
        CHECK(h.empty());
        CHECK_THROWS_AS(h.pop(), std::out_of_range);
        CHECK_THROWS_AS(h.top(), std::out_of_range);
        h.push(7);  // still usable afterwards
        CHECK(h.top() == 7);
    }
    SUBCASE("empty vector constructor") {
        MinHeap h{std::vector<int>{}};
        CHECK(h.empty());
        CHECK_THROWS_AS(h.top(), std::out_of_range);
    }
    SUBCASE("single element") {
        MinHeap h(std::vector<int>{42});
        CHECK(h.top() == 42);
        CHECK(h.pop() == 42);
        CHECK(h.empty());
    }
    SUBCASE("duplicates") {
        MinHeap h;
        for (int v : {2, 2, 1, 1, 2, 1}) h.push(v);
        CHECK(h.size() == 6);
        CHECK(drain(h) == std::vector<int>{1, 1, 1, 2, 2, 2});
    }
    SUBCASE("all equal via constructor") {
        MinHeap h(std::vector<int>(7, 5));
        CHECK(h.size() == 7);
        CHECK(drain(h) == std::vector<int>(7, 5));
    }
    SUBCASE("negatives") {
        MinHeap h;
        for (int v : {-1, -5, 0, -3, 4, -5}) h.push(v);
        CHECK(h.top() == -5);
        CHECK(drain(h) == std::vector<int>{-5, -5, -3, -1, 0, 4});
    }
    SUBCASE("INT_MIN and INT_MAX") {
        MinHeap h(std::vector<int>{INT_MAX, 0, INT_MIN, INT_MAX, INT_MIN});
        CHECK(drain(h) == std::vector<int>{INT_MIN, INT_MIN, 0, INT_MAX, INT_MAX});
    }
    SUBCASE("sorted and reverse-sorted input via constructor") {
        MinHeap up(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        MinHeap down(std::vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1});
        std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        CHECK(drain(up) == expected);
        CHECK(drain(down) == expected);
    }
    SUBCASE("constructor then push") {
        MinHeap h(std::vector<int>{8, 6, 7});
        h.push(1);
        h.push(9);
        CHECK(h.size() == 5);
        CHECK(drain(h) == std::vector<int>{1, 6, 7, 8, 9});
    }
    SUBCASE("top does not remove") {
        MinHeap h;
        h.push(4);
        h.push(2);
        CHECK(h.top() == 2);
        CHECK(h.top() == 2);
        CHECK(h.size() == 2);
    }
}

TEST_CASE("randomized vs brute force") {
    SUBCASE("heap-sort 1000 random vectors (push)") {
        for (int trial = 0; trial < 1000; ++trial) {
            std::vector<int> v = rand_vec(rand_int(0, 40), -50, 50);
            MinHeap h;
            for (int x : v) h.push(x);
            REQUIRE(h.size() == v.size());
            std::sort(v.begin(), v.end());
            CHECK(drain(h) == v);
        }
    }
    SUBCASE("heap-sort 1000 random vectors (constructor)") {
        for (int trial = 0; trial < 1000; ++trial) {
            std::vector<int> v = rand_vec(rand_int(0, 40), -50, 50);
            MinHeap h(v);
            REQUIRE(h.size() == v.size());
            std::sort(v.begin(), v.end());
            CHECK(drain(h) == v);
        }
    }
    SUBCASE("10^5 random push/pop ops vs std::priority_queue") {
        MinHeap h;
        std::priority_queue<int, std::vector<int>, std::greater<>> model;
        for (int op = 0; op < 100'000; ++op) {
            if (model.empty() || rand_int(0, 2) != 0) {
                int v = rand_int(-1000, 1000);
                h.push(v);
                model.push(v);
            } else {
                REQUIRE(h.top() == model.top());
                REQUIRE(h.pop() == model.top());
                model.pop();
            }
            REQUIRE(h.size() == model.size());
        }
        CHECK(h.empty() == model.empty());
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 4*10^5 pseudo-random values pushed then popped. Inserting into a sorted vector costs
    // O(n) per push (~4*10^10 element moves in total). Pushing is also the only path used here,
    // so this test does not check that the vector constructor is linear.
    const std::size_t n = 400'000;
    MinHeap h;
    unsigned long long x = 12345;
    for (std::size_t i = 0; i < n; ++i) {
        x = x * 6364136223846793005ULL + 1442695040888963407ULL;
        h.push(static_cast<int>(x >> 33));
    }
    REQUIRE(h.size() == n);
    int prev = INT_MIN;
    std::size_t out_of_order = 0, popped = 0;
    while (!h.empty()) {
        int v = h.pop();
        if (v < prev) ++out_of_order;
        prev = v;
        ++popped;
    }
    CHECK(popped == n);
    CHECK(out_of_order == 0);
}
