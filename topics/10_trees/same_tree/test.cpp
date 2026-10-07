#include <same_tree.hpp>

#include <doctest.h>
#include <tree_node.hpp>

TEST_CASE("examples") {
    CHECK(isSameTree(build_tree({1, 2, 3}), build_tree({1, 2, 3})) == true);
    CHECK(isSameTree(build_tree({1, 2}), build_tree({1, null, 2})) == false);
    CHECK(isSameTree(nullptr, nullptr) == true);
}

TEST_CASE("edge cases") {
    SUBCASE("one tree is null") {
        CHECK(isSameTree(build_tree({1}), nullptr) == false);
        CHECK(isSameTree(nullptr, build_tree({1})) == false);
    }
    SUBCASE("same pointer") {
        TreeNode* t = build_tree({1, 2, 3});
        CHECK(isSameTree(t, t) == true);
    }
    SUBCASE("same values, different shape") {
        CHECK(isSameTree(build_tree({1, 2, 3, 4}), build_tree({1, 2, 3, null, 4})) == false);
        CHECK(isSameTree(build_tree({1, 2, null, 3}), build_tree({1, null, 2, null, 3})) == false);
    }
    SUBCASE("same shape, one different value") {
        CHECK(isSameTree(build_tree({1, 2, 3, 4, 5}), build_tree({1, 2, 3, 4, 6})) == false);
        CHECK(isSameTree(build_tree({1, 2, 3}), build_tree({1, 3, 2})) == false);
    }
    SUBCASE("equal larger trees, negative and extreme values") {
        CHECK(isSameTree(build_tree({-2147483647 - 1, 0, 2147483647, null, -1}),
                         build_tree({-2147483647 - 1, 0, 2147483647, null, -1})) == true);
    }
    SUBCASE("two separate 1000-node chains") {
        CHECK(isSameTree(build_chain(1000), build_chain(1000)) == true);
        CHECK(isSameTree(build_chain(1000), build_chain(999)) == false);
    }
}
