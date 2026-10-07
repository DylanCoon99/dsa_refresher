#include <bst.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <set>
#include <vector>

using V = std::vector<int>;

static BST* make(const V& keys) {
    BST* t = new BST();
    for (int k : keys) t->insert(k);
    return t;
}

TEST_CASE("examples") {
    BST* t = make({5, 3, 8, 1, 4});
    CHECK(t->inorder() == V{1, 3, 4, 5, 8});
    CHECK(t->size() == 5);
    CHECK(t->insert(3) == false);
    CHECK(t->size() == 5);
    CHECK(t->contains(4));
    CHECK_FALSE(t->contains(7));
    CHECK(t->erase(5) == true);
    CHECK(t->inorder() == V{1, 3, 4, 8});
    CHECK(t->erase(42) == false);
    CHECK(t->inorder() == V{1, 3, 4, 8});
    delete t;
}

TEST_CASE("edge cases") {
    SUBCASE("empty tree") {
        BST t;
        CHECK(t.size() == 0);
        CHECK(t.inorder().empty());
        CHECK_FALSE(t.contains(0));
        CHECK(t.erase(0) == false);
    }
    SUBCASE("insert returns true then false") {
        BST t;
        CHECK(t.insert(10) == true);
        CHECK(t.insert(10) == false);
        CHECK(t.size() == 1);
    }
    SUBCASE("erase the root with two children") {
        BST t;
        for (int k : {50, 30, 70, 20, 40, 60, 80, 65}) t.insert(k);
        CHECK(t.erase(50) == true);
        CHECK(t.inorder() == V{20, 30, 40, 60, 65, 70, 80});
        CHECK(t.size() == 7);
        CHECK_FALSE(t.contains(50));
        for (int k : {20, 30, 40, 60, 65, 70, 80}) CHECK(t.contains(k));
        // successor (60) has a right child (65) in this tree: it must stay attached
        CHECK(t.erase(60) == true);
        CHECK(t.inorder() == V{20, 30, 40, 65, 70, 80});
    }
    SUBCASE("erase a leaf") {
        BST t;
        for (int k : {5, 2, 8}) t.insert(k);
        CHECK(t.erase(2) == true);
        CHECK(t.inorder() == V{5, 8});
        CHECK(t.erase(8) == true);
        CHECK(t.inorder() == V{5});
        CHECK(t.erase(5) == true);
        CHECK(t.size() == 0);
        CHECK(t.inorder().empty());
    }
    SUBCASE("erase a node with one child") {
        BST t;
        for (int k : {5, 2, 8, 1, 9}) t.insert(k);  // 2 has only a left child, 8 only a right child
        CHECK(t.erase(2) == true);
        CHECK(t.inorder() == V{1, 5, 8, 9});
        CHECK(t.erase(8) == true);
        CHECK(t.inorder() == V{1, 5, 9});
        CHECK(t.contains(1));
        CHECK(t.contains(9));
    }
    SUBCASE("erase a missing value") {
        BST t;
        for (int k : {5, 2, 8}) t.insert(k);
        CHECK(t.erase(3) == false);
        CHECK(t.erase(100) == false);
        CHECK(t.inorder() == V{2, 5, 8});
        CHECK(t.size() == 3);
    }
    SUBCASE("erase the root repeatedly") {
        BST t;
        for (int k : {4, 2, 6, 1, 3, 5, 7}) t.insert(k);
        V expected{1, 2, 3, 4, 5, 6, 7};
        for (int r : {4, 5, 6, 3, 7, 2, 1}) {
            CHECK(t.erase(r) == true);
            expected.erase(std::find(expected.begin(), expected.end(), r));
            CHECK(t.inorder() == expected);
        }
        CHECK(t.size() == 0);
    }
    SUBCASE("extreme keys") {
        BST t;
        const int lo = -2147483647 - 1, hi = 2147483647;
        CHECK(t.insert(lo));
        CHECK(t.insert(hi));
        CHECK(t.insert(0));
        CHECK(t.inorder() == V{lo, 0, hi});
        CHECK(t.erase(lo));
        CHECK(t.erase(hi));
        CHECK(t.inorder() == V{0});
    }
}

TEST_CASE("randomized vs std::set") {
    // REQUIRE: stop at the first mismatch instead of printing thousands of failures.
    BST t;
    std::set<int> ref;
    for (int op = 0; op < 20'000; ++op) {
        int v = rand_int(0, 400);
        int kind = rand_int(0, 2);
        if (kind == 0) {
            REQUIRE(t.insert(v) == ref.insert(v).second);
        } else if (kind == 1) {
            REQUIRE(t.erase(v) == (ref.erase(v) == 1));
        } else {
            REQUIRE(t.contains(v) == (ref.count(v) == 1));
        }
        REQUIRE(t.size() == ref.size());
        if (op % 500 == 0) REQUIRE(t.inorder() == V(ref.begin(), ref.end()));
    }
    REQUIRE(t.inorder() == V(ref.begin(), ref.end()));
}
