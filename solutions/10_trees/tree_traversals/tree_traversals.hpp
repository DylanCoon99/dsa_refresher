#pragma once
#include <tree_node.hpp>

#include <queue>
#include <vector>

// Approach: DFS orders keep an explicit stack of pending nodes; level order uses a queue.
// Key insight: the call stack of the recursive walk is just a stack of "nodes I still owe a visit"; make it explicit.
// Time: O(n)  Space: O(h) stack (O(n) worst case), O(w) queue
// Brute force: the recursive versions, O(n) time but O(n) call-stack depth on a chain, which overflows at 10^5.
inline std::vector<int> preorderIterative(TreeNode* root) {
    std::vector<int> out;
    std::vector<TreeNode*> st;
    if (root) st.push_back(root);
    while (!st.empty()) {
        TreeNode* n = st.back();
        st.pop_back();
        out.push_back(n->val);
        if (n->right) st.push_back(n->right);
        if (n->left) st.push_back(n->left);
    }
    return out;
}

inline std::vector<int> inorderIterative(TreeNode* root) {
    std::vector<int> out;
    std::vector<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push_back(cur); cur = cur->left; }
        cur = st.back();
        st.pop_back();
        out.push_back(cur->val);
        cur = cur->right;
    }
    return out;
}

inline std::vector<int> postorderIterative(TreeNode* root) {
    std::vector<int> out;
    std::vector<TreeNode*> st;
    TreeNode* cur = root;
    TreeNode* last = nullptr;  // last node visited
    while (cur || !st.empty()) {
        while (cur) { st.push_back(cur); cur = cur->left; }
        TreeNode* top = st.back();
        if (top->right && top->right != last) {
            cur = top->right;
        } else {
            out.push_back(top->val);
            last = top;
            st.pop_back();
        }
    }
    return out;
}

inline std::vector<int> levelOrderFlat(TreeNode* root) {
    std::vector<int> out;
    std::queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        out.push_back(n->val);
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
    return out;
}
