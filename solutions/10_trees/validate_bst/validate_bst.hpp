#pragma once
#include <tree_node.hpp>

// Approach: pass down the nearest nodes that bound the allowed range (as pointers) and check each value strictly against them.
// Key insight: every node is constrained by all of its ancestors, not just its parent; using bound nodes (not int sentinels) keeps INT_MIN/INT_MAX valid.
// Time: O(n)  Space: O(h)
// Brute force: for each node, scan its entire left and right subtrees for violations, O(n^2) on a skewed tree.
namespace validate_bst_detail {
inline bool valid(const TreeNode* n, const TreeNode* lo, const TreeNode* hi) {
    if (!n) return true;
    if (lo && n->val <= lo->val) return false;
    if (hi && n->val >= hi->val) return false;
    return valid(n->left, lo, n) && valid(n->right, n, hi);
}
}  // namespace validate_bst_detail

inline bool isValidBST(TreeNode* root) { return validate_bst_detail::valid(root, nullptr, nullptr); }
