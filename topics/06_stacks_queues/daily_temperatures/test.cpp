#include <daily_temperatures.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
std::vector<int> brute(const std::vector<int>& t) {
    const int n = static_cast<int>(t.size());
    std::vector<int> ans(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (t[j] > t[i]) {
                ans[i] = j - i;
                break;
            }
        }
    }
    return ans;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(dailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73}) == std::vector<int>{1, 1, 4, 2, 1, 1, 0, 0});
    CHECK(dailyTemperatures({30, 40, 50, 60}) == std::vector<int>{1, 1, 1, 0});
    CHECK(dailyTemperatures({5, 5, 6}) == std::vector<int>{2, 1, 0});
}

TEST_CASE("edge cases") {
    SUBCASE("single day") { CHECK(dailyTemperatures({70}) == std::vector<int>{0}); }
    SUBCASE("strictly decreasing gives all zeros") {
        CHECK(dailyTemperatures({90, 80, 70, 60}) == std::vector<int>{0, 0, 0, 0});
    }
    SUBCASE("equal temperatures are not warmer") {
        CHECK(dailyTemperatures({50, 50, 50}) == std::vector<int>{0, 0, 0});
        CHECK(dailyTemperatures({50, 50, 51, 50}) == std::vector<int>{2, 1, 0, 0});
    }
    SUBCASE("warmer day is far away") {
        CHECK(dailyTemperatures({60, 50, 50, 50, 50, 61}) == std::vector<int>{5, 4, 3, 2, 1, 0});
    }
    SUBCASE("zeros and large values") {
        CHECK(dailyTemperatures({0, 0, 1'000'000'000, 0}) == std::vector<int>{2, 1, 0, 0});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> t = rand_vec(rand_int(1, 40), 0, rand_int(1, 12));
        CAPTURE(t);
        CHECK(dailyTemperatures(t) == brute(t));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // n-1 strictly decreasing days followed by one very hot day: every earlier day waits until
    // the end, so a forward scan does ~5·10^9 steps.
    const int n = 100'000;
    std::vector<int> t;
    for (int i = 0; i < n - 1; ++i) t.push_back(500'000 - i);
    t.push_back(1'000'000'000);
    std::vector<int> want(n);
    for (int i = 0; i < n; ++i) want[i] = n - 1 - i;
    CHECK(dailyTemperatures(t) == want);
}
