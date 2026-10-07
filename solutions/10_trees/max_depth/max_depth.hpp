#pragma once
#include <tree_node.hpp>

#include <algorithm>

// Approach: depth of a node is 1 plus the larger depth of its two subtrees; an empty tree has depth 0.
// Key insight: use the empty subtree as the base case so leaves need no special handling.
// Time: O(n)  Space: O(h)
// Brute force: level-order BFS counting levels is also O(n); there is no asymptotically slower natural approach.
inline int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}
