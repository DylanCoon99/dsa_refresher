#include <reorder_list.hpp>

#include <doctest.h>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <cstddef>
#include <numeric>
#include <vector>

namespace {
// Brute-force expected order of indices: 0, n-1, 1, n-2, ...
std::vector<int> expected_order(int n) {
    std::vector<int> order;
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        order.push_back(lo++);
        if (lo <= hi) order.push_back(hi--);
    }
    return order;
}

// Builds a list, reorders it, then checks values AND node identity (same pointers, new order).
void check_reorder(const std::vector<int>& vals) {
    const int n = static_cast<int>(vals.size());
    ListNode* head = build_list(vals);
    std::vector<ListNode*> original;
    for (ListNode* p = head; p != nullptr; p = p->next) original.push_back(p);
    REQUIRE(static_cast<int>(original.size()) == n);

    reorderList(head);

    // Walk at most n + 1 steps so a cyclic result fails instead of hanging.
    std::vector<ListNode*> after;
    ListNode* p = head;
    while (p != nullptr && static_cast<int>(after.size()) <= n) {
        after.push_back(p);
        p = p->next;
    }
    REQUIRE(static_cast<int>(after.size()) == n);  // ends with nullptr after exactly n nodes
    CHECK(p == nullptr);
    std::vector<int> order = expected_order(n);
    for (int i = 0; i < n; ++i) {
        CHECK(after[i] == original[order[i]]);  // same node objects, expected order
        CHECK(after[i]->val == vals[order[i]]);
    }
}
}  // namespace

TEST_CASE("examples") {
    ListNode* a = build_list({1, 2, 3, 4});
    reorderList(a);
    CHECK(to_vector(a) == std::vector<int>{1, 4, 2, 3});
    ListNode* b = build_list({1, 2, 3, 4, 5});
    reorderList(b);
    CHECK(to_vector(b) == std::vector<int>{1, 5, 2, 4, 3});
}

TEST_CASE("edge cases") {
    SUBCASE("nullptr does not crash") { reorderList(nullptr); }
    SUBCASE("single node") {
        ListNode* h = build_list({9});
        reorderList(h);
        CHECK(to_vector(h) == std::vector<int>{9});
    }
    SUBCASE("two nodes unchanged") {
        ListNode* h = build_list({1, 2});
        reorderList(h);
        CHECK(to_vector(h) == std::vector<int>{1, 2});
    }
    SUBCASE("lengths 0 to 6 exhaustively, with node identity") {
        for (int n = 0; n <= 6; ++n) {
            std::vector<int> vals(n);
            std::iota(vals.begin(), vals.end(), 1);
            check_reorder(vals);
        }
    }
    SUBCASE("duplicate values still reuse the right nodes") { check_reorder({7, 7, 7, 7, 7}); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        check_reorder(rand_vec(rand_int(0, 50), -100, 100));
    }
}
