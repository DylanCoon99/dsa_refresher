#include <eval_rpn.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <cstdlib>
#include <string>
#include <vector>

namespace {
using Tokens = std::vector<std::string>;

// Builds a random valid expression tree in postfix order and evaluates it as it goes.
// Returns false if any intermediate value leaves the int range (caller retries).
bool gen(int depth, Tokens& out, long long& value) {
    if (depth == 0 || rand_int(0, 3) == 0) {
        int v = rand_int(-20, 20);
        out.push_back(std::to_string(v));
        value = v;
        return true;
    }
    long long a = 0, b = 0;
    if (!gen(depth - 1, out, a) || !gen(depth - 1, out, b)) return false;
    int op = rand_int(0, 3);
    if (op == 3 && b == 0) op = 0;
    switch (op) {
        case 0: value = a + b; out.push_back("+"); break;
        case 1: value = a - b; out.push_back("-"); break;
        case 2: value = a * b; out.push_back("*"); break;
        default: value = a / b; out.push_back("/"); break;  // C++ truncates toward zero
    }
    return std::llabs(value) <= 2'000'000'000LL;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(evalRPN({"2", "1", "+", "3", "*"}) == 9);
    CHECK(evalRPN({"4", "13", "5", "/", "+"}) == 6);
    CHECK(evalRPN({"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}) == 22);
}

TEST_CASE("edge cases") {
    SUBCASE("single number") { CHECK(evalRPN({"42"}) == 42); }
    SUBCASE("single negative number") { CHECK(evalRPN({"-11"}) == -11); }
    SUBCASE("negative number tokens are numbers, not operators") {
        CHECK(evalRPN({"-11", "3", "+"}) == -8);
        CHECK(evalRPN({"5", "-3", "*"}) == -15);
    }
    SUBCASE("operand order for minus") { CHECK(evalRPN({"3", "5", "-"}) == -2); }
    SUBCASE("operand order for divide") { CHECK(evalRPN({"20", "4", "/"}) == 5); }
    SUBCASE("division truncates toward zero") {
        CHECK(evalRPN({"6", "-132", "/"}) == 0);
        CHECK(evalRPN({"7", "-2", "/"}) == -3);
        CHECK(evalRPN({"-7", "2", "/"}) == -3);
        CHECK(evalRPN({"-7", "-2", "/"}) == 3);
    }
    SUBCASE("multi-digit and zero") {
        CHECK(evalRPN({"0", "300", "-"}) == -300);
        CHECK(evalRPN({"0", "5", "*"}) == 0);
    }
    SUBCASE("large intermediate values") {
        CHECK(evalRPN({"46341", "46340", "*"}) == 2147441940);
        CHECK(evalRPN({"2147483647", "-1", "*"}) == -2147483647);
    }
}

TEST_CASE("randomized vs brute force") {
    int made = 0;
    while (made < 400) {
        Tokens t;
        long long v = 0;
        if (!gen(rand_int(1, 5), t, v)) continue;
        ++made;
        CAPTURE(t);
        CHECK(evalRPN(t) == static_cast<int>(v));
    }
}
