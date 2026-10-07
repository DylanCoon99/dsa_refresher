#include <reverse_linked_list.hpp>

#include <doctest.h>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

TEST_CASE("examples") {
    CHECK(to_vector(reverseList(build_list({1, 2, 3, 4, 5}))) == std::vector<int>{5, 4, 3, 2, 1});
    CHECK(to_vector(reverseList(build_list({1, 2}))) == std::vector<int>{2, 1});
    CHECK(reverseList(nullptr) == nullptr);
}

TEST_CASE("edge cases") {
    SUBCASE("one node") {
        ListNode* head = build_list({7});
        ListNode* r = reverseList(head);
        REQUIRE(r != nullptr);
        CHECK(r->val == 7);
        CHECK(r->next == nullptr);
    }
    SUBCASE("two nodes") {
        ListNode* r = reverseList(build_list({1, 2}));
        REQUIRE(r != nullptr);
        CHECK(r->val == 2);
        REQUIRE(r->next != nullptr);
        CHECK(r->next->val == 1);
        CHECK(r->next->next == nullptr);  // the old head must not keep pointing at the old tail
    }
    SUBCASE("duplicates and extreme values") {
        CHECK(to_vector(reverseList(build_list({4, 4, -2147483647 - 1, 2147483647, 4}))) ==
              std::vector<int>{4, 2147483647, -2147483647 - 1, 4, 4});
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> vals = rand_vec(rand_int(0, 30), -50, 50);
        std::vector<int> expected(vals.rbegin(), vals.rend());
        CHECK(to_vector(reverseList(build_list(vals))) == expected);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^6 nodes: a recursive reversal overflows the stack under ASan (reported as CRASH).
    const int n = 1'000'000;
    std::vector<int> vals(n);
    for (int i = 0; i < n; ++i) vals[i] = i;
    ListNode* r = reverseList(build_list(vals));
    REQUIRE(r != nullptr);
    CHECK(r->val == n - 1);
    std::reverse(vals.begin(), vals.end());
    CHECK(to_vector(r) == vals);
}
