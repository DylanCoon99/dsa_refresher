#pragma once
#include <list_node.hpp>

// Merge two non-decreasing lists into one non-decreasing list and return its head.
// Either argument may be nullptr.
inline ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    // TODO: implement

    ListNode dummy;
    ListNode* current = &dummy;

    while (list1 || list2) {
        if (list1 == nullptr) {
            current->next = list2;
            list2 = nullptr;
        }
        else if (list2 == nullptr) {
            current->next = list1;
            list1 = nullptr;
        }
        else {

            if (list1->val < list2->val) {
                current->next = list1;
                list1 = list1->next;
            } else {
                current->next = list2;
                list2 = list2->next;
            }

            current = current->next;

        }
        
    }
    
    return dummy.next;
}
