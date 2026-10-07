#include <lru_cache.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <list>
#include <utility>

namespace {
// Obviously-correct model: most recent at the front, linear scans everywhere.
struct ModelLRU {
    explicit ModelLRU(int cap) : capacity(cap) {}
    int get(int key) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->first == key) {
                items.splice(items.begin(), items, it);
                return it->second;
            }
        }
        return -1;
    }
    void put(int key, int value) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->first == key) {
                it->second = value;
                items.splice(items.begin(), items, it);
                return;
            }
        }
        if (static_cast<int>(items.size()) == capacity) items.pop_back();
        items.emplace_front(key, value);
    }
    int capacity;
    std::list<std::pair<int, int>> items;
};
}  // namespace

TEST_CASE("examples") {
    LRUCache a(2);
    a.put(1, 1);
    a.put(2, 2);
    CHECK(a.get(1) == 1);
    a.put(3, 3);
    CHECK(a.get(2) == -1);
    a.put(4, 4);
    CHECK(a.get(1) == -1);
    CHECK(a.get(3) == 3);
    CHECK(a.get(4) == 4);

    LRUCache b(1);
    b.put(1, 10);
    b.put(2, 20);
    CHECK(b.get(1) == -1);
    CHECK(b.get(2) == 20);

    LRUCache c(2);
    c.put(1, 1);
    c.put(2, 2);
    c.put(1, 100);
    c.put(3, 3);
    CHECK(c.get(1) == 100);
}

TEST_CASE("edge cases") {
    SUBCASE("missing key on an empty cache") {
        LRUCache c(3);
        CHECK(c.get(7) == -1);
    }
    SUBCASE("capacity 1 evicts on every new key") {
        LRUCache c(1);
        c.put(1, 1);
        CHECK(c.get(1) == 1);
        c.put(2, 2);
        CHECK(c.get(1) == -1);
        CHECK(c.get(2) == 2);
        c.put(2, 5);  // update in place, nothing evicted
        CHECK(c.get(2) == 5);
        c.put(3, 3);
        CHECK(c.get(2) == -1);
        CHECK(c.get(3) == 3);
    }
    SUBCASE("get refreshes recency") {
        LRUCache c(2);
        c.put(1, 1);
        c.put(2, 2);
        CHECK(c.get(1) == 1);  // 1 is now newer than 2
        c.put(3, 3);           // must evict 2, not 1
        CHECK(c.get(1) == 1);
        CHECK(c.get(2) == -1);
        CHECK(c.get(3) == 3);
    }
    SUBCASE("a missed get does not change recency") {
        LRUCache c(2);
        c.put(1, 1);
        c.put(2, 2);
        CHECK(c.get(9) == -1);
        c.put(3, 3);  // evicts 1, the oldest
        CHECK(c.get(1) == -1);
        CHECK(c.get(2) == 2);
    }
    SUBCASE("put on an existing key refreshes recency and does not evict") {
        LRUCache c(2);
        c.put(1, 1);
        c.put(2, 2);
        c.put(1, 10);  // full cache, existing key: nothing is evicted
        CHECK(c.get(2) == 2);
        c.put(2, 20);  // refresh 2; now 1 is the oldest
        c.put(3, 3);   // evicts 1
        CHECK(c.get(1) == -1);
        CHECK(c.get(2) == 20);
        CHECK(c.get(3) == 3);
    }
    SUBCASE("put on an existing key makes it newest") {
        LRUCache c(2);
        c.put(1, 1);
        c.put(2, 2);
        c.put(1, 11);  // 2 becomes the oldest
        c.put(3, 3);
        CHECK(c.get(2) == -1);
        CHECK(c.get(1) == 11);
    }
    SUBCASE("zero is a valid value and negative keys work") {
        LRUCache c(2);
        c.put(-5, 0);
        CHECK(c.get(-5) == 0);
        c.put(0, 7);
        CHECK(c.get(0) == 7);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int cap : {1, 2, 3, 5, 8}) {
        LRUCache cache(cap);
        ModelLRU model(cap);
        for (int op = 0; op < 20'000; ++op) {
            int key = rand_int(0, 12);
            if (rand_int(0, 1) == 0) {
                REQUIRE(cache.get(key) == model.get(key));
            } else {
                int value = rand_int(0, 1'000'000'000);
                cache.put(key, value);
                model.put(key, value);
            }
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 2e5 operations, capacity 1e4. Expected values are derived by hand, not by a model:
    //  1. put(k, 2k) for k in [0, 1e4): fills the cache.                      (1e4 ops)
    //  2. get(k) cycling through 0..1e4-1, 10 rounds: always the oldest key,
    //     always a hit with value 2k. A scan-based cache walks the full list.  (1e5 ops)
    //  3. put(1e4 + i, i) for i in [0, 5e4): evicts every old key; only keys
    //     5e4..6e4-1 (values key-1e4) survive.                                 (5e4 ops)
    //  4. alternate get(5e4 + j % 1e4) -> key-1e4 and get(j % 1e4) -> -1.      (4e4 ops)
    const int cap = 10'000;
    LRUCache cache(cap);
    for (int k = 0; k < cap; ++k) cache.put(k, 2 * k);
    int wrong = 0;
    for (int i = 0; i < 100'000; ++i) {
        int k = i % cap;
        if (cache.get(k) != 2 * k) ++wrong;
    }
    CHECK(wrong == 0);
    for (int i = 0; i < 50'000; ++i) cache.put(cap + i, i);
    wrong = 0;
    for (int j = 0; j < 20'000; ++j) {
        int hit = 50'000 + j % cap;
        if (cache.get(hit) != hit - cap) ++wrong;
        if (cache.get(j % cap) != -1) ++wrong;
    }
    CHECK(wrong == 0);
}
