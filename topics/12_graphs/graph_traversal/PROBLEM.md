# Graph Traversal: BFS, DFS and Grid Search
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement four functions. `Graph` is `std::vector<std::vector<int>>`: `adj[v]` lists the vertices
that `v` has an edge to, in a fixed order. The graph may be directed, may have self-loops and
repeated edges, and may be disconnected.

```cpp
std::vector<int> bfsOrder(const Graph& adj, int start);
std::vector<int> dfsOrder(const Graph& adj, int start);
std::vector<std::vector<int>> gridDistances(const std::vector<std::string>& grid, int sr, int sc);
int countRegions(const std::vector<std::string>& grid);
```

- `bfsOrder` returns the vertices reachable from `start` in the order a breadth-first search
  first visits them, trying the neighbors of each vertex in the order they appear in `adj[v]`.
- `dfsOrder` returns the reachable vertices in depth-first **preorder**: visit a vertex, then
  fully explore its first unvisited neighbor, then the next, and so on, in adjacency-list order.
  This is exactly what a recursive DFS produces. You may write it iteratively; one way is to push a
  vertex's neighbors onto a stack in reverse and mark a vertex visited when it is popped.
- Vertices that cannot be reached from `start` do not appear in either list. Each reachable vertex
  appears once.
- `gridDistances` works on a grid of `'.'` (open) and `'#'` (wall) cells, moving up, down, left or
  right between open cells. It returns a matrix of the same shape holding the number of steps from
  `(sr, sc)` to each cell. Walls and open cells that cannot be reached are `-1`. The start cell is
  open.
- `countRegions` returns the number of 4-connected groups of `'.'` cells.

On large grids a recursive DFS can overflow the call stack (under the sanitizer build this shows up
as a CRASH rather than a clean failure). The large test uses a 300 x 300 grid, so prefer an
iterative BFS or an explicit stack.

## Examples
- `adj = {{1, 2}, {3}, {3}, {}}, start = 0` → BFS `{0, 1, 2, 3}`, DFS `{0, 1, 3, 2}`.
- `grid = {"..#", "...", "#.."}, (sr, sc) = (0, 0)` → `{{0, 1, -1}, {1, 2, 3}, {-1, 3, 4}}`.
- `grid = {".#.", "###", ".#."}` → 4 regions.

## Constraints
- 1 ≤ V ≤ 1000 vertices, 0 ≤ start < V, any number of edges (self-loops and repeats allowed).
- Grids have 1 ≤ rows, cols ≤ 300 and contain only `'.'` and `'#'`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(V + E) for the graph functions, O(rows · cols) for the grid functions · Space: O(V) or
O(rows · cols)

The large test (a fully open 300 x 300 grid) rejects running a separate search per cell
(O((rows · cols)²)).

## CLRS (optional, ≈20 min)
- §22.2 (3e) / §20.2 (4e), "Breadth-first search": the BFS pseudocode and the statement that BFS
  computes shortest unweighted distances (≈10 min; skip the proof).
- §22.3 (3e) / §20.3 (4e), "Depth-first search": the DFS pseudocode with white, gray and black
  colors (≈10 min; skip the parenthesis theorem and edge classification).
- Skip if: you can explain why BFS gives shortest paths in an unweighted graph.

## Hints
<details><summary>Hint 1</summary>Both searches need a "have I seen this vertex?" array. When exactly should a vertex be marked: when it is put in the queue or stack, or when it is taken out? Does the answer differ between BFS and the stack-based DFS?</details>
<details><summary>Hint 2</summary>A grid is a graph whose neighbors are computed rather than stored. If BFS processes cells in order of distance from the start, what is the distance of a newly discovered cell in terms of the cell that discovered it?</details>
