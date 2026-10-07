#include <jump_game.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// Mark every index reachable from 0 by trying all jump lengths: obviously correct, O(n * max).
bool brute(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::vector<bool> ok(n, false);
    ok[0] = true;
    for (int i = 0; i < n; ++i) {
        if (!ok[i]) continue;
        for (int j = i; j <= i + nums[i] && j < n; ++j) ok[j] = true;
    }
    return ok[n - 1];
}
}  // namespace

TEST_CASE("examples") {
    CHECK(canJump({2, 3, 1, 1, 4}) == true);
    CHECK(canJump({3, 2, 1, 0, 4}) == false);
    CHECK(canJump({0}) == true);
}

TEST_CASE("edge cases") {
    SUBCASE("single element") {
        CHECK(canJump({0}) == true);
        CHECK(canJump({7}) == true);
    }
    SUBCASE("zero at the start with n > 1") {
        CHECK(canJump({0, 1}) == false);
        CHECK(canJump({0, 5, 5, 5}) == false);
    }
    SUBCASE("a zero you can jump over") {
        CHECK(canJump({2, 0, 1}) == true);
        CHECK(canJump({3, 0, 0, 1}) == true);
        CHECK(canJump({1, 3, 0, 0, 1}) == true);
    }
    SUBCASE("a zero you cannot jump over") {
        CHECK(canJump({1, 1, 0, 1}) == false);
        CHECK(canJump({2, 0, 0, 1}) == false);
    }
    SUBCASE("a zero on the last index is fine") { CHECK(canJump({1, 1, 0}) == true); }
    SUBCASE("exact jump to the end") { CHECK(canJump({4, 0, 0, 0, 0}) == true); }
    SUBCASE("a long jump overshoots the end") { CHECK(canJump({100, 0}) == true); }
    SUBCASE("a big jump early fixes a later gap") { CHECK(canJump({4, 1, 0, 0, 0, 1}) == false); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 400; ++trial) {
        const int n = rand_int(1, 12);
        const std::vector<int> v = rand_vec(n, 0, 3);
        INFO("trial " << trial);
        CHECK(canJump(v) == brute(v));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    const int n = 100000;
    // Every index can jump 10^4 ahead: the end is reachable.
    CHECK(canJump(std::vector<int>(n, 10000)) == true);

    // Same, but indices [50000, 60000) are zeros. Index 49999 reaches at most 59999 (a zero), and
    // nothing before it reaches further, so the end is unreachable.
    std::vector<int> blocked(n, 10000);
    for (int i = 50000; i < 60000; ++i) blocked[i] = 0;
    CHECK(canJump(blocked) == false);
}
