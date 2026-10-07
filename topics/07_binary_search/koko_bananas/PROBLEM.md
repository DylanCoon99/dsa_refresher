# Koko Eating Bananas
**Topic:** 07 Binary Search · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Koko Eating Bananas" (title kept for cross-reference only)

## Problem
There are `n` piles of bananas; pile `i` has `piles[i]` bananas. Koko has `h` hours. She picks
an integer eating speed `k` (bananas per hour). Each hour she chooses one pile and eats up to
`k` bananas from it; if the pile has fewer than `k` left she finishes it and does nothing else
that hour. So pile `i` takes `ceil(piles[i] / k)` hours.

Return the **smallest** `k` such that she can finish every pile within `h` hours. A valid `k` always exists.

## Examples
- `piles = {3, 6, 7, 11}, h = 8` → `4` (1 + 2 + 2 + 3 = 8 hours)
- `piles = {30, 11, 23, 4, 20}, h = 5` → `30`; with h = n she must clear each pile in one hour
- `piles = {30, 11, 23, 4, 20}, h = 6` → `23`

## Constraints
- 1 ≤ n ≤ 10⁴
- 1 ≤ piles[i] ≤ 10⁹
- n ≤ h ≤ 10⁹
- The total hours for a given speed can reach about 10¹³, which does not fit in a 32-bit `int`.

## Target
Time: O(n · log(max pile)) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>If speed k is fast enough, is every larger speed fast enough too? What does that monotonic yes/no pattern let you do over the range of speeds?</details>
<details><summary>Hint 2</summary>What are the smallest and largest speeds worth trying? Write a function hours(k) first, and ask what type it must return when k = 1 and the piles are huge.</details>
