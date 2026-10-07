# Course Schedule II
**Topic:** 12 Graph Traversal and Topological Sort · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Course Schedule II" (title kept for cross-reference only)

## Problem
There are `numCourses` courses numbered `0 .. numCourses-1`. Each prerequisite `{a, b}` means
course `b` must be taken **before** course `a`. Return an order in which all courses can be taken:
a list containing every course exactly once in which each course comes after its prerequisites.
If several orders work, return any of them (the tests check the property, not a specific order). If
it is impossible (the prerequisites contain a cycle, including a course that requires itself),
return an empty vector. Courses with no prerequisites and nothing depending on them must still
appear in the order. Prerequisite pairs may repeat.

## Examples
- `numCourses = 2, {{1, 0}}` → `{0, 1}`
- `numCourses = 4, {{1,0},{2,0},{3,1},{3,2}}` → `{0, 1, 2, 3}` (or `{0, 2, 1, 3}`)
- `numCourses = 2, {{1, 0}, {0, 1}}` → `{}`

## Constraints
- 1 ≤ numCourses ≤ 2000
- 0 ≤ prerequisites.size() ≤ 5000, each course in `[0, numCourses)`.
- These limits are chosen for this exercise; they cover every test input.

## Target
Time: O(V + E) · Space: O(V + E)

## Hints
<details><summary>Hint 1</summary>If you already know how to decide whether a schedule exists, what extra information do you produce along the way that is itself a valid order?</details>
<details><summary>Hint 2</summary>How do you tell, once the search ends, that some courses were never released? What does that say about the graph?</details>
