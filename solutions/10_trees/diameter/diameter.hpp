#pragma once
#include <tree_node.hpp>

#include <algorithm>

// Approach: one post-order pass returns each subtree's height (in nodes) and records the best left + right bend.
// Key insight: the longest path has a highest node, where it turns; its length is leftHeight + rightHeight.
// Time: O(n)  Space: O(h)
// Brute force: at every node compute both subtree heights from scratch, O(n log n) balanced / O(n^2) skewed (or BFS from every node, O(n^2)).
namespace diameter_detail {
inline int height(const TreeNode* n, int& best) {
    if (!n) return 0;
    int l = height(n->left, best);
    int r = height(n->right, best);
    best = std::max(best, l + r);
    return 1 + std::max(l, r);
}
}  // namespace diameter_detail

inline int diameterOfBinaryTree(TreeNode* root) {
    int best = 0;
    diameter_detail::height(root, best);
    return best;
}
