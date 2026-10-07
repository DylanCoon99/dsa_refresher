# Number of Provinces
**Topic:** 13 Union-Find (Disjoint Sets) · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Number of Provinces" (title kept for cross-reference only)

## Problem
There are `n` cities. `isConnected` is an `n × n` matrix where `isConnected[i][j] == 1` means cities
`i` and `j` are directly connected and `0` means they are not. A province is a maximal group of cities
connected directly or through other cities. Return the number of provinces.

The matrix is symmetric and `isConnected[i][i] == 1` for every `i`.

## Examples
- `{{1,1,0},{1,1,0},{0,0,1}}` → `2` (cities 0 and 1 form one province, city 2 another)
- `{{1,0,0},{0,1,0},{0,0,1}}` → `3` (no connections: every city alone)
- `{{1}}` → `1`

## Constraints
- 1 ≤ n ≤ 200
- Every entry is `0` or `1`; the matrix is symmetric with ones on the diagonal.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(n² · α(n)) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>The matrix is an adjacency matrix of an undirected graph. What is a province in graph terms?</details>
<details><summary>Hint 2</summary>You can count components with a traversal from each unvisited city, or by starting with n groups and merging for every 1 you find. Which one reuses the structure from this topic?</details>
