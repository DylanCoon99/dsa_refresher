#include <max_path_sum.hpp>

#include <doctest.h>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <algorithm>
#include <climits>
#include <unordered_map>
#include <vector>

namespace {
void collect(TreeNode* n, TreeNode* parent, int depth, std::vector<TreeNode*>& nodes,
             std::unordered_map<TreeNode*, TreeNode*>& par, std::unordered_map<TreeNode*, int>& dep) {
    if (!n) return;
    nodes.push_back(n);
    par[n] = parent;
    dep[n] = depth;
    collect(n->left, n, depth + 1, nodes, par, dep);
    collect(n->right, n, depth + 1, nodes, par, dep);
}
// Reference: try every pair of nodes (including a node with itself), summing the path between them.
int brute(TreeNode* root) {
    std::vector<TreeNode*> nodes;
    std::unordered_map<TreeNode*, TreeNode*> par;
    std::unordered_map<TreeNode*, int> dep;
    collect(root, nullptr, 0, nodes, par, dep);
    int best = INT_MIN;
    for (TreeNode* u : nodes) {
        for (TreeNode* v : nodes) {
            TreeNode* a = u;
            TreeNode* b = v;
            int sum = 0;
            while (a != b) {  // climb the deeper one until they meet at the LCA
                if (dep[a] >= dep[b]) { sum += a->val; a = par[a]; }
                else { sum += b->val; b = par[b]; }
            }
            sum += a->val;  // the LCA itself, counted once
            best = std::max(best, sum);
        }
    }
    return best;
}
TreeNode* random_tree(int n, int lo, int hi) {
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
    CHECK(maxPathSum(build_tree({1, 2, 3})) == 6);
    CHECK(maxPathSum(build_tree({-10, 9, 20, null, null, 15, 7})) == 42);
    CHECK(maxPathSum(build_tree({-3})) == -3);
}

TEST_CASE("edge cases") {
    SUBCASE("single node") {
        CHECK(maxPathSum(build_tree({5})) == 5);
        CHECK(maxPathSum(build_tree({-1000})) == -1000);
    }
    SUBCASE("all negative: the answer is the largest single node") {
        CHECK(maxPathSum(build_tree({-2, -1})) == -1);
        CHECK(maxPathSum(build_tree({-5, -3, -8, -9, -2, -7, -4})) == -2);
        CHECK(maxPathSum(build_tree({-4, -9, -1, null, -3})) == -1);
    }
    SUBCASE("the best path does not pass through the root") {
        // 5 -> 10 -> 6 = 21 below a very negative root and a negative right child.
        CHECK(maxPathSum(build_tree({-20, 10, -30, 5, 6})) == 21);
        CHECK(maxPathSum(build_tree({-10, 9, 20, null, null, 15, 7})) == 42);
    }
    SUBCASE("a path may use only one arm below a node") {
        // Root 1 with arms 10 (left) and 2 (right, negative child below): best is 10 + 1 + 2 = 13.
        CHECK(maxPathSum(build_tree({1, 10, 2, null, null, -50})) == 13);
        // Taking a second arm would hurt: 4 -> 3 only.
        CHECK(maxPathSum(build_tree({3, 4, -100})) == 7);
    }
    SUBCASE("a negative node in the middle of the best path is skipped when possible") {
        CHECK(maxPathSum(build_tree({2, -1, -2})) == 2);
        CHECK(maxPathSum(build_tree({-1, 5, null, 4})) == 9);  // 4 -> 5 without the root
    }
    SUBCASE("skewed tree of 1000 nodes") {
        CHECK(maxPathSum(build_chain(1000)) == 499500);  // 0 + 1 + ... + 999
    }
}

TEST_CASE("randomized vs all node pairs") {
    for (int trial = 0; trial < 300; ++trial) {
        TreeNode* t = random_tree(rand_int(1, 14), -10, 10);
        CHECK(maxPathSum(t) == brute(t));
    }
    for (int trial = 0; trial < 100; ++trial) {  // mostly negative values
        TreeNode* t = random_tree(rand_int(1, 14), -10, 2);
        CHECK(maxPathSum(t) == brute(t));
    }
}
