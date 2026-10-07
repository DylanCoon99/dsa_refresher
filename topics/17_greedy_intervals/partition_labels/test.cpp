#include <partition_labels.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <string>
#include <vector>

namespace {
// A cut after position i is allowed iff no letter occurs both in s[0..i] and in s[i+1..].
// The pieces between all allowed cuts are the answer (the most pieces possible).
std::vector<int> brute(const std::string& s) {
    const int n = static_cast<int>(s.size());
    std::vector<int> out;
    int start = 0;
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int a = 0; a <= i && ok; ++a)
            for (int b = i + 1; b < n && ok; ++b)
                if (s[a] == s[b]) ok = false;
        if (ok) {
            out.push_back(i - start + 1);
            start = i + 1;
        }
    }
    return out;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(partitionLabels("ababcbacadefegdehijhklij") == std::vector<int>{9, 7, 8});
    CHECK(partitionLabels("eccbbbbdec") == std::vector<int>{10});
    CHECK(partitionLabels("abc") == std::vector<int>{1, 1, 1});
}

TEST_CASE("edge cases") {
    SUBCASE("single char") { CHECK(partitionLabels("z") == std::vector<int>{1}); }
    SUBCASE("all distinct gives all ones") {
        CHECK(partitionLabels("abcdefghijklmnopqrstuvwxyz") == std::vector<int>(26, 1));
    }
    SUBCASE("all the same letter gives one piece") {
        CHECK(partitionLabels("aaaaaaa") == std::vector<int>{7});
        CHECK(partitionLabels(std::string(1000, 'q')) == std::vector<int>{1000});
    }
    SUBCASE("repeated letters stay together, runs separate") {
        CHECK(partitionLabels("aabbcc") == std::vector<int>{2, 2, 2});
        CHECK(partitionLabels("aabbaacc") == std::vector<int>{6, 2});
    }
    SUBCASE("first and last letter equal") { CHECK(partitionLabels("abcda") == std::vector<int>{5}); }
    SUBCASE("a late repeat merges earlier pieces") { CHECK(partitionLabels("abcab") == std::vector<int>{5}); }
    SUBCASE("nested letters") { CHECK(partitionLabels("abbac") == std::vector<int>{4, 1}); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(rand_int(1, 14), 'a', static_cast<char>('a' + rand_int(1, 7)));
        INFO("trial " << trial << " s=" << s);
        CHECK(partitionLabels(s) == brute(s));
    }
}
