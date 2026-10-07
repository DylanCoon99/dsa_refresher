# Union-Find
**Topic:** 13 Union-Find (Disjoint Sets) · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement a disjoint-set (union-find) structure over the elements `0 .. n-1`:

```cpp
class UnionFind {
public:
    explicit UnionFind(int n);          // n singleton sets {0}, {1}, ..., {n-1}
    int find(int x);                    // representative of x's set
    bool unite(int a, int b);           // merge the sets of a and b
    bool connected(int a, int b);       // are a and b in the same set?
    int componentCount() const;         // current number of sets
    int componentSize(int x);           // number of elements in x's set
};
```

Rules:
- `find(x)` returns the set's representative: `find(a) == find(b)` exactly when `a` and `b` are in
  the same set, and a freshly constructed structure has `find(x) == x`. Which member represents a
  set after a merge is up to you.
- `unite(a, b)` returns `true` if it merged two different sets and `false` if `a` and `b` were already
  connected (including `a == b`).
- Use **path compression** and **union by rank or size**. Neither is checked on its own; see Target.
- Every method's argument is in `[0, n)`.

Time yourself; the mastery criterion is under 5 minutes from memory.

## Examples
- `UnionFind uf(5); uf.unite(0, 1)` → `true`; `uf.unite(1, 2)` → `true`; `uf.connected(0, 2)` → `true`; `uf.componentCount()` → `3`
- `uf.unite(2, 0)` → `false` (already connected); `uf.componentSize(0)` → `3`; `uf.componentSize(3)` → `1`
- `uf.unite(4, 4)` → `false` (an element is always connected to itself)

## Constraints
- 1 ≤ n ≤ 10⁶
- Up to about 10⁶ operations per structure.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(α(n)) amortized per operation (effectively constant) · Space: O(n)

What the large test can and cannot tell apart: it builds one chain of 10⁶ elements with
`unite(i, i+1)` and a second with `unite(i+1, i)`, then calls `find(0)` 10⁶ times on each. A solution
that has neither optimization and always links "first argument's root under second's" (or the
reverse) builds a path of length 10⁶ in one of the two chains and makes each `find(0)` walk it,
so it times out. The test does **not** require both optimizations: a solution with only union by
size, or only path compression (written iteratively), also finishes in time. Writing a recursive
`find` without union by size/rank can overflow the call stack on the 10⁶-long chain (under the
sanitizer build this shows up as a CRASH). Check your own solution against the Review bullets
rather than relying on the test to prove both heuristics are present.

## CLRS (optional, ≈20 min)
- §21.3 (3e) / §19.3 (4e), "Disjoint-set forests": the two heuristics (union by rank, path compression) and the pseudocode (≈15 min). Skip the amortized analysis.
- §21.1 (3e) / §19.1 (4e), "Disjoint-set operations": the connected-components application (≈5 min).
- Skip if: you can explain what each heuristic does to the tree and write `find` and `unite` without looking.

## Hints
<details><summary>Hint 1</summary>Store each element's parent in an array, with a root being its own parent. What does <code>find</code> do, and what single assignment performs a union?</details>
<details><summary>Hint 2</summary>Which root should become the child when two trees merge, so that trees stay shallow? And after <code>find</code> walks up to the root, what could you change on the way so the next <code>find</code> is cheaper?</details>
