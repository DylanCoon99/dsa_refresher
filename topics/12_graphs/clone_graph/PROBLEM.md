# Clone Graph
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Clone Graph" (title kept for cross-reference only)

## Problem
Graph nodes are defined in the header:

```cpp
struct GraphNode {
    int val;
    std::vector<GraphNode*> neighbors;
    explicit GraphNode(int v) : val(v) {}
};

GraphNode* cloneGraph(GraphNode* node);
```

Given a pointer to one node of a connected graph, return a pointer to the corresponding node of a
**deep copy** of the whole graph. The copy must contain a brand-new `GraphNode` for every node
reachable from `node`; no node of the copy may be a node of the original. Each clone has the same
`val` and the same neighbors **in the same order** (neighbor by value), and every original node is
copied exactly once: if two nodes in the original point at the same node, their clones point at the
same clone. Graphs may contain cycles. If `node` is `nullptr`, return `nullptr`.

The tests check all of this: no shared pointers, matching values and neighbor lists, one clone per
original node, and that the original graph is unchanged. They do not free the clone nodes.

## Examples
- `nullptr` → `nullptr`
- A single node with value 1 and no neighbors → a different node with value 1 and no neighbors.
- The 4-cycle `1 - 2 - 3 - 4 - 1` (each edge is in both endpoints' lists) → a new 4-cycle with the
  same values and the same neighbor order.

## Constraints
- 0 ≤ number of nodes ≤ 100, values are distinct integers 1..n, and every node is reachable from
  the given node.
- Self-loops and repeated edges may occur (the tests include self-loops).
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(V + E) · Space: O(V)

## Hints
<details><summary>Hint 1</summary>Copying a node is easy; copying its neighbors is the same problem again. What goes wrong if the graph has a cycle and you copy neighbors naively?</details>
<details><summary>Hint 2</summary>When you reach a node, how can you tell whether you already created its clone, and where would you look that clone up?</details>
