#include <serialize_tree.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <string>
#include <vector>

namespace {
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
// Full check for one tree: round trip keeps shape and values, serialize is canonical and non-mutating.
void check_round_trip(TreeNode* t) {
    LevelOrder before = to_level_order(t);
    std::string s = serialize(t);
    CHECK(to_level_order(t) == before);  // serialize must not modify the tree
    TreeNode* back = deserialize(s);
    CHECK(to_level_order(back) == before);
    CHECK(serialize(back) == s);
}
}  // namespace

TEST_CASE("examples") {
    check_round_trip(build_tree({1, 2, 3, null, null, 4, 5}));
    CHECK(deserialize(serialize(nullptr)) == nullptr);
    CHECK(serialize(build_tree({1, 2})) != serialize(build_tree({1, null, 2})));
}

TEST_CASE("edge cases") {
    SUBCASE("empty tree") {
        std::string s = serialize(nullptr);
        CHECK(deserialize(s) == nullptr);
        CHECK(serialize(deserialize(s)) == s);
    }
    SUBCASE("single node") { check_round_trip(build_tree({0})); }
    SUBCASE("negative values") { check_round_trip(build_tree({-1, -2, -3, null, -4, -5, -6})); }
    SUBCASE("INT_MIN and INT_MAX") {
        check_round_trip(build_tree({-2147483647 - 1, 2147483647, -2147483647 - 1, null, 2147483647}));
        TreeNode* t = deserialize(serialize(build_tree({-2147483647 - 1})));
        REQUIRE(t != nullptr);
        CHECK(t->val == -2147483647 - 1);
    }
    SUBCASE("different shapes with the same values give different strings") {
        CHECK(serialize(build_tree({1, 2})) != serialize(build_tree({1, null, 2})));
        CHECK(serialize(build_tree({1, 2, 3})) != serialize(build_tree({1, 2, null, 3})));
        CHECK(serialize(build_tree({1})) != serialize(nullptr));
    }
    SUBCASE("repeated values") { check_round_trip(build_tree({7, 7, 7, 7, null, 7, 7})); }
    SUBCASE("chains of 1000 nodes") {
        check_round_trip(build_chain(1000));
        TreeNode* left = nullptr;
        for (int i = 0; i < 1000; ++i) left = new TreeNode(i, left, nullptr);
        check_round_trip(left);
    }
    SUBCASE("deserialize returns independent nodes") {
        TreeNode* t = build_tree({1, 2, 3});
        TreeNode* back = deserialize(serialize(t));
        REQUIRE(back != nullptr);
        CHECK(back != t);
        back->val = 99;
        CHECK(t->val == 1);
    }
}

TEST_CASE("randomized round trips") {
    for (int trial = 0; trial < 300; ++trial) {
        int range = rand_int(0, 1) ? 5 : 1'000'000;
        check_round_trip(random_tree(rand_int(0, 40), -range, range));
    }
}
