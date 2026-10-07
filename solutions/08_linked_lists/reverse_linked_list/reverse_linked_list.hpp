#pragma once
#include <list_node.hpp>

// Approach: walk the list once, pointing each node's next at the node before it.
// Key insight: save next before overwriting it; the reversed prefix grows by one node per step.
// Time: O(n)  Space: O(1)
// Brute force: copy values into a vector and rewrite them reversed, O(n) space; recursion uses O(n) stack and overflows at 10^6.
inline ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head != nullptr) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}
