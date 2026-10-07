#pragma once
#include <list_node.hpp>

// Approach: a dummy head and a tail pointer; repeatedly append the smaller front node, then the leftover list.
// Key insight: the dummy head removes the "first output node" special case.
// Time: O(n + m)  Space: O(1)
// Brute force: dump both lists into a vector, sort, rebuild: O((n+m) log(n+m)).
inline ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy;
    ListNode* tail = &dummy;
    while (list1 != nullptr && list2 != nullptr) {
        if (list2->val < list1->val) {
            tail->next = list2;
            list2 = list2->next;
        } else {
            tail->next = list1;
            list1 = list1->next;
        }
        tail = tail->next;
    }
    tail->next = list1 != nullptr ? list1 : list2;
    return dummy.next;
}
