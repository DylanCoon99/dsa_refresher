#include <min_stack.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

TEST_CASE("examples") {
    MinStack s;
    s.push(-2);
    s.push(0);
    s.push(-3);
    CHECK(s.getMin() == -3);
    s.pop();
    CHECK(s.top() == 0);
    CHECK(s.getMin() == -2);

    MinStack t;
    t.push(5);
    CHECK(t.top() == 5);
    CHECK(t.getMin() == 5);
}

TEST_CASE("edge cases") {
    SUBCASE("duplicate minimums") {
        MinStack s;
        s.push(0);
        s.push(1);
        s.push(0);
        CHECK(s.getMin() == 0);
        s.pop();
        CHECK(s.getMin() == 0);
        s.pop();
        CHECK(s.getMin() == 0);
        CHECK(s.top() == 0);
    }
    SUBCASE("INT_MIN and INT_MAX") {
        MinStack s;
        s.push(INT_MAX);
        CHECK(s.getMin() == INT_MAX);
        s.push(INT_MIN);
        CHECK(s.getMin() == INT_MIN);
        s.push(INT_MAX);
        CHECK(s.getMin() == INT_MIN);
        s.pop();
        s.pop();
        CHECK(s.getMin() == INT_MAX);
        CHECK(s.top() == INT_MAX);
    }
    SUBCASE("minimum is restored after popping a smaller element") {
        MinStack s;
        s.push(3);
        s.push(5);
        s.push(1);
        s.push(4);
        CHECK(s.getMin() == 1);
        s.pop();
        s.pop();
        CHECK(s.getMin() == 3);
        CHECK(s.top() == 5);
    }
    SUBCASE("decreasing then increasing pushes") {
        MinStack s;
        for (int v : {9, 7, 5, 3}) s.push(v);
        for (int v : {4, 6, 8}) s.push(v);
        CHECK(s.getMin() == 3);
        for (int i = 0; i < 4; ++i) s.pop();
        CHECK(s.getMin() == 5);
    }
}

TEST_CASE("randomized vs brute force") {
    MinStack s;
    std::vector<int> ref;
    for (int op = 0; op < 100'000; ++op) {
        if (ref.empty() || rand_int(0, 1) == 0) {
            int v = rand_int(0, 20) == 0 ? (rand_int(0, 1) ? INT_MIN : INT_MAX) : rand_int(-50, 50);
            s.push(v);
            ref.push_back(v);
        } else {
            s.pop();
            ref.pop_back();
        }
        if (!ref.empty()) {
            REQUIRE(s.top() == ref.back());
            REQUIRE(s.getMin() == *std::min_element(ref.begin(), ref.end()));
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 pushes (the minimum, -7, goes in first), then 10^5 getMin calls. Scanning the stack
    // for each call costs 10^10 steps in total.
    const int n = 100'000;
    MinStack s;
    s.push(-7);
    for (int k = 1; k < n; ++k) s.push(k % 1000 + 1);
    long long wrong = 0;
    for (int k = 0; k < n; ++k) {
        if (s.getMin() != -7) ++wrong;
    }
    CHECK(wrong == 0);
    CHECK(s.top() == (n - 1) % 1000 + 1);
}
