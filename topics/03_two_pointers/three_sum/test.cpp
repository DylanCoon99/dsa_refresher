#include <three_sum.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <cstdint>
#include <random>
#include <set>
#include <vector>

namespace {
using Triples = std::vector<std::vector<int>>;

// Sort each triplet, then the list, so that any valid output order compares equal.
Triples normalize(Triples t) {
    for (auto& tr : t) std::sort(tr.begin(), tr.end());
    std::sort(t.begin(), t.end());
    return t;
}

Triples brute(const std::vector<int>& nums) {
    std::set<std::vector<int>> found;
    const int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k)
                if (nums[i] + nums[j] + nums[k] == 0) {
                    std::vector<int> tr = {nums[i], nums[j], nums[k]};
                    std::sort(tr.begin(), tr.end());
                    found.insert(tr);
                }
    return Triples(found.begin(), found.end());
}
}  // namespace

TEST_CASE("examples") {
    CHECK(normalize(threeSum({-1, 0, 1, 2, -1, -4})) == Triples{{-1, -1, 2}, {-1, 0, 1}});
    CHECK(normalize(threeSum({0, 1, 1})) == Triples{});
    CHECK(normalize(threeSum({0, 0, 0, 0})) == Triples{{0, 0, 0}});
}

TEST_CASE("edge cases") {
    SUBCASE("empty") { CHECK(threeSum({}).empty()); }
    SUBCASE("fewer than three elements") { CHECK(threeSum({0, 0}).empty()); }
    SUBCASE("exactly three, valid") { CHECK(normalize(threeSum({1, -3, 2})) == Triples{{-3, 1, 2}}); }
    SUBCASE("all zeros") { CHECK(normalize(threeSum({0, 0, 0})) == Triples{{0, 0, 0}}); }
    SUBCASE("many zeros") { CHECK(normalize(threeSum(std::vector<int>(50, 0))) == Triples{{0, 0, 0}}); }
    SUBCASE("two zeros are not enough") { CHECK(normalize(threeSum({0, 0, 5, 6})) == Triples{}); }
    SUBCASE("no answer, all positive") { CHECK(threeSum({1, 2, 3, 4, 5}).empty()); }
    SUBCASE("no answer, all negative") { CHECK(threeSum({-1, -2, -3, -4}).empty()); }
    SUBCASE("no answer, mixed") { CHECK(threeSum({1, 2, -10, 5, 7}).empty()); }
    SUBCASE("many duplicates") {
        CHECK(normalize(threeSum({-2, -2, -2, 0, 0, 0, 2, 2, 2, 1, 1, -1, -1})) ==
              Triples{{-2, 0, 2}, {-2, 1, 1}, {-1, -1, 2}, {-1, 0, 1}, {0, 0, 0}});
    }
    SUBCASE("one value repeated with its negation") {
        CHECK(normalize(threeSum({-4, -4, 2, 2, 2, 2, -4, 0})) == Triples{{-4, 2, 2}});
    }
    SUBCASE("extreme values") {
        CHECK(normalize(threeSum({-100000, 100000, 0, 100000, -100000})) == Triples{{-100000, 0, 100000}});
    }
    SUBCASE("unsorted input") { CHECK(normalize(threeSum({3, -2, 1, 0, -1, 2, -3})) == brute({3, -2, 1, 0, -1, 2, -3})); }
}

TEST_CASE("randomized vs O(n^3) brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(0, 14), -6, 6);
        const Triples got = normalize(threeSum(nums));
        CHECK(got == brute(nums));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 3000 pseudo-random values; O(n^3) would need ~2.7·10^10 steps.
    // Local generator (not the shared rng()) so the input does not depend on which tests ran first.
    std::mt19937 gen(12345);
    std::vector<int> nums(3000);
    for (int& v : nums) v = static_cast<int>(gen() % 200001u) - 100000;
    const Triples got = threeSum(nums);
    REQUIRE(got.size() == 16324u);
    // Spot-check the contract on every triplet.
    std::set<std::vector<int>> seen;
    for (const auto& tr : got) {
        REQUIRE(tr.size() == 3);
        CHECK(tr[0] + tr[1] + tr[2] == 0);
        std::vector<int> s = tr;
        std::sort(s.begin(), s.end());
        CHECK(seen.insert(s).second);
    }
}
