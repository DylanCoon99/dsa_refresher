#include <build_tree_pre_in.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
void pre_of(const TreeNode* n, std::vector<int>& out) {
    if (!n) return;
    out.push_back(n->val);
    pre_of(n->left, out);
    pre_of(n->right, out);
}
void in_of(const TreeNode* n, std::vector<int>& out) {
    if (!n) return;
    in_of(n->left, out);
    out.push_back(n->val);
    in_of(n->right, out);
}
// Random tree shape with n nodes; values are a random permutation of distinct numbers.
TreeNode* random_distinct_tree(int n) {
    if (n == 0) return nullptr;
    std::vector<int> vals(n);
    std::iota(vals.begin(), vals.end(), -n / 2);
    std::shuffle(vals.begin(), vals.end(), rng());
    std::vector<TreeNode*> nodes;
    TreeNode* root = new TreeNode(vals[0]);
    nodes.push_back(root);
    while (static_cast<int>(nodes.size()) < n) {
        TreeNode* p = nodes[rand_int(0, static_cast<int>(nodes.size()) - 1)];
        TreeNode*& slot = rand_int(0, 1) ? p->left : p->right;
        if (slot) continue;
        slot = new TreeNode(vals[nodes.size()]);
        nodes.push_back(slot);
    }
    return root;
}
using V = std::vector<int>;
}  // namespace

TEST_CASE("examples") {
    CHECK(to_level_order(buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7})) ==
          LevelOrder{3, 9, 20, null, null, 15, 7});
    CHECK(to_level_order(buildTree({1}, {1})) == LevelOrder{1});
    CHECK(to_level_order(buildTree({1, 2, 3}, {3, 2, 1})) == LevelOrder{1, 2, null, 3});
}

TEST_CASE("edge cases") {
    SUBCASE("empty input") { CHECK(buildTree({}, {}) == nullptr); }
    SUBCASE("single node") {
        TreeNode* t = buildTree({-5}, {-5});
        REQUIRE(t != nullptr);
        CHECK(t->val == -5);
        CHECK(t->left == nullptr);
        CHECK(t->right == nullptr);
    }
    SUBCASE("left-only chain") {
        CHECK(to_level_order(buildTree({1, 2, 3, 4}, {4, 3, 2, 1})) ==
              LevelOrder{1, 2, null, 3, null, 4});
    }
    SUBCASE("right-only chain") {
        CHECK(to_level_order(buildTree({1, 2, 3, 4}, {1, 2, 3, 4})) ==
              LevelOrder{1, null, 2, null, 3, null, 4});
    }
    SUBCASE("zigzag") {
        // 1 -> right 2 -> left 3 -> right 4
        CHECK(to_level_order(buildTree({1, 2, 3, 4}, {1, 3, 4, 2})) ==
              LevelOrder{1, null, 2, 3, null, null, 4});
    }
    SUBCASE("extreme values") {
        CHECK(to_level_order(buildTree({0, -2147483647 - 1, 2147483647}, {-2147483647 - 1, 0, 2147483647})) ==
              LevelOrder{0, -2147483647 - 1, 2147483647});
    }
}

TEST_CASE("randomized round trip") {
    for (int trial = 0; trial < 200; ++trial) {
        TreeNode* t = random_distinct_tree(rand_int(0, 30));
        V pre, in;
        pre_of(t, pre);
        in_of(t, in);
        CHECK(to_level_order(buildTree(pre, in)) == to_level_order(t));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Balanced tree of 10^5 nodes (depth about 17), so recursion is fine.
    const int n = 100'000;
    V vals(n);
    std::iota(vals.begin(), vals.end(), 0);
    TreeNode* t = build_balanced_bst(vals);
    V pre, in;
    pre_of(t, pre);
    in_of(t, in);
    TreeNode* rebuilt = buildTree(pre, in);
    REQUIRE(rebuilt != nullptr);
    INFO("rebuilt tree differs from the original (level order not printed: 10^5 values)");
    CHECK((to_level_order(rebuilt) == to_level_order(t)));
}
