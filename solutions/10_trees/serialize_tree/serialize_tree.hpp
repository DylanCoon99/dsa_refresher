#pragma once
#include <tree_node.hpp>

#include <cstddef>
#include <string>

// Approach: preorder with "#" for a missing child, tokens separated by commas; deserialize reads tokens in the same order.
// Key insight: null markers make the preorder alone unambiguous, so no inorder or level information is needed.
// Time: O(n)  Space: O(n)
// Brute force: store preorder and inorder separately and rebuild (needs distinct values and doubles the output).
namespace serialize_detail {
inline void write(const TreeNode* n, std::string& out) {
    if (!n) { out += "#,"; return; }
    out += std::to_string(n->val);
    out += ',';
    write(n->left, out);
    write(n->right, out);
}
inline TreeNode* read(const std::string& s, std::size_t& pos) {
    std::size_t comma = s.find(',', pos);
    std::string tok = s.substr(pos, comma - pos);
    pos = comma + 1;
    if (tok == "#") return nullptr;
    TreeNode* n = new TreeNode(std::stoi(tok));
    n->left = read(s, pos);
    n->right = read(s, pos);
    return n;
}
}  // namespace serialize_detail

inline std::string serialize(TreeNode* root) {
    std::string out;
    serialize_detail::write(root, out);
    return out;
}

inline TreeNode* deserialize(const std::string& data) {
    std::size_t pos = 0;
    return serialize_detail::read(data, pos);
}
