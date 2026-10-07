#include <product_except_self.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

TEST_CASE("examples") {
    CHECK(productExceptSelf({1, 2, 3, 4}) == std::vector<int>{24, 12, 8, 6});
    CHECK(productExceptSelf({-1, 1, 0, -3, 3}) == std::vector<int>{0, 0, 9, 0, 0});
    CHECK(productExceptSelf({5, 2}) == std::vector<int>{2, 5});
}

TEST_CASE("edge cases") {
    SUBCASE("one zero") { CHECK(productExceptSelf({2, 0, 3}) == std::vector<int>{0, 6, 0}); }
    SUBCASE("two zeros: everything is 0") { CHECK(productExceptSelf({0, 4, 0, 5}) == std::vector<int>{0, 0, 0, 0}); }
    SUBCASE("negatives") { CHECK(productExceptSelf({-2, -3, 4}) == std::vector<int>{-12, -8, 6}); }
    SUBCASE("n = 2") {
        CHECK(productExceptSelf({0, 7}) == std::vector<int>{7, 0});
        CHECK(productExceptSelf({-4, 3}) == std::vector<int>{3, -4});
    }
    SUBCASE("all ones") { CHECK(productExceptSelf({1, 1, 1}) == std::vector<int>{1, 1, 1}); }
}

TEST_CASE("randomized vs brute force") {
    // n <= 6 keeps every product within 30^6 = 7.29e8 < INT_MAX, matching the contract.
    for (int trial = 0; trial < 400; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(2, 6), -30, 30);
        std::vector<int> want(nums.size());
        for (std::size_t i = 0; i < nums.size(); ++i) {
            long long p = 1;
            for (std::size_t j = 0; j < nums.size(); ++j)
                if (j != i) p *= nums[j];
            want[i] = static_cast<int>(p);
        }
        CHECK(productExceptSelf(nums) == want);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 values of +-1: every product is +-1, but an O(n^2) recomputation does ~10^10 multiplies.
    const int n = 100'000;
    std::vector<int> nums(n);
    int total = 1;
    for (int& x : nums) {
        x = rand_int(0, 1) ? 1 : -1;
        total *= x;
    }
    std::vector<int> want(n);
    for (int i = 0; i < n; ++i) want[i] = total * nums[i];  // total / nums[i] with nums[i] = +-1
    CHECK(productExceptSelf(nums) == want);
}
