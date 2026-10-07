#include <task_scheduler.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <string>
#include <vector>

namespace {
std::vector<char> make(const std::string& s) { return std::vector<char>(s.begin(), s.end()); }

// Brute-force greedy simulation, one time unit per step: run the available task type (not run
// within the last n units) that has the most copies left; idle if none is available.
int brute(const std::vector<char>& tasks, int n) {
    int count[26] = {0};
    int last[26];
    for (int& l : last) l = INT_MIN / 2;
    for (char c : tasks) ++count[c - 'A'];
    int remaining = static_cast<int>(tasks.size());
    int time = 0;
    while (remaining > 0) {
        int best = -1;
        for (int c = 0; c < 26; ++c) {
            if (count[c] == 0 || time - last[c] <= n) continue;
            if (best == -1 || count[c] > count[best]) best = c;
        }
        if (best != -1) {
            --count[best];
            last[best] = time;
            --remaining;
        }
        ++time;
    }
    return time;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(leastInterval(make("AAABBB"), 2) == 8);
    CHECK(leastInterval(make("AAABBB"), 0) == 6);
    CHECK(leastInterval(make("AAAAAABCDEFG"), 1) == 12);
}

TEST_CASE("edge cases") {
    SUBCASE("n = 0 returns the number of tasks") {
        CHECK(leastInterval(make("ABACADAEAF"), 0) == 10);
        CHECK(leastInterval(make("A"), 0) == 1);
    }
    SUBCASE("single task") { CHECK(leastInterval(make("Z"), 5) == 1); }
    SUBCASE("single task type") {
        CHECK(leastInterval(make("AAAA"), 2) == 10);  // A..A..A..A
        CHECK(leastInterval(make("AA"), 100) == 102);
    }
    SUBCASE("many types, no idle time needed") {
        CHECK(leastInterval(make("ABCDEFABCDEFABCDEF"), 5) == 18);
        CHECK(leastInterval(make("ABCABCABC"), 2) == 9);
    }
    SUBCASE("ties for the most frequent type add a final slot") {
        CHECK(leastInterval(make("AABBCC"), 3) == 7);  // A B C idle A B C
    }
    SUBCASE("idle time needed with a short tail") { CHECK(leastInterval(make("AAABC"), 3) == 9); }
    SUBCASE("large n") { CHECK(leastInterval(make("AABBCCDD"), 100) == 105); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        int len = rand_int(1, 14);
        int alphabet = rand_int(1, 5);
        std::vector<char> tasks;
        for (int i = 0; i < len; ++i) tasks.push_back(static_cast<char>('A' + rand_int(0, alphabet - 1)));
        int n = rand_int(0, 5);
        CHECK(leastInterval(tasks, n) == brute(tasks, n));
    }
}
