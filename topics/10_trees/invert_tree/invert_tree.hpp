#pragma once
#include <tree_node.hpp>

// Mirror the tree (swap left and right at every node) and return its root. nullptr -> nullptr.
inline TreeNode* invertTree(TreeNode* root) {
    // TODO: implement
    
    if (!root) {
        return nullptr;
    } else {
        TreeNode* temp = root->right;
        root->right = root->left;
        root->left = temp;
        invertTree(root->left);
        invertTree(root->right);
    }

    return root;

}
