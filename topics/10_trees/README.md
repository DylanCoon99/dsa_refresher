# 10 · Trees and Binary Search Trees
Run everything: `./dsa test 10` · Status: `./dsa list 10`

## Diagnostic
Attempt cold (≤ 40 min each): `validate_bst`, `build_tree_pre_in`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] Tree terminology.
- [ ] Preorder, inorder, postorder, and level-order traversals, both recursive and iterative.
- [ ] Height and balance.
- [ ] BST invariants and operations, including deletion with successor replacement.
- [ ] Why balancing matters. AVL and red-black trees should be understood conceptually; implementing them is not necessary.
- [ ] Lowest common ancestor.
- [ ] Serialization.

## Implement
- [ ] `tree_traversals`: preorder, inorder, postorder and level order, all without recursion; the deep-chain test turns recursion into a CRASH · `./dsa test 10/tree_traversals`
- [ ] `bst`: a `BST` class with insert, contains, erase (0-, 1- and 2-child cases) and inorder · `./dsa test 10/bst`

## Practice
- [ ] `invert_tree` · Easy · `./dsa test 10/invert_tree`
- [ ] `max_depth` · Easy · `./dsa test 10/max_depth`
- [ ] `diameter` · Easy · `./dsa test 10/diameter`
- [ ] `same_tree` · Easy · `./dsa test 10/same_tree`
- [ ] `subtree` · Easy · `./dsa test 10/subtree`
- [ ] `lca_bst` · Medium · `./dsa test 10/lca_bst`
- [ ] `level_order` · Medium · `./dsa test 10/level_order`
- [ ] `validate_bst` · Medium · `./dsa test 10/validate_bst`
- [ ] `kth_smallest_bst` · Medium · `./dsa test 10/kth_smallest_bst`
- [ ] `build_tree_pre_in` · Medium · `./dsa test 10/build_tree_pre_in`
- [ ] `max_path_sum` · Hard · `./dsa test 10/max_path_sum`
- [ ] `serialize_tree` · Hard · `./dsa test 10/serialize_tree`

## CLRS quick reference (≈65 min, all optional)
| When | Read (3e / 4e) | What to read | Skip if |
|---|---|---|---|
| Before `tree_traversals` | §10.4 (3e) / §10.3 (4e), "Representing rooted trees" | Left-child/right-sibling and the plain node-with-pointers form (≈5 min) | You can describe how a node stores its children and parent. |
| Before `tree_traversals` | §12.1 (3e) / §12.1 (4e), "What is a binary search tree?" | The BST property and INORDER-TREE-WALK; the end-of-section exercise asks for a non-recursive inorder walk with a stack (≈5 min) | You can write an inorder walk with an explicit stack. |
| Before `bst` | §12.2–12.3 (3e) / §12.2–12.3 (4e), "Querying a binary search tree" and "Insertion and deletion" | TREE-SUCCESSOR, TREE-INSERT, TRANSPLANT, TREE-DELETE (≈20 min) | You can delete a node with two children from memory. |
| Review: why balance matters | §13.1 (3e) / §13.1 (4e), "Properties of red-black trees" | The five properties and the statement of the height lemma, without the proof (≈10 min) | You can say why a red-black tree with n keys has height O(log n). |
| Review: rotations | §13.2 (3e) / §13.2 (4e), "Rotations" | The picture and LEFT-ROTATE (≈10 min) | You can draw a left rotation and say which subtree changes parent. |
| Optional: database indexing context | Ch. 18 (3e) / Ch. 18 (4e), "B-Trees" | The chapter intro only (≈15 min) | You already know why disk-based indexes use wide nodes instead of binary ones. |

## Mastery criteria
- [ ] Recursive tree problems can be decomposed by asking what each node must return to its parent.
- [ ] Iterative traversals can be written from memory.
