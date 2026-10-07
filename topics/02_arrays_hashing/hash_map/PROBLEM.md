# Hash Map
**Topic:** 02 Arrays and Hashing · **Kind:** Implement · **Difficulty:** Medium

## Problem
Build a hash map from `std::string` keys to `int` values, using **separate chaining**: each
bucket holds a chain of key/value entries. A `std::vector<std::list<std::pair<std::string,int>>>`
works, or you may write your own nodes.

Required API:
- `explicit HashMap(std::size_t initial_buckets = 8)`: start with `initial_buckets` buckets (at least 1).
- `void put(key, value)`: insert, or overwrite the value if the key is already present.
- `std::optional<int> get(key) const`: the value, or `std::nullopt` if the key is absent.
- `bool erase(key)`: remove the key; return `true` if it was present, `false` otherwise.
- `std::size_t size() const`: number of distinct keys stored.
- `std::size_t bucketCount() const`: current number of buckets.

Resizing: after an insert that adds a **new** key, if `size() > 0.75 * bucketCount()`, double the
number of buckets and rehash every entry into the new table. Overwriting an existing key never
changes `size()` and never triggers a resize.

You may use `std::hash<std::string>` to hash keys. You may **not** use `std::unordered_map`
or `std::unordered_set`.

## Examples
- Fresh `HashMap()`: `size() == 0`, `bucketCount() == 8`, `get("a")` is empty.
- `put("a", 1); put("a", 2);` → `size() == 1`, `get("a") == 2`.
- 7 distinct inserts into a map with 8 buckets: 7 > 6 = 0.75 · 8, so `bucketCount() == 16`.

## Constraints
- Up to 2·10⁵ operations.
- Keys have at most 20 characters.

## Target
Time: O(1) expected per operation (amortized, counting resizes) · Space: O(n)

## CLRS (optional, ≈25 min)
- §11.2 (3e) / §11.2 (4e), "Hash tables": chaining and the load factor α (≈15 min).
- §11.4 (3e) / §11.4 (4e), "Open addressing": intro only, for the comparison with chaining (≈10 min).
- Skip if: you can explain α and why resizing keeps operations O(1) amortized.

## Hints
<details><summary>Hint 1</summary>Index a bucket with <code>std::hash&lt;std::string&gt;{}(key) % bucketCount()</code>. Each operation then only scans one short chain.</details>
<details><summary>Hint 2</summary>When the bucket count changes, every key's bucket index changes too. What must you do to the existing entries?</details>
