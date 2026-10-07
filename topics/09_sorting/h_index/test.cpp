#include <h_index.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// Try every h from n down to 0; the first one with enough papers is the answer.
int brute(const std::vector<int>& c) {
    for (int h = static_cast<int>(c.size()); h >= 1; --h) {
        int papers = 0;
        for (int x : c)
            if (x >= h) ++papers;
        if (papers >= h) return h;
    }
    return 0;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(hIndex({3, 0, 6, 1, 5}) == 3);
    CHECK(hIndex({1, 3, 1}) == 1);
    CHECK(hIndex({0, 0}) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("all zeros") {
        CHECK(hIndex({0}) == 0);
        CHECK(hIndex({0, 0, 0, 0, 0}) == 0);
    }
    SUBCASE("single paper") {
        CHECK(hIndex({0}) == 0);
        CHECK(hIndex({1}) == 1);
        CHECK(hIndex({100}) == 1);
    }
    SUBCASE("all large: h = n") {
        CHECK(hIndex({1'000'000'000, 1'000'000'000, 1'000'000'000}) == 3);
        CHECK(hIndex({50, 60, 70, 80, 90, 100}) == 6);
    }
    SUBCASE("all ones") { CHECK(hIndex({1, 1, 1, 1}) == 1); }
    SUBCASE("exactly h citations is enough") { CHECK(hIndex({4, 4, 4, 4}) == 4); }
    SUBCASE("one just below the threshold") { CHECK(hIndex({3, 3, 3, 3}) == 3); }
    SUBCASE("sorted and reversed") {
        CHECK(hIndex({0, 1, 2, 3, 4, 5}) == 3);
        CHECK(hIndex({5, 4, 3, 2, 1, 0}) == 3);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 500; ++trial) {
        const std::vector<int> c = rand_vec(static_cast<std::size_t>(rand_int(1, 30)), 0, rand_int(1, 35));
        CHECK(hIndex(c) == brute(c));
    }
}
