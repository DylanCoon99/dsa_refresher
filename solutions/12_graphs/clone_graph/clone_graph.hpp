#pragma once
#include <queue>
#include <unordered_map>
#include <vector>

struct GraphNode {
    int val;
    std::vector<GraphNode*> neighbors;
    explicit GraphNode(int v) : val(v) {}
};

// Approach: BFS over the original graph, creating each clone the first time its original is seen and recording original -> clone in a hash map; wire each clone's neighbors through the map.
// Key insight: the map is both the visited set and the way to reuse an existing clone, which is what keeps cycles from looping forever or duplicating nodes.
// Time: O(V + E)  Space: O(V)
// Brute force: no natural brute force; a naive recursive copy without the map never terminates on a cycle.
inline GraphNode* cloneGraph(GraphNode* node) {
    if (!node) return nullptr;
    std::unordered_map<GraphNode*, GraphNode*> copy;
    copy[node] = new GraphNode(node->val);
    std::queue<GraphNode*> q;
    q.push(node);
    while (!q.empty()) {
        GraphNode* cur = q.front();
        q.pop();
        for (GraphNode* nb : cur->neighbors) {
            if (!copy.count(nb)) {
                copy[nb] = new GraphNode(nb->val);
                q.push(nb);
            }
            copy[cur]->neighbors.push_back(copy[nb]);
        }
    }
    return copy[node];
}
