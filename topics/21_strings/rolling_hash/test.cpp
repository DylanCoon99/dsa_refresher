#include <rolling_hash.hpp>

#include <doctest.h>
#include <random_utils.hpp>

#include <cstdint>
#include <map>
#include <random>
#include <string>
#include <utility>
#include <vector>

TEST_CASE("examples") {
    RollingHash a("abcabc");
    CHECK(a.hash(0, 3) == a.hash(3, 3));
    CHECK(RollingHash("ab").hash(0, 2) != RollingHash("ba").hash(0, 2));
    CHECK(RollingHash("xyz").hash(1, 2) == RollingHash("yz").hash(0, 2));
}

TEST_CASE("edge cases") {
    SUBCASE("hash(pos, len) matches a fresh object on the substring") {
        const std::string s = "the quick brown fox jumps over the lazy dog";
        RollingHash h(s);
        for (std::size_t pos = 0; pos <= s.size(); pos += 3)
            for (std::size_t len = 0; pos + len <= s.size(); len += 2) {
                INFO("pos=" << pos << " len=" << len);
                CHECK(h.hash(pos, len) == RollingHash(s.substr(pos, len)).hash(0, len));
            }
    }
    SUBCASE("equal substrings at different positions") {
        RollingHash h("abracadabra");
        CHECK(h.hash(0, 4) == h.hash(7, 4));  // "abra" twice
        CHECK(h.hash(0, 4) != h.hash(1, 4));  // "abra" vs "brac"
    }
    SUBCASE("character order matters") {
        CHECK(RollingHash("ab").hash(0, 2) != RollingHash("ba").hash(0, 2));
        CHECK(RollingHash("abc").hash(0, 3) != RollingHash("cba").hash(0, 3));
        CHECK(RollingHash("ad").hash(0, 2) != RollingHash("bc").hash(0, 2));  // same character sum
    }
    SUBCASE("empty substrings") {
        RollingHash h("abc");
        CHECK(h.hash(0, 0) == h.hash(2, 0));
        CHECK(RollingHash("").hash(0, 0) == h.hash(1, 0));
    }
    SUBCASE("single character") {
        RollingHash h("ab");
        CHECK(h.hash(0, 1) != h.hash(1, 1));
        CHECK(h.hash(1, 1) == RollingHash("b").hash(0, 1));
    }
}

TEST_CASE("randomized: same-length substrings of ab strings") {
    // For every length, equal substrings must hash equal (checked across 300 different objects
    // and against fresh objects), and distinct substrings of that length must hash differently.
    std::map<std::pair<std::size_t, std::uint64_t>, std::string> seen;  // (len, hash) -> substring
    std::map<std::string, std::uint64_t> byText;                        // substring -> hash
    for (int trial = 0; trial < 300; ++trial) {
        const std::string s = rand_string(12, 'a', 'b');
        RollingHash h(s);
        for (std::size_t pos = 0; pos < s.size(); ++pos)
            for (std::size_t len = 1; pos + len <= s.size(); ++len) {
                const std::string sub = s.substr(pos, len);
                const std::uint64_t v = h.hash(pos, len);
                INFO("s=" << s << " pos=" << pos << " len=" << len);
                CHECK(v == RollingHash(sub).hash(0, len));
                auto [it, inserted] = byText.emplace(sub, v);
                if (!inserted) CHECK_MESSAGE(it->second == v, "equal substrings \"" << sub << "\" hashed differently");
                auto [jt, fresh] = seen.emplace(std::make_pair(len, v), sub);
                if (!fresh) CHECK_MESSAGE(jt->second == sub, "\"" << sub << "\" and \"" << jt->second << "\" collide");
            }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // s = a random 1000-character block repeated 1000 times (n = 10^6), so substrings that start
    // 1000 apart are equal. Hashing each query's substring from scratch would cost ~10^11 steps.
    const std::size_t block = 1000, reps = 1000, n = block * reps;
    std::mt19937 g(12345);
    std::string blk(block, 'a');
    for (char& c : blk) c = static_cast<char>('a' + g() % 26);
    std::string s;
    s.reserve(n);
    for (std::size_t r = 0; r < reps; ++r) s += blk;
    RollingHash h(s);

    // 250000 iterations x 4 queries = 10^6 queries.
    long long badEq = -1, badNe = -1;
    for (int q = 0; q < 250'000; ++q) {
        const std::size_t len = 2000 + g() % 200'000;           // >= block, so a shift by 1 differs
        const std::size_t span = n - len;                        // largest legal start
        const std::size_t i = g() % (span - 1000 + 1);           // leave room for a shift of 1000 * k
        const std::size_t k = 1 + g() % ((span - i) / 1000);
        const std::size_t j = i + 1000 * k;                      // s[j..j+len) == s[i..i+len)
        if (badEq < 0 && h.hash(i, len) != h.hash(j, len)) badEq = q;
        // s[i+1..] differs from s[i..] over any window of >= 1000 chars (random block is not 1-periodic).
        if (badNe < 0 && h.hash(i, len) == h.hash(i + 1, len)) badNe = q;
    }
    CHECK_MESSAGE(badEq == -1, "equal substrings hashed differently at query " << badEq);
    CHECK_MESSAGE(badNe == -1, "different substrings collided at query " << badNe);
}
