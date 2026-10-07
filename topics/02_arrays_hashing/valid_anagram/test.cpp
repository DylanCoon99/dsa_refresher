#include <valid_anagram.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <string>

TEST_CASE("examples") {
    CHECK(isAnagram("anagram", "nagaram") == true);
    CHECK(isAnagram("rat", "car") == false);
    CHECK(isAnagram("", "") == true);
}

TEST_CASE("edge cases") {
    SUBCASE("different lengths") {
        CHECK(isAnagram("ab", "abc") == false);
        CHECK(isAnagram("abc", "ab") == false);
        CHECK(isAnagram("a", "") == false);
    }
    SUBCASE("same letters, different counts") {
        CHECK(isAnagram("aab", "abb") == false);
        CHECK(isAnagram("abb", "aab") == false);
    }
    SUBCASE("both empty") { CHECK(isAnagram("", "") == true); }
    SUBCASE("single characters") {
        CHECK(isAnagram("a", "a") == true);
        CHECK(isAnagram("a", "b") == false);
    }
    SUBCASE("identical and reversed") {
        CHECK(isAnagram("listen", "listen") == true);
        CHECK(isAnagram("listen", "netsil") == true);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        std::string s = rand_string(rand_int(0, 8), 'a', 'd');
        std::string t;
        if (rand_int(0, 1) == 0) {
            t = s;
            std::shuffle(t.begin(), t.end(), rng());
            if (rand_int(0, 3) == 0 && !t.empty()) t[rand_int(0, static_cast<int>(t.size()) - 1)] = 'a' + rand_int(0, 3);
        } else {
            t = rand_string(rand_int(0, 8), 'a', 'd');
        }
        std::string a = s, b = t;
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        CHECK(isAnagram(s, t) == (a == b));
    }
}
