#pragma once
#include <tree_node.hpp>

// Approach: walk down from the root; go left if both targets are smaller, right if both are larger; otherwise stop.
// Key insight: the BST ordering means the first node that separates (or equals) p and q is the lowest common ancestor.
// Time: O(h)  Space: O(1)
// Brute force: find the root-to-p and root-to-q paths in a generic tree and compare them, O(n).
inline TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* cur = root;
    while (cur) {
        if (p->val < cur->val && q->val < cur->val) cur = cur->left;
        else if (p->val > cur->val && q->val > cur->val) cur = cur->right;
        else return cur;
    }
    return nullptr;
}
