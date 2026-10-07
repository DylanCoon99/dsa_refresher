#include <longest_substring_no_repeat.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <random>
#include <set>
#include <string>

namespace {
// Every substring, with a fresh set each time.
int brute(const std::string& s) {
    int best = 0;
    const int n = static_cast<int>(s.size());
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j) {
            std::set<char> seen(s.begin() + i, s.begin() + j + 1);
            if (static_cast<int>(seen.size()) == j - i + 1) best = std::max(best, j - i + 1);
        }
    return best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(lengthOfLongestSubstring("abcabcbb") == 3);
    CHECK(lengthOfLongestSubstring("bbbbb") == 1);
    CHECK(lengthOfLongestSubstring("pwwkew") == 3);
}

TEST_CASE("edge cases") {
    SUBCASE("empty string") { CHECK(lengthOfLongestSubstring("") == 0); }
    SUBCASE("a single space") { CHECK(lengthOfLongestSubstring(" ") == 1); }
    SUBCASE("single character") { CHECK(lengthOfLongestSubstring("a") == 1); }
    SUBCASE("all distinct") { CHECK(lengthOfLongestSubstring("abcdef") == 6); }
    SUBCASE("left pointer must never move backward") { CHECK(lengthOfLongestSubstring("abba") == 2); }
    SUBCASE("repeat just outside the window") { CHECK(lengthOfLongestSubstring("tmmzuxt") == 5); }
    SUBCASE("spaces and symbols") { CHECK(lengthOfLongestSubstring("a b a!~ ") == 5); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(rand_int(0, 30), 'a', rand_int(0, 1) ? 'e' : 'j');
        CAPTURE(s);
        CHECK(lengthOfLongestSubstring(s) == brute(s));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 5·10^4 random printable characters with all 95 printable characters planted in a shuffled run.
    // 95 is the largest possible answer, and nothing random can beat or tie it by accident.
    const int n = 50'000;
    std::mt19937 gen(4242);
    std::string s(n, ' ');
    for (char& c : s) c = static_cast<char>(32 + gen() % 95u);
    std::string run;
    for (int c = 32; c <= 126; ++c) run += static_cast<char>(c);
    std::shuffle(run.begin(), run.end(), gen);
    s.replace(20'000, run.size(), run);
    CHECK(lengthOfLongestSubstring(s) == 95);
}
