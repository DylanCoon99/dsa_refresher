# Stage 3a: Topics 10–11 (Tasks 13–14)

Read `00-index.md` first. The conventions are the same as `03a-topics-02-05.md`:
- **Sig** is the exact stub signature.
- **Tests** lists the required cases beyond the standard groups.
- **Large** defines the large-input test. If there is no Large line, there is no large test.
- **CLRS** is the PROBLEM.md pointer.

Every task follows the Exercise Authoring Procedure in `00-index.md` (A–E).

**Tree conventions** (state them in each tree PROBLEM.md):
- Trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`.
- Results are compared with `to_level_order`.
- Tests never free nodes.
- Except for `tree_traversals`, large tree inputs are **balanced** (`build_balanced_bst`), so that recursive solutions are acceptable.

---

### Task 13: Topic 10 Trees and Binary Search Trees

`TOPIC=10_trees`, `NN=10`.

**Diagnostic picks:** `validate_bst`, `build_tree_pre_in`.

**Exercises:**

- **`tree_traversals`** · Implement · Medium
  - Sig: `std::vector<int> preorderIterative(TreeNode* root)`, `std::vector<int> inorderIterative(TreeNode* root)`, `std::vector<int> postorderIterative(TreeNode* root)` and `std::vector<int> levelOrderFlat(TreeNode* root)`
  - Contract: no recursion (stated). Use an explicit `std::vector` stack or `std::queue`.
  - Tests:
    - empty tree;
    - a single node;
    - a left-only chain;
    - the example tree;
    - 200 random trees compared with recursive reference traversals written in the test.
  - Large: `build_chain(100000)` for all four. Recursion 10⁵ deep overflows the stack under ASan and shows up as CRASH, which PROBLEM.md explains is the intended lesson. Confirm in procedure E that a recursive solution produces CRASH or FAIL.
  - CLRS: §12.1 (3e) / §12.1 (4e), "What is a binary search tree?": INORDER-TREE-WALK (≈5 min). An end-of-section exercise there asks for the non-recursive inorder walk with a stack. §10.4 (3e) / §10.3 (4e), "Representing rooted trees" (≈5 min).
- **`bst`** · Implement · Medium
  - Sig:
    ```cpp
    class BST { public: BST(); ~BST(); BST(const BST&) = delete; BST& operator=(const BST&) = delete; bool insert(int v); bool contains(int v) const; bool erase(int v); std::vector<int> inorder() const; std::size_t size() const; };
    ```
  - Contract: no duplicates (`insert` returns false). `erase` handles the 0-, 1- and 2-child cases, the last using successor replacement.
  - Tests: erase the root with two children; erase a leaf; erase a missing value; 2·10⁴ random ops against `std::set`.
  - Large: none (an unbalanced BST is acceptable here; random inserts keep it shallow).
  - CLRS: §12.2–12.3 (3e) / §12.2–12.3 (4e), "Querying a binary search tree" and "Insertion and deletion": TREE-SUCCESSOR, TREE-INSERT, TRANSPLANT, TREE-DELETE (≈20 min). Skip if you can delete a node with two children from memory.
- **`invert_tree`** · Easy
  - Sig: `TreeNode* invertTree(TreeNode* root)`
  - Tests: empty; single node; asymmetric tree.
- **`max_depth`** · Easy
  - Sig: `int maxDepth(TreeNode* root)`
  - Tests: empty → 0; a skewed tree of 1000 nodes.
- **`diameter`** · Easy
  - Sig: `int diameterOfBinaryTree(TreeNode* root)`
  - Contract: counted in edges.
  - Tests: single node → 0; the diameter doesn't pass through the root.
  - Large: balanced tree with 2·10⁵ nodes. Recomputing heights at every node is O(n log n), which still passes, so this large test only rules out O(n²) on balanced input. That's acceptable.
- **`same_tree`** · Easy
  - Sig: `bool isSameTree(TreeNode* p, TreeNode* q)`
  - Tests: both null; one null; same values but different shape.
- **`subtree`** · Easy
  - Sig: `bool isSubtree(TreeNode* root, TreeNode* subRoot)`
  - Tests: subRoot matches but root has extra descendants below the match → false; subRoot equals root; duplicate values in root.
- **`lca_bst`** · Medium
  - Sig: `TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)`
  - Tests: p is an ancestor of q; p == q; nodes found via `find_node`; compare by pointer.
- **`level_order`** · Medium
  - Sig: `std::vector<std::vector<int>> levelOrder(TreeNode* root)`
  - Tests: empty; single node; unbalanced.
- **`validate_bst`** · Medium
  - Sig: `bool isValidBST(TreeNode* root)`
  - Contract: strict ordering, no duplicates allowed.
  - Tests:
    - `{5,1,4,null,null,3,6}` → false (the grandchild breaks the root bound);
    - a node equal to its parent → false;
    - INT_MIN and INT_MAX values: `{2147483647}` → true, `{-2147483648, null, 2147483647}` → true.
- **`kth_smallest_bst`** · Medium
  - Sig: `int kthSmallest(TreeNode* root, int k)`
  - Tests: k = 1; k = n; randomized balanced BSTs.
- **`build_tree_pre_in`** · Medium
  - Sig: `TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder)`
  - Contract: distinct values.
  - Tests: single node; left-only chain; right-only chain; 200 random trees (build, take traversals, rebuild, compare level order).
  - Large: balanced tree of 10⁵ nodes. A linear search for each root in inorder is O(n log n) on balanced input, so this only catches O(n²) slicing via vector copies at each level. Acceptable.
- **`max_path_sum`** · Hard
  - Sig: `int maxPathSum(TreeNode* root)`
  - Tests: all negative (answer = the max single node); a single node; a path not through the root; randomized small trees against brute force (all node pairs).
- **`serialize_tree`** · Hard
  - Sig: `std::string serialize(TreeNode* root)` and `TreeNode* deserialize(const std::string& data)`
  - Contract: any format is fine.
  - Tests: round-trip on an empty tree; negative values; INT_MIN; 300 random trees; `serialize(deserialize(s)) == s`.

**CLRS quick reference rows:**
- Rooted tree representation: §10.4 / §10.3, ≈5 min.
- BST walk, search and successor: §12.1–12.2 / §12.1–12.2, ≈15 min.
- BST insert and delete: §12.3 / §12.3, ≈15 min.
- Why balance matters: §13.1 / §13.1, "Properties of red-black trees"; read the properties and the height lemma statement, ≈10 min.
- Rotations: §13.2 / §13.2, "Rotations"; the picture and LEFT-ROTATE, ≈10 min.
- Optional: Ch. 18 / Ch. 18, "B-Trees"; intro only, for database indexing context, ≈15 min.

---

### Task 14: Topic 11 Heaps and Priority Queues

`TOPIC=11_heaps`, `NN=11`.

**Diagnostic picks:** `k_closest_points`, `median_finder`.

**Exercises:**

- **`min_heap`** · Implement · Medium
  - Sig:
    ```cpp
    class MinHeap { public: MinHeap(); explicit MinHeap(std::vector<int> values); void push(int v); int pop(); int top() const; std::size_t size() const; bool empty() const; };
    ```
  - Contract:
    - Array-backed, without `std::priority_queue` or `std::make_heap` (stated).
    - The vector constructor must heapify in O(n) (bottom-up sift-down).
    - `pop` and `top` on an empty heap throw `std::out_of_range`.
  - Tests:
    - empty throws;
    - duplicates;
    - negatives;
    - heap-sort 1000 random vectors by repeated pop and compare with `std::sort`;
    - 10⁵ random push/pop ops against `std::priority_queue<int, std::vector<int>, std::greater<>>`.
  - Large: push 10⁶ values then pop all. A sorted-vector insert is O(n²).
  - CLRS: §6.1–6.3 (3e) / §6.1–6.3 (4e), "Heaps", "Maintaining the heap property", "Building a heap": the index arithmetic, MAX-HEAPIFY, and the O(n) BUILD-MAX-HEAP bound (≈20 min). Skip if you can explain why bottom-up heapify is linear.
- **`kth_largest_stream`** · Easy
  - Sig: `class KthLargest { public: KthLargest(int k, const std::vector<int>& nums); int add(int val); };`
  - Contract: after each `add` there are at least k elements.
  - Tests: nums initially shorter than k; negatives; duplicates.
  - Large: k = 10⁴ with 10⁵ adds. Re-sorting on each add is far too slow.
- **`last_stone_weight`** · Easy
  - Sig: `int lastStoneWeight(const std::vector<int>& stones)`
  - Tests: single stone; two equal → 0; randomized against a brute-force sort-each-round simulation.
- **`k_closest_points`** · Medium
  - Sig: `std::vector<std::vector<int>> kClosest(const std::vector<std::vector<int>>& points, int k)`
  - Contract: unique answer; any order.
  - Tests: normalize; k = n; negative coordinates; coordinates of ±10⁴ (squared sums fit in int).
  - Large: 10⁵ points with k = 10. O(n log n) passes; the Target says O(n log k).
- **`task_scheduler`** · Medium
  - Sig: `int leastInterval(const std::vector<char>& tasks, int n)`
  - Tests: n = 0 → tasks.size(); a single task type; many types with no idle time needed; randomized against brute-force greedy simulation for tiny inputs.
- **`median_finder`** · Hard
  - Sig: `class MedianFinder { public: void addNum(int num); double findMedian() const; };`
  - Contract: `findMedian` is never called while empty.
  - Tests: odd and even counts; negatives; INT_MAX + INT_MAX averaging (compute in double, no int overflow); 10⁴ random ops against a sorted-vector model.
  - Large: 10⁵ adds, each followed by `findMedian`. Sorting on each query is far too slow.
  - CLRS: §6.5 (3e) / §6.5 (4e), "Priority queues" (≈10 min).

**CLRS quick reference rows:**
- Heap structure and heapify: §6.1–6.2 / §6.1–6.2, ≈10 min.
- Linear build-heap: §6.3 / §6.3, ≈10 min.
- Priority-queue operations: §6.5 / §6.5, ≈10 min.
- PROBLEM.md hint for the plan's Python `heapq` negation note: in C++, use `std::priority_queue<int>` (a max-heap) or pass `std::greater<>` for a min-heap.
