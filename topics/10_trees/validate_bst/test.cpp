#include <validate_bst.hpp>

#include <doctest.h>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <vector>

namespace {
void inorder_vals(const TreeNode* n, std::vector<int>& out) {
    if (!n) return;
    inorder_vals(n->left, out);
    out.push_back(n->val);
    inorder_vals(n->right, out);
}
// Reference: a tree is a strict BST exactly when its inorder sequence is strictly increasing.
bool brute_valid(const TreeNode* root) {
    std::vector<int> v;
    inorder_vals(root, v);
    for (std::size_t i = 1; i < v.size(); ++i)
        if (v[i - 1] >= v[i]) return false;
    return true;
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
// Random valid BST: random distinct sorted values, then a random shape by recursive random split.
TreeNode* random_bst(const std::vector<int>& sorted, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = rand_int(lo, hi);
    return new TreeNode(sorted[mid], random_bst(sorted, lo, mid - 1), random_bst(sorted, mid + 1, hi));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(isValidBST(build_tree({2, 1, 3})) == true);
    CHECK(isValidBST(build_tree({5, 1, 4, null, null, 3, 6})) == false);
    CHECK(isValidBST(build_tree({2, 2, 3})) == false);
}

TEST_CASE("edge cases") {
    SUBCASE("empty tree and single node") {
        CHECK(isValidBST(nullptr) == true);
        CHECK(isValidBST(build_tree({0})) == true);
    }
    SUBCASE("grandchild breaks the root's bound") {
        CHECK(isValidBST(build_tree({5, 1, 4, null, null, 3, 6})) == false);
        CHECK(isValidBST(build_tree({10, 5, 15, null, null, 6, 20})) == false);  // 6 < 10 in the right subtree
        CHECK(isValidBST(build_tree({10, 5, 15, 2, 12})) == false);              // 12 > 10 in the left subtree
    }
    SUBCASE("a node equal to its parent") {
        CHECK(isValidBST(build_tree({1, 1})) == false);
        CHECK(isValidBST(build_tree({1, null, 1})) == false);
        CHECK(isValidBST(build_tree({2, 2, 3})) == false);
    }
    SUBCASE("a node equal to an ancestor, not its parent") {
        CHECK(isValidBST(build_tree({5, 4, 6, null, null, 5, 7})) == false);
        CHECK(isValidBST(build_tree({5, 3, 8, 1, 5})) == false);
    }
    SUBCASE("valid trees") {
        CHECK(isValidBST(build_tree({3, 1, 5, 0, 2, 4, 6})) == true);
        CHECK(isValidBST(build_tree({5, 3, 8, null, 4, 6})) == true);
        CHECK(isValidBST(build_tree({1, null, 2, null, 3})) == true);
    }
    SUBCASE("INT_MIN and INT_MAX values") {
        CHECK(isValidBST(build_tree({2147483647})) == true);
        CHECK(isValidBST(build_tree({-2147483647 - 1})) == true);
        CHECK(isValidBST(build_tree({-2147483647 - 1, null, 2147483647})) == true);
        CHECK(isValidBST(build_tree({0, -2147483647 - 1, 2147483647})) == true);
        CHECK(isValidBST(build_tree({2147483647, 2147483647})) == false);
        CHECK(isValidBST(build_tree({-2147483647 - 1, -2147483647 - 1})) == false);
        CHECK(isValidBST(build_tree({2147483647, null, 2147483647})) == false);
    }
    SUBCASE("skewed trees of 1000 nodes") {
        CHECK(isValidBST(build_chain(1000)) == true);  // 0, 1, 2, ... going right
        TreeNode* bad = build_chain(1000);
        find_node(bad, 500)->val = 3;  // breaks the increasing order deep down
        CHECK(isValidBST(bad) == false);
    }
}

TEST_CASE("randomized vs inorder check") {
    for (int trial = 0; trial < 300; ++trial) {
        TreeNode* t = random_tree(rand_int(1, 8), 0, 6);
        CHECK(isValidBST(t) == brute_valid(t));
    }
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 25);
        std::vector<int> vals;
        for (int i = 0, v = rand_int(-30, 0); i < n; ++i, v += rand_int(1, 4)) vals.push_back(v);
        TreeNode* t = random_bst(vals, 0, n - 1);
        CHECK(isValidBST(t) == true);
        // Overwrite one random node with a random nearby value; compare with the reference.
        TreeNode* victim = find_node(t, vals[rand_int(0, n - 1)]);
        victim->val = rand_int(-30, 80);
        CHECK(isValidBST(t) == brute_valid(t));
    }
}
