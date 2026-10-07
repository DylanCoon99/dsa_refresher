#pragma once
#include <cstddef>
#include <optional>
#include <queue>
#include <stdexcept>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x = 0, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(x), left(l), right(r) {}
};

inline constexpr std::nullopt_t null = std::nullopt;
using LevelOrder = std::vector<std::optional<int>>;

// Builds a tree from level order with null gaps, e.g. {3, 9, 20, null, null, 15, 7}.
inline TreeNode* build_tree(const LevelOrder& vals) {
    if (vals.empty() || !vals[0]) return nullptr;
    TreeNode* root = new TreeNode(*vals[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    std::size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode* node = q.front();
        q.pop();
        if (i < vals.size() && vals[i]) { node->left = new TreeNode(*vals[i]); q.push(node->left); }
        ++i;
        if (i < vals.size() && vals[i]) { node->right = new TreeNode(*vals[i]); q.push(node->right); }
        ++i;
    }
    return root;
}

// Inverse of build_tree with trailing nulls trimmed. Throws past `limit` nodes (cycle guard).
inline LevelOrder to_level_order(const TreeNode* root, std::size_t limit = 1'000'000) {
    LevelOrder out;
    std::queue<const TreeNode*> q;
    q.push(root);
    std::size_t seen = 0;
    while (!q.empty()) {
        const TreeNode* n = q.front();
        q.pop();
        if (!n) { out.push_back(null); continue; }
        if (++seen > limit) throw std::runtime_error("tree exceeds node limit (cycle?)");
        out.push_back(n->val);
        q.push(n->left);
        q.push(n->right);
    }
    while (!out.empty() && !out.back()) out.pop_back();
    return out;
}

// First node with value `val` in level order, or nullptr.
inline TreeNode* find_node(TreeNode* root, int val) {
    std::queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        if (n->val == val) return n;
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
    return nullptr;
}

// Right-leaning chain with values 0..n-1, for deep-recursion tests.
inline TreeNode* build_chain(int n) {
    TreeNode dummy;
    TreeNode* tail = &dummy;
    for (int i = 0; i < n; ++i) { tail->right = new TreeNode(i); tail = tail->right; }
    return dummy.right;
}

// Height-balanced BST from strictly increasing values.
inline TreeNode* build_balanced_bst(const std::vector<int>& sorted, int lo = 0, int hi = -2) {
    if (hi == -2) hi = static_cast<int>(sorted.size()) - 1;
    if (lo > hi) return nullptr;
    int mid = lo + (hi - lo) / 2;
    return new TreeNode(sorted[mid], build_balanced_bst(sorted, lo, mid - 1),
                        build_balanced_bst(sorted, mid + 1, hi));
}
