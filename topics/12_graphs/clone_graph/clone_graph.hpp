#pragma once
#include <vector>

struct GraphNode {
    int val;
    std::vector<GraphNode*> neighbors;
    explicit GraphNode(int v) : val(v) {}
};

// Return a deep copy of the connected graph reachable from `node` (nullptr for nullptr).
inline GraphNode* cloneGraph(GraphNode* node) {
    // TODO: implement
    return nullptr;
}
