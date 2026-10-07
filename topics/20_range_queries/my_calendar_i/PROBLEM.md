# My Calendar I
**Topic:** 20 Range Query Structures · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "My Calendar I" (title kept for cross-reference only)

## Problem
Implement a `MyCalendar` that stores bookings, each a **half-open** interval `[start, end)`.

`book(start, end)` tries to add the booking. It succeeds (returns `true` and stores it) only if it overlaps no stored booking; otherwise it returns `false` and stores nothing. Two half-open intervals `[a, b)` and `[c, d)` overlap exactly when `a < d` and `c < b`, so bookings that merely touch (`[10, 20)` and `[20, 30)`) do not overlap. A nested booking or an identical one does.

A failed `book` leaves the calendar unchanged.

## Examples
- `book(10, 20)` → `true`; `book(15, 25)` → `false` (overlaps `[15, 20)`); `book(20, 30)` → `true` (touches only)
- `book(5, 10)` → `true`, then `book(5, 10)` → `false` (identical)
- `book(0, 100)` → `true`, then `book(40, 50)` → `false` (nested)

## Constraints
- 0 ≤ start < end ≤ 10⁹.
- At most 10⁵ bookings per test (the large test makes 10⁵ + 1000 calls; limits chosen for this exercise).

## Target
Time: O(log n) per `book` (a scan of all bookings is O(n) per call, O(n²) in total) · Space: O(n)

## CLRS (optional, ≈15 min)
- §14.3 (3e) / §17.3 (4e), "Interval trees": read INTERVAL-SEARCH. Finding any stored interval that overlaps a query interval is exactly this operation. A `std::map` keyed by start with `lower_bound` is the practical equivalent.
- Skip if: you can explain why only the stored booking just before and the one just after `start` need to be checked.

## Hints
<details><summary>Hint 1</summary>Keep the bookings sorted by start. If the existing bookings never overlap each other, which one or two neighbours of the new interval could possibly collide with it?</details>
<details><summary>Hint 2</summary>With an ordered map from start to end, what does `lower_bound(start)` give you, and what two comparisons decide the answer?</details>
