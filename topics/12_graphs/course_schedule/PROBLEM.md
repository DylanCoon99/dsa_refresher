# Course Schedule
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Course Schedule" (title kept for cross-reference only)

## Problem
There are `numCourses` courses numbered `0 .. numCourses-1`. Each prerequisite is a pair
`{a, b}` meaning course `b` must be completed **before** course `a`. Return `true` if it is
possible to complete every course, and `false` otherwise (for example because the prerequisites
form a cycle; a course that requires itself counts as a cycle). Prerequisite pairs may repeat.

## Examples
- `numCourses = 2, {{1, 0}}` → `true` (take 0, then 1)
- `numCourses = 2, {{1, 0}, {0, 1}}` → `false` (each needs the other first)
- `numCourses = 4, {{1,0},{2,0},{3,1},{3,2}}` → `true`

## Constraints
- 1 ≤ numCourses ≤ 10⁵
- 0 ≤ prerequisites.size() ≤ 10⁵, each course in `[0, numCourses)`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(V + E) · Space: O(V + E)

The large test (a chain of 10⁵ courses, then the same chain closed into a cycle) rejects
repeatedly rescanning all prerequisites (O(V · E)). A recursive DFS over a 10⁵-long chain can also
overflow the call stack (under the sanitizer build this shows up as a CRASH); prefer an iterative
approach.

## Hints
<details><summary>Hint 1</summary>Draw an arrow from each prerequisite to the course that needs it. When is it impossible to finish all courses in terms of this graph?</details>
<details><summary>Hint 2</summary>Which courses can you take right now, and what changes for the others once you take one?</details>
