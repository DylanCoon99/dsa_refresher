# Valid Palindrome
**Topic:** 03 Two Pointers · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Valid Palindrome" (title kept for cross-reference only)

## Problem
Return `true` if the string reads the same forwards and backwards once you ignore everything
except letters and digits and treat upper and lower case as equal. Otherwise return `false`.
A string with no letters or digits at all counts as a palindrome.

## Examples
- `"A man, a plan, a canal: Panama"` → `true` (it becomes `amanaplanacanalpanama`)
- `"race a car"` → `false` (it becomes `raceacar`)
- `" "` → `true` (nothing remains)

## Constraints
- 0 ≤ length ≤ 2·10⁵
- Printable ASCII characters

## Target
Time: O(n) · Space: O(1)

## Hints
<details><summary>Hint 1</summary>Put one index at each end and compare the characters they point to. You don't have to build a cleaned-up copy.</details>
<details><summary>Hint 2</summary>If an index points at a punctuation mark or space, which way should it move without comparing anything?</details>
