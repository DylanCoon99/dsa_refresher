#include <valid_palindrome.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <cctype>
#include <string>

namespace {
bool brute(const std::string& s) {
    std::string t;
    for (unsigned char c : s) {
        if (std::isalnum(c)) t.push_back(static_cast<char>(std::tolower(c)));
    }
    std::string r(t.rbegin(), t.rend());
    return t == r;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(isPalindrome("A man, a plan, a canal: Panama") == true);
    CHECK(isPalindrome("race a car") == false);
    CHECK(isPalindrome(" ") == true);
}

TEST_CASE("edge cases") {
    SUBCASE("empty string") { CHECK(isPalindrome("") == true); }
    SUBCASE("only punctuation") { CHECK(isPalindrome(".,!?;") == true); }
    SUBCASE("single character") { CHECK(isPalindrome("a") == true); }
    SUBCASE("digit and letter must not match") { CHECK(isPalindrome("0P") == false); }
    SUBCASE("digits") { CHECK(isPalindrome("12321") == true); }
    SUBCASE("digits, not a palindrome") { CHECK(isPalindrome("12345") == false); }
    SUBCASE("case-insensitive") { CHECK(isPalindrome("Aa") == true); }
    SUBCASE("mixed punctuation") { CHECK(isPalindrome("Madam, I'm Adam!") == true); }
    SUBCASE("punctuation hides a mismatch") { CHECK(isPalindrome("ab,.;ba!c") == false); }
    SUBCASE("leading and trailing junk") { CHECK(isPalindrome("  -- a b a --  ") == true); }
}

TEST_CASE("randomized vs brute force") {
    const std::string alphabet = "abAB01 ,.:-";
    for (int trial = 0; trial < 400; ++trial) {
        const int n = rand_int(0, 12);
        std::string s;
        for (int i = 0; i < n; ++i) s.push_back(alphabet[static_cast<std::size_t>(rand_int(0, static_cast<int>(alphabet.size()) - 1))]);
        CHECK(isPalindrome(s) == brute(s));
    }
}
