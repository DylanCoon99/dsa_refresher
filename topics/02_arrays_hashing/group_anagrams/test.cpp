#include <group_anagrams.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <map>
#include <string>
#include <vector>

namespace {
using Groups = std::vector<std::vector<std::string>>;

// Group and word order are free, so sort inside each group and then sort the groups.
Groups normalize(Groups g) {
    for (auto& grp : g) std::sort(grp.begin(), grp.end());
    std::sort(g.begin(), g.end());
    return g;
}

std::string sorted_key(std::string s) {
    std::sort(s.begin(), s.end());
    return s;
}

// Obviously-correct brute force: compare each word to the first member of every existing group.
Groups brute(const std::vector<std::string>& strs) {
    Groups groups;
    for (const std::string& w : strs) {
        bool placed = false;
        for (auto& g : groups) {
            if (sorted_key(g[0]) == sorted_key(w)) {
                g.push_back(w);
                placed = true;
                break;
            }
        }
        if (!placed) groups.push_back({w});
    }
    return groups;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(normalize(groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"})) ==
          normalize({{"eat", "tea", "ate"}, {"tan", "nat"}, {"bat"}}));
    CHECK(normalize(groupAnagrams({""})) == normalize({{""}}));
    CHECK(normalize(groupAnagrams({"a"})) == normalize({{"a"}}));
}

TEST_CASE("edge cases") {
    SUBCASE("the empty string is its own group") {
        CHECK(normalize(groupAnagrams({"", "a", ""})) == normalize({{"", ""}, {"a"}}));
    }
    SUBCASE("duplicate words stay duplicated") {
        CHECK(normalize(groupAnagrams({"ab", "ba", "ab"})) == normalize({{"ab", "ab", "ba"}}));
    }
    SUBCASE("no anagrams at all") {
        CHECK(normalize(groupAnagrams({"abc", "abd", "abe"})) == normalize({{"abc"}, {"abd"}, {"abe"}}));
    }
    SUBCASE("all anagrams of each other") {
        CHECK(normalize(groupAnagrams({"abc", "bca", "cab", "acb"})) == normalize({{"abc", "acb", "bca", "cab"}}));
    }
    SUBCASE("same letters but different counts are not anagrams") {
        CHECK(normalize(groupAnagrams({"aab", "abb", "baa"})) == normalize({{"aab", "baa"}, {"abb"}}));
    }
    SUBCASE("empty input") { CHECK(groupAnagrams({}).empty()); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<std::string> strs;
        int n = rand_int(1, 15);
        for (int i = 0; i < n; ++i) strs.push_back(rand_string(rand_int(0, 4), 'a', 'c'));
        CHECK(normalize(groupAnagrams(strs)) == normalize(brute(strs)));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^4 words of length 100 over a skewed alphabet, so most sorted keys share a long
    // common prefix. Pairwise grouping does ~5·10^7 comparisons of length-100 strings.
    const int n = 10'000;
    std::vector<std::string> strs;
    for (int i = 0; i < n; ++i) {
        std::string w(96, 'a');
        w += rand_string(4, 'b', 'z');
        std::shuffle(w.begin(), w.end(), rng());
        strs.push_back(w);
    }
    std::map<std::string, std::vector<std::string>> by_key;
    for (const auto& w : strs) by_key[sorted_key(w)].push_back(w);
    Groups want;
    for (auto& kv : by_key) want.push_back(kv.second);
    CHECK(normalize(groupAnagrams(strs)) == normalize(want));
}
