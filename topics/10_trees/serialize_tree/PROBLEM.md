# Serialize and Deserialize Binary Tree
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Practice · **Difficulty:** Hard
**Plan reference:** LeetCode "Serialize and Deserialize Binary Tree" (title kept for cross-reference only)

## Problem
Implement two functions:

- `std::string serialize(TreeNode* root)`: encode a binary tree as a string.
- `TreeNode* deserialize(const std::string& data)`: rebuild the tree from a string produced by `serialize`.

The format is up to you, as long as `deserialize(serialize(t))` gives back a tree with exactly the
same shape and values as `t`, including the empty tree (`nullptr`). The tests also check that
`serialize(deserialize(s)) == s` for every `s` your own `serialize` produced (the format must be
canonical), and that `serialize` does not modify the tree and `deserialize` returns newly allocated nodes (not the original ones). `deserialize` is only ever given strings
that your `serialize` produced. Remember that values can be negative and as large as `INT_MIN`/`INT_MAX`, so a delimiter and a
marker for "no child" are needed (a preorder listing with null markers is the simplest option).

**Tree conventions:** trees are built with `build_tree` from level order, e.g. `{3, 9, 20, null, null, 15, 7}`; results are compared with `to_level_order`; the tests never free nodes. Large tree inputs here are balanced, so recursion is fine.

## Examples
- `{1, 2, 3, null, null, 4, 5}` → some string `s`; `deserialize(s)` has level order `{1, 2, 3, null, null, 4, 5}`.
- `nullptr` → some string; `deserialize` of it is `nullptr`.
- `{1, 2}` and `{1, null, 2}` must serialize to different strings.

## Constraints
- 0 ≤ number of nodes ≤ 1000 in the tests (the deepest is a 1000-node chain).
- Any `int` values, including `INT_MIN` and `INT_MAX`.

## Target
Time: O(n) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>If you write a preorder traversal but also write a marker for every missing child, is the tree determined by that single list? Why is a plain preorder (without markers) not enough?</details>
<details><summary>Hint 2</summary>When reading the list back, how does "take the next token as the root, then rebuild the left subtree, then the right subtree" consume tokens in exactly the order they were written? A stream (such as `std::istringstream`) or a moving index makes this easy.</details>
