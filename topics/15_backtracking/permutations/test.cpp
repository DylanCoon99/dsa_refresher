#include <permutations.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
using Rows = std::vector<std::vector<int>>;

// Order inside a permutation matters, so only the outer vector is sorted.
Rows outer_sorted(Rows v) {
    std::sort(v.begin(), v.end());
    return v;
}

bool has_duplicates(Rows v) {
    std::sort(v.begin(), v.end());
    return std::adjacent_find(v.begin(), v.end()) != v.end();
}

Rows brute(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    Rows out;
    do out.push_back(nums);
    while (std::next_permutation(nums.begin(), nums.end()));
    return out;
}

void check_perms(const std::vector<int>& nums) {
    Rows got = permute(nums);
    CHECK_FALSE(has_duplicates(got));
    CHECK(outer_sorted(got) == brute(nums));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(outer_sorted(permute({1, 2, 3})) ==
          Rows{{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}});
    CHECK(outer_sorted(permute({0, 1})) == Rows{{0, 1}, {1, 0}});
    CHECK(permute({1}) == Rows{{1}});
}

TEST_CASE("edge cases") {
    SUBCASE("n = 1") { CHECK(permute({-4}) == Rows{{-4}}); }
    SUBCASE("negatives and unsorted input") { check_perms({3, -1, 0, -7}); }
    SUBCASE("n = 6 gives 720 distinct permutations") {
        Rows got = permute({1, 2, 3, 4, 5, 6});
        CHECK(got.size() == 720);
        CHECK_FALSE(has_duplicates(got));
        check_perms({1, 2, 3, 4, 5, 6});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 200; ++trial) {
        std::vector<int> pool(21);
        std::iota(pool.begin(), pool.end(), -10);
        std::shuffle(pool.begin(), pool.end(), rng());
        pool.resize(rand_int(1, 6));
        check_perms(pool);
    }
}
