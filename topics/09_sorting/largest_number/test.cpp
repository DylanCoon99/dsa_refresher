#include <largest_number.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

namespace {
// Try every ordering of the indices, keep the lexicographically largest concatenation. All
// concatenations have the same length, so lexicographic order is numeric order.
std::string brute(const std::vector<int>& nums) {
    std::vector<std::size_t> order(nums.size());
    std::iota(order.begin(), order.end(), std::size_t{0});
    std::string best;
    do {
        std::string s;
        for (std::size_t i : order) s += std::to_string(nums[i]);
        best = std::max(best, s);
    } while (std::next_permutation(order.begin(), order.end()));
    const std::size_t first = best.find_first_not_of('0');
    return first == std::string::npos ? "0" : best;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(largestNumber({10, 2}) == "210");
    CHECK(largestNumber({3, 30, 34, 5, 9}) == "9534330");
    CHECK(largestNumber({0, 0}) == "0");
}

TEST_CASE("edge cases") {
    SUBCASE("all zeros") {
        CHECK(largestNumber({0}) == "0");
        CHECK(largestNumber({0, 0, 0, 0}) == "0");
    }
    SUBCASE("single number") { CHECK(largestNumber({1'000'000'000}) == "1000000000"); }
    SUBCASE("zeros mixed with others") {
        CHECK(largestNumber({0, 1, 0}) == "100");
        CHECK(largestNumber({10, 0}) == "100");
    }
    SUBCASE("one number is a prefix of another") {
        CHECK(largestNumber({34, 3, 30}) == "34330");
        CHECK(largestNumber({824, 8247}) == "8248247");
        CHECK(largestNumber({121, 12}) == "12121");
    }
    SUBCASE("equal numbers") { CHECK(largestNumber({5, 5, 5}) == "555"); }
    SUBCASE("large values") { CHECK(largestNumber({999'999'999, 1'000'000'000, 99}) == "999999999991000000000"); }
}

TEST_CASE("randomized vs brute force (all permutations)") {
    for (int trial = 0; trial < 300; ++trial) {
        // Small values (0..120) so prefixes, repeats and zeros show up often.
        std::vector<int> nums = rand_vec(static_cast<std::size_t>(rand_int(1, 6)), 0, 120);
        CHECK(largestNumber(nums) == brute(nums));
    }
}
