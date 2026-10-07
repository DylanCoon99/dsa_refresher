# Time-Based Key-Value Store
**Topic:** 07 Binary Search · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Time Based Key-Value Store" (title kept for cross-reference only)

## Problem
Implement a class `TimeMap` that stores several values per key, each tagged with a timestamp.

- `void set(const std::string& key, const std::string& value, int timestamp)`: store `value` for `key` at `timestamp`. For a given key, the timestamps passed to successive `set` calls are **strictly increasing**. Different keys have independent timestamps.
- `std::string get(const std::string& key, int timestamp) const`: return the value stored for `key` with the **largest timestamp ≤ `timestamp`**. Return `""` if the key is unknown or every stored timestamp for it is greater than `timestamp`.

## Examples
- `set("love", "high", 10); set("love", "low", 20)`
  - `get("love", 10)` → `"high"`; exact match
  - `get("love", 15)` → `"high"`; the latest entry at or before 15 is the one at 10
  - `get("love", 25)` → `"low"`
  - `get("love", 5)` → `""`; before the first entry
- `get("hate", 10)` → `""`; unknown key

## Constraints
- At most 2·10⁵ calls to `set` and `get` combined
- 1 ≤ timestamp ≤ 10⁹ for both methods
- Keys and values are non-empty strings of at most 100 characters

## Target
Time: O(1) per `set` and O(log k) per `get`, where k is the number of entries for that key · Space: O(total entries)

## Hints
<details><summary>Hint 1</summary>Because timestamps only increase per key, what order is each key's list of entries already in?</details>
<details><summary>Hint 2</summary>"Largest timestamp ≤ t" is "the entry just before the first timestamp > t". Which of the bound functions from `bounds` finds that position?</details>
