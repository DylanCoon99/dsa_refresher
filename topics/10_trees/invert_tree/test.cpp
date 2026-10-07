#include <invert_tree.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <vector>

namespace {
// Reference: build the mirror from scratch (never touches the input).
TreeNode* mirror_copy(const TreeNode* n) {
    if (!n) return nullptr;
    return new TreeNode(n->val, mirror_copy(n->right), mirror_copy(n->left));
}
TreeNode* random_tree(int n, int lo, int hi) {
    if (n == 0) return nullptr;
    std::vector<TreeNode*> nodes;
    TreeNode* root = new TreeNode(rand_int(lo, hi));
    nodes.push_back(root);
    while (static_cast<int>(nodes.size()) < n) {
        TreeNode* p = nodes[rand_int(0, static_cast<int>(nodes.size()) - 1)];
        TreeNode*& slot = rand_int(0, 1) ? p->left : p->right;
        if (slot) continue;
        slot = new TreeNode(rand_int(lo, hi));
        nodes.push_back(slot);
    }
    return root;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(to_level_order(invertTree(build_tree({4, 2, 7, 1, 3, 6, 9}))) ==
          LevelOrder{4, 7, 2, 9, 6, 3, 1});
    CHECK(to_level_order(invertTree(build_tree({1, 2}))) == LevelOrder{1, null, 2});
    CHECK(invertTree(nullptr) == nullptr);
}

TEST_CASE("edge cases") {
    SUBCASE("single node") {
        TreeNode* r = invertTree(build_tree({9}));
        REQUIRE(r != nullptr);
        CHECK(r->val == 9);
        CHECK(r->left == nullptr);
        CHECK(r->right == nullptr);
    }
    SUBCASE("asymmetric tree") {
        CHECK(to_level_order(invertTree(build_tree({1, 2, 3, null, 4, 5, null, null, null, 6}))) ==
              LevelOrder{1, 3, 2, null, 5, 4, null, null, 6});
    }
    SUBCASE("left chain becomes right chain") {
        CHECK(to_level_order(invertTree(build_tree({1, 2, null, 3, null, 4}))) ==
              LevelOrder{1, null, 2, null, 3, null, 4});
    }
}

TEST_CASE("randomized vs mirror copy") {
    for (int trial = 0; trial < 200; ++trial) {
        TreeNode* t = random_tree(rand_int(0, 30), -9, 9);
        TreeNode* expected = mirror_copy(t);
        CHECK(to_level_order(invertTree(t)) == to_level_order(expected));
    }
}

TEST_CASE("deep chain") {
    TreeNode* t = build_chain(1000);
    TreeNode* r = invertTree(t);
    int depth = 0;
    for (TreeNode* n = r; n; n = n->left) {
        CHECK(n->right == nullptr);
        CHECK(n->val == depth);
        ++depth;
    }
    CHECK(depth == 1000);
}
