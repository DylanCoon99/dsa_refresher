#pragma once
#include <tree_node.hpp>

#include <cstddef>
#include <queue>
#include <vector>

// Approach: BFS with a queue; at the start of each round, the queue holds exactly one level, so process that many nodes.
// Key insight: snapshot the queue size before the inner loop to separate levels.
// Time: O(n)  Space: O(w)
// Brute force: compute each node's depth recursively, then bucket values by depth (also O(n)).
inline std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> out;
    std::queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        std::size_t count = q.size();
        std::vector<int> row;
        for (std::size_t i = 0; i < count; ++i) {
            TreeNode* n = q.front();
            q.pop();
            row.push_back(n->val);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        out.push_back(row);
    }
    return out;
}
