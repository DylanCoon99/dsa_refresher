#include <linked_list_cycle.hpp>

#include <doctest.h>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <unordered_set>
#include <vector>

TEST_CASE("examples") {
    CHECK(hasCycle(build_list_with_cycle({3, 2, 0, -4}, 1)) == true);
    CHECK(hasCycle(build_list_with_cycle({1, 2}, 0)) == true);
    CHECK(hasCycle(build_list_with_cycle({1}, -1)) == false);
}

TEST_CASE("edge cases") {
    SUBCASE("empty list") { CHECK(hasCycle(nullptr) == false); }
    SUBCASE("single node without cycle") { CHECK(hasCycle(build_list({1})) == false); }
    SUBCASE("single node pointing to itself") { CHECK(hasCycle(build_list_with_cycle({1}, 0)) == true); }
    SUBCASE("cycle through the head") { CHECK(hasCycle(build_list_with_cycle({1, 2, 3, 4, 5}, 0)) == true); }
    SUBCASE("cycle starting in the middle") { CHECK(hasCycle(build_list_with_cycle({1, 2, 3, 4, 5, 6}, 3)) == true); }
    SUBCASE("tail points to itself") { CHECK(hasCycle(build_list_with_cycle({1, 2, 3, 4}, 3)) == true); }
    SUBCASE("no cycle, even and odd lengths") {
        CHECK(hasCycle(build_list({1, 2})) == false);
        CHECK(hasCycle(build_list({1, 2, 3})) == false);
        CHECK(hasCycle(build_list({1, 2, 3, 4})) == false);
    }
    SUBCASE("equal values do not make a cycle") { CHECK(hasCycle(build_list({7, 7, 7, 7})) == false); }
    SUBCASE("the list is not modified") {
        ListNode* head = build_list_with_cycle({1, 2, 3}, 1);
        hasCycle(head);
        CHECK(head->val == 1);
        CHECK(head->next->val == 2);
        CHECK(head->next->next->val == 3);
        CHECK(head->next->next->next == head->next);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> vals = rand_vec(rand_int(0, 20), 0, 5);
        int pos = vals.empty() ? -1 : rand_int(-1, static_cast<int>(vals.size()) - 1);
        ListNode* head = build_list_with_cycle(vals, pos);
        // Brute force: a visited set of node addresses.
        std::unordered_set<ListNode*> seen;
        bool expected = false;
        for (ListNode* p = head; p != nullptr; p = p->next) {
            if (!seen.insert(p).second) {
                expected = true;
                break;
            }
        }
        CHECK(hasCycle(head) == expected);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    const int n = 1'000'000;
    ListNode* head = build_list(std::vector<int>(n, 1));
    ListNode* tail = head;
    while (tail->next) tail = tail->next;
    tail->next = head;  // cycle through the head
    CHECK(hasCycle(head) == true);
    tail->next = nullptr;  // same nodes, no cycle
    CHECK(hasCycle(head) == false);
}
