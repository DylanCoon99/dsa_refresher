#include <queue_two_stacks.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <climits>
#include <queue>
#include <stdexcept>

TEST_CASE("examples") {
    TwoStackQueue q;
    q.push(1);
    q.push(2);
    CHECK(q.peek() == 1);
    CHECK(q.size() == 2);

    TwoStackQueue r;
    r.push(1);
    r.push(2);
    CHECK(r.pop() == 1);
    r.push(3);
    CHECK(r.pop() == 2);
    CHECK(r.pop() == 3);
    CHECK(r.empty());
}

TEST_CASE("edge cases") {
    SUBCASE("empty queue throws") {
        TwoStackQueue q;
        CHECK(q.empty());
        CHECK(q.size() == 0);
        CHECK_THROWS_AS(q.pop(), std::out_of_range);
        CHECK_THROWS_AS(q.peek(), std::out_of_range);
    }
    SUBCASE("throws again after being drained") {
        TwoStackQueue q;
        q.push(7);
        CHECK(q.pop() == 7);
        CHECK_THROWS_AS(q.pop(), std::out_of_range);
        CHECK_THROWS_AS(q.peek(), std::out_of_range);
        CHECK(q.empty());
    }
    SUBCASE("peek does not remove") {
        TwoStackQueue q;
        q.push(5);
        q.push(6);
        CHECK(q.peek() == 5);
        CHECK(q.peek() == 5);
        CHECK(q.size() == 2);
        CHECK(q.pop() == 5);
        CHECK(q.peek() == 6);
    }
    SUBCASE("interleaved pushes and pops keep FIFO order") {
        TwoStackQueue q;
        q.push(1);
        q.push(2);
        q.push(3);
        CHECK(q.pop() == 1);
        q.push(4);
        q.push(5);
        CHECK(q.pop() == 2);
        CHECK(q.pop() == 3);
        q.push(6);
        CHECK(q.size() == 3);
        CHECK(q.pop() == 4);
        CHECK(q.pop() == 5);
        CHECK(q.pop() == 6);
        CHECK(q.empty());
    }
    SUBCASE("extreme values and duplicates") {
        TwoStackQueue q;
        q.push(INT_MIN);
        q.push(INT_MAX);
        q.push(INT_MIN);
        CHECK(q.pop() == INT_MIN);
        CHECK(q.pop() == INT_MAX);
        CHECK(q.pop() == INT_MIN);
    }
}

TEST_CASE("randomized vs std::queue") {
    TwoStackQueue q;
    std::queue<int> ref;
    for (int op = 0; op < 100'000; ++op) {
        int kind = rand_int(0, 9);
        if (kind < 5) {
            int x = rand_int(-1000, 1000);
            q.push(x);
            ref.push(x);
        } else if (kind < 8) {
            if (ref.empty()) {
                CHECK_THROWS_AS(q.pop(), std::out_of_range);
            } else {
                int want = ref.front();
                ref.pop();
                REQUIRE(q.pop() == want);
            }
        } else {
            if (ref.empty()) {
                CHECK_THROWS_AS(q.peek(), std::out_of_range);
            } else {
                REQUIRE(q.peek() == ref.front());
            }
        }
        REQUIRE(q.size() == ref.size());
        REQUIRE(q.empty() == ref.empty());
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^6 operations in total: 4·10^5 pushes build up a long queue, then 3·10^5 push/pop pairs
    // run against it. Moving every element between the stacks on each operation costs
    // ~4·10^5 per op, about 4·10^11 in all. Values are 1-based so a stub's 0 never matches.
    const int base = 400'000, pairs = 300'000;
    TwoStackQueue q;
    for (int k = 1; k <= base; ++k) q.push(k);
    long long mismatches = 0;
    for (int k = 0; k < pairs; ++k) {
        q.push(base + 1 + k);
        if (q.pop() != k + 1) ++mismatches;
    }
    CHECK(mismatches == 0);
    CHECK(q.size() == static_cast<std::size_t>(base));
    CHECK(q.peek() == pairs + 1);
}
