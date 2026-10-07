#include <permutation_in_string.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <random>
#include <string>

namespace {
// Sort every window of the right length and compare it with the sorted s1.
bool brute(const std::string& s1, const std::string& s2) {
    if (s1.size() > s2.size()) return false;
    std::string key = s1;
    std::sort(key.begin(), key.end());
    for (std::size_t i = 0; i + s1.size() <= s2.size(); ++i) {
        std::string w = s2.substr(i, s1.size());
        std::sort(w.begin(), w.end());
        if (w == key) return true;
    }
    return false;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(checkInclusion("ab", "eidbaooo") == true);
    CHECK(checkInclusion("ab", "eidboaoo") == false);
    CHECK(checkInclusion("abc", "abc") == true);
}

TEST_CASE("edge cases") {
    SUBCASE("s1 longer than s2") { CHECK(checkInclusion("abcd", "abc") == false); }
    SUBCASE("s1 equals s2") { CHECK(checkInclusion("hello", "hello") == true); }
    SUBCASE("s2 is a rearrangement of s1") { CHECK(checkInclusion("hello", "olleh") == true); }
    SUBCASE("same length, different letters") { CHECK(checkInclusion("abc", "abd") == false); }
    SUBCASE("match at the very start") { CHECK(checkInclusion("abc", "cabxyz") == true); }
    SUBCASE("match at the very end") { CHECK(checkInclusion("abc", "xyzzycba") == true); }
    SUBCASE("single letters") {
        CHECK(checkInclusion("a", "a") == true);
        CHECK(checkInclusion("a", "b") == false);
        CHECK(checkInclusion("a", "xyza") == true);
    }
    SUBCASE("counts matter, not just letters") {
        CHECK(checkInclusion("aab", "abbab") == false);
        CHECK(checkInclusion("aab", "abbaab") == true);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        const std::string s1 = rand_string(rand_int(1, 6), 'a', 'c');
        const std::string s2 = rand_string(rand_int(1, 20), 'a', 'c');
        CAPTURE(s1);
        CAPTURE(s2);
        CHECK(checkInclusion(s1, s2) == brute(s1, s2));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // |s1| = 5000 over a..m, |s2| = 10^5 over a..m. Sorting every window is ~10^5 * 5000 log 5000.
    const int m = 5000, n = 100'000;
    std::mt19937 gen(555);
    std::string s1(m, 'a');
    for (char& c : s1) c = static_cast<char>('a' + gen() % 13u);

    SUBCASE("no match") {
        // A 'z' every 4000 characters sits in every length-5000 window, and s1 has no 'z'.
        std::string s2(n, 'a');
        for (char& c : s2) c = static_cast<char>('a' + gen() % 13u);
        for (int i = 0; i < n; i += 4000) s2[i] = 'z';
        CHECK(checkInclusion(s1, s2) == false);
    }
    SUBCASE("match only at the very end") {
        // Random a..m filler (no 'z') followed by a shuffled copy of s1.
        std::string s2(n - m, 'a');
        for (char& c : s2) c = static_cast<char>('a' + gen() % 13u);
        std::string tail = s1;
        std::shuffle(tail.begin(), tail.end(), gen);
        s2 += tail;
        CHECK(checkInclusion(s1, s2) == true);
    }
}
