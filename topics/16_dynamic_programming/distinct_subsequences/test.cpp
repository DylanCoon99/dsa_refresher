#include <distinct_subsequences.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <string>

namespace {
// Cache-free recursion over (i, j): either skip s[i], or (if it matches t[j]) use it. Exponential, tiny inputs only.
int brute(const std::string& s, const std::string& t, std::size_t i, std::size_t j) {
    if (j == t.size()) return 1;
    if (i == s.size()) return 0;
    int r = brute(s, t, i + 1, j);
    if (s[i] == t[j]) r += brute(s, t, i + 1, j + 1);
    return r;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(numDistinct("rabbbit", "rabbit") == 3);
    CHECK(numDistinct("babgbag", "bag") == 5);
    CHECK(numDistinct("abc", "") == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("t empty") {
        CHECK(numDistinct("", "") == 1);
        CHECK(numDistinct("abc", "") == 1);
    }
    SUBCASE("t longer than s") {
        CHECK(numDistinct("ab", "abc") == 0);
        CHECK(numDistinct("", "a") == 0);
    }
    SUBCASE("identical strings") { CHECK(numDistinct("abc", "abc") == 1); }
    SUBCASE("character absent from s") { CHECK(numDistinct("aaaa", "b") == 0); }
    SUBCASE("order matters") { CHECK(numDistinct("ba", "ab") == 0); }
    SUBCASE("all the same letter is a binomial coefficient") {
        CHECK(numDistinct("aaaaa", "aa") == 10);
        CHECK(numDistinct(std::string(30, 'a'), std::string(15, 'a')) == 155117520);  // C(30, 15)
    }
    SUBCASE("s = a x 1000, t = a") { CHECK(numDistinct(std::string(1000, 'a'), "a") == 1000); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        const std::string s = rand_string(rand_int(0, 12), 'a', 'b');
        const std::string t = rand_string(rand_int(0, 5), 'a', 'b');
        INFO("s=" << s << " t=" << t);
        CHECK(numDistinct(s, t) == brute(s, t, 0, 0));
    }
}

TEST_CASE("overflow trap: intermediate counts exceed long long" * doctest::timeout(2.0)) {
    // t's last character 'c' never occurs in s, so the answer is 0, but the counts for the "a" prefix of t
    // grow like C(500, 250) (about 1e149): a signed table overflows (UBSan reports a crash), and plain
    // recursion would explore that many paths.
    CHECK(numDistinct(std::string(500, 'a') + "b", std::string(250, 'a') + "c") == 0);
}
