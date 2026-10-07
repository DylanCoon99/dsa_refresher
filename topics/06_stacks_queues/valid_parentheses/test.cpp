#include <valid_parentheses.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <string>

namespace {
bool brute(std::string s) {
    for (bool changed = true; changed;) {
        changed = false;
        for (const char* pair : {"()", "[]", "{}"}) {
            std::size_t p = s.find(pair);
            if (p != std::string::npos) {
                s.erase(p, 2);
                changed = true;
            }
        }
    }
    return s.empty();
}
}  // namespace

TEST_CASE("examples") {
    CHECK(isValid("()[]{}") == true);
    CHECK(isValid("([)]") == false);
    CHECK(isValid("((") == false);
    CHECK(isValid("{[]}") == true);
}

TEST_CASE("edge cases") {
    SUBCASE("empty string") { CHECK(isValid("") == true); }
    SUBCASE("lone closing bracket") { CHECK(isValid("]") == false); }
    SUBCASE("lone opening bracket") { CHECK(isValid("(") == false); }
    SUBCASE("closing before opening") { CHECK(isValid(")(") == false); }
    SUBCASE("extra closer at the end") { CHECK(isValid("()]") == false); }
    SUBCASE("mismatched types") { CHECK(isValid("(]") == false); }
    SUBCASE("nested and sequential") { CHECK(isValid("{[()()]}[]") == true); }
    SUBCASE("deep nesting") {
        std::string s(10'000, '(');
        s += std::string(10'000, ')');
        CHECK(isValid(s) == true);
        s.back() = ']';
        CHECK(isValid(s) == false);
        CHECK(isValid(std::string(10'000, '[')) == false);
    }
}

TEST_CASE("randomized vs brute force") {
    const std::string alphabet = "()[]{}";
    for (int trial = 0; trial < 500; ++trial) {
        std::string s;
        int len = rand_int(0, 12);
        for (int i = 0; i < len; ++i) s += alphabet[rand_int(0, 5)];
        CAPTURE(s);
        CHECK(isValid(s) == brute(s));
    }
    // Random strings are rarely balanced, so also build balanced ones and damage one character.
    for (int trial = 0; trial < 300; ++trial) {
        std::string s;
        std::string open;
        int len = rand_int(0, 8);
        for (int i = 0; i < len; ++i) {
            if (!open.empty() && rand_int(0, 1)) {
                char o = open.back();
                open.pop_back();
                s += (o == '(' ? ')' : o == '[' ? ']' : '}');
            } else {
                char o = "([{"[rand_int(0, 2)];
                open += o;
                s += o;
            }
        }
        while (!open.empty()) {
            char o = open.back();
            open.pop_back();
            s += (o == '(' ? ')' : o == '[' ? ']' : '}');
        }
        CAPTURE(s);
        CHECK(isValid(s) == true);
        if (!s.empty()) {
            s[rand_int(0, static_cast<int>(s.size()) - 1)] = alphabet[rand_int(0, 5)];
            CAPTURE(s);
            CHECK(isValid(s) == brute(s));
        }
    }
}
