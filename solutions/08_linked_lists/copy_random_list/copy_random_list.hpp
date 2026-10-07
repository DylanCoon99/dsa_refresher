#pragma once
#include <list_node.hpp>

#include <unordered_map>

// Approach: first pass creates a copy of every node and records original -> copy in a hash map; second pass wires next and random through the map.
// Key insight: the map answers "which copy does this random pointer correspond to?" in O(1), instead of walking the list to find it.
// Time: O(n)  Space: O(n)
// Brute force: for each node, find its random target's index by walking from the head, then walk the copy to that index: O(n^2).
inline RandomListNode* copyRandomList(RandomListNode* head) {
    std::unordered_map<const RandomListNode*, RandomListNode*> copyOf;
    for (const RandomListNode* p = head; p != nullptr; p = p->next) copyOf[p] = new RandomListNode(p->val);
    for (const RandomListNode* p = head; p != nullptr; p = p->next) {
        RandomListNode* c = copyOf[p];
        c->next = p->next ? copyOf[p->next] : nullptr;
        c->random = p->random ? copyOf[p->random] : nullptr;
    }
    return head ? copyOf[head] : nullptr;
}
