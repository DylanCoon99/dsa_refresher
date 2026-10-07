# Edit Distance
**Topic:** 16 Dynamic Programming · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Edit Distance" (title kept for cross-reference only)

## Problem
Find the minimum number of single-character operations that turn `word1` into `word2`. The operations are:
insert a character, delete a character, and replace one character by another.

```cpp
int minDistance(const std::string& word1, const std::string& word2);
```

**Before coding, write a comment** with the *state*, the *transition*, the *base cases* and the *evaluation order*.

## Examples
- `"horse"` → `"ros"`: `3` (replace h with r, delete r, delete e)
- `"intention"` → `"execution"`: `5`
- `""` → `"abc"`: `3` (three insertions)

## Constraints
- 0 ≤ word1.size(), word2.size() ≤ 500; lowercase letters only.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(|word1| · |word2|) · Space: O(|word1| · |word2|) (O(min) with rolling rows)

The large test (500 × 500) rejects the cache-free three-way recursion, which is exponential.

## CLRS (optional, ≈10 min)
- Ch. 15 (3e) / Ch. 14 (4e), "Dynamic Programming": the end-of-chapter problem "Edit distance" (≈10 min). Set up the recurrence yourself before reading further.
- Skip if: you can write the recurrence for `dist(i, j)` including what each of the three operations corresponds to.

## Hints
<details><summary>Hint 1</summary>Let <code>d[i][j]</code> be the distance between the first <code>i</code> characters of <code>word1</code> and the first <code>j</code> of <code>word2</code>. What is <code>d[i][0]</code>? What is <code>d[0][j]</code>?</details>
<details><summary>Hint 2</summary>Look at the last characters. If they are equal, what is free? If not, the last operation is an insert, a delete or a replace; which neighbouring cell does each one come from?</details>
