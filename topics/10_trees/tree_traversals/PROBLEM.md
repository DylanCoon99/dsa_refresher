# Tree Traversals (Iterative)
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement four traversals of a binary tree, each returning the node values in visiting order:

- `std::vector<int> preorderIterative(TreeNode* root)`: node, left subtree, right subtree.
- `std::vector<int> inorderIterative(TreeNode* root)`: left subtree, node, right subtree.
- `std::vector<int> postorderIterative(TreeNode* root)`: left subtree, right subtree, node.
- `std::vector<int> levelOrderFlat(TreeNode* root)`: level by level, left to right, as one flat list.

An empty tree (`nullptr`) gives an empty vector. Do not use recursion: keep an explicit
`std::vector` as a stack (or a `std::queue` for level order). The tests cannot see your code;
the only thing that enforces this is the deep-chain test, where a recursive version needs one
stack frame per node (10⁵ deep) and is expected to overflow the stack under ASan, which `./dsa`
reports as CRASH. That CRASH is the intended lesson. (Whether it overflows depends on frame size
and the stack limit; the test does not detect recursion in any other way.)

**Tree conventions (all tree exercises):** trees are built with `build_tree` from level order,
e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never
free nodes. Except in this exercise, large tree inputs are balanced, so recursion is fine elsewhere.

## Examples
- Tree `{3, 9, 20, null, null, 15, 7}`: preorder `3 9 20 15 7`, inorder `9 3 15 20 7`, postorder `9 15 7 20 3`, level order `3 9 20 15 7`.
- Tree `{1, null, 2, null, 3}` (a right chain): preorder `1 2 3`, inorder `1 2 3`, postorder `3 2 1`.
- `nullptr`: all four return `{}`.

## Constraints
- 0 ≤ number of nodes ≤ 10⁵ (the deepest test is a right-leaning chain of 10⁵ nodes).
- Any `int` values.

## Target
Time: O(n) · Space: O(h) for the stack in the DFS traversals (O(n) for a chain), O(w) for the queue in level order

## CLRS (optional, ≈10 min)
- §12.1 (3e) / §12.1 (4e), "What is a binary search tree?": INORDER-TREE-WALK (≈5 min). An end-of-section exercise there asks for the non-recursive inorder walk using a stack.
- §10.4 (3e) / §10.3 (4e), "Representing rooted trees" (≈5 min).
- Skip if: you can write an inorder walk with an explicit stack and say what the stack holds at each moment.

## Hints
<details><summary>Hint 1</summary>A recursive walk uses the call stack to remember "where to go back to". What would you push onto your own stack to remember the same thing?</details>
<details><summary>Hint 2</summary>For inorder: keep going left while pushing nodes; when you cannot go left, what do you pop, visit, and then move to? For postorder: how do you know a popped node's right subtree is already finished?</details>
