# Stage 2a: Topics 02–05 (Tasks 5–8)

Read `00-index.md` first. Every task here follows its **Exercise Authoring Procedure**:
- section A for PROBLEM.md, B for test.cpp, C for the solution comment, D for the README;
- the steps in section E.

**How to read each exercise entry:**
- **Sig** is the exact stub signature.
- **Constraints** goes verbatim into PROBLEM.md.
- **Tests** lists the cases that are *required* in addition to the template's standard groups.
- **Large** defines the large-input test. If there is no Large line, there is no large test.
- **CLRS** is the PROBLEM.md pointer. If there is no CLRS line, there is no CLRS section.

All exercises depend only on `common/` (Task 1) and `./dsa` (Task 3).

---

### Task 5: Topic 02 Arrays and Hashing

`TOPIC=02_arrays_hashing`, `NN=02`. `two_sum` already exists (Task 2): the README lists it, but don't recreate it.

**Diagnostic picks:** `group_anagrams`, `product_except_self`.

**Exercises:**

- **`hash_map`** · Implement · Medium
  - Sig:
    ```cpp
    class HashMap { public: explicit HashMap(std::size_t initial_buckets = 8); void put(const std::string& key, int value); std::optional<int> get(const std::string& key) const; bool erase(const std::string& key); std::size_t size() const; std::size_t bucketCount() const; };
    ```
  - Contract:
    - Separate chaining with `std::vector<std::list<std::pair<std::string,int>>>` or your own nodes.
    - When `size() > 0.75 * bucketCount()` after an insert, double the buckets and rehash.
    - `std::hash<std::string>` is allowed; `std::unordered_map` is not (say so in PROBLEM.md).
  - Constraints: up to 2·10⁵ operations; keys up to 20 chars.
  - Tests:
    - overwrite keeps `size()` unchanged;
    - erasing a missing key returns false;
    - `bucketCount()` is 8 initially and ≥ 16 after 7 inserts;
    - load factor stays ≤ 0.75 after each of 1000 inserts;
    - `HashMap(1)` works;
    - randomized: 20 000 mixed ops vs `std::unordered_map` over 50 keys.
  - Large: 2·10⁵ distinct inserts then lookups. A map that never resizes degrades to O(n) chains, giving ~10¹⁰/8 comparisons.
  - CLRS: §11.2 (3e) / §11.2 (4e), "Hash tables": chaining and load factor α (≈15 min). Also §11.4, "Open addressing": intro only, for the comparison (≈10 min). Skip if you can explain α and why resizing keeps operations O(1) amortized.
- **`contains_duplicate`** · Easy
  - Sig: `bool containsDuplicate(const std::vector<int>& nums)`
  - Constraints: 1 ≤ n ≤ 10⁵, values fit in int.
  - Tests: single element; INT_MIN and INT_MAX together; duplicate at the far ends.
  - Large: n = 10⁵ distinct values.
- **`valid_anagram`** · Easy
  - Sig: `bool isAnagram(const std::string& s, const std::string& t)`
  - Constraints: lowercase a–z; length ≤ 5·10⁴.
  - Tests: different lengths; same letters with different counts (`"aab"` / `"abb"`); both empty → true.
- **`group_anagrams`** · Medium
  - Sig: `std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs)`
  - Constraints: n ≤ 10⁴; lengths ≤ 100; lowercase.
  - Tests:
    - normalize before comparing (sort within each group, then sort the groups);
    - the empty string is its own group;
    - duplicate words stay duplicated;
    - randomized against brute-force grouping by pairwise sorted-key comparison.
  - Large: 10⁴ words of length 100. Pairwise grouping is ~5·10⁷ string compares of length 100, which times out.
- **`top_k_frequent`** · Medium
  - Sig: `std::vector<int> topKFrequent(const std::vector<int>& nums, int k)`
  - Contract: the answer is unique; any order.
  - Constraints: n ≤ 10⁵; 1 ≤ k ≤ number of distinct values.
  - Tests: normalize by sorting; k equals the number of distinct values; negative values.
  - CLRS: §9.2 (3e) / §9.2 (4e), "Selection in expected linear time": intro and RANDOMIZED-SELECT pseudocode (≈15 min). Skip if you know why bucket sort by frequency gives O(n).
- **`product_except_self`** · Medium
  - Sig: `std::vector<int> productExceptSelf(const std::vector<int>& nums)`
  - Contract: no division. Every prefix and suffix product fits in int.
  - Constraints: 2 ≤ n ≤ 10⁵; −30 ≤ nums[i] ≤ 30.
  - Tests: one zero; two zeros (all outputs 0); negatives; n = 2.
  - Large: n = 10⁵ of ±1.
- **`longest_consecutive`** · Medium
  - Sig: `int longestConsecutive(const std::vector<int>& nums)`
  - Constraints: 0 ≤ n ≤ 10⁵; values fit in int.
  - Tests: empty → 0; duplicates (`{1,2,2,3}` → 3); a run crossing zero; INT_MAX next to INT_MAX−1 with no overflow when testing `x+1`.
  - Large: 10⁵ values forming one shuffled run. Naive "for each x, walk upward with set lookups" without the start-of-run check is O(n²).

**CLRS quick reference rows (README):**
- Hash table design: §11.2 / §11.2, "Hash tables", ≈15 min.
- Hash functions: §11.3 / §11.3, "Hash functions"; division and multiplication methods only, ≈10 min.
- Open addressing: §11.4 / §11.4, "Open addressing"; intro and linear probing, ≈10 min.
- Dynamic array growth: §17.4 / §16.4, "Dynamic tables", ≈15 min.

---

### Task 6: Topic 03 Two Pointers

`TOPIC=03_two_pointers`, `NN=03`. The README states "Not directly covered by CLRS" (plan) and has no CLRS table.

**Diagnostic picks:** `three_sum`, `container_most_water`.

**Exercises:**

- **`dedup_sorted`** · Implement · Easy
  - Sig: `int removeDuplicates(std::vector<int>& nums)`
  - Contract: in place; the first k entries are the unique values in order; return k.
  - Constraints: n ≤ 3·10⁴, sorted ascending.
  - Tests: empty; all equal; already unique; only the first k entries are checked.
- **`partition_pivot`** · Implement · Medium
  - Sig: `std::size_t partitionAround(std::vector<int>& nums, int pivot)`
  - Contract: rearrange in place so that all values < pivot come first; return their count. O(1) extra space.
  - Tests:
    - property check (multiset preserved; prefix < pivot; suffix ≥ pivot);
    - pivot smaller than all values, larger than all, absent from the array;
    - randomized 500 trials.
- **`valid_palindrome`** · Easy
  - Sig: `bool isPalindrome(const std::string& s)`
  - Contract: consider only alphanumerics, case-insensitive.
  - Tests: `""` and `" "` → true; `"0P"` → false; mixed punctuation.
- **`two_sum_ii`** · Medium
  - Sig: `std::vector<int> twoSum(const std::vector<int>& numbers, int target)`
  - Contract: input sorted; return 1-indexed `{i, j}`, i < j; exactly one solution; O(1) extra space.
  - Tests: negatives; duplicates (`{1,1,3}`, 2 → {1,2}); answer at the ends.
  - Large: n = 3·10⁵ with the answer at the two middle positions.
- **`three_sum`** · Medium
  - Sig: `std::vector<std::vector<int>> threeSum(std::vector<int> nums)`
  - Contract: unique triplets summing to 0; any order.
  - Tests: normalize; all zeros → `{{0,0,0}}`; no answer; many duplicates; randomized against O(n³) brute force with a set.
  - Large: n = 3000 of values in [−10⁵, 10⁵]. O(n³) is 2.7·10¹⁰.
- **`container_most_water`** · Medium
  - Sig: `int maxArea(const std::vector<int>& height)`
  - Constraints: 2 ≤ n ≤ 10⁵; 0 ≤ h ≤ 10⁴.
  - Tests: n = 2; all zeros; randomized against O(n²).
  - Large: n = 10⁵.
- **`trapping_rain_water`** · Hard
  - Sig: `int trap(const std::vector<int>& height)`
  - Constraints: n ≤ 2·10⁴; 0 ≤ h ≤ 10⁵.
  - Tests: empty; strictly increasing → 0; a single valley; randomized against brute force (per-index left/right max scan).
  - Large: none. At LeetCode's n = 2·10⁴ the O(n²) brute force is only 4·10⁸ operations, which 2 s doesn't reliably catch, so the Target line carries the requirement.

---

### Task 7: Topic 04 Sliding Window

`TOPIC=04_sliding_window`, `NN=04`. Not covered by CLRS (state once in the README).

**Diagnostic picks:** `longest_substring_no_repeat`, `char_replacement`.

**Exercises:**

- **`window_template`** · Implement · Medium
  - Sig:
    ```cpp
    template <typename Valid> int longestValidWindow(const std::string& s, Valid is_valid)
    ```
    `is_valid(const std::unordered_map<char,int>& freq, int window_len) -> bool` is assumed monotone: if a window is valid, every sub-window is valid. Return the length of the longest valid substring.
  - Tests use three predicates: "≤ 2 distinct chars", "no repeats", and "window_len − maxfreq ≤ 1". Each is compared against brute force over all substrings on random strings over `abc`; also test the empty string.
  - Large: n = 10⁵ with "≤ 2 distinct". Re-scanning each window from scratch is O(n²).
- **`best_time_stock`** · Easy
  - Sig: `int maxProfit(const std::vector<int>& prices)`
  - Tests: decreasing → 0; single day → 0.
  - Large: n = 10⁵.
- **`longest_substring_no_repeat`** · Medium
  - Sig: `int lengthOfLongestSubstring(const std::string& s)`
  - Constraints: printable ASCII; n ≤ 5·10⁴.
  - Tests: `""`; `" "`; `"abba"` (the left pointer must never move backward).
  - Large: n = 5·10⁴ of random chars over 95 printable values.
- **`char_replacement`** · Medium
  - Sig: `int characterReplacement(const std::string& s, int k)`
  - Constraints: uppercase A–Z; 0 ≤ k ≤ n ≤ 10⁵.
  - Tests: k = 0; k ≥ n; randomized against O(n²·26).
  - Large: n = 10⁵.
- **`permutation_in_string`** · Medium
  - Sig: `bool checkInclusion(const std::string& s1, const std::string& s2)`
  - Tests: s1 longer than s2; s1 == s2; a match at the very end.
  - Large: |s1| = 5000, |s2| = 10⁵ with no match. Sort-each-window is far too slow.
- **`min_window_substring`** · Hard
  - Sig: `std::string minWindow(const std::string& s, const std::string& t)`
  - Contract: return "" if there is no window.
  - Tests:
    - validate the result is a substring of s that covers t's multiset, with length equal to the brute-force minimum;
    - t has duplicate chars (`"aa"`);
    - t longer than s.
  - Large: |s| = 10⁵, |t| = 50.
- **`sliding_window_max`** · Hard
  - Sig: `std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k)`
  - Tests: k = 1; k = n; decreasing input; negatives.
  - Large: n = 10⁵, k = 5·10⁴. O(nk) = 2.5·10⁹.

---

### Task 8: Topic 05 Prefix Sums and Difference Arrays

`TOPIC=05_prefix_sums`, `NN=05`. Not covered by CLRS (state once in the README).

**Diagnostic picks:** `subarray_sum_k`, `range_sum_query_2d`.

**Exercises:**

- **`prefix_sum_2d`** · Implement · Medium
  - Sig:
    ```cpp
    class PrefixSum2D { public: explicit PrefixSum2D(const std::vector<std::vector<int>>& grid); long long sumRegion(int r1, int c1, int r2, int c2) const; };
    ```
    The rectangle is inclusive, with r1 ≤ r2 and c1 ≤ c2.
  - Tests: 1×1 grid; full-grid query; values near INT_MAX whose total overflows int (answer needs long long); random queries against brute force.
  - Large: 1000×1000 grid with 10⁵ queries.
- **`range_sum_query`** · Easy
  - Sig: `class NumArray { public: explicit NumArray(const std::vector<int>& nums); int sumRange(int left, int right) const; };`
  - Large: n = 10⁵ with 10⁵ queries.
- **`range_sum_query_2d`** · Medium
  - Sig: `class NumMatrix { public: explicit NumMatrix(const std::vector<std::vector<int>>& matrix); int sumRegion(int row1, int col1, int row2, int col2) const; };`
  - PROBLEM.md note: "Re-derive this from scratch even though you just did prefix_sum_2d; it should take under 5 minutes."
  - Large: 200×200 grid with 10⁵ queries.
- **`subarray_sum_k`** · Medium
  - Sig: `int subarraySum(const std::vector<int>& nums, int k)`
  - Constraints: n ≤ 2·10⁴; −1000 ≤ nums[i] ≤ 1000.
  - Tests: negatives; k = 0 with zeros (`{0,0,0}` → 6); randomized against O(n²).
  - Large: none. LeetCode's n makes O(n²) only 4·10⁸, so the Target line carries the requirement.
- **`continuous_subarray_sum`** · Medium
  - Sig: `bool checkSubarraySum(const std::vector<int>& nums, int k)`
  - Contract: a subarray of length ≥ 2 whose sum is a multiple of k (0 counts as a multiple).
  - Tests: `{0}` → false; `{0,0}` → true; `{5,0,0,0}` with k = 3 → true; k = 1; randomized against brute force.
  - Large: n = 10⁵ with no answer. O(n²) = 10¹⁰.
- **`corporate_flight_bookings`** · Medium
  - Sig: `std::vector<int> corpFlightBookings(const std::vector<std::vector<int>>& bookings, int n)`
  - Contract: each booking is `{first, last, seats}`, 1-indexed and inclusive.
  - Tests: a single booking covering all flights; overlapping bookings; booking at the last flight.
  - Large: n = 10⁵ flights with 10⁵ full-range bookings. Adding each booking seat by seat is 10¹⁰ operations.
