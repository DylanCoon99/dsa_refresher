#pragma once
#include <list_node.hpp>

// Approach: find the middle with slow/fast pointers, reverse the second half, then interleave the two halves.
// Key insight: "front, back, front, back" is just a merge of the first half with the reversed second half.
// Time: O(n)  Space: O(1)
// Brute force: store the node pointers in a vector and relink with two indices, O(n) space.
inline void reorderList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return;
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* second = slow->next;  // first node of the second half
    slow->next = nullptr;
    ListNode* prev = nullptr;
    while (second != nullptr) {
        ListNode* next = second->next;
        second->next = prev;
        prev = second;
        second = next;
    }
    ListNode* a = head;
    ListNode* b = prev;
    while (b != nullptr) {
        ListNode* an = a->next;
        ListNode* bn = b->next;
        a->next = b;
        b->next = an;
        a = an;
        b = bn;
    }
}
