#pragma once
#include <list_node.hpp>

// Approach: dummy head; advance `fast` n+1 steps ahead of `slow`, then move both until fast falls off; slow is just before the target.
// Key insight: keeping two pointers n apart finds the n-th from the end in one pass, and the dummy handles removing the head.
// Time: O(n)  Space: O(1)
// Brute force: count the length L, then walk to node L - n: two passes.
inline ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;
    for (int i = 0; i < n; ++i) fast = fast->next;
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* target = slow->next;
    slow->next = target->next;
    delete target;
    return dummy.next;
}
