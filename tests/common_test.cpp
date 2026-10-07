#include <doctest.h>
#include <graph.hpp>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <stdexcept>

TEST_CASE("list round trip") {
    CHECK(to_vector(build_list({1, 2, 3})) == std::vector<int>{1, 2, 3});
    CHECK(build_list({}) == nullptr);
    CHECK(to_vector(nullptr).empty());
}

TEST_CASE("cyclic list fails instead of hanging") {
    ListNode* head = build_list_with_cycle({1, 2, 3}, 1);
    REQUIRE(head->next->next->next == head->next);
    CHECK_THROWS_AS(to_vector(head, 100), std::runtime_error);
    CHECK(to_vector(build_list_with_cycle({1, 2}, -1)) == std::vector<int>{1, 2});
}

TEST_CASE("random list round trip") {
    std::vector<std::pair<int, int>> spec{{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    CHECK(to_random_spec(build_random_list(spec)) == spec);
    CHECK(build_random_list({}) == nullptr);
}

TEST_CASE("tree round trip") {
    LevelOrder lo{3, 9, 20, null, null, 15, 7};
    CHECK(to_level_order(build_tree(lo)) == lo);
    CHECK(to_level_order(build_tree({1, null, 2, null, null})) == LevelOrder{1, null, 2});
    CHECK(build_tree({}) == nullptr);
    CHECK(to_level_order(nullptr).empty());
}

TEST_CASE("cyclic tree fails instead of hanging") {
    TreeNode* root = build_tree({1, 2});
    root->left->left = root;
    CHECK_THROWS_AS(to_level_order(root, 100), std::runtime_error);
}

TEST_CASE("tree helpers") {
    TreeNode* root = build_tree({6, 2, 8, 0, 4, 7, 9});
    REQUIRE(find_node(root, 4) != nullptr);
    CHECK(find_node(root, 4)->val == 4);
    CHECK(find_node(root, 5) == nullptr);
    TreeNode* chain = build_chain(100000);
    int depth = 0;
    for (TreeNode* n = chain; n; n = n->right) ++depth;
    CHECK(depth == 100000);
    CHECK(to_level_order(build_balanced_bst({1, 2, 3})) == LevelOrder{2, 1, 3});
}

TEST_CASE("printing") {
    CHECK(dsa_print::to_text(std::vector<int>{1, 2}) == "[1, 2]");
    CHECK(dsa_print::to_text(std::vector<std::vector<int>>{{1}, {}}) == "[[1], []]");
    CHECK(dsa_print::to_text(LevelOrder{1, null}) == "[1, null]");
    CHECK(dsa_print::to_text(std::vector<std::string>{"a"}) == "[\"a\"]");
    CHECK(dsa_print::to_text(std::pair<int, char>{1, 'x'}) == "(1, 'x')");
}

TEST_CASE("graph helpers") {
    Graph g = edges_to_graph(3, {{0, 1}, {1, 2}}, false);
    CHECK(g == Graph{{1}, {0, 2}, {1}});
    Graph d = edges_to_graph(3, {{0, 1}, {1, 2}}, true);
    CHECK(d == Graph{{1}, {2}, {}});
    WeightedGraph w = weighted_edges_to_graph(2, {{0, 1, 5}}, true);
    CHECK(w[0] == std::vector<std::pair<int, int>>{{1, 5}});
}

TEST_CASE("random utils stay in range") {
    for (int v : rand_vec(1000, -5, 5)) { CHECK(v >= -5); CHECK(v <= 5); }
    for (char c : rand_string(1000, 'a', 'c')) { CHECK(c >= 'a'); CHECK(c <= 'c'); }
}
