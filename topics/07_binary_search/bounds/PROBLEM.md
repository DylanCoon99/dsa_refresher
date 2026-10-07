# Lower and Upper Bound
**Topic:** 07 Binary Search · **Kind:** Implement · **Difficulty:** Medium

## Problem
Given a vector `a` sorted in non-decreasing order (duplicates allowed) and an `int x`, implement two
functions that behave exactly like `std::lower_bound` and `std::upper_bound`, returning **indices**:

- `std::size_t lowerBound(const std::vector<int>& a, int x)`: the index of the first element that is `>= x`, or `a.size()` if there is none.
- `std::size_t upperBound(const std::vector<int>& a, int x)`: the index of the first element that is `> x`, or `a.size()` if there is none.

Both must be **iterative** and must not use anything from `<algorithm>`. Above each loop, write
your **loop invariant as a comment** (what is true about the answer and the search range at the
top of every iteration), and say why it holds at the start, is kept by each iteration, and
gives the answer when the loop ends.

## Examples
- `a = {1, 2, 2, 2, 5}, x = 2` → `lowerBound = 1`, `upperBound = 4`; the equal run occupies indices 1 to 3
- `a = {1, 2, 2, 2, 5}, x = 3` → both return `4`; nothing equals 3, so both point at the 5
- `a = {}, x = 7` → both return `0`

## Constraints
- 0 ≤ n ≤ 10⁶
- Any `int` values in `a` and for `x`, including `INT_MIN` and `INT_MAX`.

## Target
Time: O(log n) · Space: O(1)

## CLRS (optional, ≈10 min)
- §2.1 (3e) / §2.1 (4e), "Insertion sort": read only the loop-invariant discussion (initialization, maintenance, termination).
- Skip if: you can state your loop's invariant precisely.

## Hints
<details><summary>Hint 1</summary>Keep a half-open range [lo, hi) of indices that might still hold the answer. What is true of everything left of lo, and everything at or right of hi?</details>
<details><summary>Hint 2</summary>The two functions differ by a single comparison. Which one of "a[mid] < x" and "a[mid] <= x" belongs to which function, and which half do you discard in each case?</details>
