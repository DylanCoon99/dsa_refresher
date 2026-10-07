# Accounts Merge
**Topic:** 13 Union-Find (Disjoint Sets) · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Accounts Merge" (title kept for cross-reference only)

## Problem
Each account is a list of strings: the first is a person's name and the rest are email addresses
belonging to that account. Two accounts belong to the same person if they share at least one email,
and this is transitive (if A shares an email with B and B shares one with C, all three are one person).
Accounts with the same name but no chain of shared emails are different people.

Merge the accounts. Return one row per person: the name followed by that person's distinct emails in
ascending (`std::string`) order. The rows may be returned in any order.

An email never appears under two different names.

## Examples
- `{{"A","a@x","b@x"},{"B","c@x"},{"A","b@x","d@x"}}` → `{{"A","a@x","b@x","d@x"},{"B","c@x"}}` (the first and third share `b@x`)
- `{{"A","a@x"},{"A","b@x"}}` → both rows unchanged (same name, no shared email)
- `{{"A","a@x","a@x","b@x"}}` → `{{"A","a@x","b@x"}}` (duplicate emails inside one account collapse)

## Constraints
- 1 ≤ accounts.size() ≤ 1000.
- Every account has a name followed by 1 to 10 emails (duplicates inside an account are allowed).
- Names and emails are non-empty strings of at most 30 characters, and an email is never listed under two different names.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(N · α(N) + N log N) for N total emails · Space: O(N)

## Hints
<details><summary>Hint 1</summary>Think of the accounts as the nodes. When should two accounts be joined, and how can you find that out quickly using the emails rather than comparing every pair of accounts?</details>
<details><summary>Hint 2</summary>Remember which account first claimed each email. When a later account lists an email already claimed, what should happen to the two accounts? After all the joining, how do you group the emails by set and put them in order?</details>
