#pragma once
#include <tree_node.hpp>

#include <vector>

// Approach: iterative inorder traversal with an explicit stack; stop when the k-th node is popped.
// Key insight: a BST's inorder sequence is sorted, so the k-th node visited is the k-th smallest.
// Time: O(h + k)  Space: O(h)
// Brute force: full inorder traversal into a vector, then index k - 1, O(n) time and space.
inline int kthSmallest(TreeNode* root, int k) {
    std::vector<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push_back(cur); cur = cur->left; }
        cur = st.back();
        st.pop_back();
        if (--k == 0) return cur->val;
        cur = cur->right;
    }
    return -1;  // not reached when 1 <= k <= n
}
