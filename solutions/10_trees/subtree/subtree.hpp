#pragma once
#include <tree_node.hpp>

// Approach: for every node of root, test whether the tree rooted there is identical to subRoot.
// Key insight: "identical" must cover all descendants, and every node (not just the first one with a matching value) is a candidate.
// Time: O(n * m)  Space: O(h)
// Brute force: the same idea (n * m); serialization plus substring search gets O(n + m) but needs care with delimiters.
namespace subtree_detail {
inline bool same(const TreeNode* a, const TreeNode* b) {
    if (!a || !b) return a == b;
    return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
}
}  // namespace subtree_detail

inline bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return subRoot == nullptr;
    return subtree_detail::same(root, subRoot) || isSubtree(root->left, subRoot) ||
           isSubtree(root->right, subRoot);
}
