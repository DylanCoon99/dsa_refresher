# DSA C++ Exercises — Design Spec

**Date:** 2026-10-06
**Status:** Approved in conversation; pending written-spec review
**Companion to:** `dsa-refresher-plan.md`

## 1. Goal

Build a local, self-contained C++ exercise repository that follows `dsa-refresher-plan.md` topic by topic. For every topic, the learner gets:

- a stub for every **Implement** item in the plan;
- a self-written version of every **Practice** problem in the plan (no LeetCode account or website needed);
- a test suite that reports pass/fail with one command;
- a hidden reference solution with complexity notes and the key insight;
- short, targeted pointers into CLRS (*Introduction to Algorithms*), so the book serves as a quick reference rather than required reading.

**Success criteria**

1. From a fresh clone, `./dsa test 02/two_sum` builds and runs in seconds with no installs beyond the existing Apple clang + CMake.
2. Every stub compiles as shipped and fails its tests.
3. `./dsa verify` passes: every test suite passes against its reference solution.
4. Every topic README mirrors the plan's Review / Implement / Practice / CLRS / Mastery sections as a checkbox list.

**Non-goals:** a web UI, automatic progress syncing into the plan's markdown tables, a spaced-repetition scheduler, Python versions of the exercises.

## 2. Decisions (from brainstorming)

| Decision | Choice |
|---|---|
| Scope | All Implement items + all Practice problems; Claude writes problem statements |
| Test framework | CMake + doctest (vendored single header) |
| Solutions | Yes, in a separate `solutions/` tree, runnable with `--solution` |
| Layout | One folder per exercise (Layout A) |
| CLRS | Short reading pointers in topic READMEs and relevant exercises |

## 3. Repository Layout

```
dsa-refresher-plan.md            # existing plan (unchanged)
dsa                              # bash helper script (executable)
CMakeLists.txt
third_party/doctest/doctest.h
common/
  list_node.hpp                  # ListNode + build_list / to_vector / doctest StringMaker
  tree_node.hpp                  # TreeNode + level-order build (std::optional<int>) / serialize
  graph.hpp                      # adjacency-list aliases, edge-list helpers
  random_utils.hpp               # seeded generators for randomized tests
  test_main.cpp                  # DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN, compiled once as a library
topics/
  01_complexity/
    README.md
    WORKSHEET.md                 # hand derivations; no code
  02_arrays_hashing/
    README.md                    # topic checklist + CLRS quick reference
    hash_map/                    # Implement item
      PROBLEM.md
      hash_map.hpp               # learner edits this
      test.cpp
    two_sum/                     # Practice problem
      PROBLEM.md
      two_sum.hpp
      test.cpp
  ...
  22_advanced_graphs/
solutions/
  01_complexity/ANSWERS.md
  02_arrays_hashing/two_sum/two_sum.hpp     # same filename and interface as the stub
  ...
.starter/                        # pristine copies of every stub, same relative paths as topics/
.attempts/                       # git-ignored; backups created by `./dsa reset`
build/                           # git-ignored
docs/superpowers/specs/, docs/superpowers/plans/
```

Topic folder names use a two-digit prefix matching the plan's numbering (`01_complexity` … `22_advanced_graphs`). Exercise folder names are `snake_case` versions of the problem or Implement item title.

## 4. Exercise Anatomy

### 4.1 `PROBLEM.md`

```markdown
# LRU Cache
**Topic:** 08 Linked Lists · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "LRU Cache" (title kept for cross-reference only)

## Problem
<statement written in original wording>

## Examples
<2–3 worked examples with explanation>

## Constraints
<input sizes and value ranges; these determine the target complexity>

## Target
Time: O(1) per operation · Space: O(capacity)

## CLRS (optional, ≈15 min)
- §10.2 (3e) / §10.2 (4e), "Linked lists": read the part on sentinels and the LIST-DELETE' pseudocode.
- Skip if you can already write a sentinel-based delete without special cases.

## Hints
<details><summary>Hint 1</summary>…</details>
<details><summary>Hint 2</summary>…</details>
```

- Problem statements are written in original words. The LeetCode title is kept only so the exercise matches the plan's checklist.
- The **Target** line follows the plan's "analyze before submitting" rule, so the learner knows what complexity to aim for.
- Implement items use the same template but set **Kind: Implement**, and the Problem section describes the required API.

### 4.2 Stub header (`<name>.hpp`)

- Self-contained `#pragma once` header, C++20, standard library plus `common/` only.
- Free functions declared `inline`; design problems (LRU cache, min stack, trie, …) as classes with all methods defined inline.
- The stub **compiles** and returns a neutral default (`{}`, `0`, `-1`, `false`) so the tests fail cleanly instead of failing to build.
- A `// TODO: implement` marker inside every body the learner must write.
- Signature comments state the contract (for example, whether input may be modified and what to return when no answer exists).

### 4.3 `test.cpp`

- Includes the exercise header with **angle brackets** (`#include <two_sum.hpp>`). Quoted includes search the test file's own directory first, so `--solution` would silently test the stub. Angle brackets resolve only through `-I`, which CMake points at either `topics/...` or `solutions/...`.
- Standard case groups (use those that apply):
  1. `examples`: the examples from PROBLEM.md;
  2. `edge cases`: empty, single element, duplicates, negatives, overflow boundaries (`INT_MIN`/`INT_MAX`), disconnected or cyclic structures;
  3. `randomized vs brute force`: a seeded generator compares the learner's answer with a brute-force reference written inside the test (where an obviously correct brute force exists);
  4. `large input`: sized so that a solution with the wrong complexity class takes clearly longer than ~2 s. It is tagged `* doctest::timeout(2.0)` so it reports a failure instead of hanging.
- For problems that accept any valid answer (any order, any valid index pair), tests normalize or validate the property instead of comparing against one exact output.

### 4.4 Reference solution

Same path relative to `solutions/`, same filename, same interface. The header comment contains:

```cpp
// Approach: <one or two sentences>
// Key insight: <the single sentence that unlocks it, in the style of the plan's error-log guidance>
// Time: O(...)  Space: O(...)
// Brute force: <naive approach and why it is too slow>
```

### 4.5 Topic `README.md`

```markdown
# 08 · Linked Lists
## Diagnostic
Start cold with: `reverse_linked_list`, `reorder_list` (≤ 40 min each).
## Review (self-check, from memory)
- [ ] Singly vs doubly linked lists …
## Implement
- [ ] `doubly_linked_list` — ./dsa test 08/doubly_linked_list
- [ ] `lru_cache` …
## Practice
- [ ] `reverse_linked_list` · Easy
…
## CLRS quick reference (≈20 min total)
| When | Read | Edition 3e / 4e |
## Mastery criteria
- [ ] …
```

- The Review, Implement, Practice and Mastery lists are copied from the plan.
- **Diagnostic** names the two practice problems to attempt cold, following step 1 of the plan's working method.

### 4.6 Topic 01 (Complexity Analysis)

Topic 01 has no code. `WORKSHEET.md` asks the learner to derive the recurrence and complexity, by hand, for merge sort, binary search, build-heap and recursive Fibonacci (both naive and memoized), and to apply the Master Theorem to 6 recurrences. The worked answers are in `solutions/01_complexity/ANSWERS.md`. Topic 01 is not built by CMake.

## 5. CLRS Pointers

The goal is targeted lookups, not reading assignments.

- **Where they appear:**
  - Every topic README has a **CLRS quick reference** table.
  - A `## CLRS` section is added to a `PROBLEM.md` **only** when a specific section directly helps with that exercise. Every Implement item that CLRS covers gets one. Practice problems get one where the underlying algorithm is in the book (e.g. Kth Largest → randomized select, Network Delay Time → Dijkstra, LCS).
  - Topics the plan marks "Not directly covered" (3, 4, 5, 15, and most of 19) state this once in the README and point to the problem hints instead. They contain no per-exercise CLRS notes.
- **Format of each pointer:**
  - section number for **both editions** (`§24.3 (3e) / §22.3 (4e)`) **plus the section title**, so a numbering mistake can still be resolved by title;
  - **what to read**, following the plan's reading order: chapter intro → pseudocode → statement of the key theorem or lemma, with proofs only when correctness is unclear;
  - a **time budget** (≤ 20 min per pointer);
  - a **skip-if** line: the self-check that means the reading is unnecessary.
- **Accuracy rule:**
  - Chapter mappings come from the plan's CLRS lines.
  - Finer subsection numbers are added only when known with confidence. Otherwise the pointer cites the chapter plus the section title, and never a guessed number.
  - Optional CLRS end-of-section exercises may be listed in the README for topics the learner finds uncertain (plan: "optionally attempt one or two section exercises"). They are not built as code.

## 6. Build System

- A top-level `CMakeLists.txt` requires C++20 and sets `-Wall -Wextra -Wno-unused-parameter`. Unused-parameter warnings are disabled because stubs ignore their parameters.
- `common/test_main.cpp` builds once as the static library `dsa_test_main`, so doctest's main is not recompiled for every exercise.
- Discovery: `file(GLOB ... CONFIGURE_DEPENDS topics/*/*/test.cpp)`. For each exercise `NN_topic/name`:
  - target `ex_NN_name`: include dirs `topics/NN_topic/name` and `common/`;
  - target `sol_NN_name`: include dirs `solutions/NN_topic/name` and `common/` (created only if the solution header exists).
- Build type `Debug` by default with `-fsanitize=address,undefined -fno-omit-frame-pointer` (catches pointer bugs in the linked-list and tree topics).
- Large-input tests are compiled in Debug too. Their sizes are calibrated so that the reference solution passes in Debug+ASan well under the timeout.
- Only requested targets are built (`cmake --build build --target ex_08_lru_cache`), which keeps a single test fast.

## 7. `./dsa` Helper Script

A bash script that runs under macOS's built-in `/bin/bash` 3.2, which rules out associative arrays and other bash-4 features.

| Command | Behavior |
|---|---|
| `./dsa test <NN>[/<name>] [--solution]` | Configure if needed, build the target(s), run them, print doctest output. `<NN>` alone runs every exercise in the topic and prints a summary line per exercise. Records pass/fail in `build/.status`. |
| `./dsa list [NN]` | Table of exercises with status: **untouched** (stub identical to `.starter/`), **failing**, **passing** (from the last recorded run), or **edited** (changed but not run since). |
| `./dsa reset <NN>/<name>` | Copy the current header to `.attempts/<NN>_<name>/<timestamp>.hpp`, then restore it from `.starter/`. Used for spaced re-solves. |
| `./dsa verify [--starters]` | Build and run every `sol_*` target; exit non-zero if any fails. With `--starters`, also check that every `topics/` stub is byte-identical to its `.starter/` copy (a maintainer check, run before committing new exercises). |
| `./dsa help` | Usage. |

Topic arguments accept the number (`08`, `8`) or the full folder name. Exercise names are matched exactly.

## 8. Shared Helpers (`common/`)

- `ListNode { int val; ListNode* next; }` matching the familiar interview signature, plus:
  - `build_list(std::vector<int>)` and `to_vector(ListNode*)`;
  - `free_list(ListNode*)`, used in tests so ASan does not report leaks;
  - cycle-aware variants for the cycle problems;
  - a separate `RandomListNode` that also carries a `random` pointer, for Copy List with Random Pointer.
- `TreeNode { int val; TreeNode* left; TreeNode* right; }` plus:
  - `build_tree(std::vector<std::optional<int>>)` in level-order form;
  - `to_level_order(TreeNode*)` and `free_tree(TreeNode*)`.
- Graph exercises use plain `std::vector<std::vector<int>>` adjacency lists or edge lists, the same shapes the problems define. `graph.hpp` holds only conversion helpers. Clone Graph uses its own `Node` type, defined in the exercise header.
- doctest `StringMaker` specializations so vectors, nested vectors and lists print their values when a check fails.

## 9. Exercise Inventory

All Implement and Practice items from topics 2–22 of the plan, plus the Topic 01 worksheet. The implementation plan lists every exercise as a checklist item. Notes on specific items:

- "Sort an Array" is a single exercise, with three test cases that call `merge_sort`, `quick_sort` and `heap_sort` entry points declared in the same header.
- "Kth Largest Element in an Array" asks for quickselect. The tests cannot enforce the technique, so PROBLEM.md says so explicitly.
- Premium problems (Meeting Rooms II, Alien Dictionary) are included, written in original words. The plan's free alternative, Car Pooling, is added alongside Meeting Rooms II.
- Topic 16 Implement items (Coin Change, LCS, 0/1 knapsack, each in memoized and tabulated form) are one exercise each, with two required entry points: `*_memo` and `*_tab`.

## 10. Source Control

- `git init` at the repo root.
- `.gitignore` covers `build/` and `.attempts/`.
- The spec and the plan are committed. Exercises are committed phase by phase as the plan is executed.

## 11. Risks

| Risk | Mitigation |
|---|---|
| Incorrect test or solution | `./dsa verify` must pass at the end of every phase; randomized brute-force cross-checks |
| Timeouts flaky under ASan | Calibrate large-input sizes against the reference solution in Debug, with ≥ 4× headroom |
| Wrong CLRS section numbers | Always pair the number with the section title; follow the accuracy rule in §5 |
| Solution leaks into the learner's view | Separate `solutions/` tree; topic READMEs never link into it |
