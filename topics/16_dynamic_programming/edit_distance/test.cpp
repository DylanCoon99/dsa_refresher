#include <edit_distance.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <algorithm>
#include <string>

namespace {
// Cache-free recursion over the last characters. Exponential, fine for strings of length <= 6.
int brute(const std::string& a, const std::string& b, std::size_t i, std::size_t j) {
    if (i == 0) return static_cast<int>(j);
    if (j == 0) return static_cast<int>(i);
    if (a[i - 1] == b[j - 1]) return brute(a, b, i - 1, j - 1);
    return 1 + std::min({brute(a, b, i - 1, j - 1), brute(a, b, i - 1, j), brute(a, b, i, j - 1)});
}

std::string alternating(const std::string& pair, int n) {
    std::string s;
    for (int i = 0; i < n; ++i) s += pair[i % 2];
    return s;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(minDistance("horse", "ros") == 3);
    CHECK(minDistance("intention", "execution") == 5);
    CHECK(minDistance("", "abc") == 3);
}

TEST_CASE("edge cases") {
    SUBCASE("an empty side") {
        CHECK(minDistance("", "") == 0);
        CHECK(minDistance("abc", "") == 3);
        CHECK(minDistance("", "abcd") == 4);
    }
    SUBCASE("identical") {
        CHECK(minDistance("same", "same") == 0);
        CHECK(minDistance("a", "a") == 0);
    }
    SUBCASE("a full replace") {
        CHECK(minDistance("aaa", "bbb") == 3);
        CHECK(minDistance("abc", "xyz") == 3);
    }
    SUBCASE("single operations") {
        CHECK(minDistance("abc", "abxc") == 1);  // insert
        CHECK(minDistance("abxc", "abc") == 1);  // delete
        CHECK(minDistance("abc", "abd") == 1);   // replace
    }
    SUBCASE("different lengths with a shared core") {
        CHECK(minDistance("kitten", "sitting") == 3);
        CHECK(minDistance("sunday", "saturday") == 3);
    }
    SUBCASE("symmetric") { CHECK(minDistance("horse", "ros") == minDistance("ros", "horse")); }
}

TEST_CASE("randomized vs brute force (length <= 6)") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string a = rand_string(rand_int(0, 6), 'a', 'a' + rand_int(1, 3));
        const std::string b = rand_string(rand_int(0, 6), 'a', 'a' + rand_int(1, 3));
        INFO("a=" << a << " b=" << b);
        CHECK(minDistance(a, b) == brute(a, b, a.size(), b.size()));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // (ab)^250 vs (ba)^250: delete the leading 'a' and append an 'a'. The strings have equal length and
    // differ in every position, so one operation is impossible; the answer is 2.
    CHECK(minDistance(alternating("ab", 500), alternating("ba", 500)) == 2);
    // No common character: replace every position.
    CHECK(minDistance(std::string(500, 'a'), std::string(500, 'b')) == 500);
    // a^500 vs a^250 b^250: keep 250 a's, replace 250.
    CHECK(minDistance(std::string(500, 'a'), std::string(250, 'a') + std::string(250, 'b')) == 250);
}
