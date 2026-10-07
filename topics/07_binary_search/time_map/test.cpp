#include <time_map.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

TEST_CASE("examples") {
    TimeMap m;
    m.set("love", "high", 10);
    m.set("love", "low", 20);
    CHECK(m.get("love", 10) == "high");
    CHECK(m.get("love", 15) == "high");
    CHECK(m.get("love", 25) == "low");
    CHECK(m.get("love", 5) == "");
    CHECK(m.get("hate", 10) == "");
}

TEST_CASE("edge cases") {
    SUBCASE("query before the first timestamp") {
        TimeMap m;
        m.set("a", "x", 5);
        CHECK(m.get("a", 4) == "");
        CHECK(m.get("a", 1) == "");
        CHECK(m.get("a", 5) == "x");
    }
    SUBCASE("unknown key") {
        TimeMap m;
        CHECK(m.get("nothing", 100) == "");
        m.set("a", "x", 1);
        CHECK(m.get("b", 100) == "");
    }
    SUBCASE("exact match and just-before / just-after") {
        TimeMap m;
        m.set("k", "v1", 3);
        m.set("k", "v2", 7);
        m.set("k", "v3", 12);
        CHECK(m.get("k", 2) == "");
        CHECK(m.get("k", 3) == "v1");
        CHECK(m.get("k", 6) == "v1");
        CHECK(m.get("k", 7) == "v2");
        CHECK(m.get("k", 11) == "v2");
        CHECK(m.get("k", 12) == "v3");
        CHECK(m.get("k", 1'000'000'000) == "v3");
    }
    SUBCASE("keys have independent timestamps") {
        TimeMap m;
        m.set("a", "a-late", 100);
        m.set("b", "b-early", 1);
        m.set("a", "a-later", 200);
        m.set("b", "b-mid", 50);
        CHECK(m.get("a", 99) == "");
        CHECK(m.get("a", 150) == "a-late");
        CHECK(m.get("b", 1) == "b-early");
        CHECK(m.get("b", 60) == "b-mid");
        CHECK(m.get("b", 49) == "b-early");
    }
    SUBCASE("same value stored at different times") {
        TimeMap m;
        m.set("k", "same", 1);
        m.set("k", "same", 2);
        m.set("k", "other", 3);
        CHECK(m.get("k", 2) == "same");
        CHECK(m.get("k", 3) == "other");
    }
    SUBCASE("single entry at the maximum timestamp") {
        TimeMap m;
        m.set("k", "v", 1'000'000'000);
        CHECK(m.get("k", 999'999'999) == "");
        CHECK(m.get("k", 1'000'000'000) == "v");
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 200; ++trial) {
        TimeMap m;
        std::map<std::string, std::vector<std::pair<int, std::string>>> ref;
        std::map<std::string, int> last_ts;
        for (int op = 0; op < 60; ++op) {
            const std::string key(1, static_cast<char>('a' + rand_int(0, 3)));
            if (rand_int(0, 2) == 0) {
                const int ts = last_ts[key] + rand_int(1, 5);
                last_ts[key] = ts;
                const std::string val = rand_string(3);
                m.set(key, val, ts);
                ref[key].push_back({ts, val});
            } else {
                const int q = rand_int(1, 80);
                std::string expected;
                for (const auto& [ts, val] : ref[key])
                    if (ts <= q) expected = val;
                CHECK(m.get(key, q) == expected);
            }
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 entries on one key at timestamps 3, 5, 7, ... (2i + 3) with value "v<i>".
    // Query t >= 3 should return entry (t - 3) / 2. A linear scan per get is ~5·10^9 steps in total.
    const int n = 100'000;
    TimeMap m;
    for (int i = 0; i < n; ++i) m.set("key", "v" + std::to_string(i), 2 * i + 3);
    long long mismatches = 0;
    for (long long k = 0; k < n; ++k) {
        const int t = static_cast<int>((k * 7919 + 1) % (2LL * n + 10));   // ranges past the last timestamp
        std::string expected;
        if (t >= 3) expected = "v" + std::to_string(std::min((t - 3) / 2, n - 1));
        if (m.get("key", t) != expected) ++mismatches;
    }
    CHECK(mismatches == 0);
    CHECK(m.get("key", 2) == "");
    CHECK(m.get("key", 1'000'000'000) == "v" + std::to_string(n - 1));
}
