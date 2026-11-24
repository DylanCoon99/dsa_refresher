#pragma once
#include <tree_node.hpp>

// True if both trees have the same shape and the same values. Two empty trees are the same.
inline bool isSameTree(TreeNode* p, TreeNode* q) {
    // TODO: implement

    if (p == NULL && q == NULL) {
        return true;
    }

    if ((p != NULL && q != NULL) && p->val == q->val) {
        return isSameTree(p->right, q->right) && isSameTree(p->left, q->left);
    } else {
        return false;
    }

}
