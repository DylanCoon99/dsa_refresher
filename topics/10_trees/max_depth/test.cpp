#include <max_depth.hpp>

#include <doctest.h>
#include <tree_node.hpp>

TEST_CASE("examples") {
    CHECK(maxDepth(build_tree({3, 9, 20, null, null, 15, 7})) == 3);
    CHECK(maxDepth(build_tree({1, null, 2})) == 2);
    CHECK(maxDepth(nullptr) == 0);
}

TEST_CASE("edge cases") {
    SUBCASE("single node") { CHECK(maxDepth(build_tree({-4})) == 1); }
    SUBCASE("uneven tree, deepest path is 1-2-4-6-7") {
        CHECK(maxDepth(build_tree({1, 2, 3, 4, null, null, 5, 6, null, null, null, 7})) == 5);
    }
    SUBCASE("right-skewed tree of 1000 nodes") { CHECK(maxDepth(build_chain(1000)) == 1000); }
    SUBCASE("left-skewed tree of 1000 nodes") {
        TreeNode* root = nullptr;
        for (int i = 0; i < 1000; ++i) root = new TreeNode(i, root, nullptr);
        CHECK(maxDepth(root) == 1000);
    }
    SUBCASE("zigzag tree of 500 nodes") {
        TreeNode* root = new TreeNode(0);
        TreeNode* cur = root;
        for (int i = 1; i < 500; ++i) {
            TreeNode* next = new TreeNode(i);
            (i % 2 ? cur->left : cur->right) = next;
            cur = next;
        }
        CHECK(maxDepth(root) == 500);
    }
}

TEST_CASE("balanced tree") {
    std::vector<int> vals(1023);
    for (int i = 0; i < 1023; ++i) vals[i] = i;
    CHECK(maxDepth(build_balanced_bst(vals)) == 10);  // perfect tree with 2^10 - 1 nodes
}
