# Binary Search Tree
**Topic:** 10 Trees and Binary Search Trees · **Kind:** Implement · **Difficulty:** Medium

## Problem
Implement a `BST` class holding distinct `int` keys with the usual ordering invariant (every key
in a node's left subtree is smaller, every key in its right subtree is larger):

```cpp
class BST {
public:
    BST();                                  // empty tree
    ~BST();                                 // free every node you allocated
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;
    bool insert(int v);                     // true if added, false if v was already present
    bool contains(int v) const;
    bool erase(int v);                      // true if removed, false if v was not present
    std::vector<int> inorder() const;       // all keys in ascending order
    std::size_t size() const;               // number of keys
};
```

No duplicates are stored. `erase` must handle all three cases: a leaf, a node with one child, and
a node with two children. For the two-children case replace the node's key with its **inorder
successor** (the smallest key in its right subtree) and remove that node instead. The tests can
only observe contents, `size` and return values, so a predecessor-based delete would also pass.
Nothing is balanced; the tests insert random keys, which keep the tree shallow. Do not rely on the
tree staying shallow for sorted input in your own experiments (it degenerates into a list).

**Tree conventions (all tree exercises):** the tree here is your own node type; for the other
tree exercises, trees are built with `build_tree` from level order and compared with
`to_level_order`. The tests never free nodes, but `BST` owns its nodes, so write the destructor.

## Examples
- Insert 5, 3, 8, 1, 4: `inorder()` is `{1, 3, 4, 5, 8}`, `size()` is `5`; inserting 3 again returns `false`.
- On that tree `erase(5)` (root, two children) returns `true` and `inorder()` is `{1, 3, 4, 8}`.
- `erase(42)` on a tree that does not hold 42 returns `false` and changes nothing.

## Constraints
- Any `int` keys. The tests use up to 2·10⁴ operations on keys drawn from a few hundred values, so the tree height stays small.

## Target
Time: O(h) per operation (h = tree height; O(log n) expected for random keys) · Space: O(n)

## CLRS (optional, ≈20 min)
- §12.2–12.3 (3e) / §12.2–12.3 (4e), "Querying a binary search tree" and "Insertion and deletion": TREE-SUCCESSOR, TREE-INSERT, TRANSPLANT, TREE-DELETE (≈20 min).
- Skip if: you can delete a node with two children from memory.

## Hints
<details><summary>Hint 1</summary>For erase, first find the node (and its parent, or a pointer to the link that points at it). How many children does it have, and what should its parent's link point to afterwards in the 0- and 1-child cases?</details>
<details><summary>Hint 2</summary>With two children, which existing node can take this node's place without breaking the ordering? Where does it live, and how many children can it itself have?</details>
