# Stage 2b: Topics 06–09 (Tasks 9–12)

Read `00-index.md` first. The conventions are the same as `03a-topics-02-05.md`:
- **Sig** is the exact stub signature.
- **Tests** lists the required cases beyond the template's standard groups.
- **Large** defines the large-input test. If there is no Large line, there is no large test.
- **CLRS** is the PROBLEM.md pointer.

Every task follows the Exercise Authoring Procedure in `00-index.md` (A–E).

---

### Task 9: Topic 06 Stacks, Queues, and Monotonic Structures

`TOPIC=06_stacks_queues`, `NN=06`. `min_stack` is both the Implement item and the "Min Stack" practice problem, so the README lists it under both headings.

**Diagnostic picks:** `daily_temperatures`, `eval_rpn`.

**Exercises:**

- **`queue_two_stacks`** · Implement · Easy
  - Sig: `class TwoStackQueue { public: void push(int x); int pop(); int peek(); bool empty() const; std::size_t size() const; };`
  - Contract: `pop` and `peek` on an empty queue throw `std::out_of_range`. Use only two `std::vector<int>` stacks (push_back/pop_back/back).
  - Tests: `CHECK_THROWS_AS` on empty; interleaved ops; 10⁵ random ops against `std::queue`.
  - Large: 10⁶ ops alternating push and pop. Moving every element on each op is O(n²).
  - CLRS: §10.1 (3e) / §10.1 (4e), stacks and queues. Read STACK and ENQUEUE/DEQUEUE pseudocode; an end-of-section exercise asks for exactly this design (≈10 min). Also §17.1 (3e) / §16.1 (4e), "Aggregate analysis", for the amortized argument (≈15 min). Skip if you can explain why each element is moved at most twice.
- **`min_stack`** · Implement + Practice · Medium
  - Sig: `class MinStack { public: void push(int val); void pop(); int top() const; int getMin() const; };`
  - Contract: all O(1); calls on an empty stack never happen.
  - Tests: duplicate minimums (push 0, 1, 0, pop → min still 0); INT_MIN; 10⁵ random ops against a brute-force min scan.
  - Large: 10⁵ pushes, then 10⁵ getMin calls. Scanning for the min is 10¹⁰.
- **`valid_parentheses`** · Easy
  - Sig: `bool isValid(const std::string& s)`
  - Tests: `""` → true; `"]"` → false; `"(("` → false; `"([)]"` → false; deep nesting of 10⁴.
- **`eval_rpn`** · Medium
  - Sig: `int evalRPN(const std::vector<std::string>& tokens)`
  - Contract: `+ - * /`; division truncates toward zero; intermediate values fit in int.
  - Tests: negative number tokens (`"-11"`); `6 / -132` → 0; a single number.
- **`daily_temperatures`** · Medium
  - Sig: `std::vector<int> dailyTemperatures(const std::vector<int>& temperatures)`
  - Tests: strictly decreasing → all 0; equal temperatures don't count as warmer.
  - Large: n = 10⁵ strictly decreasing, then one hot day at the end. The O(n²) scan does ~5·10⁹ steps.
- **`car_fleet`** · Medium
  - Sig: `int carFleet(int target, const std::vector<int>& position, const std::vector<int>& speed)`
  - Tests:
    - a single car;
    - cars meeting exactly at the target count as one fleet;
    - catching up only after the target doesn't count;
    - compute arrival times exactly (fractions): use `(long long)(target-p)*s2` comparisons in the brute force.
  - Large: none.
- **`largest_rectangle_histogram`** · Hard
  - Sig: `int largestRectangleArea(const std::vector<int>& heights)`
  - Tests: a single bar; all equal; increasing; decreasing; zeros; randomized against O(n²).
  - Large: n = 10⁵ all equal to 1. O(n²) = 10¹⁰.

**CLRS quick reference rows:**
- Stack/queue basics: §10.1 / §10.1, ≈10 min.
- Amortized two-stack queue: §17.1 / §16.1, "Aggregate analysis"; the stack operations example, ≈15 min.
- Monotonic stacks: not in CLRS; see the hints.

---

### Task 10: Topic 07 Binary Search

`TOPIC=07_binary_search`, `NN=07`.

**Diagnostic picks:** `koko_bananas`, `search_rotated`.

**Exercises:**

- **`bounds`** · Implement · Medium
  - Sig: `std::size_t lowerBound(const std::vector<int>& a, int x)` and `std::size_t upperBound(const std::vector<int>& a, int x)`
  - Contract: iterative; don't use `<algorithm>`; same results as `std::lower_bound` / `std::upper_bound`. PROBLEM.md asks the learner to write the loop invariant as a comment.
  - Tests:
    - empty array;
    - x below the minimum and above the maximum;
    - all equal;
    - INT_MIN and INT_MAX queries;
    - 2000 random arrays and queries compared with the std versions.
  - CLRS: §2.1 (3e) / §2.1 (4e), "Insertion sort": read only the loop-invariant discussion (initialization / maintenance / termination), ≈10 min. Skip if you can state your loop's invariant precisely.
- **`binary_search`** · Easy
  - Sig: `int search(const std::vector<int>& nums, int target)`
  - Contract: distinct values; return the index or −1.
  - Tests: n = 1 hit and miss; target at both ends.
  - Large: 10⁶ elements with 10⁶ queries. Linear scan is 10¹².
- **`search_2d_matrix`** · Medium
  - Sig: `bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target)`
  - Contract: rows are sorted, and each row's first value is greater than the previous row's last.
  - Tests: 1×1; a single row; a single column; target between rows.
- **`koko_bananas`** · Medium
  - Sig: `int minEatingSpeed(const std::vector<int>& piles, int h)`
  - Constraints: n ≤ 10⁴; piles[i] ≤ 10⁹; n ≤ h ≤ 10⁹.
  - Tests: h == n (answer = max pile); a huge h (answer 1); piles of 10⁹ where the hour sum overflows int (needs long long).
  - Large: 10⁴ piles of 10⁹ with h = 10⁴ + 1. A linear search over speeds is ~10⁹ × n.
- **`find_min_rotated`** · Medium
  - Sig: `int findMin(const std::vector<int>& nums)`
  - Contract: distinct values.
  - Tests: not rotated; rotated by n−1; n = 1; n = 2 both orders.
- **`search_rotated`** · Medium
  - Sig: `int search(const std::vector<int>& nums, int target)`
  - Contract: distinct values; return the index or −1.
  - Tests: every rotation of `{0..9}` against every target in −1..10.
- **`time_map`** · Medium
  - Sig: `class TimeMap { public: void set(const std::string& key, const std::string& value, int timestamp); std::string get(const std::string& key, int timestamp) const; };`
  - Contract: timestamps for a key are strictly increasing across `set` calls. `get` returns the value with the largest timestamp ≤ the given one, or "".
  - Tests: query before the first timestamp; unknown key; exact match.
  - Large: 10⁵ sets on one key, then 10⁵ gets. A linear scan is 10¹⁰.
- **`median_two_sorted`** · Hard
  - Sig: `double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2)`
  - Tests: one array empty; arrays of very different sizes; all of nums1 < nums2; even and odd totals; randomized against merging and taking the middle.
  - The Target is O(log(min(m,n))). The tests can't enforce it, and PROBLEM.md says so.

**CLRS quick reference rows:**
- Loop invariants: §2.1 / §2.1, ≈10 min.
- Binary search: appears only as an end-of-section exercise in Ch. 2 (the "binary search" exercise in §2.3), ≈5 min.

---

### Task 11: Topic 08 Linked Lists

`TOPIC=08_linked_lists`, `NN=08`. `lru_cache` is both the Implement item and the "LRU Cache" practice problem.

All list exercises use `common/list_node.hpp` and compare with `to_vector`. Tests never free nodes. PROBLEM.md says "you may `delete` nodes you remove; the tests don't care".

**Diagnostic picks:** `reorder_list`, `remove_nth_from_end`.

**Exercises:**

- **`doubly_linked_list`** · Implement · Medium
  - Sig:
    ```cpp
    class DoublyLinkedList { public: DoublyLinkedList(); ~DoublyLinkedList(); DoublyLinkedList(const DoublyLinkedList&) = delete; DoublyLinkedList& operator=(const DoublyLinkedList&) = delete; void pushFront(int v); void pushBack(int v); int popFront(); int popBack(); int front() const; int back() const; bool remove(int v); std::size_t size() const; bool empty() const; std::vector<int> toVector() const; };
    ```
  - Contract: sentinel node(s) are required (stated in PROBLEM.md). pop/front/back on an empty list throw `std::out_of_range`. `remove` deletes the first occurrence.
  - Tests:
    - empty throws;
    - remove the head, the tail and the only element;
    - remove a missing value → false;
    - 10⁵ random ops against `std::list`;
    - the destructor runs (construct and destroy 1000 lists; ASan catches a double free).
  - CLRS: §10.2 (3e) / §10.2 (4e), "Linked lists": LIST-INSERT/LIST-DELETE, then the sentinel versions (≈15 min). Skip if you can write delete without any head/tail special case.
- **`lru_cache`** · Implement + Practice · Medium
  - Sig: `class LRUCache { public: explicit LRUCache(int capacity); int get(int key); void put(int key, int value); };`
  - Contract: `get` returns −1 if the key is missing. `put` on an existing key updates it and makes it most recent. O(1) each.
  - Tests:
    - capacity 1;
    - `get` refreshes recency;
    - `put` on an existing key refreshes recency and doesn't evict;
    - 10⁵ random ops against a brute-force `std::list` scan model.
  - Large: capacity 10⁴ with 2·10⁵ ops. O(capacity) per op is 2·10⁹.
  - CLRS: §10.2 / §10.2, "Linked lists": sentinels (≈10 min).
- **`reverse_linked_list`** · Easy
  - Sig: `ListNode* reverseList(ListNode* head)`
  - Tests: nullptr; one node; two nodes.
  - Large: 10⁶ nodes (also catches deep recursion crashing under ASan, which PROBLEM.md mentions as the reason to know the iterative form).
- **`merge_two_lists`** · Easy
  - Sig: `ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)`
  - Tests: both empty; one empty; equal values; randomized against `std::merge`.
- **`linked_list_cycle`** · Easy
  - Sig: `bool hasCycle(ListNode* head)`
  - Contract: O(1) memory target.
  - Tests: `build_list_with_cycle` with pos 0, middle, tail-to-itself; no cycle; empty.
  - Large: 10⁶ nodes with a cycle at 0.
- **`reorder_list`** · Medium
  - Sig: `void reorderList(ListNode* head)`
  - Contract: L0→Ln→L1→Ln−1…, in place.
  - Tests: lengths 0–6 exhaustively; check node identity (the same node pointers are reused, not new nodes).
- **`remove_nth_from_end`** · Medium
  - Sig: `ListNode* removeNthFromEnd(ListNode* head, int n)`
  - Tests: remove the head (n = length); remove the tail; a single node → nullptr.
- **`copy_random_list`** · Medium
  - Sig: `RandomListNode* copyRandomList(RandomListNode* head)`
  - Tests:
    - `to_random_spec(copy) == spec` (−2 would mean it points into the original);
    - no copied node's address appears among the original nodes;
    - the original is unchanged afterwards;
    - random pointing to self;
    - empty list.
  - Large: 10⁵ nodes. An O(n²) "find random by index" approach times out.
- **`merge_k_lists`** · Hard
  - Sig: `ListNode* mergeKLists(std::vector<ListNode*>& lists)`
  - Tests: empty vector; a vector of nullptrs; one list; randomized against sort-all.
  - Large: 10⁴ lists × 10 nodes. Merging one list at a time is ~5·10⁸ node steps, which ASan makes slower than 2 s. Confirm with the brute-force check in procedure E.
  - CLRS: §6.5 (3e) / §6.5 (4e), "Priority queues", ≈10 min.

**CLRS quick reference rows:**
- Linked lists: §10.2 / §10.2, ≈15 min.
- Floyd cycle detection: not in CLRS.
- k-way merge: §6.5 / §6.5, ≈10 min.

---

### Task 12: Topic 09 Sorting and Selection

`TOPIC=09_sorting`, `NN=09`.

**Diagnostic picks:** `sort_colors`, `kth_largest_array`.

**Exercises:**

- **`sort_an_array`** · Implement + Practice · Medium
  - Sig: `void mergeSort(std::vector<int>& a)`, `void quickSort(std::vector<int>& a)`, `void heapSort(std::vector<int>& a)`
  - Contract: don't use `std::sort` (stated); one header holds all three.
  - Tests: one `TEST_CASE` per algorithm, each checking:
    - empty;
    - one element;
    - sorted;
    - reversed;
    - all equal;
    - INT_MIN/INT_MAX;
    - 500 random arrays against `std::sort`.
  - Large (per algorithm):
    - 2·10⁵ random values;
    - for quickSort also 2·10⁵ already-sorted values and 2·10⁵ all-equal values. These defeat a fixed pivot and plain Lomuto: O(n²) = 4·10¹⁰.
  - CLRS:
    - §2.3 (3e) / §2.3 (4e), "Designing algorithms": MERGE and MERGE-SORT pseudocode (≈15 min).
    - §7.1 / §7.1, "Description of quicksort": PARTITION (Lomuto) (≈15 min). The end-of-chapter problem on Hoare partition covers the other scheme.
    - §7.3 / §7.3, "A randomized version of quicksort" (≈5 min).
    - §6.4 / §6.4, "The heapsort algorithm" (≈10 min).
    - Skip each if you can write it from memory.
- **`quickselect`** · Implement · Medium
  - Sig: `int quickselect(std::vector<int>& nums, std::size_t k)`
  - Contract: return the k-th smallest, 0-indexed; nums may be reordered; expected O(n).
  - Tests: k = 0; k = n−1; duplicates; 500 randomized trials against sort.
  - Large: 10⁶ all-equal values with k = n/2. Requires three-way partitioning or random-pivot handling of equal keys.
  - CLRS: §9.2 (3e) / §9.2 (4e), "Selection in expected linear time": RANDOMIZED-SELECT (≈15 min).
- **`sort_colors`** · Medium
  - Sig: `void sortColors(std::vector<int>& nums)`
  - Contract: values in {0, 1, 2}; one pass; O(1) space (the Dutch national flag).
  - Tests: all one color; length 1; `{2,0,1}`.
- **`kth_largest_array`** · Medium
  - Sig: `int findKthLargest(std::vector<int>& nums, int k)`
  - Contract: 1-indexed k. PROBLEM.md requires quickselect and notes the tests can't enforce it.
  - Tests: duplicates; k = 1; k = n.
  - Large: 10⁶ all-equal values.
  - CLRS: same as `quickselect`.
- **`largest_number`** · Medium
  - Sig: `std::string largestNumber(const std::vector<int>& nums)`
  - Tests: all zeros → "0"; `{3,30,34,5,9}` → "9534330"; `{10,2}` → "210"; randomized against brute force (all permutations for n ≤ 6).
- **`h_index`** · Medium
  - Sig: `int hIndex(const std::vector<int>& citations)`
  - Tests: all zeros → 0; all large → n; a single paper; randomized against brute force.
  - Mention the counting-sort O(n) approach in the hints.
  - CLRS: §8.2 (3e) / §8.2 (4e), "Counting sort" (≈10 min).

**CLRS quick reference rows:**
- Merge sort: §2.3 / §2.3, ≈15 min.
- Quicksort: §7.1 and §7.3 / §7.1 and §7.3, ≈20 min.
- Heapsort: §6.4 / §6.4, ≈10 min.
- Comparison lower bound: §8.1 / §8.1, "Lower bounds for sorting"; decision-tree argument, statement only, ≈10 min.
- Counting and radix sort: §8.2–8.3 / §8.2–8.3, ≈15 min.
- Selection: §9.2 / §9.2, ≈15 min.
