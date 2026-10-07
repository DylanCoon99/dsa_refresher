# Stage 4b: Topics 17–18 (Tasks 20–21)

Read `00-index.md` first. The conventions are the same as `03a-topics-02-05.md`:
- **Sig** is the exact stub signature.
- **Tests** lists the required cases beyond the standard groups.
- **Large** defines the large-input test. If there is no Large line, there is no large test.
- **CLRS** is the PROBLEM.md pointer.

Every task follows the Exercise Authoring Procedure in `00-index.md` (A–E).

---

### Task 20: Topic 17 Greedy Algorithms and Intervals

`TOPIC=17_greedy_intervals`, `NN=17`. `merge_intervals` is both the Implement item ("interval-merging routine") and the "Merge Intervals" practice problem.

Every greedy PROBLEM.md has a final hint: "Before coding, write one sentence on why the greedy choice is safe (the exchange argument)." That is the plan's mastery criterion.

**Interval conventions** (state these in each PROBLEM.md):
- Intervals are `{start, end}` with start ≤ end.
- Closed intervals: touching intervals overlap. This applies to merge, insert and arrows.
- Half-open intervals: touching intervals don't overlap. This applies to max_overlap, meeting rooms, car pooling and non-overlapping, each stated explicitly.

**Diagnostic picks:** `non_overlapping_intervals`, `gas_station`.

**Exercises:**

- **`merge_intervals`** · Implement + Practice · Medium
  - Sig: `std::vector<std::vector<int>> merge(std::vector<std::vector<int>> intervals)`
  - Contract: output sorted by start.
  - Tests: touching `{1,4},{4,5}` → `{1,5}`; containment; unsorted input; a single interval; randomized against a brute-force coverage-array merge over a small range.
  - Large: 10⁵ intervals. Repeated pairwise merging until stable is O(n²).
- **`max_overlap`** · Implement · Medium
  - Sig: `int maxOverlap(const std::vector<std::pair<int,int>>& intervals)`
  - Contract: half-open [start, end); return the maximum number active at any instant. PROBLEM.md requires the sweep-line approach (events sorted, with end before start at equal times).
  - Tests: touching intervals → 1; identical intervals → n; empty → 0; randomized against brute-force counting at each start point.
  - Large: 10⁵ intervals.
  - CLRS: §16.1 (3e) / §15.1 (4e); the end-of-section exercise on scheduling activities among the fewest lecture halls (interval-graph coloring) is exactly this problem (≈5 min).
- **`jump_game`** · Medium · Sig: `bool canJump(const std::vector<int>& nums)` · Tests: a single element → true; a zero at the start with n > 1 → false; a zero you can jump over. · Large: n = 10⁵ (BFS over all jumps is O(n·max)).
- **`jump_game_ii`** · Medium · Sig: `int jump(const std::vector<int>& nums)` · Tests: a single element → 0; already reaches the end in one jump. · Large: n = 10⁵ of value 10⁴.
- **`gas_station`** · Medium
  - Sig: `int canCompleteCircuit(const std::vector<int>& gas, const std::vector<int>& cost)`
  - Contract: the answer is unique if it exists, else −1.
  - Tests: a single station; total gas < total cost → −1; the start is the last index; against O(n²) simulation.
  - Large: n = 10⁵ with the answer at n−1.
- **`partition_labels`** · Medium · Sig: `std::vector<int> partitionLabels(const std::string& s)` · Tests: a single char; all distinct → all 1s; all the same letter → `{n}`.
- **`insert_interval`** · Medium
  - Sig: `std::vector<std::vector<int>> insert(std::vector<std::vector<int>> intervals, std::vector<int> newInterval)`
  - Contract: the input is sorted and non-overlapping.
  - Tests: empty list; inserted before all; after all; swallowing everything; touching (closed).
- **`non_overlapping_intervals`** · Medium
  - Sig: `int eraseOverlapIntervals(std::vector<std::vector<int>> intervals)`
  - Contract: touching is not overlap.
  - Tests: `{1,2},{2,3}` → 0; all identical → n−1; nested intervals; against brute force over all subsets for n ≤ 12.
  - Large: 10⁵ intervals.
  - CLRS: §16.1 (3e) / §15.1 (4e), "An activity-selection problem": this is the same problem (keep n − max compatible). Read the greedy-choice theorem statement (≈15 min). Skip if you can state why sorting by end time is safe.
- **`min_arrows`** · Medium
  - Sig: `int findMinArrowShots(std::vector<std::vector<int>> points)`
  - Contract: closed; coordinates span the full int range.
  - Tests: `{{-2147483648, 2147483647}}` → 1; `{{INT_MIN,INT_MIN},{INT_MAX,INT_MAX}}` → 2. A subtraction comparator such as `a[1] - b[1]` overflows here, which UBSan reports.
- **`meeting_rooms_ii`** · Medium
  - Sig: `int minMeetingRooms(const std::vector<std::vector<int>>& intervals)`
  - Contract: half-open; touching meetings can share a room.
  - Tests: empty → 0; touching → 1; all overlapping → n.
  - PROBLEM.md notes that this is a premium problem on LeetCode, written here in original words.
- **`car_pooling`** · Medium
  - Sig: `bool carPooling(const std::vector<std::vector<int>>& trips, int capacity)`
  - Contract: trips are `{passengers, from, to}`; passengers leave at `to` before new ones board.
  - Tests: drop-off and pick-up at the same point stay within capacity; a single trip over capacity.
  - Large: 10⁵ trips spread over locations up to 10⁹, so a per-kilometer array is infeasible and the sweep is required.

**CLRS quick reference rows:**
- Activity selection: §16.1 / §15.1, ≈15 min.
- Greedy-choice property and optimal substructure: §16.2 / §15.2, "Elements of the greedy strategy", ≈15 min.
- Huffman (review only): §16.3 / §15.3, "Huffman codes"; the algorithm and the greedy lemma statement, ≈15 min.

---

### Task 21: Topic 18 Bit Manipulation and Mathematics

`TOPIC=18_bits_math`, `NN=18`.

**Diagnostic picks:** `counting_bits`, `sum_two_integers`.

**Exercises:**

- **`fast_pow`** · Implement · Easy
  - Sig: `long long modPow(long long base, long long exp, long long mod)`
  - Contract: 1 ≤ mod ≤ 2·10⁹; 0 ≤ exp ≤ 10¹⁸; base may be negative or ≥ mod. Return a value in [0, mod). By definition `modPow(x, 0, 1) == 0`.
  - Tests: exp 0; mod 1; a negative base; base ≥ mod; Fermat checks (`modPow(a, p−1, p) == 1` for prime p = 10⁹+7); against a naive loop for exp ≤ 1000.
  - Large: exp = 10¹⁸, 1000 calls. A linear loop never finishes.
  - CLRS: §31.6 (3e) / §31.6 (4e), "Powers of an element": MODULAR-EXPONENTIATION (≈10 min).
- **`sieve`** · Implement · Easy
  - Sig: `std::vector<int> primesUpTo(int n)`
  - Contract: all primes ≤ n, ascending. n < 2 → empty.
  - Tests: n = 0, 1, 2; n = 100 (25 primes); against trial division for n ≤ 10⁴.
  - Large: n = 10⁷ (664579 primes). Trial division is far too slow.
- **`single_number`** · Easy · Sig: `int singleNumber(const std::vector<int>& nums)` · Tests: n = 1; negatives; INT_MIN as the single number.
- **`hamming_weight`** · Easy · Sig: `int hammingWeight(std::uint32_t n)` · Tests: 0; 0xFFFFFFFF → 32; powers of two. PROBLEM.md hint: `n & (n - 1)`.
- **`counting_bits`** · Easy · Sig: `std::vector<int> countBits(int n)` · Tests: n = 0 → `{0}`; against `std::popcount`. · Large: n = 10⁷ (also correct with per-number popcount; the Target says O(n) via DP).
- **`missing_number`** · Easy · Sig: `int missingNumber(const std::vector<int>& nums)` · Tests: missing 0; missing n; n = 1.
- **`reverse_bits`** · Easy · Sig: `std::uint32_t reverseBits(std::uint32_t n)` · Tests: 0; 1 → 0x80000000; 0xFFFFFFFF; against a brute-force string reversal.
- **`sum_two_integers`** · Medium
  - Sig: `int getSum(int a, int b)`
  - Contract: no `+` or `-` (stated; unenforced).
  - Tests: negatives; mixed signs; (−1, 1) → 0; INT_MAX + INT_MIN → −1.
  - PROBLEM.md notes that shifting the carry is done in `unsigned` to avoid UB in older standards, and that C++20 defines it.
- **`pow_x_n`** · Medium
  - Sig: `double myPow(double x, int n)`
  - Tests: n = 0; a negative n; **n = INT_MIN** (`-n` overflows int, which UBSan reports); x = 1.0 with n = INT_MAX; compare with `std::pow` within 1e-9 relative error.
  - Large: 10⁶ calls with n = INT_MAX. A linear loop never finishes.
- **`count_primes`** · Medium · Sig: `int countPrimes(int n)` · Contract: primes strictly less than n. · Tests: n = 0, 1, 2 → 0; n = 3 → 1. · Large: n = 5·10⁶.

**CLRS quick reference rows:**
- GCD and Euclid: §31.2 / §31.2, "Greatest common divisor"; EUCLID, the GCD recursion theorem statement, ≈10 min.
- Modular exponentiation: §31.6 / §31.6, ≈10 min.
- Bit tricks and the sieve: not in CLRS; see the hints.
