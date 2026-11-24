#pragma once
#include <algorithm>
#include <tree_node.hpp>

// Number of nodes on the longest root-to-leaf path. Empty tree -> 0.
inline int maxDepth(TreeNode* root) {
    // TODO: implement

    if (!root) {
        return 0;
    } else {
        return 1 + std::max(maxDepth(root->right), maxDepth(root->left));
    }

}
