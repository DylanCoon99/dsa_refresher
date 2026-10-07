# Corporate Flight Bookings
**Topic:** 05 Prefix Sums and Difference Arrays · **Kind:** Practice · **Difficulty:** Medium
**Plan reference:** LeetCode "Corporate Flight Bookings" (title kept for cross-reference only)

## Problem
There are `n` flights, numbered `1` to `n`. Each booking is a triple `{first, last, seats}`
that reserves `seats` seats on every flight from `first` to `last`, both inclusive
(1-indexed). Return a list `answer` of length `n` where `answer[i - 1]` is the total number
of seats reserved on flight `i`, summed over all bookings.

## Examples
- `bookings = {{1, 2, 10}, {2, 3, 20}, {2, 5, 25}}, n = 5` → `{10, 55, 45, 25, 25}`
  (flight 2 gets 10 + 20 + 25 = 55)
- `bookings = {{1, 2, 10}, {2, 2, 15}}, n = 2` → `{10, 25}`
- `bookings = {{1, 1, 4}}, n = 3` → `{4, 0, 0}` (flights nobody booked stay at 0)

## Constraints
- 1 ≤ n ≤ 10⁵
- 0 ≤ number of bookings ≤ 10⁵
- 1 ≤ first ≤ last ≤ n
- 1 ≤ seats ≤ 10⁴, and every flight's total fits in `int`

## Target
Time: O(n + number of bookings) · Space: O(n)

## Hints
<details><summary>Hint 1</summary>Adding `seats` to every flight in a range one by one costs O(range length) per booking. Could you instead record only where the extra seats start and where they stop?</details>
<details><summary>Hint 2</summary>If diff[i] is "how much does flight i differ from flight i-1", what does a running sum over diff give you, and which two entries does one booking touch?</details>
