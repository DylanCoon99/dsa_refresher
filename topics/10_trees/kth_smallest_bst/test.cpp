#include <kth_smallest_bst.hpp>

#include <doctest.h>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <vector>

TEST_CASE("examples") {
    CHECK(kthSmallest(build_tree({3, 1, 4, null, 2}), 1) == 1);
    TreeNode* t = build_tree({5, 3, 6, 2, 4, null, null, 1});
    CHECK(kthSmallest(t, 3) == 3);
    CHECK(kthSmallest(t, 6) == 6);
}

TEST_CASE("edge cases") {
    SUBCASE("single node") { CHECK(kthSmallest(build_tree({7}), 1) == 7); }
    SUBCASE("k = 1 is the leftmost node, k = n the rightmost") {
        TreeNode* t = build_tree({8, 3, 10, 1, 6, null, 14, null, null, 4, 7, 13});
        CHECK(kthSmallest(t, 1) == 1);
        CHECK(kthSmallest(t, 9) == 14);
    }
    SUBCASE("every k on an unbalanced tree") {
        TreeNode* t = build_tree({5, 3, 6, 2, 4, null, null, 1});
        const std::vector<int> sorted{1, 2, 3, 4, 5, 6};
        for (int k = 1; k <= 6; ++k) CHECK(kthSmallest(t, k) == sorted[k - 1]);
    }
    SUBCASE("negative and extreme values") {
        TreeNode* t = build_tree({0, -2147483647 - 1, 2147483647});
        CHECK(kthSmallest(t, 1) == -2147483647 - 1);
        CHECK(kthSmallest(t, 2) == 0);
        CHECK(kthSmallest(t, 3) == 2147483647);
    }
    SUBCASE("right chain of 1000 nodes") {
        TreeNode* t = build_chain(1000);
        CHECK(kthSmallest(t, 1) == 0);
        CHECK(kthSmallest(t, 1000) == 999);
        CHECK(kthSmallest(t, 500) == 499);
    }
}

TEST_CASE("randomized balanced BSTs") {
    for (int trial = 0; trial < 200; ++trial) {
        int n = rand_int(1, 60);
        std::vector<int> vals;
        for (int i = 0, v = rand_int(0, 20); i < n; ++i, v += rand_int(1, 10)) vals.push_back(v);
        TreeNode* t = build_balanced_bst(vals);
        int k = rand_int(1, n);
        CHECK(kthSmallest(t, k) == vals[k - 1]);
    }
}
