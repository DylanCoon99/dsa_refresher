# Stage 3b: Topics 12–14 (Tasks 15–17)

Read `00-index.md` first. The conventions are the same as `03a-topics-02-05.md`:
- **Sig** is the exact stub signature.
- **Tests** lists the required cases beyond the standard groups.
- **Large** defines the large-input test. If there is no Large line, there is no large test.
- **CLRS** is the PROBLEM.md pointer.

Every task follows the Exercise Authoring Procedure in `00-index.md` (A–E).

**Graph conventions:**
- `Graph` and `WeightedGraph` come from `common/graph.hpp`.
- Grids are `std::vector<std::vector<char|int>>`, taken by value when the problem lets you mutate them.
- Grid problems with a large test use at most 300×300. PROBLEM.md warns that recursive DFS on large grids can overflow the stack (and shows up as CRASH under ASan), and recommends iterative BFS/DFS.
- Every reference solution is iterative.

---

### Task 15: Topic 12 Graph Traversal and Topological Sort

`TOPIC=12_graphs`, `NN=12`.

**Diagnostic picks:** `rotting_oranges`, `course_schedule_ii`.

**Exercises:**

- **`graph_traversal`** · Implement · Medium
  - Sig:
    - `std::vector<int> bfsOrder(const Graph& adj, int start)`
    - `std::vector<int> dfsOrder(const Graph& adj, int start)`
    - `std::vector<std::vector<int>> gridDistances(const std::vector<std::string>& grid, int sr, int sc)`
    - `int countRegions(const std::vector<std::string>& grid)`
  - Contract:
    - Both orders visit neighbors in adjacency-list order.
    - `dfsOrder` is the recursive preorder order, but the learner may implement it iteratively (push neighbors in reverse).
    - Grids use '.' for open and '#' for wall; distances are 4-directional; unreachable cells and walls are −1.
    - `countRegions` counts 4-connected '.' regions.
  - Tests:
    - disconnected graph (only the reachable vertices are listed);
    - self-loop;
    - start isolated;
    - grid start surrounded by walls;
    - 1×1 grid;
    - 200 random graphs compared with reference BFS/DFS in the test.
  - Large: 300×300 open grid for `gridDistances` and `countRegions`.
  - CLRS: §22.2 (3e) / §20.2 (4e), "Breadth-first search": BFS pseudocode and the shortest-path property statement (≈15 min). §22.3 (3e) / §20.3 (4e), "Depth-first search": DFS with white/gray/black colors (≈15 min). Skip if you can explain why BFS gives shortest unweighted paths.
- **`kahn_topo`** · Implement · Medium
  - Sig: `std::vector<int> topoSortKahn(int n, const std::vector<std::pair<int,int>>& edges)`
  - Contract: edge {u, v} means u before v. Return any valid order, or an empty vector if there is a cycle.
  - Tests: validate the order (a permutation, and every edge goes forward); a cycle → empty; no edges; self-loop → empty; multiple components.
  - Large: 10⁵ vertices in a chain.
  - CLRS: §22.4 (3e) / §20.4 (4e), "Topological sort": the DFS-finish-time version; Kahn's algorithm appears there as an end-of-section exercise (≈10 min).
- **`num_islands`** · Medium
  - Sig: `int numIslands(std::vector<std::vector<char>> grid)`
  - Tests: all water; all land; diagonal cells aren't connected; 1×N; N×1.
  - Large: 300×300 all land.
- **`max_area_island`** · Medium
  - Sig: `int maxAreaOfIsland(std::vector<std::vector<int>> grid)`
  - Tests: no land → 0; a single cell; two islands of equal size.
- **`clone_graph`** · Medium
  - Sig: define in the header:
    ```cpp
    struct GraphNode { int val; std::vector<GraphNode*> neighbors; explicit GraphNode(int v) : val(v) {} };
    GraphNode* cloneGraph(GraphNode* node);
    ```
    The solution header defines the identical struct.
  - Tests:
    - nullptr;
    - a single node;
    - a 4-cycle;
    - verify a deep copy (no pointer shared with the original; adjacency by value matches; the clone's cycle structure is preserved).
- **`rotting_oranges`** · Medium
  - Sig: `int orangesRotting(std::vector<std::vector<int>> grid)`
  - Tests: no fresh oranges → 0; unreachable fresh → −1; no rotten but fresh present → −1; multi-source simultaneous spread.
  - Large: 300×300 with rotten oranges in the corners.
- **`pacific_atlantic`** · Medium
  - Sig: `std::vector<std::vector<int>> pacificAtlantic(const std::vector<std::vector<int>>& heights)`
  - Tests: normalize; 1×1; a flat grid (all cells); a single row.
  - Large: 300×300. Per-cell BFS is O((mn)²).
- **`course_schedule`** · Medium
  - Sig: `bool canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites)`
  - Contract: `{a, b}` means b before a.
  - Tests: no prerequisites; a 2-cycle; a self-dependency; a long chain.
  - Large: 10⁵ courses in a chain.
- **`course_schedule_ii`** · Medium
  - Sig: `std::vector<int> findOrder(int numCourses, const std::vector<std::vector<int>>& prerequisites)`
  - Tests: validate the order; a cycle → empty; isolated courses included.
- **`is_bipartite`** · Medium
  - Sig: `bool isBipartite(const std::vector<std::vector<int>>& graph)`
  - Tests: disconnected components (one non-bipartite) → false; an odd cycle; an even cycle; isolated vertices.
  - CLRS: §22.2 (3e) / §20.2 (4e); an end-of-section exercise there is exactly the two-coloring problem (≈5 min).
- **`word_ladder`** · Hard
  - Sig: `int ladderLength(const std::string& beginWord, const std::string& endWord, const std::vector<std::string>& wordList)`
  - Tests: endWord not in the list → 0; beginWord == endWord is not in the problem's domain, so don't test it; a single step; no path.
  - Large: 5000 words of length 5. Building the full O(n²·L) adjacency is slower; the wildcard-bucket approach passes.

**CLRS quick reference rows:**
- Representations: §22.1 / §20.1, "Representations of graphs", ≈10 min.
- BFS: §22.2 / §20.2, ≈15 min.
- DFS and colors: §22.3 / §20.3, ≈15 min.
- Topological sort: §22.4 / §20.4, ≈10 min.

---

### Task 16: Topic 13 Union-Find (Disjoint Sets)

`TOPIC=13_union_find`, `NN=13`.

**Diagnostic picks:** `redundant_connection`, `accounts_merge`.

**Exercises:**

- **`union_find`** · Implement · Medium
  - Sig:
    ```cpp
    class UnionFind { public: explicit UnionFind(int n); int find(int x); bool unite(int a, int b); bool connected(int a, int b); int componentCount() const; int componentSize(int x); };
    ```
  - Contract: path compression plus union by rank or size. `unite` returns false if already connected.
  - Tests: self-union; repeated unions; sizes after merges; 10⁵ random ops against brute-force BFS connectivity on small n (n = 50).
  - Large: n = 10⁶, uniting i with i+1 in order, then 10⁶ finds on element 0. Without both optimizations this is O(n²).
  - PROBLEM.md note: "Time yourself; the mastery criterion is under 5 minutes from memory."
  - CLRS: §21.3 (3e) / §19.3 (4e), "Disjoint-set forests": the two heuristics and the pseudocode (≈15 min). Skip the amortized proof, as the plan says. §21.1 (3e) / §19.1 (4e), "Disjoint-set operations": the connected-components application (≈5 min).
- **`count_components`** · Medium
  - Sig: `int countComponents(int n, const std::vector<std::vector<int>>& edges)`
  - Tests: no edges → n; one component; duplicate edges.
- **`redundant_connection`** · Medium
  - Sig: `std::vector<int> findRedundantConnection(const std::vector<std::vector<int>>& edges)`
  - Contract: 1-indexed nodes; return the last edge in input order whose removal leaves a tree.
  - Tests: the cycle edge is the last edge; the cycle edge is in the middle (it must return the later one); a 3-node triangle.
- **`accounts_merge`** · Medium
  - Sig: `std::vector<std::vector<std::string>> accountsMerge(const std::vector<std::vector<std::string>>& accounts)`
  - Contract: each output row is the name followed by sorted emails; rows in any order.
  - Tests:
    - normalize by sorting rows;
    - two people with the same name but no shared email stay separate;
    - a transitive merge (A–B shares one email, B–C shares another);
    - a single account with duplicate emails.
- **`number_of_provinces`** · Medium
  - Sig: `int findCircleNum(const std::vector<std::vector<int>>& isConnected)`
  - Tests: identity matrix → n; all ones → 1; n = 1.

**CLRS quick reference rows:**
- Disjoint-set forests: §21.3 / §19.3, ≈15 min.
- Components application: §21.1 / §19.1, ≈5 min.
- Inverse Ackermann: §21.4 / §19.4; the theorem statement only, ≈5 min.

---

### Task 17: Topic 14 Shortest Paths and Minimum Spanning Trees

`TOPIC=14_shortest_paths_mst`, `NN=14`.

**Diagnostic picks:** `network_delay`, `cheapest_flights_k_stops`.

**Exercises:**

- **`dijkstra`** · Implement · Medium
  - Sig:
    ```cpp
    inline constexpr long long kUnreachable = std::numeric_limits<long long>::max();
    std::vector<long long> dijkstra(int n, const WeightedGraph& adj, int src);
    ```
  - Contract: non-negative weights; binary heap with lazy deletion.
  - Tests:
    - unreachable vertices;
    - zero-weight edges;
    - parallel edges;
    - path sums exceeding INT_MAX (weights of 10⁹);
    - 200 random graphs compared with Bellman-Ford written in the test.
  - Large: 10⁵ vertices and 3·10⁵ edges. An O(V²) array scan is 10¹⁰.
  - CLRS: Ch. 24 intro (3e) / Ch. 22 intro (4e), relaxation and why negative weights matter (≈10 min). §24.3 (3e) / §22.3 (4e), "Dijkstra's algorithm": pseudocode and the correctness theorem statement (≈15 min). Skip if you can explain why a negative edge breaks the greedy finalization.
- **`kruskal`** · Implement · Medium
  - Sig: `long long kruskalMstWeight(int n, std::vector<std::tuple<int,int,int>> edges)`
  - Contract: edges are {u, v, w} and undirected; return −1 if the graph is disconnected.
  - PROBLEM.md: "Write your UnionFind again inside this header; rewriting it is part of the drill."
  - Tests: disconnected → −1; n = 1 → 0; negative weights are allowed; 200 random graphs against brute force (Prim's O(V²) in the test).
  - Large: 10⁵ vertices with 3·10⁵ edges.
  - CLRS: §23.1 (3e) / §21.1 (4e), "Growing a minimum spanning tree": the cut-property theorem statement (≈10 min). §23.2 (3e) / §21.2 (4e), "The algorithms of Kruskal and Prim" (≈15 min).
- **`network_delay`** · Medium
  - Sig: `int networkDelayTime(const std::vector<std::vector<int>>& times, int n, int k)`
  - Tests: unreachable → −1; n = 1 → 0; multiple paths.
- **`min_effort_path`** · Medium
  - Sig: `int minimumEffortPath(const std::vector<std::vector<int>>& heights)`
  - Tests: 1×1 → 0; a single row; equal heights → 0.
  - Large: 100×100. Plain DFS over all paths is exponential.
- **`cheapest_flights_k_stops`** · Medium
  - Sig: `int findCheapestPrice(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int k)`
  - Tests:
    - the cheapest path has too many stops (the answer is the pricier, shorter path);
    - k = 0;
    - unreachable → −1;
    - the stop-limit trap: n = 4, flights `{0,1,1}`, `{1,2,1}`, `{0,2,5}`, `{2,3,1}`, src 0, dst 3, k = 1 → 6 (0→2→3). The cheaper 0→1→2→3 costs 3 but needs 2 stops, and plain Dijkstra on cost alone settles node 2 through it.
  - CLRS: §24.1 (3e) / §22.1 (4e), "The Bellman-Ford algorithm": k+1 relaxation rounds bound the edge count (≈15 min).
- **`min_cost_connect_points`** · Medium
  - Sig: `int minCostConnectPoints(const std::vector<std::vector<int>>& points)`
  - Contract: Manhattan distance.
  - Tests: a single point → 0; two points; collinear points.
  - Large: 1000 points. Dense Prim O(n²) passes; Kruskal on all n² edges also passes, which is fine.
- **`swim_rising_water`** · Hard
  - Sig: `int swimInWater(const std::vector<std::vector<int>>& grid)`
  - Contract: grid is a permutation of 0..n²−1.
  - Tests: 1×1; 2×2; the start is the highest cell.
  - Large: 50×50 (LeetCode's limit).

**CLRS quick reference rows:**
- Relaxation and negative weights: Ch. 24 intro / Ch. 22 intro, ≈10 min.
- Bellman-Ford: §24.1 / §22.1, ≈15 min.
- Dijkstra: §24.3 / §22.3, ≈15 min.
- Floyd-Warshall (review only): §25.2 / §23.2, ≈10 min.
- MST cut property: §23.1 / §21.1, ≈10 min.
- Kruskal and Prim: §23.2 / §21.2, ≈15 min.
- 0-1 BFS: not in CLRS.
