#include <clone_graph.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <map>
#include <memory>
#include <queue>
#include <set>
#include <vector>

namespace {
// Owns the original graph for the duration of a test. Nodes have values 1..n.
struct Original {
    std::vector<std::unique_ptr<GraphNode>> nodes;
    // adj[i] lists the values (1-based) of node i+1's neighbors.
    explicit Original(const std::vector<std::vector<int>>& adj) {
        for (std::size_t i = 0; i < adj.size(); ++i) nodes.push_back(std::make_unique<GraphNode>(static_cast<int>(i) + 1));
        for (std::size_t i = 0; i < adj.size(); ++i)
            for (int v : adj[i]) nodes[i]->neighbors.push_back(nodes[static_cast<std::size_t>(v) - 1].get());
    }
    GraphNode* root() { return nodes.empty() ? nullptr : nodes[0].get(); }
    std::set<const GraphNode*> pointers() const {
        std::set<const GraphNode*> s;
        for (const auto& n : nodes) s.insert(n.get());
        return s;
    }
};

// Checks that `copy` is an independent, structurally identical copy of the graph in `orig`.
void checkDeepCopy(Original& orig, GraphNode* copy) {
    REQUIRE(copy != nullptr);
    CHECK(copy->val == orig.root()->val);
    auto originals = orig.pointers();
    std::map<int, const GraphNode*> byVal;  // clone node for each value
    std::set<const GraphNode*> seen{copy};
    std::queue<const GraphNode*> q;
    q.push(copy);
    byVal[copy->val] = copy;
    std::size_t visited = 0;
    while (!q.empty()) {
        const GraphNode* cur = q.front();
        q.pop();
        ++visited;
        CHECK(originals.count(cur) == 0);  // no node is shared with the original graph
        REQUIRE(cur->val >= 1);
        REQUIRE(cur->val <= static_cast<int>(orig.nodes.size()));
        const GraphNode* o = orig.nodes[static_cast<std::size_t>(cur->val) - 1].get();
        REQUIRE(cur->neighbors.size() == o->neighbors.size());  // same adjacency, same order
        for (std::size_t i = 0; i < cur->neighbors.size(); ++i) {
            const GraphNode* nb = cur->neighbors[i];
            REQUIRE(nb != nullptr);
            CHECK(nb->val == o->neighbors[i]->val);
            auto it = byVal.find(nb->val);
            if (it == byVal.end()) {
                byVal[nb->val] = nb;
            } else {
                CHECK(it->second == nb);  // one clone per original: the graph's cycles are preserved
            }
            if (seen.insert(nb).second) q.push(nb);
        }
        REQUIRE(visited <= orig.nodes.size());  // more distinct clones than originals: nodes were duplicated
    }
    CHECK(visited == orig.nodes.size());  // every original node has a clone
}
}  // namespace

TEST_CASE("examples") {
    // The 4-cycle 1-2-3-4-1 (undirected: each edge appears in both lists).
    Original g({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
    checkDeepCopy(g, cloneGraph(g.root()));
}

TEST_CASE("edge cases") {
    SUBCASE("nullptr") { CHECK(cloneGraph(nullptr) == nullptr); }
    SUBCASE("a single node") {
        Original g({{}});
        checkDeepCopy(g, cloneGraph(g.root()));
    }
    SUBCASE("two nodes") {
        Original g({{2}, {1}});
        checkDeepCopy(g, cloneGraph(g.root()));
    }
    SUBCASE("a node with a self-loop") {
        Original g({{1, 2}, {1}});
        checkDeepCopy(g, cloneGraph(g.root()));
    }
    SUBCASE("a path") {
        Original g({{2}, {1, 3}, {2, 4}, {3}});
        checkDeepCopy(g, cloneGraph(g.root()));
    }
    SUBCASE("a directed cycle") {
        Original g({{2}, {3}, {1}});
        checkDeepCopy(g, cloneGraph(g.root()));
    }
    SUBCASE("a complete graph on 4 nodes") {
        Original g({{2, 3, 4}, {1, 3, 4}, {1, 2, 4}, {1, 2, 3}});
        checkDeepCopy(g, cloneGraph(g.root()));
    }
    SUBCASE("cloning does not change the original") {
        Original g({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
        GraphNode* copy = cloneGraph(g.root());
        REQUIRE(copy != nullptr);
        copy->val = 99;
        copy->neighbors.clear();
        CHECK(g.root()->val == 1);
        CHECK(g.root()->neighbors.size() == 2);
        CHECK(g.nodes[1]->neighbors.size() == 2);
    }
}

TEST_CASE("randomized connected graphs") {
    for (int trial = 0; trial < 100; ++trial) {
        int n = rand_int(1, 9);
        std::vector<std::vector<int>> adj(n);
        for (int v = 2; v <= n; ++v) {  // a random tree keeps every node reachable from node 1
            int u = rand_int(1, v - 1);
            adj[u - 1].push_back(v);
            adj[v - 1].push_back(u);
        }
        int extra = rand_int(0, 8);
        for (int i = 0; i < extra; ++i) {
            int u = rand_int(1, n), v = rand_int(1, n);  // may add self-loops or repeated edges
            adj[u - 1].push_back(v);
            if (rand_int(0, 1)) adj[v - 1].push_back(u);
        }
        Original g(adj);
        checkDeepCopy(g, cloneGraph(g.root()));
    }
}
