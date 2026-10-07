#pragma once
#include <tree_node.hpp>

// Approach: compare the two roots, then recurse on the left pair and the right pair.
// Key insight: "both empty" is equal, "exactly one empty" is different; only then compare values and recurse.
// Time: O(min(n, m))  Space: O(h)
// Brute force: serialize both trees with null markers and compare the strings, O(n + m) with extra space.
inline bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p || !q) return p == q;
    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
