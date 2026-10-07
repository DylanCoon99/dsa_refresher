# 12 · Graph Traversal and Topological Sort
Run everything: `./dsa test 12` · Status: `./dsa list 12`

## Diagnostic
Attempt cold (≤ 40 min each): `rotting_oranges`, `course_schedule_ii`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Adjacency lists versus adjacency matrices.
- [ ] Implicit graphs, such as grids and state spaces.
- [ ] BFS: shortest paths in unweighted graphs, and multi-source BFS.
- [ ] DFS: recursive and iterative forms, and visited-set management.
- [ ] Cycle detection:
  - in undirected graphs, using a parent check;
  - in directed graphs, using three-color marking.
- [ ] Topological sort with Kahn's algorithm and with DFS postorder.
- [ ] Bipartite checking.

## Implement
- [ ] `graph_traversal`: BFS and DFS on an adjacency list, plus BFS distances and region counting on a grid · `./dsa test 12/graph_traversal`
- [ ] `kahn_topo`: Kahn's topological sort, empty result on a cycle · `./dsa test 12/kahn_topo`

## Practice
- [ ] `num_islands` · Medium · `./dsa test 12/num_islands`
- [ ] `max_area_island` · Medium · `./dsa test 12/max_area_island`
- [ ] `clone_graph` · Medium · `./dsa test 12/clone_graph`
- [ ] `rotting_oranges` · Medium · `./dsa test 12/rotting_oranges`
- [ ] `pacific_atlantic` · Medium · `./dsa test 12/pacific_atlantic`
- [ ] `course_schedule` · Medium · `./dsa test 12/course_schedule`
- [ ] `course_schedule_ii` · Medium · `./dsa test 12/course_schedule_ii`
- [ ] `is_bipartite` · Medium · `./dsa test 12/is_bipartite`
- [ ] `word_ladder` · Hard · `./dsa test 12/word_ladder`

## CLRS quick reference (≈45 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `graph_traversal` | §22.1 (3e) / §20.1 (4e), "Representations of graphs" | Adjacency lists versus adjacency matrices and when each is the better fit (≈10 min) | You can say what each representation costs in space and for "list the neighbors of v". |
| Before `graph_traversal` | §22.2 (3e) / §20.2 (4e), "Breadth-first search" | The BFS pseudocode and the statement that BFS computes shortest unweighted distances; skip the proof (≈10 min) | You can explain why BFS gives shortest paths in an unweighted graph. |
| Before `graph_traversal` | §22.3 (3e) / §20.3 (4e), "Depth-first search" | The DFS pseudocode with white, gray and black colors; skip the parenthesis theorem and edge classification (≈10 min) | You can say what a gray vertex means and how that detects a cycle in a directed graph. |
| Before `kahn_topo` | §22.4 (3e) / §20.4 (4e), "Topological sort" | The DFS-finish-time version; Kahn's algorithm appears there as an end-of-section exercise (≈10 min) | You can explain why a graph has a topological order exactly when it has no cycle. |
| Before `is_bipartite` | §22.2 (3e) / §20.2 (4e), "Breadth-first search" | The end-of-section exercise on two-coloring (≈5 min) | You can explain why a graph is bipartite exactly when it has no odd cycle. |

## Mastery criteria
- [ ] Grids and dependency problems are recognized as graphs.
- [ ] BFS and DFS can be written without errors in visited-state handling.
