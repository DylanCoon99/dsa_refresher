# 01 · Complexity Analysis: Answer Key

Check these only after finishing the worksheet. Logs are base 2 unless stated.

---

## 1. Merge sort

**Recurrence.** Split into two halves, sort each recursively, merge in linear time:

T(n) = 2T(n/2) + Θ(n), T(1) = Θ(1).

**Recursion tree.** Write the merge cost as cn.

```
level 0:   1 node  of size n      cost cn
level 1:   2 nodes of size n/2    cost 2 · c(n/2)   = cn
level 2:   4 nodes of size n/4    cost 4 · c(n/4)   = cn
  ...
level k:   2^k nodes of size n/2^k  cost 2^k · c(n/2^k) = cn
  ...
leaves:    n nodes of size 1      cost n · Θ(1)     = Θ(n)
```

- The tree stops when n/2^k = 1, i.e. k = log₂ n, so there are log₂ n + 1 levels (log₂ n levels of merging plus the leaf level).
- Every level costs cn.
- Total = cn · log₂ n + Θ(n) = **Θ(n log n)**. This holds for best, average and worst case, since the split is always even.

**Summary:** log₂n levels × cn per level → Θ(n log n); space Θ(n) for the merge buffer.

**Space.** The merge needs a temporary buffer of up to n elements: **Θ(n)** auxiliary space. The recursion depth adds only Θ(log n), which is dominated by the buffer.

---

## 2. Binary search

Each step compares with the middle element and discards half of the range.

**Recurrence:** T(n) = T(n/2) + Θ(1), T(1) = Θ(1).

**Solution.** Unrolling: T(n) = T(n/2^k) + k·c. It bottoms out at k = log₂ n, giving T(n) = Θ(1) + c·log₂ n = **Θ(log n)**. (Master Theorem: a=1, b=2, n^(log_b a) = n⁰ = 1 = Θ(f(n)), case 2.)

**Space.**
- **Iterative:** a few index variables (lo, hi, mid). **O(1)** extra space.
- **Recursive:** one stack frame per halving, depth log₂ n. **O(log n)** extra space. (A compiler may turn the tail call into a loop, but you cannot count on it.)

**Summary:** T(n)=T(n/2)+Θ(1) → Θ(log n); iterative O(1) space, recursive O(log n) stack.

---

## 3. Build-heap

**Why n × O(log n) is loose.** It charges every sift-down the full height of the tree. But a sift-down from a node at height h costs at most O(h), and most nodes are near the bottom, where h is tiny. About half the nodes are leaves (h = 0, cost 0), a quarter have h = 1, an eighth have h = 2, and so on. Only the root costs log n.

**Derivation.** A heap of n nodes has at most ⌈n/2^(h+1)⌉ nodes at height h. Summing the sift-down costs over all heights:

Σ_{h=0}^{⌊log n⌋} ⌈n/2^(h+1)⌉ · O(h)
= O( n · Σ_{h=0}^{⌊log n⌋} h/2^(h+1) )
= O( (n/2) · Σ_{h=0}^{⌊log n⌋} h/2^h )
≤ O( n · Σ_{h=0}^{∞} h/2^h ).

(The ceiling adds at most one extra node per height, which contributes O(Σ h) = O(log² n), which is O(n).)

**The sum.** For |x| < 1, Σ_{h=0}^{∞} x^h = 1/(1−x). Differentiating and multiplying by x gives Σ_{h=0}^{∞} h·x^h = x/(1−x)². At x = 1/2:

Σ h/2^h = (1/2) / (1/2)² = (1/2) / (1/4) = **2**.

So the total is O(n · 2) = **O(n)**. Since build-heap also has to touch every node, it is Θ(n).

---

## 4. Recursive Fibonacci

```
fib(n) = n                      if n ≤ 1
fib(n) = fib(n-1) + fib(n-2)    otherwise
```

**Without memoization.**
- Time: T(n) = T(n−1) + T(n−2) + Θ(1). This is the Fibonacci recurrence itself, with solution T(n) = Θ(φⁿ), where φ = (1+√5)/2 ≈ 1.618 is the positive root of x² = x + 1. So **Θ(φⁿ) ≈ O(1.618ⁿ)**. This is within O(2ⁿ): T(n) ≤ 2T(n−1) gives the cruder upper bound 2ⁿ.
- Space: the call tree is deep on the left spine only. The longest chain of live frames is fib(n) → fib(n−1) → … → fib(1), so the stack depth is **O(n)**. (Siblings run one after another, so they don't add up.)

**With memoization.**
- Time: each of fib(0)…fib(n) is computed once, with Θ(1) work beyond the recursive calls (cached lookups are Θ(1)). Total **Θ(n)**.
- Space: the memo table holds n+1 values, and the stack depth is still n. Total **Θ(n)**.

---

## 5. Master Theorem

For T(n) = aT(n/b) + f(n), compare f(n) with n^(log_b a):
- Case 1: f(n) = O(n^(log_b a − ε)) for some ε > 0, so T(n) = Θ(n^(log_b a)).
- Case 2: f(n) = Θ(n^(log_b a)), so T(n) = Θ(n^(log_b a) · log n).
- Case 3: f(n) = Ω(n^(log_b a + ε)) plus the regularity condition, so T(n) = Θ(f(n)).

| | a, b | n^(log_b a) | f(n) vs. it | Case | Result |
|---|---|---|---|---|---|
| (a) | 2, 2 | n | f = n, equal | 2 | **Θ(n log n)** |
| (b) | 1, 2 | n⁰ = 1 | f = 1, equal | 2 | **Θ(log n)** |
| (c) | 2, 2 | n | f = 1 = O(n^(1−ε)), ε = 1 | 1 | **Θ(n)** |
| (d) | 4, 2 | n² | f = n = O(n^(2−ε)), ε = 1 | 1 | **Θ(n²)** |
| (e) | 7, 2 | n^(log₂7) ≈ n^2.81 | f = n² = O(n^(2.81−ε)), ε ≈ 0.81 | 1 | **Θ(n^(log₂7)) ≈ Θ(n^2.81)** |
| (f) | 2, 2 | n | f = n log n | see below | **Θ(n log² n)** |

**(f) in detail.** Here n^(log_b a) = n and f(n) = n log n.
- It is not case 2, since f(n) ≠ Θ(n).
- It is not case 3: f(n) = n log n is larger than n, but not **polynomially** larger. For any ε > 0, n log n ≠ Ω(n^(1+ε)), because log n grows slower than n^ε. So the three-case theorem (3e) **does not apply**.
- The 4e extended case 2: if f(n) = Θ(n^(log_b a) · log^k n) for some k ≥ 0, then T(n) = Θ(n^(log_b a) · log^(k+1) n). With k = 1 this gives **Θ(n log² n)**.
- Sanity check with the recursion tree: each of the log n levels costs Σ over nodes of (n/2^i) log(n/2^i) · 2^i = n(log n − i). Summing over i = 0..log n gives n · Θ(log² n).

---

## 6. Amortized analysis

**Doubling.** Start with capacity 1. An append into a non-full array costs 1 write. When the array is full at size k, the append first allocates capacity 2k and copies k elements, then writes.

Over n appends, resizes happen when the size is 1, 2, 4, …, 2^j, where 2^j < n, i.e. j ≤ ⌊log₂(n−1)⌋. The total copy cost is

1 + 2 + 4 + … + 2^j = 2^(j+1) − 1 < 2n.

(Equivalently, copies ≤ n + n/2 + n/4 + … < 2n if you count back from n.) The writes cost n. So the total is < 3n = **O(n)**, and the amortized cost per append is O(1).

Intuition via the accounting method: charge 3 per append. 1 pays for the write, 2 are saved as credit. When the array of size k doubles, the k/2 elements added since the last resize have saved k credits, which pay for copying all k elements.

**Growing by a constant 10.** Resizes happen when the size is 10, 20, 30, …, up to about n, i.e. every 10 appends, about n/10 resizes. Resize number i copies 10·i elements, so

copies = 10 + 20 + … + 10·(n/10) = 10 · (n/10)(n/10 + 1)/2 ≈ n²/20 = **Θ(n²)**.

The amortized cost per append is then Θ(n), not O(1). Any constant increment gives Θ(n²); growth must be a constant **factor** to be amortized O(1).

---

## 7. Input-size table

Budget ≈ 10⁸ simple operations per second.

| Complexity | Solve f(n) ≲ 10⁸ | Largest practical n |
|---|---|---|
| O(n!) | 11! ≈ 4·10⁷ (12! ≈ 4.8·10⁸ is too slow) | **~11** |
| O(2ⁿ) | 2²⁵ ≈ 3.4·10⁷ (2²⁷ ≈ 1.3·10⁸) | **~25** |
| O(n³) | n ≈ (10⁸)^(1/3) ≈ 464 | **~450** |
| O(n²) | n = √10⁸ = 10⁴ | **~10⁴** |
| O(n log n) | 5·10⁶ · log₂(5·10⁶) ≈ 5·10⁶ · 22 ≈ 1.1·10⁸ | **~5·10⁶** |
| O(n) | n = 10⁸ | **~10⁸** |

These are rough, to within a small constant factor. Constants matter in practice, but the orders of magnitude are what to remember.
