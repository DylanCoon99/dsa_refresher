#include <merge_two_lists.hpp>

#include <doctest.h>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
std::vector<int> merged(std::vector<int> a, std::vector<int> b) {
    return to_vector(mergeTwoLists(build_list(a), build_list(b)));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(merged({1, 2, 4}, {1, 3, 4}) == std::vector<int>{1, 1, 2, 3, 4, 4});
    CHECK(merged({}, {}).empty());
    CHECK(merged({}, {0}) == std::vector<int>{0});
}

TEST_CASE("edge cases") {
    SUBCASE("both empty") { CHECK(mergeTwoLists(nullptr, nullptr) == nullptr); }
    SUBCASE("first empty") { CHECK(merged({}, {1, 2, 3}) == std::vector<int>{1, 2, 3}); }
    SUBCASE("second empty") { CHECK(merged({1, 2, 3}, {}) == std::vector<int>{1, 2, 3}); }
    SUBCASE("all values equal") { CHECK(merged({5, 5}, {5, 5, 5}) == std::vector<int>{5, 5, 5, 5, 5}); }
    SUBCASE("one list entirely before the other") {
        CHECK(merged({1, 2}, {3, 4}) == std::vector<int>{1, 2, 3, 4});
        CHECK(merged({3, 4}, {1, 2}) == std::vector<int>{1, 2, 3, 4});
    }
    SUBCASE("different lengths, interleaved") {
        CHECK(merged({1, 10}, {2, 3, 4, 11, 12}) == std::vector<int>{1, 2, 3, 4, 10, 11, 12});
    }
    SUBCASE("extreme values") {
        CHECK(merged({-2147483647 - 1, 0}, {0, 2147483647}) ==
              std::vector<int>{-2147483647 - 1, 0, 0, 2147483647});
    }
}

TEST_CASE("randomized vs std::merge") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> a = rand_vec(rand_int(0, 15), -20, 20);
        std::vector<int> b = rand_vec(rand_int(0, 15), -20, 20);
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        std::vector<int> expected;
        std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(expected));
        CHECK(merged(a, b) == expected);
    }
}
