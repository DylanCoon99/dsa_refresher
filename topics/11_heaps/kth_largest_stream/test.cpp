#include <kth_largest_stream.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <functional>
#include <queue>
#include <vector>

TEST_CASE("examples") {
    KthLargest a(3, {4, 5, 8, 2});
    CHECK(a.add(3) == 4);
    CHECK(a.add(5) == 5);
    CHECK(a.add(10) == 5);
    CHECK(a.add(9) == 8);
    CHECK(a.add(4) == 8);

    KthLargest b(1, {});
    CHECK(b.add(-3) == -3);
    CHECK(b.add(-1) == -1);

    KthLargest c(3, {1, 2});
    CHECK(c.add(3) == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("nums shorter than k") {
        KthLargest kl(4, {10, 20, 30});
        CHECK(kl.add(5) == 5);
        CHECK(kl.add(25) == 10);
        CHECK(kl.add(1) == 10);
    }
    SUBCASE("empty nums with k = 1 tracks the maximum") {
        KthLargest kl(1, {});
        CHECK(kl.add(2) == 2);
        CHECK(kl.add(-7) == 2);
        CHECK(kl.add(9) == 9);
    }
    SUBCASE("negatives") {
        KthLargest kl(2, {-5, -1, -9});
        CHECK(kl.add(-3) == -3);
        CHECK(kl.add(-2) == -2);
        CHECK(kl.add(-10) == -2);
    }
    SUBCASE("duplicates count separately") {
        KthLargest kl(3, {5, 5});
        CHECK(kl.add(5) == 5);
        CHECK(kl.add(7) == 5);
        CHECK(kl.add(7) == 5);
        CHECK(kl.add(7) == 7);
    }
    SUBCASE("extreme values") {
        KthLargest kl(2, {INT_MIN});
        CHECK(kl.add(INT_MAX) == INT_MIN);
        CHECK(kl.add(INT_MAX) == INT_MAX);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int k = rand_int(1, 6);
        std::vector<int> nums = rand_vec(rand_int(k - 1, 10), -20, 20);
        KthLargest kl(k, nums);
        std::vector<int> model = nums;
        for (int step = 0; step < 20; ++step) {
            int v = rand_int(-20, 20);
            model.push_back(v);
            std::vector<int> sorted = model;
            std::sort(sorted.begin(), sorted.end(), std::greater<>());
            CHECK(kl.add(v) == sorted[static_cast<std::size_t>(k) - 1]);
        }
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // k = 10^4, 10^4 initial values, 10^5 adds. Expected answers come from a separate min-heap
    // model inside the test. Re-sorting on each add costs about 10^5 * 10^5 * log work.
    const int k = 10'000, adds = 100'000;
    std::vector<int> nums = rand_vec(k, -1'000'000, 1'000'000);
    std::vector<int> vals = rand_vec(adds, -1'000'000, 1'000'000);
    std::priority_queue<int, std::vector<int>, std::greater<>> model(nums.begin(), nums.end());
    while (model.size() > static_cast<std::size_t>(k)) model.pop();
    std::vector<int> expected;
    expected.reserve(adds);
    for (int v : vals) {
        if (v > model.top()) {
            model.pop();
            model.push(v);
        }
        expected.push_back(model.top());
    }

    KthLargest kl(k, nums);
    int mismatches = 0;
    for (int i = 0; i < adds; ++i)
        if (kl.add(vals[static_cast<std::size_t>(i)]) != expected[static_cast<std::size_t>(i)]) ++mismatches;
    CHECK(mismatches == 0);
}
