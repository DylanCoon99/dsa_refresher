#pragma once
#include <list_node.hpp>

// Reverse the list and return the new head. nullptr -> nullptr.
// Aim for the iterative form: 10^6 nodes is too deep for recursion in the Debug+ASan build.
inline ListNode* reverseList(ListNode* head) {
    // TODO: implement

    // if list is empty or size 1; return the list (it doesn't change)
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* prev = nullptr;
    ListNode* current = head;
    ListNode* next;
    //ListNode* temp;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }


    return prev;
}
