#include <subtree.hpp>

#include <doctest.h>
#include <tree_node.hpp>

TEST_CASE("examples") {
    CHECK(isSubtree(build_tree({3, 4, 5, 1, 2}), build_tree({4, 1, 2})) == true);
    CHECK(isSubtree(build_tree({3, 4, 5, 1, 2, null, null, null, null, 0}), build_tree({4, 1, 2})) ==
          false);
    CHECK(isSubtree(build_tree({1, 1}), build_tree({1})) == true);
}

TEST_CASE("edge cases") {
    SUBCASE("subRoot equals root") {
        CHECK(isSubtree(build_tree({1, 2, 3}), build_tree({1, 2, 3})) == true);
    }
    SUBCASE("subRoot is a single leaf of root") {
        CHECK(isSubtree(build_tree({1, 2, 3}), build_tree({3})) == true);
        CHECK(isSubtree(build_tree({1, 2, 3}), build_tree({4})) == false);
    }
    SUBCASE("matching node has extra descendants below it") {
        // Node 2 in root has a child 9; subRoot is the bare node 2.
        CHECK(isSubtree(build_tree({1, 2, 3, 9}), build_tree({2})) == false);
        // Deeper: the extra descendant is a grandchild.
        CHECK(isSubtree(build_tree({1, 2, null, 3, null, 4}), build_tree({2, 3})) == false);
    }
    SUBCASE("subRoot larger than root") {
        CHECK(isSubtree(build_tree({1}), build_tree({1, 1})) == false);
    }
    SUBCASE("same values, different shape") {
        CHECK(isSubtree(build_tree({1, 2, 3}), build_tree({1, null, 2})) == false);
        CHECK(isSubtree(build_tree({5, 1, null, null, 2}), build_tree({1, 2})) == false);
    }
    SUBCASE("duplicate values: the first node with the value is not the match") {
        // root: 1 -> left 1 -> left 2.  subRoot: 1 -> left 2.  The root has value 1 but is not a match;
        // its left child is.
        CHECK(isSubtree(build_tree({1, 1, null, 2}), build_tree({1, 2})) == true);
        // No node matches 1 -> right 2 even though 1 and 2 both occur.
        CHECK(isSubtree(build_tree({1, 1, null, 2}), build_tree({1, null, 2})) == false);
    }
    SUBCASE("all values equal") {
        CHECK(isSubtree(build_tree({7, 7, 7, 7, 7}), build_tree({7, 7, 7})) == true);
        CHECK(isSubtree(build_tree({7, 7, 7, 7, 7}), build_tree({7, 7, null, 7})) == false);
    }
    SUBCASE("deep match at the bottom of a long chain") {
        TreeNode* root = build_chain(1000);  // 0 -> 1 -> ... -> 999 (right chain)
        // subRoot is an independent copy of the last three nodes.
        CHECK(isSubtree(root, build_tree({997, null, 998, null, 999})) == true);
        CHECK(isSubtree(root, build_tree({997, null, 998})) == false);
    }
}
