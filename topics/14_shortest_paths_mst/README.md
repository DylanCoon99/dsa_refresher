# 14 · Shortest Paths and Minimum Spanning Trees
Run everything: `./dsa test 14` · Status: `./dsa list 14`

## Diagnostic
Attempt cold (≤ 40 min each): `network_delay`, `cheapest_flights_k_stops`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Dijkstra's algorithm with a binary heap, the lazy-deletion technique, and why negative edge weights break it.
- [ ] Bellman-Ford and negative-cycle detection.
- [ ] Floyd-Warshall.
- [ ] 0-1 BFS.
- [ ] Prim's and Kruskal's algorithms, and the cut property.

## Implement
- [ ] `dijkstra`: Dijkstra's algorithm with a heap · `./dsa test 14/dijkstra`
- [ ] `kruskal`: Kruskal's algorithm using the union-find structure from Topic 13 · `./dsa test 14/kruskal`

## Practice
⭐ = interview priority: do these first if you're short on time.
- [ ] `network_delay` · Medium · `./dsa test 14/network_delay` · ⭐ interview priority
- [ ] `min_effort_path` · Medium · `./dsa test 14/min_effort_path`
- [ ] `cheapest_flights_k_stops` · Medium · `./dsa test 14/cheapest_flights_k_stops` · ⭐ interview priority
- [ ] `min_cost_connect_points` · Medium · `./dsa test 14/min_cost_connect_points`
- [ ] `swim_rising_water` · Hard · `./dsa test 14/swim_rising_water`

## CLRS quick reference (≈75 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `dijkstra` | Ch. 24 (3e) / Ch. 22 (4e), "Single-Source Shortest Paths" (intro) | Relaxation and why negative weights matter (≈10 min) | You can explain what relaxing an edge does and why a negative edge breaks the greedy finalization. |
| Before `dijkstra` | §24.3 (3e) / §22.3 (4e), "Dijkstra's algorithm" | The pseudocode and the correctness theorem statement (≈15 min) | You can write Dijkstra with a heap and lazy deletion from memory. |
| Before `cheapest_flights_k_stops` | §24.1 (3e) / §22.1 (4e), "The Bellman-Ford algorithm" | The relaxation rounds; k+1 rounds bound the edge count (≈15 min) | You can explain why V-1 rounds suffice and how one more round detects a negative cycle. |
| Review only | §25.2 (3e) / §23.2 (4e), "The Floyd-Warshall algorithm" | The recurrence and the triple loop (≈10 min) | You can write the three nested loops and say what the loop variable in the outermost one means. |
| Before `kruskal` | §23.1 (3e) / §21.1 (4e), "Growing a minimum spanning tree" | The cut-property theorem statement (≈10 min) | You can state why the lightest edge crossing any cut belongs to some MST. |
| Before `kruskal` | §23.2 (3e) / §21.2 (4e), "The algorithms of Kruskal and Prim" | Both algorithms and their implementations (≈15 min) | You can write Kruskal with union-find and say when Prim is the better choice. |

0-1 BFS is not in CLRS.

## Mastery criteria
- [ ] The correct shortest-path algorithm can be selected from the graph's properties (weighted or unweighted, negative weights, single-source or all-pairs).
- [ ] Dijkstra's algorithm can be written from memory.
