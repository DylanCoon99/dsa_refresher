#pragma once
#include <tree_node.hpp>

#include <string>

// Encode a tree as a string, and rebuild it. Any format works, but it must be canonical:
// deserialize(serialize(t)) has t's shape and values, and serialize(deserialize(s)) == s.
inline std::string serialize(TreeNode* root) {
    // TODO: implement
    return "";
}
inline TreeNode* deserialize(const std::string& data) {
    // TODO: implement
    return nullptr;
}
