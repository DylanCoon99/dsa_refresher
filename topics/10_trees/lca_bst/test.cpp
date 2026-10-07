#include <lca_bst.hpp>

#include <doctest.h>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <algorithm>
#include <vector>

namespace {
// Reference that ignores the BST property: root-to-node path by DFS, then the last shared node.
bool path_to(TreeNode* n, TreeNode* target, std::vector<TreeNode*>& path) {
    if (!n) return false;
    path.push_back(n);
    if (n == target) return true;
    if (path_to(n->left, target, path) || path_to(n->right, target, path)) return true;
    path.pop_back();
    return false;
}
TreeNode* brute_lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    std::vector<TreeNode*> a, b;
    path_to(root, p, a);
    path_to(root, q, b);
    TreeNode* ans = nullptr;
    for (std::size_t i = 0; i < a.size() && i < b.size() && a[i] == b[i]; ++i) ans = a[i];
    return ans;
}
}  // namespace

TEST_CASE("examples") {
    TreeNode* t = build_tree({6, 2, 8, 0, 4, 7, 9, null, null, 3, 5});
    CHECK(lowestCommonAncestor(t, find_node(t, 2), find_node(t, 8)) == find_node(t, 6));
    CHECK(lowestCommonAncestor(t, find_node(t, 2), find_node(t, 4)) == find_node(t, 2));
    CHECK(lowestCommonAncestor(t, find_node(t, 3), find_node(t, 5)) == find_node(t, 4));
}

TEST_CASE("edge cases") {
    TreeNode* t = build_tree({6, 2, 8, 0, 4, 7, 9, null, null, 3, 5});
    SUBCASE("p is an ancestor of q (either argument order)") {
        CHECK(lowestCommonAncestor(t, find_node(t, 6), find_node(t, 3)) == find_node(t, 6));
        CHECK(lowestCommonAncestor(t, find_node(t, 3), find_node(t, 6)) == find_node(t, 6));
        CHECK(lowestCommonAncestor(t, find_node(t, 4), find_node(t, 5)) == find_node(t, 4));
    }
    SUBCASE("p == q") {
        CHECK(lowestCommonAncestor(t, find_node(t, 5), find_node(t, 5)) == find_node(t, 5));
        CHECK(lowestCommonAncestor(t, find_node(t, 6), find_node(t, 6)) == find_node(t, 6));
    }
    SUBCASE("argument order does not matter") {
        CHECK(lowestCommonAncestor(t, find_node(t, 9), find_node(t, 0)) == find_node(t, 6));
        CHECK(lowestCommonAncestor(t, find_node(t, 0), find_node(t, 9)) == find_node(t, 6));
        CHECK(lowestCommonAncestor(t, find_node(t, 7), find_node(t, 9)) == find_node(t, 8));
    }
    SUBCASE("single node") {
        TreeNode* one = build_tree({5});
        CHECK(lowestCommonAncestor(one, one, one) == one);
    }
    SUBCASE("negative values") {
        TreeNode* n = build_tree({-1, -5, 3, -7, -3});
        CHECK(lowestCommonAncestor(n, find_node(n, -7), find_node(n, -3)) == find_node(n, -5));
        CHECK(lowestCommonAncestor(n, find_node(n, -7), find_node(n, 3)) == find_node(n, -1));
    }
}

TEST_CASE("randomized vs path comparison") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 60);
        std::vector<int> vals;
        for (int i = 0, v = rand_int(-50, 0); i < n; ++i, v += rand_int(1, 5)) vals.push_back(v);
        TreeNode* t = build_balanced_bst(vals);
        TreeNode* p = find_node(t, vals[rand_int(0, n - 1)]);
        TreeNode* q = find_node(t, vals[rand_int(0, n - 1)]);
        REQUIRE(p != nullptr);
        REQUIRE(q != nullptr);
        CHECK(lowestCommonAncestor(t, p, q) == brute_lca(t, p, q));
    }
}
