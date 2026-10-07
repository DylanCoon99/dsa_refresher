#pragma once
#include <cstddef>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// Tests never free nodes: solutions may delete nodes they remove.
inline ListNode* build_list(const std::vector<int>& vals) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

// The tail links back to the node at index `pos`; pos = -1 means no cycle.
inline ListNode* build_list_with_cycle(const std::vector<int>& vals, int pos) {
    ListNode* head = build_list(vals);
    if (pos < 0 || head == nullptr) return head;
    ListNode* target = head;
    for (int i = 0; i < pos; ++i) target = target->next;
    ListNode* tail = head;
    while (tail->next) tail = tail->next;
    tail->next = target;
    return head;
}

// Throws past `limit` nodes, so a list a buggy solution made cyclic fails the test instead of hanging it.
inline std::vector<int> to_vector(const ListNode* head, std::size_t limit = 1'000'000) {
    std::vector<int> out;
    for (; head != nullptr; head = head->next) {
        if (out.size() == limit) throw std::runtime_error("list exceeds node limit (cycle?)");
        out.push_back(head->val);
    }
    return out;
}

struct RandomListNode {
    int val;
    RandomListNode* next;
    RandomListNode* random;
    explicit RandomListNode(int x) : val(x), next(nullptr), random(nullptr) {}
};

// Each entry is {value, index of the random target or -1}.
inline RandomListNode* build_random_list(const std::vector<std::pair<int, int>>& spec) {
    std::vector<RandomListNode*> nodes;
    for (const auto& entry : spec) nodes.push_back(new RandomListNode(entry.first));
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (i + 1 < nodes.size()) nodes[i]->next = nodes[i + 1];
        if (spec[i].second >= 0) nodes[i]->random = nodes[spec[i].second];
    }
    return nodes.empty() ? nullptr : nodes[0];
}

// Inverse of build_random_list. A random pointer to a node outside the list becomes -2.
inline std::vector<std::pair<int, int>> to_random_spec(const RandomListNode* head,
                                                       std::size_t limit = 1'000'000) {
    std::vector<const RandomListNode*> nodes;
    std::unordered_map<const RandomListNode*, int> index;
    for (; head != nullptr; head = head->next) {
        if (nodes.size() == limit) throw std::runtime_error("list exceeds node limit (cycle?)");
        index[head] = static_cast<int>(nodes.size());
        nodes.push_back(head);
    }
    std::vector<std::pair<int, int>> out;
    for (const RandomListNode* n : nodes) {
        int r = -1;
        if (n->random) {
            auto it = index.find(n->random);
            r = it == index.end() ? -2 : it->second;
        }
        out.emplace_back(n->val, r);
    }
    return out;
}
