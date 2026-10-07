# DSA Refresher: C++ Exercises

Hands-on exercises for every topic in [`dsa-refresher-plan.md`](dsa-refresher-plan.md).
Each topic folder has a checklist README; each exercise has a problem statement,
a stub for you to fill in, and a test suite.

## Quick start
```bash
./dsa test 02/two_sum     # build + run one exercise
./dsa test 02             # every exercise in a topic, one line each
./dsa list                # untouched / edited / failing / passing for everything
```
Requirements: Apple clang (Xcode command line tools) and CMake ≥ 3.20. Nothing else to install.

## Working an exercise
1. Read `topics/NN_topic/<name>/PROBLEM.md`. It ends with the target complexity and, where useful, a CLRS pointer.
2. State the brute force and its complexity, then edit `<name>.hpp`. Don't edit `test.cpp`.
3. Run `./dsa test NN/<name>`. The tests cover examples, edge cases, a randomized check
   against brute force, and (for some exercises) a large input that a slow algorithm fails.
4. Stuck for 30–40 minutes? Hints are folded at the bottom of PROBLEM.md. After that, read
   `solutions/NN_topic/<name>/<name>.hpp` and record the missed insight in your error log.

## Re-solving (spaced repetition)
`./dsa reset NN/<name>` saves your current attempt to `.attempts/` and restores the
blank stub, so you can re-solve at ~3 days, ~1 week, and ~3 weeks.

## Result words
| Word | Meaning |
|---|---|
| PASS / FAIL | Tests passed / at least one check failed |
| BUILD-ERROR | Your header doesn't compile; compiler output is shown |
| TIMEOUT | Killed after 60 s (`DSA_RUN_TIMEOUT` overrides): infinite loop or wrong complexity class |
| CRASH | AddressSanitizer / UBSan caught a memory error or undefined behavior; read the report |

## CLRS
Topic READMEs have a "CLRS quick reference" table; PROBLEM.md files point to specific
sections when one directly helps. Every pointer gives both 3e and 4e numbering, the section
title, what to read, a time budget, and a "skip if" check. All of it is optional.

## Layout
`topics/` (your work) · `solutions/` (references; don't peek early) · `common/` (test helpers)
· `.starter/` (pristine stubs used by reset) · `docs/superpowers/` (design spec and build plan)
