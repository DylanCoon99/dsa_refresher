#pragma once
#include <tree_node.hpp>

#include <utility>

// Approach: recursively mirror both subtrees, then swap the two child pointers.
// Key insight: mirroring a tree is mirroring each child subtree and swapping which side they hang on.
// Time: O(n)  Space: O(h)
// Brute force: collect values level by level and rebuild the reversed rows, O(n) extra space.
inline TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    TreeNode* l = invertTree(root->left);
    TreeNode* r = invertTree(root->right);
    root->left = r;
    root->right = l;
    return root;
}
