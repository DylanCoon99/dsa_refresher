# 22 · Advanced Graph Topics
Run everything: `./dsa test 22` · Status: `./dsa list 22`

This is an Advanced topic: begin it after the core topics are complete.

## Diagnostic
Attempt cold (≤ 40 min each): `eventual_safe_states`, `reconstruct_itinerary`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Strongly connected components, using the Kosaraju and Tarjan algorithms.
- [ ] Bridges and articulation points.
- [ ] A* search.
- [ ] Maximum flow (Ford-Fulkerson and Edmonds-Karp) and bipartite matching, at a conceptual level.

## Implement
- [ ] `tarjan_bridges_ap`: Tarjan's algorithm for bridges, plus articulation points · `./dsa test 22/tarjan_bridges_ap`

## Practice
- [ ] `critical_connections` · Hard · `./dsa test 22/critical_connections`
- [ ] `eventual_safe_states` · Medium · `./dsa test 22/eventual_safe_states`
- [ ] `reconstruct_itinerary` · Hard · `./dsa test 22/reconstruct_itinerary`
- [ ] `alien_dictionary` · Hard · `./dsa test 22/alien_dictionary` (a premium problem, written here in original words)

## CLRS quick reference (≈80 min, all optional)
A* is not in CLRS. Strongly connected components, max flow and matching have no exercises here; they are review reading only.

| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Review: SCC | §22.5 (3e) / §20.5 (4e), "Strongly connected components" | The two-pass DFS algorithm and the component graph; skip the proofs (≈15 min) | You can explain why the second pass runs on the transposed graph in decreasing finish-time order. |
| With `tarjan_bridges_ap` | Ch. 22 (3e) / Ch. 20 (4e), end-of-chapter problem "Articulation points, bridges, and biconnected components" | The definitions and the low-point idea (≈20 min) | You can explain what `low[v]` means and why `low[child] > tin[parent]` marks a bridge. |
| With `eventual_safe_states` | §22.3 (3e) / §20.3 (4e), "Depth-first search" | White / gray / black coloring and back edges (≈10 min) | You can explain why reaching a gray vertex proves a cycle. |
| With `reconstruct_itinerary` | Ch. 22 (3e) / Ch. 20 (4e), end-of-chapter problem "Euler tour" | The statement and the edge-walking idea (≈10 min) | You can state when a directed graph has a tour using every edge once. |
| Review: max flow | §26.2 (3e) / §24.2 (4e), "The Ford-Fulkerson method" | The residual-graph idea; Edmonds-Karp is analyzed in this section (≈20 min) | You can explain what an augmenting path is and why Edmonds-Karp picks the shortest one. |
| Review: matching | §26.3 (3e), "Maximum bipartite matching" / Ch. 25 (4e) | How matching reduces to max flow (≈15 min) | You can describe the flow network that models bipartite matching. |

## Mastery criteria
- [ ] The purpose and complexity of each algorithm can be stated.
- [ ] Bridge-finding can be implemented with brief reference.
