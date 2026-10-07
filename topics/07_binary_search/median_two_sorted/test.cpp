#include <median_two_sorted.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

namespace {
// Concatenate, sort, take the middle. Exact: the sum of two ints fits in long long and /2.0 is exact.
double brute(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> all = a;
    all.insert(all.end(), b.begin(), b.end());
    std::sort(all.begin(), all.end());
    const std::size_t n = all.size();
    if (n % 2 == 1) return static_cast<double>(all[n / 2]);
    return static_cast<double>(static_cast<long long>(all[n / 2 - 1]) + all[n / 2]) / 2.0;
}
void check(const std::vector<int>& a, const std::vector<int>& b) {
    CAPTURE(a);
    CAPTURE(b);
    CHECK(findMedianSortedArrays(a, b) == brute(a, b));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(findMedianSortedArrays({1, 3}, {2}) == 2.0);
    CHECK(findMedianSortedArrays({1, 2}, {3, 4}) == 2.5);
    CHECK(findMedianSortedArrays({}, {5}) == 5.0);
}

TEST_CASE("edge cases") {
    SUBCASE("one array empty") {
        CHECK(findMedianSortedArrays({}, {1, 2, 3, 4}) == 2.5);
        CHECK(findMedianSortedArrays({7, 8, 9}, {}) == 8.0);
        CHECK(findMedianSortedArrays({}, {-2}) == -2.0);
    }
    SUBCASE("very different sizes") {
        std::vector<int> big;
        for (int i = 0; i < 100; ++i) big.push_back(i * 2);
        check({1}, big);
        check({1000}, big);
        check({-5}, big);
        check({3, 4}, big);
        check(big, {99, 101});
    }
    SUBCASE("all of nums1 < nums2") {
        CHECK(findMedianSortedArrays({1, 2, 3}, {10, 20, 30}) == 6.5);
        CHECK(findMedianSortedArrays({1, 2}, {10, 20, 30}) == 10.0);
        check({1, 2, 3, 4}, {5, 6});
    }
    SUBCASE("all of nums1 > nums2") {
        CHECK(findMedianSortedArrays({10, 20, 30}, {1, 2, 3}) == 6.5);
        check({5, 6}, {1, 2, 3, 4});
    }
    SUBCASE("odd and even totals") {
        CHECK(findMedianSortedArrays({1, 4, 7}, {2, 3}) == 3.0);
        CHECK(findMedianSortedArrays({1, 4, 7}, {2, 3, 9}) == 3.5);
    }
    SUBCASE("duplicates") {
        CHECK(findMedianSortedArrays({2, 2, 2}, {2, 2}) == 2.0);
        CHECK(findMedianSortedArrays({1, 1}, {1, 1}) == 1.0);
        check({1, 2, 2, 3}, {2, 2, 4});
    }
    SUBCASE("interleaved") {
        check({1, 3, 5, 7}, {2, 4, 6, 8});
        check({1, 3, 5, 7, 9}, {2, 4, 6, 8});
    }
    SUBCASE("extreme values: sum of the middle pair overflows int") {
        CHECK(findMedianSortedArrays({INT_MAX}, {INT_MAX}) == static_cast<double>(INT_MAX));
        CHECK(findMedianSortedArrays({INT_MIN}, {INT_MIN}) == static_cast<double>(INT_MIN));
        CHECK(findMedianSortedArrays({INT_MIN}, {INT_MAX}) == -0.5);
        CHECK(findMedianSortedArrays({INT_MAX - 1, INT_MAX}, {}) == static_cast<double>(INT_MAX) - 0.5);
    }
    SUBCASE("negatives") {
        check({-9, -5, -1}, {-7, -3});
        check({-4, -2}, {-3, 0, 5});
    }
}

TEST_CASE("randomized vs merge-and-take-the-middle") {
    for (int trial = 0; trial < 500; ++trial) {
        int m = rand_int(0, 15), n = rand_int(0, 15);
        if (m + n == 0) m = 1;
        std::vector<int> a = rand_vec(m, -30, 30), b = rand_vec(n, -30, 30);
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        check(a, b);
    }
    for (int trial = 0; trial < 100; ++trial) {   // lopsided sizes
        std::vector<int> a = rand_vec(rand_int(0, 2), -100, 100), b = rand_vec(rand_int(1, 60), -100, 100);
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        check(a, b);
        check(b, a);
    }
}
