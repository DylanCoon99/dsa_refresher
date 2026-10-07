#include <two_sum_ii.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

TEST_CASE("examples") {
    CHECK(twoSum({2, 7, 11, 15}, 9) == std::vector<int>{1, 2});
    CHECK(twoSum({1, 1, 3}, 2) == std::vector<int>{1, 2});
    CHECK(twoSum({-5, -1, 0, 4}, -1) == std::vector<int>{1, 4});
}

TEST_CASE("edge cases") {
    SUBCASE("minimum size") { CHECK(twoSum({3, 5}, 8) == std::vector<int>{1, 2}); }
    SUBCASE("negatives") { CHECK(twoSum({-9, -6, -4, 1, 8}, -10) == std::vector<int>{2, 3}); }
    SUBCASE("negative and positive cancel") { CHECK(twoSum({-7, -2, 3, 7, 10}, 0) == std::vector<int>{1, 4}); }
    SUBCASE("duplicates") { CHECK(twoSum({1, 1, 3}, 2) == std::vector<int>{1, 2}); }
    SUBCASE("duplicate pair in the middle") { CHECK(twoSum({1, 4, 4, 9}, 8) == std::vector<int>{2, 3}); }
    SUBCASE("answer at the two ends") { CHECK(twoSum({1, 3, 4, 6, 8, 11}, 12) == std::vector<int>{1, 6}); }
    SUBCASE("answer at the start") { CHECK(twoSum({1, 2, 10, 20, 30}, 3) == std::vector<int>{1, 2}); }
    SUBCASE("answer at the end") { CHECK(twoSum({1, 2, 10, 20, 30}, 50) == std::vector<int>{4, 5}); }
    SUBCASE("extreme values") { CHECK(twoSum({-1'000'000'000, 0, 1'000'000'000}, 0) == std::vector<int>{1, 3}); }
    SUBCASE("both extremes sum") {
        CHECK(twoSum({-1'000'000'000, -3, 5, 1'000'000'000, 1'000'000'000}, 2'000'000'000) == std::vector<int>{4, 5});
    }
}

TEST_CASE("randomized vs brute force") {
    int made = 0;
    while (made < 300) {
        std::vector<int> v = rand_vec(rand_int(2, 25), -30, 30);
        std::sort(v.begin(), v.end());
        const int n = static_cast<int>(v.size());
        const int target = rand_int(-60, 60);
        // The problem promises exactly one pair; skip inputs with zero or several.
        std::vector<int> expected;
        int count = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (v[i] + v[j] == target) {
                    ++count;
                    expected = {i + 1, j + 1};
                }
        if (count != 1) continue;
        ++made;
        CHECK(twoSum(v, target) == expected);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Multiples of 4, except the two middle positions hold 4m-3 and 4m+1 (still sorted).
    // Their sum is 8m-2 (= 2 mod 4); no other pair can reach it, so the answer is unique
    // and an O(n^2) pair scan does ~4.5·10^10 checks.
    const int n = 300'000, m = n / 2;
    std::vector<int> v(n);
    for (int k = 0; k < n; ++k) v[k] = 4 * k;
    v[m - 1] = 4 * (m - 1) + 1;
    v[m] = 4 * m + 1;
    CHECK(twoSum(v, 8 * m - 2) == std::vector<int>{m, m + 1});
}
