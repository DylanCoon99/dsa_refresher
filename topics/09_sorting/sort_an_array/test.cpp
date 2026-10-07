#include <sort_an_array.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <vector>

namespace {
using SortFn = void (*)(std::vector<int>&);

// Sort a copy with std::sort and compare. (A bool, so a failing large case does not print 2e5 numbers.)
void check_sorts(SortFn f, std::vector<int> a) {
    std::vector<int> expected = a;
    std::sort(expected.begin(), expected.end());
    f(a);
    const bool ok = (a == expected);
    CHECK(ok);
}

void small_cases(SortFn f) {
    SUBCASE("examples") {
        std::vector<int> a = {5, 2, 3, 1};
        f(a);
        CHECK(a == std::vector<int>{1, 2, 3, 5});
        std::vector<int> b = {5, 1, 1, 2, 0, 0};
        f(b);
        CHECK(b == std::vector<int>{0, 0, 1, 1, 2, 5});
    }
    SUBCASE("empty") {
        std::vector<int> a;
        f(a);
        CHECK(a.empty());
    }
    SUBCASE("one element") {
        std::vector<int> a = {42};
        f(a);
        CHECK(a == std::vector<int>{42});
    }
    SUBCASE("two elements") {
        check_sorts(f, {2, 1});
        check_sorts(f, {1, 2});
    }
    SUBCASE("already sorted") { check_sorts(f, {1, 2, 3, 4, 5, 6, 7, 8}); }
    SUBCASE("reversed") { check_sorts(f, {9, 8, 7, 6, 5, 4, 3, 2, 1}); }
    SUBCASE("all equal") { check_sorts(f, std::vector<int>(17, 3)); }
    SUBCASE("INT_MIN and INT_MAX") {
        check_sorts(f, {INT_MAX, 0, INT_MIN, INT_MAX, -1, INT_MIN, 1});
        check_sorts(f, {INT_MAX, INT_MIN});
    }
    SUBCASE("500 random arrays against std::sort") {
        for (int trial = 0; trial < 500; ++trial) {
            // Narrow value range so duplicates are common.
            check_sorts(f, rand_vec(static_cast<std::size_t>(rand_int(0, 60)), -20, 20));
        }
    }
}

constexpr std::size_t kLarge = 200'000;
}  // namespace

TEST_CASE("mergeSort") { small_cases(mergeSort); }
TEST_CASE("quickSort") { small_cases(quickSort); }
TEST_CASE("heapSort") { small_cases(heapSort); }

TEST_CASE("large input: mergeSort" * doctest::timeout(2.0)) {
    check_sorts(mergeSort, rand_vec(kLarge, -1'000'000'000, 1'000'000'000));
}

TEST_CASE("large input: heapSort" * doctest::timeout(2.0)) {
    check_sorts(heapSort, rand_vec(kLarge, -1'000'000'000, 1'000'000'000));
}

TEST_CASE("large input: quickSort" * doctest::timeout(2.0)) {
    // Sorted and all-equal input make a fixed pivot with plain Lomuto quadratic (~4·10^10 steps).
    // (The random case also guarantees the stub, which leaves its input alone, fails here.)
    check_sorts(quickSort, rand_vec(kLarge, -1'000'000'000, 1'000'000'000));
    std::vector<int> sorted(kLarge);
    for (std::size_t i = 0; i < kLarge; ++i) sorted[i] = static_cast<int>(i);
    check_sorts(quickSort, sorted);
    check_sorts(quickSort, std::vector<int>(kLarge, 7));
}
