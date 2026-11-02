#pragma once
#include <list_node.hpp>
#include <vector>
#include <deque>



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


// Merge k sorted lists (entries may be nullptr; the vector may be empty) into one sorted list.
// Return nullptr if there are no nodes. Target: O(N log k).
inline ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    // TODO: implement

    std::deque<ListNode*> dq(lists.begin(), lists.end());

    if (lists.size() == 0) {
        return nullptr;
    }

    while (dq.size() > 1) {
        // pick 2 lists; merge them together
        ListNode* list1 = dq.front();
        dq.pop_front();
        ListNode* list2 = dq.front();
        dq.pop_front();

        dq.push_back(mergeTwoLists(list1, list2));

    }

    return dq[0];
}
