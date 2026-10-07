# LRU Cache
**Topic:** 08 Linked Lists · **Kind:** Implement + Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "LRU Cache" (title kept for cross-reference only)

## Problem
Implement a fixed-capacity cache named `LRUCache` that evicts the **least recently used** entry when it is full.

- `explicit LRUCache(int capacity)`: the cache holds at most `capacity` entries.
- `int get(int key)`: return the value stored for `key`, or `-1` if `key` is not in the cache. A successful `get` makes `key` the most recently used.
- `void put(int key, int value)`: store `value` under `key` and make `key` the most recently used. If `key` already exists, update its value; this never evicts anything. If `key` is new and the cache is already full, first evict the least recently used entry.

Both operations must run in **O(1)** time. Values are never negative, so `-1` is unambiguous. (The tests also cannot enforce O(1) exactly; they only reject solutions that scan the entries on every operation.)

## Examples
- capacity 2: `put(1,1)`, `put(2,2)`, `get(1)` → `1`, `put(3,3)` evicts key 2, `get(2)` → `-1`, `put(4,4)` evicts key 1, `get(1)` → `-1`, `get(3)` → `3`, `get(4)` → `4`
- capacity 1: `put(1,10)`, `put(2,20)` evicts key 1; `get(1)` → `-1`, `get(2)` → `20`
- capacity 2: `put(1,1)`, `put(2,2)`, `put(1,100)` (update, no eviction), `put(3,3)` evicts key 2; `get(1)` → `100`

## Constraints
- 1 ≤ capacity ≤ 10⁴
- Up to 2·10⁵ operations per test (the large test uses exactly 2·10⁵).
- Keys are any `int`; 0 ≤ value ≤ 10⁹ (the tests use keys up to 6·10⁴ and values up to 10⁹).

## Target
Time: O(1) per operation · Space: O(capacity)

## CLRS (optional, ≈10 min)
- §10.2 (3e) / §10.2 (4e), "Linked lists": re-read the sentinel version of LIST-DELETE; moving a node to the front is one delete plus one insert.
- Skip if: you can splice a node out of a doubly linked list and re-insert it at the front without any head/tail special case.

## Hints
<details><summary>Hint 1</summary>You need two things in O(1): find an entry by key, and know which entry is oldest. Which structure gives each?</details>
<details><summary>Hint 2</summary>If the hash map stores a pointer to the entry's node in a doubly linked list ordered by recency, what does a "touch" cost?</details>
