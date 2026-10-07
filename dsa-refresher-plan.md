# Data Structures and Algorithms: Refresher Plan

A topic-organized plan for restoring interview-level fluency in data structures and algorithms. There is no schedule; topics are completed at whatever pace is sustainable, and a topic is considered finished only when its mastery criteria are met.

---

## Contents

- [How to Use This Plan](#how-to-use-this-plan)
- [Using CLRS as a Reference](#using-clrs-as-a-reference)
- [Recommended Topic Order](#recommended-topic-order)
- [Core Topics](#core-topics)
  1. Complexity Analysis
  2. Arrays and Hashing
  3. Two Pointers
  4. Sliding Window
  5. Prefix Sums and Difference Arrays
  6. Stacks, Queues, and Monotonic Structures
  7. Binary Search
  8. Linked Lists
  9. Sorting and Selection
  10. Trees and Binary Search Trees
  11. Heaps and Priority Queues
  12. Graph Traversal and Topological Sort
  13. Union-Find (Disjoint Sets)
  14. Shortest Paths and Minimum Spanning Trees
  15. Backtracking
  16. Dynamic Programming
  17. Greedy Algorithms and Intervals
  18. Bit Manipulation and Mathematics
- [Advanced Topics](#advanced-topics)
  19. Tries
  20. Range Query Structures
  21. String Algorithms
  22. Advanced Graph Topics
- [Consolidation](#consolidation)
- [Appendix A: Error Log Template](#appendix-a-error-log-template)
- [Appendix B: Progress Tracker](#appendix-b-progress-tracker)

---

## How to Use This Plan

Each topic contains five parts:

| Part | Purpose |
|---|---|
| **Review** | The concepts to recall. Attempt to recall each one before consulting any reference. |
| **Implement** | Code to write from scratch, without references, until it can be produced correctly on the first attempt. |
| **Practice** | Representative problems, listed approximately from easiest to hardest. Titles correspond to LeetCode problems. |
| **CLRS** | Chapters to consult when a gap appears. These are references, not required reading. |
| **Mastery criteria** | The conditions under which the topic may be marked complete. |

### Working method

1. **Diagnose before reviewing.** Begin each topic by attempting two practice problems cold. If both are solved comfortably within the time cap, skim the Review list, complete the Implement item, and move to the mastery check. If not, work through the topic fully.
2. **Retrieve rather than re-read.** Attempt to state each Review concept from memory before looking anything up. Consult references only for what could not be recalled.
3. **Cap the time spent stuck.** After 30–40 minutes without progress, study the solution, record the missed insight in the error log (Appendix A), and re-solve the problem independently the following day.
4. **State the brute-force approach first.** For every problem, describe the naive solution and its complexity, identify the bottleneck, and then select the structure or technique that removes it.
5. **Analyze before submitting.** State time and space complexity, and test edge cases: empty input, a single element, duplicates, negative values, overflow, and disconnected or cyclic structures.
6. **Revisit on a spaced schedule.** Re-solve every logged problem after approximately 3 days, 1 week, and 3 weeks.
7. **Use one language consistently.** Python minimizes syntactic overhead in interviews. C++ is often expected for robotics and embedded roles. If C++ is chosen, include the STL containers (`vector`, `deque`, `unordered_map`, `map`, `priority_queue`, `set`) and their complexity guarantees in the review of each relevant topic.

---

## Using CLRS as a Reference

*Introduction to Algorithms* (Cormen, Leiserson, Rivest, and Stein) is comprehensive and rigorous, but it is not organized around interview patterns. Use it selectively:

- **Consult it only after a concrete gap appears.** For example, an inability to state why Dijkstra's algorithm fails with negative edge weights is a reason to open the book.
- **Read in this order:**
  1. The chapter introduction.
  2. The pseudocode.
  3. The statement of the key theorem or lemma.

  Read full proofs only when the correctness argument itself is unclear.
- **Skip the mathematical appendices** unless a specific derivation is needed.
- **Optionally, attempt one or two section exercises** on topics that remain uncertain after practice.
- **Expect gaps in coverage.** Several interview-centric patterns are not covered by CLRS: two pointers, sliding window, prefix sums, monotonic stacks, backtracking templates, and tries (beyond an end-of-chapter problem). Problem editorials and the NeetCode explanations are better references for these.

**Edition note.** Chapter numbers differ between editions. References below are given as **3e / 4e**. The 4th edition (2022) moved Dynamic Programming and Greedy Algorithms earlier and removed the chapters on Fibonacci heaps and van Emde Boas trees.

---

## Recommended Topic Order

The core topics are numbered in a dependency-respecting order. The following constraints matter most:

- **Complexity Analysis** precedes everything else.
- **Arrays and Hashing** precedes Two Pointers, Sliding Window, and Prefix Sums.
- **Stacks and Queues** precede Trees and Graph Traversal, since DFS uses a stack and BFS uses a queue.
- **Trees** precede Heaps, Graphs, and Tries.
- **Recursion** comes before Dynamic Programming. Recursion is practiced in Trees and Backtracking, and DP is far easier once memoized recursion is comfortable.
- **Graph Traversal** precedes Union-Find, Shortest Paths, and Advanced Graph Topics.

Topics already rated as comfortable during diagnosis may be compressed or skipped.

---

## Core Topics

### 1. Complexity Analysis

**Review**
- Big-O, Big-Ω, and Big-Θ, and the distinction between worst-case, average-case, and amortized bounds.
- The common growth classes and their practical input-size limits (approximately 10⁸ simple operations per second).
- Amortized analysis, using dynamic array doubling as the canonical example.
- Recurrence relations and the Master Theorem.
- Space complexity, including recursion stack depth.

**Implement**
- No implementation is needed. Instead, derive by hand the complexity of: merge sort, binary search, building a heap, and a recursive Fibonacci with and without memoization.

**Practice**
- For each problem solved in later topics, write the time and space complexity before running the code.

**CLRS**
- Growth of Functions / Characterizing Running Times: Ch. 3 / Ch. 3.
- Master method: §4.5 / §4.5.
- Amortized Analysis: Ch. 17 / Ch. 16.

**Mastery criteria**
- The complexity of any solution can be stated and justified without hesitation.
- The Master Theorem can be applied to standard divide-and-conquer recurrences.

---

### 2. Arrays and Hashing

**Review**
- Dynamic array growth, contiguous memory, and cache locality.
- Hash table internals:
  - hash functions,
  - chaining versus open addressing,
  - load factor and resizing,
  - worst-case degradation.
- Hash sets versus hash maps, and frequency counting.
- String immutability and the cost of repeated concatenation.

**Implement**
- A hash map with separate chaining and automatic resizing.

**Practice**
- Contains Duplicate
- Valid Anagram
- Two Sum
- Group Anagrams
- Top K Frequent Elements
- Product of Array Except Self
- Longest Consecutive Sequence

**CLRS**
- Hash Tables: Ch. 11 / Ch. 11. Read the sections on chaining and open addressing. Universal hashing is optional.

**Mastery criteria**
- Hashing can be used to reduce O(n²) pair searches to O(n) without prompting.
- Collision handling and resizing can be explained.

---

### 3. Two Pointers

**Review**
- Opposite-direction pointers on sorted data.
- Same-direction (read/write) pointers for in-place modification.
- Fast and slow pointers. Their use for cycles is revisited in Linked Lists.

**Implement**
- In-place deduplication of a sorted array.
- Partitioning an array around a pivot.

**Practice**
- Valid Palindrome
- Two Sum II – Input Array Is Sorted
- 3Sum
- Container With Most Water
- Trapping Rain Water

**CLRS**
- Not directly covered.

**Mastery criteria**
- It can be recognized immediately when sorted input permits a two-pointer approach, and the reason each pointer moves can be justified.

---

### 4. Sliding Window

**Review**
- Fixed-size windows.
- Variable-size windows: expand on the right, contract on the left while a constraint is violated.
- Maintaining window state with counters, hash maps, or a deque.

**Implement**
- A reusable variable-window template that maintains a frequency map.

**Practice**
- Best Time to Buy and Sell Stock
- Longest Substring Without Repeating Characters
- Longest Repeating Character Replacement
- Permutation in String
- Minimum Window Substring
- Sliding Window Maximum

**CLRS**
- Not directly covered.

**Mastery criteria**
- Any "longest/shortest contiguous subarray or substring satisfying a condition" problem can be solved in O(n) using the template.

---

### 5. Prefix Sums and Difference Arrays

**Review**
- One-dimensional and two-dimensional prefix sums.
- Combining prefix sums with a hash map to count subarrays that hit a target sum.
- Difference arrays for O(1) range updates.

**Implement**
- A 2-D prefix sum structure that answers rectangle-sum queries in O(1).

**Practice**
- Range Sum Query – Immutable
- Range Sum Query 2D – Immutable
- Subarray Sum Equals K
- Continuous Subarray Sum
- Corporate Flight Bookings

**CLRS**
- Not directly covered.

**Mastery criteria**
- It can be recognized when a running-sum transformation converts a subarray problem into a lookup problem.

---

### 6. Stacks, Queues, and Monotonic Structures

**Review**
- Stack (LIFO) and queue (FIFO) semantics and their array or linked implementations.
- Deques.
- Monotonic stacks for "next greater/smaller element" problems.
- Monotonic deques for sliding-window extrema.
- Expression parsing.

**Implement**
- A queue using two stacks, with an amortized O(1) analysis.
- A min stack.

**Practice**
- Valid Parentheses
- Min Stack
- Evaluate Reverse Polish Notation
- Daily Temperatures
- Car Fleet
- Largest Rectangle in Histogram

**CLRS**
- Stacks and queues: §10.1 / §10.1.

**Mastery criteria**
- It can be explained why a monotonic stack achieves O(n) total time.
- "Next greater element" problems can be recognized and solved without assistance.

---

### 7. Binary Search

**Review**
- The standard search on a sorted array.
- Lower-bound and upper-bound variants.
- Overflow-safe midpoint computation.
- Loop invariants.
- Searching rotated arrays.
- **Binary search on the answer:** searching a monotonic predicate over a value range.

**Implement**
- Lower-bound and upper-bound functions, iterative, with clearly stated invariants.

**Practice**
- Binary Search
- Search a 2D Matrix
- Koko Eating Bananas
- Find Minimum in Rotated Sorted Array
- Search in Rotated Sorted Array
- Time Based Key-Value Store
- Median of Two Sorted Arrays

**CLRS**
- Binary search appears only as an exercise in Ch. 2. Invariant reasoning is covered in §2.1 (loop invariants) in both editions.

**Mastery criteria**
- Off-by-one errors no longer occur.
- Problems phrased as "minimize the maximum" or "find the smallest value such that…" are recognized as binary search on the answer.

---

### 8. Linked Lists

**Review**
- Singly and doubly linked lists.
- Sentinel (dummy) nodes.
- Iterative and recursive reversal.
- Merging sorted lists.
- Fast and slow pointers: cycle detection with Floyd's algorithm, and finding the middle node.
- The LRU cache design, which combines a hash map with a doubly linked list.

**Implement**
- A doubly linked list with sentinel nodes.
- An LRU cache with O(1) `get` and `put`.

**Practice**
- Reverse Linked List
- Merge Two Sorted Lists
- Linked List Cycle
- Reorder List
- Remove Nth Node From End of List
- Copy List with Random Pointer
- LRU Cache
- Merge k Sorted Lists

**CLRS**
- Linked lists: §10.2 / §10.2.

**Mastery criteria**
- Pointer manipulation is performed correctly on the first attempt, including at the head and tail boundaries.

---

### 9. Sorting and Selection

**Review**
- Insertion sort, merge sort, quicksort (including partition schemes and pivot selection), and heapsort.
- Counting sort and radix sort.
- Stability.
- The Ω(n log n) lower bound for comparison sorting.
- The default sorts used by standard libraries (Timsort, introsort).
- Quickselect.
- Custom comparators.

**Implement**
- Merge sort.
- Quicksort with Lomuto or Hoare partitioning.
- Quickselect.

**Practice**
- Sort an Array (solve it with each implementation above)
- Sort Colors
- Kth Largest Element in an Array (solve with quickselect)
- Largest Number
- H-Index

**CLRS**
- Getting Started (insertion sort, merge sort): Ch. 2 / Ch. 2.
- Heapsort: Ch. 6 / Ch. 6.
- Quicksort: Ch. 7 / Ch. 7.
- Sorting in Linear Time: Ch. 8 / Ch. 8.
- Medians and Order Statistics: Ch. 9 / Ch. 9.

**Mastery criteria**
- Merge sort and quicksort can be written from memory.
- Each algorithm's trade-offs in complexity, stability, and space can be stated.

---

### 10. Trees and Binary Search Trees

**Review**
- Tree terminology.
- Preorder, inorder, postorder, and level-order traversals, both recursive and iterative.
- Height and balance.
- BST invariants and operations, including deletion with successor replacement.
- Why balancing matters. AVL and red-black trees should be understood conceptually; implementing them is not necessary.
- Lowest common ancestor.
- Serialization.

**Implement**
- All four traversals, iteratively.
- BST insertion, search, and deletion.

**Practice**
- Invert Binary Tree
- Maximum Depth of Binary Tree
- Diameter of Binary Tree
- Same Tree
- Subtree of Another Tree
- Lowest Common Ancestor of a Binary Search Tree
- Binary Tree Level Order Traversal
- Validate Binary Search Tree
- Kth Smallest Element in a BST
- Construct Binary Tree from Preorder and Inorder Traversal
- Binary Tree Maximum Path Sum
- Serialize and Deserialize Binary Tree

**CLRS**
- Binary Search Trees: Ch. 12 / Ch. 12.
- Red-Black Trees: Ch. 13 / Ch. 13. Read only the properties and the intuition behind rotations.
- B-Trees: Ch. 18 / Ch. 18. This is optional, but relevant to database indexing.

**Mastery criteria**
- Recursive tree problems can be decomposed by asking what each node must return to its parent.
- Iterative traversals can be written from memory.

---

### 11. Heaps and Priority Queues

**Review**
- Binary heap array representation and index arithmetic.
- Sift-up and sift-down.
- O(n) heapify, including why it is linear.
- Min-heaps versus max-heaps, and the negation technique in Python's `heapq`.
- Top-k patterns.
- Two-heap median maintenance.
- Merging k sorted sequences.

**Implement**
- A binary min-heap supporting push, pop, peek, and heapify.

**Practice**
- Kth Largest Element in a Stream
- Last Stone Weight
- K Closest Points to Origin
- Task Scheduler
- Find Median from Data Stream

**CLRS**
- Heapsort, which covers heaps and priority queues: Ch. 6 / Ch. 6.

**Mastery criteria**
- It can be decided quickly whether a problem calls for a heap, sorting, or quickselect, and the choice can be justified.

---

### 12. Graph Traversal and Topological Sort

**Review**
- Adjacency lists versus adjacency matrices.
- Implicit graphs, such as grids and state spaces.
- BFS: shortest paths in unweighted graphs, and multi-source BFS.
- DFS: recursive and iterative forms, and visited-set management.
- Cycle detection:
  - in undirected graphs, using a parent check;
  - in directed graphs, using three-color marking.
- Topological sort with Kahn's algorithm and with DFS postorder.
- Bipartite checking.

**Implement**
- BFS and DFS on both an adjacency list and a grid.
- Kahn's algorithm.

**Practice**
- Number of Islands
- Max Area of Island
- Clone Graph
- Rotting Oranges
- Pacific Atlantic Water Flow
- Course Schedule
- Course Schedule II
- Is Graph Bipartite?
- Word Ladder

**CLRS**
- Elementary Graph Algorithms: Ch. 22 / Ch. 20.
  - BFS: §22.2 / §20.2.
  - DFS: §22.3 / §20.3.
  - Topological sort: §22.4 / §20.4.

**Mastery criteria**
- Grids and dependency problems are recognized as graphs.
- BFS and DFS can be written without errors in visited-state handling.

---

### 13. Union-Find (Disjoint Sets)

**Review**
- Find and union.
- Path compression.
- Union by rank or size.
- The inverse Ackermann bound.
- When union-find is preferable to DFS: incremental connectivity and cycle detection during edge insertion.

**Implement**
- Union-find with path compression and union by rank.

**Practice**
- Number of Connected Components in an Undirected Graph
- Redundant Connection
- Accounts Merge
- Number of Provinces

**CLRS**
- Data Structures for Disjoint Sets: Ch. 21 / Ch. 19. §21.3 / §19.3 covers the forest implementation. The amortized proof may be skipped.

**Mastery criteria**
- The structure can be written from memory in under five minutes.
- Its use cases can be stated.

---

### 14. Shortest Paths and Minimum Spanning Trees

**Review**
- Dijkstra's algorithm with a binary heap, the lazy-deletion technique, and why negative edge weights break it.
- Bellman-Ford and negative-cycle detection.
- Floyd-Warshall.
- 0-1 BFS.
- Prim's and Kruskal's algorithms, and the cut property.

**Implement**
- Dijkstra's algorithm with a heap.
- Kruskal's algorithm using the union-find structure from Topic 13.

**Practice**
- Network Delay Time
- Path With Minimum Effort
- Cheapest Flights Within K Stops
- Min Cost to Connect All Points
- Swim in Rising Water

**CLRS**
- Single-Source Shortest Paths: Ch. 24 / Ch. 22.
  - Bellman-Ford: §24.1 / §22.1.
  - Dijkstra: §24.3 / §22.3.
- All-Pairs Shortest Paths: Ch. 25 / Ch. 23. Floyd-Warshall is in §25.2 / §23.2.
- Minimum Spanning Trees: Ch. 23 / Ch. 21.

**Mastery criteria**
- The correct shortest-path algorithm can be selected from the graph's properties (weighted or unweighted, negative weights, single-source or all-pairs).
- Dijkstra's algorithm can be written from memory.

---

### 15. Backtracking

**Review**
- The choose–explore–unchoose template.
- State representation.
- Pruning.
- Handling duplicates by sorting and skipping.
- The complexity of generating subsets (2ⁿ) and permutations (n!).

**Implement**
- Generic templates for generating subsets, permutations, and combinations.

**Practice**
- Subsets
- Subsets II
- Permutations
- Combination Sum
- Combination Sum II
- Word Search
- Palindrome Partitioning
- N-Queens

**CLRS**
- Not directly covered.

**Mastery criteria**
- Any enumeration problem can be expressed with the template.
- Duplicate results are avoided reliably.

---

### 16. Dynamic Programming

**Review**
- The two prerequisite properties: optimal substructure and overlapping subproblems.
- The procedure: define the state, define the transition, set the base cases, and determine the evaluation order.
- Top-down memoization versus bottom-up tabulation.
- Space optimization by rolling arrays.
- Pattern families:
  - one-dimensional;
  - grid;
  - 0/1 and unbounded knapsack;
  - two-sequence (LCS, edit distance);
  - longest increasing subsequence, including the O(n log n) version;
  - interval;
  - bitmask;
  - tree;
  - state machine.

**Implement**
- Each of these problems in both memoized and tabulated form:
  - Coin Change,
  - Longest Common Subsequence,
  - 0/1 knapsack.

**Practice**
- One-dimensional:
  - Climbing Stairs
  - House Robber
  - House Robber II
  - Decode Ways
  - Coin Change
  - Word Break
  - Longest Increasing Subsequence
- Grid and knapsack:
  - Unique Paths
  - Partition Equal Subset Sum
  - Target Sum
  - Coin Change II
- Two-sequence:
  - Longest Common Subsequence
  - Edit Distance
  - Distinct Subsequences
- Other patterns:
  - Best Time to Buy and Sell Stock with Cooldown
  - Longest Palindromic Subsequence
  - Burst Balloons

**CLRS**
- Dynamic Programming: Ch. 15 / Ch. 14.
  - Rod cutting: §15.1 / §14.1. This is the clearest introduction to memoization versus tabulation.
  - Elements of DP: §15.3 / §14.3. This section is highly recommended for rebuilding intuition.
  - LCS: §15.4 / §14.4.

**Mastery criteria**
- The state and recurrence can be written down before coding.
- New problems can be classified into a known pattern family.
- A memoized solution can be converted to a tabulated one.

---

### 17. Greedy Algorithms and Intervals

**Review**
- The greedy-choice property, and the exchange argument for proving correctness.
- Common counterexamples where a greedy approach fails.
- Interval problems:
  - sorting by start or end,
  - merging,
  - removing overlaps,
  - counting the maximum concurrent intervals (sweep line, or a min-heap of end times).

**Implement**
- An interval-merging routine.
- A sweep-line computation of maximum overlap.

**Practice**
- Jump Game
- Jump Game II
- Gas Station
- Partition Labels
- Merge Intervals
- Insert Interval
- Non-overlapping Intervals
- Minimum Number of Arrows to Burst Balloons
- Meeting Rooms II (premium; Car Pooling is a free alternative)

**CLRS**
- Greedy Algorithms: Ch. 16 / Ch. 15.
  - Activity selection: §16.1 / §15.1.
  - Huffman codes: §16.3 / §15.3.

**Mastery criteria**
- A brief argument can be given for why a greedy choice is safe, or a counterexample found when it is not.

---

### 18. Bit Manipulation and Mathematics

**Review**
- Bitwise operators.
- Two's complement.
- `x & (x - 1)` (clear the lowest set bit) and `x & -x` (isolate the lowest set bit).
- Properties of XOR.
- Enumerating subsets with bitmasks.
- The GCD via the Euclidean algorithm.
- Fast modular exponentiation.
- The Sieve of Eratosthenes.
- Overflow awareness. This matters especially in C++.

**Implement**
- Fast exponentiation.
- The Sieve of Eratosthenes.

**Practice**
- Single Number
- Number of 1 Bits
- Counting Bits
- Missing Number
- Reverse Bits
- Sum of Two Integers
- Pow(x, n)
- Count Primes

**CLRS**
- Number-Theoretic Algorithms: Ch. 31 / Ch. 31. Read the Euclidean algorithm (§31.2) and modular exponentiation (§31.6) sections.

**Mastery criteria**
- The standard bit tricks can be applied without derivation.
- Each mathematical routine can be written from memory.

---

## Advanced Topics

These topics appear less frequently in general software engineering interviews, but they are expected by some employers and are valuable for depth. Begin them after the core topics are complete.

### 19. Tries

**Review**
- Node structure using a child map or a fixed-size array.
- Insert, search, and prefix search.
- Wildcard matching via DFS.
- Pruning a trie during backtracking.

**Implement**
- A trie supporting insert, search, and `startsWith`.

**Practice**
- Implement Trie (Prefix Tree)
- Design Add and Search Words Data Structure
- Word Search II

**CLRS**
- Covered only by the radix-tree problem at the end of Ch. 12. Prefer external references.

**Mastery criteria**
- A trie can be implemented in under ten minutes and combined with DFS.

---

### 20. Range Query Structures

**Review**
- Segment trees: build, point update, range query, and lazy propagation.
- Fenwick trees (binary indexed trees).
- When a prefix-sum array suffices and when a dynamic structure is required.

**Implement**
- A Fenwick tree.
- A segment tree supporting range-sum queries and point updates.

**Practice**
- Range Sum Query – Mutable
- Count of Smaller Numbers After Self
- My Calendar I

**CLRS**
- Augmenting Data Structures: Ch. 14 / Ch. 17. This covers order-statistic trees and interval trees, which are conceptually related.

**Mastery criteria**
- A Fenwick tree can be written from memory.
- A segment tree can be written with brief reference.

---

### 21. String Algorithms

**Review**
- Knuth-Morris-Pratt and its prefix function.
- Rabin-Karp and rolling hashes.
- The Z-algorithm.
- Expand-around-center for palindromes. Manacher's algorithm is optional.

**Implement**
- The KMP prefix function and matcher.
- A rolling hash.

**Practice**
- Find the Index of the First Occurrence in a String (solve with KMP)
- Repeated String Match
- Longest Palindromic Substring
- Palindromic Substrings
- Longest Duplicate Substring

**CLRS**
- String Matching: Ch. 32 / Ch. 32.
  - Rabin-Karp: §32.2.
  - KMP: §32.4.

**Mastery criteria**
- The prefix function can be explained.
- KMP can be implemented with brief reference.

---

### 22. Advanced Graph Topics

**Review**
- Strongly connected components, using the Kosaraju and Tarjan algorithms.
- Bridges and articulation points.
- A* search.
- Maximum flow (Ford-Fulkerson and Edmonds-Karp) and bipartite matching, at a conceptual level.

**Implement**
- Tarjan's algorithm for bridges.

**Practice**
- Critical Connections in a Network
- Find Eventual Safe States
- Reconstruct Itinerary
- Alien Dictionary (premium)

**CLRS**
- Strongly connected components: §22.5 / §20.5.
- Maximum Flow: Ch. 26 / Ch. 24.
- Bipartite matching: §26.3 / Ch. 25.

**Mastery criteria**
- The purpose and complexity of each algorithm can be stated.
- Bridge-finding can be implemented with brief reference.

---

## Consolidation

Return to consolidation periodically, and continuously once the core topics are complete.

1. **Re-solve logged problems** according to the spaced schedule in Appendix A, without notes.
2. **Practice mixed, unlabeled sets.** Solve two medium problems in 45 minutes, drawn from random topics, so that pattern recognition is practiced along with implementation.
3. **Practice communication.** Narrate the approach aloud while solving: brute force, optimization, complexity, and edge cases. Conduct periodic mock interviews with a peer or on a platform such as Pramp or interviewing.io.
4. **Review pattern recognition.** Given only a problem statement, identify the likely technique within two minutes. A recognition table is useful here; see Section 9 of the earlier reference summary.

---

## Appendix A: Error Log Template

Record every problem that could not be solved within the time cap, or that was solved with a significant error.

| Date | Problem | Topic | Pattern | Missed Insight | Re-solve 1 (≈3 days) | Re-solve 2 (≈1 week) | Re-solve 3 (≈3 weeks) |
|---|---|---|---|---|---|---|---|
| | | | | | | | |

**Guidance for the "Missed Insight" column:** state the specific idea that unlocks the problem, in one sentence. A useful entry reads like this: "Sorting by end time makes the greedy choice safe." An entry such as "Did not understand the problem" is not useful.

---

## Appendix B: Progress Tracker

Status values: **Not started**, **In progress**, **Mastered**.

| # | Topic | Diagnostic Result | Implementation Done | Practice Done | Status |
|---|---|---|---|---|---|
| 1 | Complexity Analysis | | | | |
| 2 | Arrays and Hashing | | | | |
| 3 | Two Pointers | | | | |
| 4 | Sliding Window | | | | |
| 5 | Prefix Sums and Difference Arrays | | | | |
| 6 | Stacks, Queues, and Monotonic Structures | | | | |
| 7 | Binary Search | | | | |
| 8 | Linked Lists | | | | |
| 9 | Sorting and Selection | | | | |
| 10 | Trees and Binary Search Trees | | | | |
| 11 | Heaps and Priority Queues | | | | |
| 12 | Graph Traversal and Topological Sort | | | | |
| 13 | Union-Find | | | | |
| 14 | Shortest Paths and MSTs | | | | |
| 15 | Backtracking | | | | |
| 16 | Dynamic Programming | | | | |
| 17 | Greedy Algorithms and Intervals | | | | |
| 18 | Bit Manipulation and Mathematics | | | | |
| 19 | Tries | | | | |
| 20 | Range Query Structures | | | | |
| 21 | String Algorithms | | | | |
| 22 | Advanced Graph Topics | | | | |
