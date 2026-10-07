#pragma once
#include <tree_node.hpp>

#include <unordered_map>
#include <vector>

// Approach: the next preorder value is the root; its inorder index splits the remaining range into left and right subtrees.
// Key insight: preorder fixes the root, inorder fixes the sizes of the two sides; recurse with index ranges and a value -> index map.
// Time: O(n)  Space: O(n) for the map plus O(h) recursion
// Brute force: std::find the root in the inorder slice and copy sub-vectors at every level (O(n log n) balanced, O(n^2) skewed).
namespace build_tree_detail {
struct Builder {
    const std::vector<int>& pre;
    std::unordered_map<int, int> pos;  // value -> index in inorder
    std::size_t next = 0;              // next preorder index to use as a root

    TreeNode* build(int lo, int hi) {  // inorder range [lo, hi]
        if (lo > hi) return nullptr;
        int val = pre[next++];
        TreeNode* node = new TreeNode(val);
        int mid = pos[val];
        node->left = build(lo, mid - 1);
        node->right = build(mid + 1, hi);
        return node;
    }
};
}  // namespace build_tree_detail

inline TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    build_tree_detail::Builder b{preorder, {}, 0};
    b.pos.reserve(inorder.size() * 2);
    for (std::size_t i = 0; i < inorder.size(); ++i) b.pos[inorder[i]] = static_cast<int>(i);
    return b.build(0, static_cast<int>(inorder.size()) - 1);
}
