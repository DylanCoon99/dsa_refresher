#include <level_order.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <vector>

using Rows = std::vector<std::vector<int>>;

namespace {
void bucket(const TreeNode* n, std::size_t depth, Rows& rows) {
    if (!n) return;
    if (rows.size() <= depth) rows.resize(depth + 1);
    bucket(n->left, depth + 1, rows);  // left before right keeps each row left to right
    rows[depth].push_back(n->val);
    bucket(n->right, depth + 1, rows);
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
    CHECK(levelOrder(build_tree({3, 9, 20, null, null, 15, 7})) == Rows{{3}, {9, 20}, {15, 7}});
    CHECK(levelOrder(build_tree({1})) == Rows{{1}});
    CHECK(levelOrder(nullptr) == Rows{});
}

TEST_CASE("edge cases") {
    SUBCASE("empty tree gives no rows") { CHECK(levelOrder(nullptr).empty()); }
    SUBCASE("single node") { CHECK(levelOrder(build_tree({-8})) == Rows{{-8}}); }
    SUBCASE("unbalanced: left chain") {
        CHECK(levelOrder(build_tree({1, 2, null, 3, null, 4})) == Rows{{1}, {2}, {3}, {4}});
    }
    SUBCASE("unbalanced: gaps inside a level") {
        // Level 2 holds 4 (child of 2) and 5 (child of 3), in that order.
        CHECK(levelOrder(build_tree({1, 2, 3, 4, null, null, 5, 6, null, null, 7})) ==
              Rows{{1}, {2, 3}, {4, 5}, {6, 7}});
    }
    SUBCASE("right chain of 1000 nodes has 1000 rows") {
        Rows r = levelOrder(build_chain(1000));
        REQUIRE(r.size() == 1000);
        CHECK(r[0] == std::vector<int>{0});
        CHECK(r[999] == std::vector<int>{999});
    }
}

TEST_CASE("randomized vs depth bucketing") {
    for (int trial = 0; trial < 200; ++trial) {
        TreeNode* t = random_tree(rand_int(0, 40), -20, 20);
        Rows expected;
        bucket(t, 0, expected);
        CHECK(levelOrder(t) == expected);
    }
}
