#include <diameter.hpp>

#include <doctest.h>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <vector>

TEST_CASE("examples") {
    CHECK(diameterOfBinaryTree(build_tree({1, 2, 3, 4, 5})) == 3);
    CHECK(diameterOfBinaryTree(build_tree({1, 2})) == 1);
    CHECK(diameterOfBinaryTree(build_tree({1})) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("empty tree") { CHECK(diameterOfBinaryTree(nullptr) == 0); }
    SUBCASE("single node") { CHECK(diameterOfBinaryTree(build_tree({42})) == 0); }
    SUBCASE("the longest path does not pass through the root") {
        // Root 1 has a short right side; the long path 8-6-4-2-5-7-9 hangs entirely below the left child.
        TreeNode* t = build_tree({1, 2, 3, 4, 5, null, null, 6, null, null, 7, 8, null, null, 9});
        CHECK(diameterOfBinaryTree(t) == 6);
    }
    SUBCASE("chain") { CHECK(diameterOfBinaryTree(build_chain(1000)) == 999); }
    SUBCASE("path bends at the root") {
        CHECK(diameterOfBinaryTree(build_tree({1, 2, 3, 4, null, null, 5, 6, null, null, 7})) == 6);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Balanced tree of 200000 nodes: the root's subtrees have 99999 and 100000 nodes, both 17 levels
    // deep, so the longest leaf-to-leaf path through the root has 17 + 17 = 34 edges.
    const int n = 200'000;
    std::vector<int> vals(n);
    for (int i = 0; i < n; ++i) vals[i] = i;
    CHECK(diameterOfBinaryTree(build_balanced_bst(vals)) == 34);
}
