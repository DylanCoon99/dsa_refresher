# Min Cost to Connect Points
**Topic:** 14 Shortest Paths and Minimum Spanning Trees · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Min Cost to Connect All Points" (title kept for cross-reference only)

## Problem
`points[i] = {x, y}` is a point on the plane. You may connect any two points with a cable whose
cost is their **Manhattan distance**, `|x1 - x2| + |y1 - y2|`. Return the minimum total cost
needed so that every pair of points is connected, directly or through other points. With a
single point the answer is `0`.

## Examples
- `{{0,0},{2,2},{3,10},{5,2},{7,0}}` → `20`
- `{{3,12},{-2,5},{-4,1}}` → `18`
- `{{5,5}}` → `0`

## Constraints
- 1 ≤ points.size() ≤ 1000.
- -10⁶ ≤ x, y ≤ 10⁶, and all points are distinct.
- The answer fits in an `int` for every test input.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n²) (dense Prim) or O(n² log n) (Kruskal on all pairs) · Space: O(n) or O(n²)

The large test uses 1000 points. Both dense Prim and Kruskal on all n² pairs pass; slower
approaches such as growing the tree by rescanning every pair at every step (O(n³)) time out.

## CLRS (optional, ≈10 min)
- §23.1 (3e) / §21.1 (4e), "Growing a minimum spanning tree": the cut-property theorem statement (≈10 min). The Kruskal/Prim section (§23.2 / §21.2) is covered under `kruskal`.
- Skip if: you can state why the lightest edge crossing any cut belongs to some MST.

## Hints
<details><summary>Hint 1</summary>Treat each point as a vertex and every pair as an edge weighted by the distance. What are you asked to compute on this complete graph?</details>
<details><summary>Hint 2</summary>With n up to 1000 there are about 500,000 edges. Is it cheaper to sort them all and use union-find, or to grow one tree and keep, for every outside point, its cheapest distance to the tree?</details>
