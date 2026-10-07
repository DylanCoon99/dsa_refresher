# Stage 4a: Topics 15–16 (Tasks 18–19)

Read `00-index.md` first. The conventions are the same as `03a-topics-02-05.md`:
- **Sig** is the exact stub signature.
- **Tests** lists the required cases beyond the standard groups.
- **Large** defines the large-input test. If there is no Large line, there is no large test.
- **CLRS** is the PROBLEM.md pointer.

Every task follows the Exercise Authoring Procedure in `00-index.md` (A–E).

**Enumeration outputs** (`std::vector<std::vector<…>>` in any order) are compared after normalizing: sort each inner vector when the problem says order inside doesn't matter, then sort the outer vector. Each test also checks there are no duplicate results.

---

### Task 18: Topic 15 Backtracking

`TOPIC=15_backtracking`, `NN=15`. Not covered by CLRS (plan), so the README says so once and has no CLRS table.

PROBLEM.md for the Implement item shows the choose → explore → unchoose skeleton as pseudocode in the hints.

**Diagnostic picks:** `combination_sum_ii`, `word_search`.

**Exercises:**

- **`backtracking_templates`** · Implement · Medium
  - Sig:
    - `std::vector<std::vector<int>> allSubsets(const std::vector<int>& items)`
    - `std::vector<std::vector<int>> allPermutations(const std::vector<int>& items)`
    - `std::vector<std::vector<int>> allCombinations(int n, int k)`
  - Contract:
    - items are distinct;
    - combinations choose k values from 1..n, each combination ascending;
    - subsets keep the items' relative order.
  - Tests:
    - counts are 2ⁿ, n! and C(n,k) for n ≤ 8;
    - empty items → `{{}}` for subsets and permutations;
    - k = 0 → `{{}}`;
    - k = n → one combination;
    - normalized comparison with `std::next_permutation` / bitmask brute force.
- **`subsets`** · Medium
  - Sig: `std::vector<std::vector<int>> subsets(const std::vector<int>& nums)`
  - Tests: n = 0; n = 1; n = 10 count = 1024; negatives.
- **`subsets_ii`** · Medium
  - Sig: `std::vector<std::vector<int>> subsetsWithDup(std::vector<int> nums)`
  - Tests: all equal (`{2,2,2}` → 4 subsets); a mix; no duplicates in the output (checked explicitly); compared with brute force (bitmask + set of sorted vectors).
- **`permutations`** · Medium
  - Sig: `std::vector<std::vector<int>> permute(const std::vector<int>& nums)`
  - Tests: n = 1; n = 6 count = 720; compared with `std::next_permutation`.
- **`combination_sum`** · Medium
  - Sig: `std::vector<std::vector<int>> combinationSum(const std::vector<int>& candidates, int target)`
  - Contract: distinct candidates; unlimited reuse.
  - Tests: target smaller than every candidate → empty; target equal to a candidate; candidate 1 with target 10 (many results); against brute-force DP enumeration.
- **`combination_sum_ii`** · Medium
  - Sig: `std::vector<std::vector<int>> combinationSum2(std::vector<int> candidates, int target)`
  - Contract: candidates may repeat; each used at most once; no duplicate combinations.
  - Tests: `{1,1,1,1}` with target 2 → `{{1,1}}`; no solution; against bitmask brute force.
  - Large: 100 copies of 1 with target 30. Without the duplicate-skip this explodes combinatorially; with it there's exactly one result.
- **`word_search`** · Medium
  - Sig: `bool exist(std::vector<std::vector<char>> board, const std::string& word)`
  - Tests: a single cell; a word longer than the cell count; a cell reused → false (`"ABA"` on a 1×2 board `AB`); a snake path.
- **`palindrome_partitioning`** · Medium
  - Sig: `std::vector<std::vector<std::string>> partition(const std::string& s)`
  - Contract: the order inside each partition matters, so don't sort inner vectors. Sort the outer vector only.
  - Tests: `"a"`; `"aab"`; `"aaaa"` (8 partitions); against brute force (2ⁿ⁻¹ cut masks).
- **`n_queens`** · Hard
  - Sig: `std::vector<std::vector<std::string>> solveNQueens(int n)`
  - Tests: counts for n = 1..9 are 1, 0, 0, 2, 10, 4, 40, 92, 352; every board is valid (one queen per row, column and diagonal).

---

### Task 19: Topic 16 Dynamic Programming

`TOPIC=16_dynamic_programming`, `NN=16`.

The three Implement items each require **two** entry points: `…Memo` (top-down recursion with a cache) and `…Tab` (bottom-up). Their tests run the same cases against both. `coin_change` and `lcs` double as the practice problems of the same name, so the README lists them under Implement and under Practice.

PROBLEM.md for every DP exercise asks the learner to write a comment *before coding*: state definition, transition, base cases, evaluation order. This is the plan's mastery criterion.

**Diagnostic picks:** `decode_ways`, `edit_distance`.

**Exercises (Implement):**

- **`coin_change`** · Implement + Practice · Medium
  - Sig: `int coinChangeMemo(const std::vector<int>& coins, int amount)` and `int coinChangeTab(const std::vector<int>& coins, int amount)`
  - Contract: fewest coins, or −1.
  - Tests: amount 0 → 0; impossible → −1; greedy fails (`{1,3,4}`, 6 → 2); a coin larger than the amount.
  - Large: coins `{1,2,5}` with amount 10⁴ for Tab. For Memo, use amount 10³ (keeps the recursion depth safe). Exponential recursion without a cache times out.
  - CLRS: §15.1 (3e) / §14.1 (4e), "Rod cutting": the clearest memo-vs-tab comparison (≈20 min). Skip if you can convert memo↔tab freely.
- **`lcs`** · Implement + Practice · Medium
  - Sig: `int lcsMemo(const std::string& a, const std::string& b)` and `int lcsTab(const std::string& a, const std::string& b)`
  - Tests: an empty string; identical strings; no common chars; against 2ⁿ brute force for length ≤ 10.
  - Large: 1000×1000 for Tab; 300×300 for Memo.
  - CLRS: §15.4 (3e) / §14.4 (4e), "Longest common subsequence": the theorem on optimal substructure, and LCS-LENGTH (≈15 min).
- **`knapsack_01`** · Implement · Medium
  - Sig: `int knapsackMemo(const std::vector<int>& weights, const std::vector<int>& values, int capacity)` and `int knapsackTab(…same…)`
  - Tests: capacity 0; an item heavier than the capacity; every item fits; against 2ⁿ brute force for n ≤ 15.
  - Large: n = 100 items with capacity 10⁴.
  - PROBLEM.md hint: a 1-D rolling array iterating capacity downward.
  - CLRS: §16.2 (3e) / §15.2 (4e), "Elements of the greedy strategy": the 0-1 vs fractional knapsack contrast (≈10 min).

**Exercises (Practice):**

- **`climbing_stairs`** · Easy · Sig: `int climbStairs(int n)` · Tests: n = 1, 2, 45 (fits in int).
- **`house_robber`** · Medium · Sig: `int rob(const std::vector<int>& nums)` · Tests: a single house; two houses; alternating values; against brute force.
- **`house_robber_ii`** · Medium · Sig: `int rob(const std::vector<int>& nums)` (circular street) · Tests: a single house; two houses; three equal houses.
- **`decode_ways`** · Medium
  - Sig: `int numDecodings(const std::string& s)`
  - Tests: `"0"` → 0; `"06"` → 0; `"10"` → 1; `"27"` → 1; `"226"` → 3; `"100"` → 0.
  - Large: "1"×60 + "00" → 0. The trailing "00" makes every branch fail at the end, so un-memoized recursion explores ~fib(60) ≈ 1.5·10¹² branches, while the memoized version is O(n).
- **`word_break`** · Medium
  - Sig: `bool wordBreak(const std::string& s, const std::vector<std::string>& wordDict)`
  - Tests: reuse of a word; no split; empty dictionary words don't occur.
  - Large: s = "a"×150 + "b", dictionary {"a", "aa", …, "a"×10}. Without memo this is exponential.
- **`lis`** · Medium
  - Sig: `int lengthOfLIS(const std::vector<int>& nums)`
  - Tests: strictly increasing means duplicates don't count (`{7,7,7}` → 1); decreasing → 1; against O(n²) brute force.
  - Large: n = 10⁵. O(n²) = 10¹⁰, so the O(n log n) version is required.
  - CLRS: §15.4 (3e) / §14.4 (4e); end-of-section exercises ask for the O(n²) and O(n log n) longest monotonically increasing subsequence (≈5 min).
- **`unique_paths`** · Medium · Sig: `int uniquePaths(int m, int n)` · Tests: 1×1; 1×N; 3×7 → 28; 23×12 (fits in int).
- **`partition_equal_subset`** · Medium
  - Sig: `bool canPartition(const std::vector<int>& nums)`
  - Tests: odd total → false; a single element; against brute force.
  - Large: n = 200 values ≤ 100 (sum 2·10⁴); 2²⁰⁰ subsets is hopeless.
- **`target_sum`** · Medium
  - Sig: `int findTargetSumWays(const std::vector<int>& nums, int target)`
  - Tests: zeros double the count (`{0,0,1}`, 1 → 4); unreachable target; a negative target.
  - Large: n = 20 (2²⁰ ≈ 10⁶) passes even without DP, so there's no large test.
- **`coin_change_ii`** · Medium
  - Sig: `int change(int amount, const std::vector<int>& coins)`
  - Contract: the answer fits in a signed 32-bit int.
  - Tests: amount 0 → 1; no way → 0; the order of coins doesn't create duplicates (`{1,2}`, 3 → 2).
  - Hint: intermediate table values can exceed int even when the answer doesn't; use `unsigned long long` or `long long` for the table.
- **`edit_distance`** · Medium
  - Sig: `int minDistance(const std::string& word1, const std::string& word2)`
  - Tests: an empty side; identical; a full replace; against small brute force via recursion.
  - Large: 500×500.
  - CLRS: the end-of-chapter problem "Edit distance" in Ch. 15 (3e) / Ch. 14 (4e) (≈10 min).
- **`distinct_subsequences`** · Hard
  - Sig: `int numDistinct(const std::string& s, const std::string& t)`
  - Tests: t empty → 1; t longer than s → 0.
  - Tests: s = "a"×1000, t = "a" → 1000.
  - The overflow trap: s = "a"×500 + "b", t = "a"×250 + "c" → 0. Intermediate counts like C(500,250) overflow int and long long, so a signed table triggers UBSan (CRASH).
  - Hint: use `unsigned long long` (wraparound is defined, and the result is exact whenever the true answer fits). The reference does this.
- **`stock_cooldown`** · Medium · Sig: `int maxProfit(const std::vector<int>& prices)` · Tests: a single day; decreasing; `{1,2,3,0,2}` → 3; against brute-force recursion.
- **`longest_palindromic_subseq`** · Medium
  - Sig: `int longestPalindromeSubseq(const std::string& s)`
  - Tests: a single char; all same; no repeats → 1.
  - Large: n = 1000.
  - CLRS: the end-of-chapter problem "Longest palindrome subsequence" in Ch. 15 (3e) / Ch. 14 (4e) (≈5 min).
- **`burst_balloons`** · Hard
  - Sig: `int maxCoins(const std::vector<int>& nums)`
  - Tests: a single balloon; `{3,1,5,8}` → 167; zeros; against brute force over all orders for n ≤ 7.
  - Large: n = 300 (interval DP is O(n³) = 2.7·10⁷).

**CLRS quick reference rows:**
- Memo vs tab: §15.1 / §14.1, "Rod cutting", ≈20 min.
- When DP applies: §15.3 / §14.3, "Elements of dynamic programming"; the plan's "highly recommended" section, ≈20 min.
- LCS: §15.4 / §14.4, ≈15 min.
- 0-1 knapsack contrast: §16.2 / §15.2, ≈10 min.
- Edit distance and palindrome subsequence: end-of-chapter problems, Ch. 15 / Ch. 14, ≈10 min.
