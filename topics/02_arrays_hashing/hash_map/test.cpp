#include <hash_map.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

TEST_CASE("examples") {
    HashMap m;
    CHECK(m.size() == 0);
    CHECK(m.bucketCount() == 8);
    CHECK(m.get("a") == std::nullopt);
    m.put("a", 1);
    CHECK(m.get("a") == std::optional<int>(1));
    m.put("a", 2);
    CHECK(m.size() == 1);
    CHECK(m.get("a") == std::optional<int>(2));
    CHECK(m.erase("a"));
    CHECK(m.size() == 0);
    CHECK(m.get("a") == std::nullopt);
}

TEST_CASE("edge cases") {
    SUBCASE("overwrite keeps size unchanged") {
        HashMap m;
        m.put("x", 1);
        m.put("y", 2);
        m.put("x", 10);
        m.put("x", 11);
        CHECK(m.size() == 2);
        CHECK(m.get("x") == std::optional<int>(11));
        CHECK(m.get("y") == std::optional<int>(2));
    }
    SUBCASE("erasing a missing key returns false") {
        HashMap m;
        CHECK_FALSE(m.erase("nope"));
        m.put("a", 1);
        CHECK_FALSE(m.erase("b"));
        CHECK(m.size() == 1);
        CHECK(m.erase("a"));
        CHECK_FALSE(m.erase("a"));
        CHECK(m.size() == 0);
    }
    SUBCASE("bucket count starts at 8 and grows") {
        HashMap m;
        CHECK(m.bucketCount() == 8);
        for (int i = 0; i < 6; ++i) m.put("k" + std::to_string(i), i);
        CHECK(m.bucketCount() == 8);  // 6 > 0.75 * 8 is false
        m.put("k6", 6);
        CHECK(m.bucketCount() >= 16);  // 7 > 6
    }
    SUBCASE("overwrite does not trigger a resize") {
        HashMap m;
        for (int i = 0; i < 6; ++i) m.put("k" + std::to_string(i), i);
        for (int rep = 0; rep < 20; ++rep) m.put("k0", rep);
        CHECK(m.bucketCount() == 8);
    }
    SUBCASE("custom initial bucket count") {
        HashMap m(16);
        CHECK(m.bucketCount() == 16);
    }
    SUBCASE("a single initial bucket works") {
        HashMap m(1);
        for (int i = 0; i < 100; ++i) m.put("k" + std::to_string(i), i);
        CHECK(m.size() == 100);
        for (int i = 0; i < 100; ++i) CHECK(m.get("k" + std::to_string(i)) == std::optional<int>(i));
        CHECK(m.erase("k50"));
        CHECK(m.get("k50") == std::nullopt);
        CHECK(m.get("k51") == std::optional<int>(51));
    }
    SUBCASE("empty key and negative values") {
        HashMap m;
        m.put("", -5);
        CHECK(m.get("") == std::optional<int>(-5));
        CHECK(m.size() == 1);
    }
    SUBCASE("load factor stays <= 0.75 after every insert") {
        HashMap m;
        for (int i = 0; i < 1000; ++i) {
            m.put("key" + std::to_string(i), i);
            REQUIRE(m.size() == static_cast<std::size_t>(i + 1));
            REQUIRE(static_cast<double>(m.size()) <= 0.75 * static_cast<double>(m.bucketCount()));
        }
        for (int i = 0; i < 1000; ++i) REQUIRE(m.get("key" + std::to_string(i)) == std::optional<int>(i));
    }
    SUBCASE("erase then reinsert") {
        HashMap m;
        for (int i = 0; i < 50; ++i) m.put("k" + std::to_string(i), i);
        for (int i = 0; i < 50; i += 2) CHECK(m.erase("k" + std::to_string(i)));
        CHECK(m.size() == 25);
        m.put("k0", 99);
        CHECK(m.get("k0") == std::optional<int>(99));
        CHECK(m.get("k1") == std::optional<int>(1));
        CHECK(m.size() == 26);
    }
}

TEST_CASE("randomized vs brute force") {
    // 20 000 mixed operations over 50 keys, checked against std::unordered_map.
    HashMap m;
    std::unordered_map<std::string, int> ref;
    for (int step = 0; step < 20000; ++step) {
        const std::string key = "k" + std::to_string(rand_int(0, 49));
        switch (rand_int(0, 2)) {
            case 0: {
                int v = rand_int(-1000, 1000);
                m.put(key, v);
                ref[key] = v;
                break;
            }
            case 1: {
                auto it = ref.find(key);
                std::optional<int> want = it == ref.end() ? std::nullopt : std::optional<int>(it->second);
                REQUIRE(m.get(key) == want);
                break;
            }
            default: {
                bool want = ref.erase(key) > 0;
                REQUIRE(m.erase(key) == want);
                break;
            }
        }
        REQUIRE(m.size() == ref.size());
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 2e5 distinct inserts then lookups. A table that never resizes keeps 8 chains of ~25 000
    // entries, i.e. on the order of 10^10 / 8 string comparisons.
    const int n = 200'000;
    std::vector<std::string> keys;
    keys.reserve(n);
    for (int i = 0; i < n; ++i) keys.push_back("key" + std::to_string(i));
    HashMap m;
    for (int i = 0; i < n; ++i) m.put(keys[i], i);
    REQUIRE(m.size() == static_cast<std::size_t>(n));
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        auto v = m.get(keys[i]);
        if (!v) FAIL("missing key" << i);
        sum += *v;
    }
    CHECK(sum == static_cast<long long>(n) * (n - 1) / 2);
    CHECK(m.get("key" + std::to_string(n)) == std::nullopt);
}
