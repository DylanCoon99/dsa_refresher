#pragma once
#include <list_node.hpp>

// Approach: Floyd's tortoise and hare; slow moves 1 step, fast moves 2.
// Key insight: inside a cycle the fast pointer gains one node per step on the slow one, so they must meet.
// Time: O(n)  Space: O(1)
// Brute force: a hash set of visited node addresses, O(n) space.
inline bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
