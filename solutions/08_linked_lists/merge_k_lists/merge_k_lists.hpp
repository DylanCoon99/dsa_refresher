#pragma once
#include <list_node.hpp>

#include <functional>
#include <queue>
#include <vector>

// Approach: a min-heap holds the current head of each non-empty list; pop the smallest, append it, push its successor.
// Key insight: only k candidates compete for the next output node, and a heap picks the smallest in O(log k).
// Time: O(N log k)  Space: O(k)
// Brute force: merge the lists one by one into an accumulator, O(N * k) node steps.
inline ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    auto later = [](const ListNode* a, const ListNode* b) { return a->val > b->val; };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(later)> heap(later);
    for (ListNode* l : lists) {
        if (l != nullptr) heap.push(l);
    }
    ListNode dummy;
    ListNode* tail = &dummy;
    while (!heap.empty()) {
        ListNode* smallest = heap.top();
        heap.pop();
        tail->next = smallest;
        tail = smallest;
        if (smallest->next != nullptr) heap.push(smallest->next);
    }
    tail->next = nullptr;
    return dummy.next;
}
