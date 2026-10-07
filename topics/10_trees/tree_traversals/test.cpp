#include <tree_traversals.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <queue>
#include <vector>

namespace {
void ref_pre(const TreeNode* n, std::vector<int>& out) {
    if (!n) return;
    out.push_back(n->val);
    ref_pre(n->left, out);
    ref_pre(n->right, out);
}
void ref_in(const TreeNode* n, std::vector<int>& out) {
    if (!n) return;
    ref_in(n->left, out);
    out.push_back(n->val);
    ref_in(n->right, out);
}
void ref_post(const TreeNode* n, std::vector<int>& out) {
    if (!n) return;
    ref_post(n->left, out);
    ref_post(n->right, out);
    out.push_back(n->val);
}
std::vector<int> ref_level(const TreeNode* root) {
    std::vector<int> out;
    std::queue<const TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        const TreeNode* n = q.front();
        q.pop();
        out.push_back(n->val);
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
    return out;
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

using V = std::vector<int>;
}  // namespace

TEST_CASE("examples") {
    TreeNode* t = build_tree({3, 9, 20, null, null, 15, 7});
    CHECK(preorderIterative(t) == V{3, 9, 20, 15, 7});
    CHECK(inorderIterative(t) == V{9, 3, 15, 20, 7});
    CHECK(postorderIterative(t) == V{9, 15, 7, 20, 3});
    CHECK(levelOrderFlat(t) == V{3, 9, 20, 15, 7});
    TreeNode* chain = build_tree({1, null, 2, null, 3});
    CHECK(preorderIterative(chain) == V{1, 2, 3});
    CHECK(inorderIterative(chain) == V{1, 2, 3});
    CHECK(postorderIterative(chain) == V{3, 2, 1});
    CHECK(levelOrderFlat(chain) == V{1, 2, 3});
}

TEST_CASE("edge cases") {
    SUBCASE("empty tree") {
        CHECK(preorderIterative(nullptr).empty());
        CHECK(inorderIterative(nullptr).empty());
        CHECK(postorderIterative(nullptr).empty());
        CHECK(levelOrderFlat(nullptr).empty());
    }
    SUBCASE("single node") {
        TreeNode* t = build_tree({-5});
        CHECK(preorderIterative(t) == V{-5});
        CHECK(inorderIterative(t) == V{-5});
        CHECK(postorderIterative(t) == V{-5});
        CHECK(levelOrderFlat(t) == V{-5});
    }
    SUBCASE("left-only chain") {
        TreeNode* t = build_tree({1, 2, null, 3, null, 4});
        CHECK(preorderIterative(t) == V{1, 2, 3, 4});
        CHECK(inorderIterative(t) == V{4, 3, 2, 1});
        CHECK(postorderIterative(t) == V{4, 3, 2, 1});
        CHECK(levelOrderFlat(t) == V{1, 2, 3, 4});
    }
    SUBCASE("traversals do not modify the tree") {
        LevelOrder spec{1, 2, 3, 4, 5, null, 6};
        TreeNode* t = build_tree(spec);
        preorderIterative(t);
        inorderIterative(t);
        postorderIterative(t);
        levelOrderFlat(t);
        CHECK(to_level_order(t) == spec);
    }
}

TEST_CASE("randomized vs recursive reference") {
    for (int trial = 0; trial < 200; ++trial) {
        TreeNode* t = random_tree(rand_int(0, 25), -20, 20);
        V pre, in, post;
        ref_pre(t, pre);
        ref_in(t, in);
        ref_post(t, post);
        CHECK(preorderIterative(t) == pre);
        CHECK(inorderIterative(t) == in);
        CHECK(postorderIterative(t) == post);
        CHECK(levelOrderFlat(t) == ref_level(t));
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Right-leaning chain with values 0..n-1, 10^5 deep. A recursive traversal needs one frame per
    // node and is expected to overflow the stack under ASan (reported as CRASH).
    const int n = 100'000;
    TreeNode* t = build_chain(n);
    // (double parentheses: a failure prints false, not 10^5 numbers)
    V asc(n), desc(n);
    for (int i = 0; i < n; ++i) { asc[i] = i; desc[i] = n - 1 - i; }
    INFO("preorder on the chain");
    CHECK((preorderIterative(t) == asc));
    INFO("inorder on the chain");
    CHECK((inorderIterative(t) == asc));
    INFO("postorder on the chain");
    CHECK((postorderIterative(t) == desc));
    INFO("level order on the chain");
    CHECK((levelOrderFlat(t) == asc));
}
