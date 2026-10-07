# DSA C++ Exercises Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a local C++ exercise repo with a stub, tests, a hidden reference solution and CLRS pointers for every Implement and Practice item in `dsa-refresher-plan.md`. There are 169 exercises plus the Topic 01 worksheet.

**Architecture:**
- **Layout:** one folder per exercise under `topics/NN_topic/<name>/`, containing `PROBLEM.md`, `<name>.hpp` (the learner edits this) and `test.cpp` (doctest). A same-named reference header lives under `solutions/`.
- **Build:** CMake compiles each `test.cpp` twice, once against the stub and once against the solution, by switching the `-I` path.
- **Tooling:** the bash script `./dsa` wraps building, running, status tracking, resetting and verification.

**Tech Stack:** C++20, Apple clang 21, CMake ≥ 3.20, doctest 2.4.11 (vendored), bash 3.2, perl (for the run timeout; ships with macOS).

**Spec:** `docs/superpowers/specs/2026-10-06-dsa-cpp-exercises-design.md`

## Plan files (chunked per CLAUDE.md: no file over 500 lines)

| File | Contents | Tasks |
|---|---|---|
| `00-index.md` (this file) | Constraints, review focus, authoring procedure, master checklist | — |
| `01a-infrastructure.md` | CMake, doctest, helper self-tests, the worked Two Sum example | 1–2 |
| `01b-common-helpers.md` | Full source of the `common/` helper headers (Task 1, Steps 5–8) | 1 |
| `02-tooling.md` | `./dsa` script, script self-test, root README, Topic 01 worksheet | 3–4 |
| `03a-topics-02-05.md` | Topics 02–05 | 5–8 |
| `03b-topics-06-09.md` | Topics 06–09 | 9–12 |
| `04a-topics-10-11.md` | Topics 10–11 | 13–14 |
| `04b-topics-12-14.md` | Topics 12–14 | 15–17 |
| `05a-topics-15-16.md` | Topics 15–16 | 18–19 |
| `05b-topics-17-18.md` | Topics 17–18 | 20–21 |
| `06-topics-19-22.md` | Topics 19–22 + final check | 22–26 |

Execute the files in order. Each task ends in a commit.

## Global Constraints

**Toolchain**
- C++20 (`CMAKE_CXX_STANDARD 20`, extensions off). Flags: `-Wall -Wextra -Wno-unused-parameter`. Debug builds add `-fsanitize=address,undefined -fno-omit-frame-pointer`, and Debug is the default build type.
- No dependencies beyond the standard library and `third_party/doctest/doctest.h` (v2.4.11).
- `./dsa` must run on macOS `/bin/bash` 3.2, so no associative arrays, `${x,,}`, `mapfile` or `[[ -v ]]`.

**File and include rules**
- Every exercise header is named after its folder: `topics/NN_x/<name>/<name>.hpp`. The solution is at `solutions/NN_x/<name>/<name>.hpp` and has an identical interface.
- `test.cpp` includes the exercise header with **angle brackets** first (`#include <name.hpp>`), then `<doctest.h>`, then any `common/` headers.

**Stubs**
- Every stub compiles, contains `// TODO: implement` in each body, and returns a neutral default (`{}`, `0`, `-1`, `false`, `nullptr`).
- Run against a stub, every test must report **FAIL**, never CRASH. Use `REQUIRE` before indexing into or dereferencing a returned value.

**Naming and wording**
- Practice exercises keep LeetCode's familiar function and class names (`twoSum`, `LRUCache`).
- Implement items use PascalCase classes, camelCase methods and free functions.
- Problem statements are written in original words. The LeetCode title appears only as "Plan reference".

**Tests**
- Randomized tests use `common/random_utils.hpp` (fixed seed) so failures are reproducible.
- "large input" tests are tagged `* doctest::timeout(2.0)`, and the reference solution must finish them in **< 0.5 s** in the Debug+ASan build.
- Large-input tests only need to separate complexity classes with a polynomial gap (O(n²) vs O(n log n), exponential vs polynomial). They don't try to catch a missing log factor; `PROBLEM.md` states the target instead.
- Tests never free linked or tree nodes. Learners may `delete` removed nodes, so freeing would risk a double free, and LeakSanitizer is unavailable on macOS arm64 anyway.

**CLRS pointers**
- Format: `§X.Y (3e) / §X.Y (4e), "<section title>"`, then what to read, a time budget of 20 minutes or less, and a "Skip if" line.
- Chapter numbers come from `dsa-refresher-plan.md`. Never guess a subsection or exercise number. If unsure, cite the chapter plus the title.

## Spec deviations (decided while planning)

1. **No `free_list` / `free_tree` helpers** (spec §8). This follows the "tests never free nodes" rule above.
2. **`./dsa verify` takes an optional topic** (`./dsa verify 08 --starters`), so each topic task can check itself without re-running all earlier topics.
3. **`./dsa` kills any test binary after 60 s** (override with `DSA_RUN_TIMEOUT`). doctest's `timeout` decorator only reports a slow test after it finishes, so without this an exponential solution would hang the terminal.
4. **`./dsa` accepts tab-completed paths** (`topics/08_linked_lists/lru_cache/`) as well as `08/lru_cache`.
5. **`--starters` also checks the stub itself:** the stub must contain `TODO: implement` and must produce FAIL, not CRASH, TIMEOUT or BUILD-ERROR.
6. **Design-problem duplicates share one exercise.** Where the plan lists the same thing under both Implement and Practice, only one exercise is built, and the topic README lists it under both headings:
   - Min Stack (06);
   - LRU Cache (08);
   - Coin Change and LCS (16);
   - Merge Intervals (17);
   - Trie (19).

## Review Focus

These are inputs the spec implies but no exercise test covers. Each one has a test in the task named in brackets.

1. **A learner's solution loops forever or runs in exponential time.** `./dsa` should report TIMEOUT and move on, not hang. [Task 3: `hang` fixture]
2. **One exercise in a topic doesn't compile.** `./dsa test NN` should report BUILD-ERROR for that exercise and still run the rest. [Task 3: `broken` fixture]
3. **A buggy solution leaves a linked list or tree cyclic.** Converting it for comparison should throw and fail the test, not hang. [Task 1: `to_vector` / `to_level_order` cycle tests]
4. **The learner runs `./dsa` from another directory or passes a tab-completed path.** It should still work. [Task 3: "works from another directory", "tab-completed path accepted"]
5. **A memory error such as an out-of-bounds read or use-after-free.** It should be reported as CRASH with the sanitizer report, not as an ordinary FAIL. [Task 3: `crash` fixture]

---

## Exercise Authoring Procedure

Every topic task (5–26) follows this procedure. The topic task lists the exercises, their exact signatures, the tests specific to each, and its CLRS pointers. This section defines everything else.

### A. `PROBLEM.md` template

```markdown
# <Title>
**Topic:** NN <Topic name> · **Kind:** Practice|Implement · **Difficulty:** Easy|Medium|Hard
**Plan reference:** LeetCode "<title>" (title kept for cross-reference only)   ← Practice only

## Problem
<original statement; for Implement items, the required API with each method's contract>

## Examples
<2–3 examples: input, output, one-line explanation>

## Constraints
<sizes and value ranges, copied from the task's "Constraints" line>

## Target
Time: O(…) · Space: O(…)

## CLRS (optional, ≈N min)        ← only when the task lists a CLRS pointer for this exercise
- §… (3e) / §… (4e), "<title>": <what to read>.
- Skip if: <self-check>.

## Hints
<details><summary>Hint 1</summary><nudge toward the right structure></details>
<details><summary>Hint 2</summary><the key insight, phrased as a question></details>
```

### B. `test.cpp` skeleton

```cpp
#include <EXERCISE.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>
// plus list_node.hpp / tree_node.hpp / graph.hpp as needed

TEST_CASE("examples") { /* the PROBLEM.md examples, exactly */ }

TEST_CASE("edge cases") {
    // the applicable items from: empty, single element, all duplicates, negatives,
    // INT_MIN/INT_MAX, disconnected or cyclic input, plus the task's listed edge cases
}

TEST_CASE("randomized vs brute force") {
    // 200–500 seeded trials of small inputs; brute force written inline in this file
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // only when the task lists "Large:"; sizes as specified there
}
```

- When several answers are valid, validate the property (or normalize by sorting) instead of comparing with one exact output.
- Brute-force references in tests must be obviously correct: nested loops, full enumeration, or `std::sort` and the standard library.

### C. Solution header comment

```cpp
// Approach: <1–2 sentences>
// Key insight: <one sentence, in the style of the plan's error-log "Missed Insight" column>
// Time: O(...)  Space: O(...)
// Brute force: <naive approach and its complexity>
```

### D. Topic `README.md` template

```markdown
# NN · <Topic name>
Run everything: `./dsa test NN` · Status: `./dsa list NN`

## Diagnostic
Attempt cold (≤ 40 min each): `<a>`, `<b>`. Both comfortable → skim Review, do Implement, go to Mastery.

## Review (from memory first)
- [ ] <each Review bullet from dsa-refresher-plan.md for this topic>

## Implement
- [ ] `<name>`: <one line> · `./dsa test NN/<name>`

## Practice
- [ ] `<name>` · <Difficulty> · `./dsa test NN/<name>`

## CLRS quick reference (≈<total> min, all optional)
| When | Read (3e / 4e) | What to read |
|---|---|---|

## Mastery criteria
- [ ] <each Mastery bullet from the plan>
```

The README must not link into `solutions/`.

### E. Standard steps of every topic task

The task gives the folder `TOPIC` (e.g. `08_linked_lists`) and the number `NN`.

- [ ] **Write tests first:** for every exercise in the task, write `PROBLEM.md` and `test.cpp` following A and B and the task's per-exercise notes.
- [ ] **Write stubs and snapshot them:** write each `<name>.hpp` stub, then copy the stubs into `.starter/`:
  ```bash
  for d in topics/TOPIC/*/; do n=$(basename "$d"); mkdir -p ".starter/TOPIC/$n" && cp "$d$n.hpp" ".starter/TOPIC/$n/"; done
  ```
- [ ] **Run against the stubs (red):** `./dsa test NN`. Expected: every line starts with `FAIL`, and the summary reads `0/K passing`. Any `BUILD-ERROR` or `CRASH` is a stub or test bug: fix it before continuing.
- [ ] **Write solutions:** write each `solutions/TOPIC/<name>/<name>.hpp` with the comment from C.
- [ ] **Verify (green):** `./dsa verify NN --starters`. Expected: every line `PASS … (solution)` and a final line `verify: OK`.
- [ ] **Check the large-input timing:** for each exercise marked **Large**, run `build/bin/sol_NN_<name> -tc="large input" --duration=true`. Expected: under 0.5 s. If it is slower, shrink the input and re-run verify.
- [ ] **Check that large tests reject brute force:** for each exercise marked **Large**, paste the brute force described in the solution comment into the stub header, then run `DSA_RUN_TIMEOUT=20 ./dsa test NN/<name>`. Expected: `FAIL` (doctest timeout) or `TIMEOUT`. Then run `./dsa reset NN/<name>`.
- [ ] **Write the topic README** following D, using the task's diagnostic picks and CLRS table.
- [ ] **Commit:**
  ```bash
  git add topics/TOPIC solutions/TOPIC .starter/TOPIC
  git commit -m "Add topic NN exercises: <topic name>"
  ```

---

## Master Checklist

### Stage 1: Infrastructure (`01a`, `01b`, `02-tooling.md`)
- [ ] Task 1: CMake, doctest, `common/` helpers + helper self-tests
- [ ] Task 2: Worked example `02_arrays_hashing/two_sum` (the reference exercise)
- [ ] Task 3: `./dsa` script + `tests/dsa_selftest.sh` + root `README.md`
- [ ] Task 4: Topic 01 Complexity worksheet + answer key

### Stage 2: Linear structures (`03a`, `03b`)
- [ ] Task 5: 02 Arrays and Hashing (8, incl. two_sum)
- [ ] Task 6: 03 Two Pointers (7)
- [ ] Task 7: 04 Sliding Window (7)
- [ ] Task 8: 05 Prefix Sums and Difference Arrays (6)
- [ ] Task 9: 06 Stacks, Queues, Monotonic (7)
- [ ] Task 10: 07 Binary Search (8)
- [ ] Task 11: 08 Linked Lists (9)
- [ ] Task 12: 09 Sorting and Selection (6)

### Stage 3: Trees and graphs (`04a`, `04b`)
- [ ] Task 13: 10 Trees and BSTs (14)
- [ ] Task 14: 11 Heaps (6)
- [ ] Task 15: 12 Graph Traversal and Topological Sort (11)
- [ ] Task 16: 13 Union-Find (5)
- [ ] Task 17: 14 Shortest Paths and MSTs (7)

### Stage 4: Techniques (`05a`, `05b`)
- [ ] Task 18: 15 Backtracking (9)
- [ ] Task 19: 16 Dynamic Programming (18)
- [ ] Task 20: 17 Greedy and Intervals (11)
- [ ] Task 21: 18 Bit Manipulation and Math (10)

### Stage 5: Advanced (`06-topics-19-22.md`)
- [ ] Task 22: 19 Tries (3)
- [ ] Task 23: 20 Range Query Structures (5)
- [ ] Task 24: 21 String Algorithms (7)
- [ ] Task 25: 22 Advanced Graph Topics (5)
- [ ] Task 26: Final full verification + script self-test

**Total:** 169 exercises + 1 worksheet.
