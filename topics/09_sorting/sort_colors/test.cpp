#include <sort_colors.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
void check_sorted(std::vector<int> nums) {
    std::vector<int> expected = nums;
    std::sort(expected.begin(), expected.end());
    sortColors(nums);
    CHECK(nums == expected);
}
}  // namespace

TEST_CASE("examples") {
    std::vector<int> a = {2, 0, 2, 1, 1, 0};
    sortColors(a);
    CHECK(a == std::vector<int>{0, 0, 1, 1, 2, 2});
    std::vector<int> b = {2, 0, 1};
    sortColors(b);
    CHECK(b == std::vector<int>{0, 1, 2});
    std::vector<int> c = {1};
    sortColors(c);
    CHECK(c == std::vector<int>{1});
}

TEST_CASE("edge cases") {
    SUBCASE("length 1") {
        check_sorted({0});
        check_sorted({2});
    }
    SUBCASE("all one color") {
        check_sorted({0, 0, 0, 0});
        check_sorted({1, 1, 1});
        check_sorted({2, 2, 2, 2, 2});
    }
    SUBCASE("two colors only") {
        check_sorted({2, 0, 2, 0});
        check_sorted({1, 0, 1, 0});
        check_sorted({2, 1, 2, 1});
    }
    SUBCASE("already sorted") { check_sorted({0, 0, 1, 1, 2, 2}); }
    SUBCASE("reversed") { check_sorted({2, 2, 1, 1, 0, 0}); }
    SUBCASE("a 2 swapped to the back brings a 0 forward") { check_sorted({2, 0, 0, 1, 2, 0, 1}); }
}

TEST_CASE("randomized vs sort") {
    for (int trial = 0; trial < 300; ++trial) {
        check_sorted(rand_vec(static_cast<std::size_t>(rand_int(1, 30)), 0, 2));
    }
}
