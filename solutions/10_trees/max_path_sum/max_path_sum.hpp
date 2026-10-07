#pragma once
#include <tree_node.hpp>

#include <algorithm>
#include <climits>

// Approach: post-order; each node returns its best downward path sum (clamping negative child arms to 0) and records node + both arms as a candidate.
// Key insight: a path has a highest node; there it uses up to two downward arms, but it hands only one arm up to its parent.
// Time: O(n)  Space: O(h)
// Brute force: for every pair of nodes compute the path sum, O(n^2) pairs (each O(h) to sum).
namespace max_path_detail {
inline int down(const TreeNode* n, int& best) {
    if (!n) return 0;
    int l = std::max(0, down(n->left, best));
    int r = std::max(0, down(n->right, best));
    best = std::max(best, n->val + l + r);
    return n->val + std::max(l, r);
}
}  // namespace max_path_detail

inline int maxPathSum(TreeNode* root) {
    int best = INT_MIN;
    max_path_detail::down(root, best);
    return best;
}
