# Repeated String Match
**Topic:** 21 String Algorithms · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Repeated String Match" (title kept for cross-reference only)

## Problem
Given non-empty strings `a` and `b`, return the smallest number `k ≥ 1` such that `b` is a substring of `a` written `k` times in a row (`a + a + ... + a`). Return `-1` if no such `k` exists.

## Examples
- `a = "abcd"`, `b = "cdabcdab"` → `3`: `"abcdabcdabcd"` contains `b`, and two copies do not
- `a = "abc"`, `b = "bc"` → `1`: `b` is already inside `a`
- `a = "abc"`, `b = "acb"` → `-1`: no number of copies helps

## Constraints
- `1 ≤ |a|, |b| ≤ 10⁴` (limits chosen for this exercise; the tests stay inside them). Characters are arbitrary; the tests use lowercase letters.

## Target
Time: O(|a| + |b|) with KMP, or O(|b| · (|a| + |b|)) is accepted by the tests · Space: O(|a| + |b|)

## Hints
<details><summary>Hint 1</summary>How many copies of `a` are needed just to be at least as long as `b`? If `b` appears at all, where can it start (inside the first copy), and how many extra copies can that push you to?</details>
<details><summary>Hint 2</summary>Only two candidates matter: the smallest k with `k * |a| >= |b|`, and that k plus one. Why is trying anything larger pointless, and what do you return if both fail?</details>
