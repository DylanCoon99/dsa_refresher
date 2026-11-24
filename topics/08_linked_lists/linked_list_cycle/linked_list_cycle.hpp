#pragma once
#include <list_node.hpp>

// Return true if following next pointers from head ever revisits a node.
// Target: O(1) extra memory (Floyd's slow/fast pointers). Do not modify the list.
inline bool hasCycle(ListNode* head) {
    // TODO: implement



    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true;
        }
    }

    return false;
}
