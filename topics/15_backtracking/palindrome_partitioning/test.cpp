#include <palindrome_partitioning.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <string>
#include <vector>

namespace {
using Splits = std::vector<std::vector<std::string>>;

// The pieces' order inside a split matters, so only the outer vector is sorted.
Splits outer_sorted(Splits v) {
    std::sort(v.begin(), v.end());
    return v;
}

bool has_duplicates(Splits v) {
    std::sort(v.begin(), v.end());
    return std::adjacent_find(v.begin(), v.end()) != v.end();
}

bool is_pal(const std::string& t) {
    return std::equal(t.begin(), t.begin() + t.size() / 2, t.rbegin());
}

// Every cut mask over the n-1 gaps (2^(n-1) of them); keep those whose pieces are all palindromes.
Splits brute(const std::string& s) {
    const int n = static_cast<int>(s.size());
    Splits out;
    for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
        std::vector<std::string> pieces;
        std::string cur;
        for (int i = 0; i < n; ++i) {
            cur += s[i];
            if (i == n - 1 || (mask >> i & 1)) {
                pieces.push_back(cur);
                cur.clear();
            }
        }
        if (std::all_of(pieces.begin(), pieces.end(), is_pal)) out.push_back(pieces);
    }
    return out;
}

void check_partition(const std::string& s) {
    Splits got = partition(s);
    CHECK_FALSE(has_duplicates(got));
    CHECK(outer_sorted(got) == outer_sorted(brute(s)));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(outer_sorted(partition("aab")) == Splits{{"a", "a", "b"}, {"aa", "b"}});
    CHECK(partition("a") == Splits{{"a"}});
    Splits four = partition("aaaa");
    CHECK(four.size() == 8);
    CHECK_FALSE(has_duplicates(four));
}

TEST_CASE("edge cases") {
    SUBCASE("single character") { CHECK(partition("z") == Splits{{"z"}}); }
    SUBCASE("aab") { CHECK(outer_sorted(partition("aab")) == Splits{{"a", "a", "b"}, {"aa", "b"}}); }
    SUBCASE("aaaa has 8 partitions") {
        Splits got = partition("aaaa");
        CHECK(got.size() == 8);
        CHECK_FALSE(has_duplicates(got));
        CHECK(outer_sorted(got) ==
              Splits{{"a", "a", "a", "a"}, {"a", "a", "aa"}, {"a", "aa", "a"}, {"a", "aaa"},
                     {"aa", "a", "a"}, {"aa", "aa"}, {"aaa", "a"}, {"aaaa"}});
    }
    SUBCASE("no repeated letters: only single characters") {
        CHECK(partition("abcd") == Splits{{"a", "b", "c", "d"}});
    }
    SUBCASE("order inside a split matters") {
        CHECK(outer_sorted(partition("abb")) == Splits{{"a", "b", "b"}, {"a", "bb"}});
    }
    SUBCASE("whole string is a palindrome") { check_partition("racecar"); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        check_partition(rand_string(rand_int(1, 10), 'a', 'b'));
    }
    for (int trial = 0; trial < 100; ++trial) {
        check_partition(rand_string(rand_int(1, 8), 'a', 'c'));
    }
}
