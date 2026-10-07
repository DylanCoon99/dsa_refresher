# 01 · Complexity Analysis Worksheet

Work these by hand, on paper or in this file. Write each answer on the **Your answer:** line (or below it).

---

## 1. Merge sort

Derive the recurrence and the closed-form running time of **merge sort**. Draw the recursion tree and give the per-level cost and the number of levels.

**Your answer:**

---

## 2. Binary search

**Binary search** on n sorted elements: give the recurrence and its solution, for both the iterative and the recursive version. State the extra space each uses.

**Your answer:**

---

## 3. Build-heap

**Build-heap** (bottom-up heapify): explain why the naive "n sift-downs × O(log n)" bound is loose, and derive O(n) using the sum Σ h · n/2^(h+1).

**Your answer:**

---

## 4. Recursive Fibonacci

Give the running time of recursive **Fibonacci** without memoization (a bound in terms of φ, or at least O(2ⁿ)) and with memoization. Also give the recursion-stack space for each.

**Your answer:**

---

## 5. Master Theorem

Apply the **Master Theorem**, naming the case, to each recurrence.

- (a) T(n) = 2T(n/2) + n
- (b) T(n) = T(n/2) + 1
- (c) T(n) = 2T(n/2) + 1
- (d) T(n) = 4T(n/2) + n
- (e) T(n) = 7T(n/2) + n²
- (f) T(n) = 2T(n/2) + n log n

**Your answer:**

---

## 6. Amortized analysis

Show that n appends to a dynamic array that doubles when full cost O(n) in total. Then show that the total becomes Θ(n²) if the array instead grows by a constant 10 slots each time.

**Your answer:**

---

## 7. Input-size table

For a 1-second limit (about 10⁸ simple operations), give the largest n that is practical for each class.

| Complexity | Largest practical n |
|---|---|
| O(n!) | |
| O(2ⁿ) | |
| O(n³) | |
| O(n²) | |
| O(n log n) | |
| O(n) | |

**Your answer:**

---

*From Topic 02 on, write the time and space complexity in a comment before running the tests.*
