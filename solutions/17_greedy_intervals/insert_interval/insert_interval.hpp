#pragma once
#include <algorithm>
#include <vector>

// Approach: copy intervals that end before the new one starts; absorb every interval that starts at or
//           before the new end by widening the new interval; then copy the rest.
// Key insight: sortedness splits the list into before / overlapping / after, so one linear pass suffices.
// Time: O(n)  Space: O(n)
// Brute force: append the new interval and run a full sort-and-merge: O(n log n) (correct, but ignores sortedness).
inline std::vector<std::vector<int>> insert(std::vector<std::vector<int>> intervals, std::vector<int> newInterval) {
    std::vector<std::vector<int>> out;
    std::size_t i = 0;
    const std::size_t n = intervals.size();
    while (i < n && intervals[i][1] < newInterval[0]) out.push_back(intervals[i++]);
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = std::min(newInterval[0], intervals[i][0]);
        newInterval[1] = std::max(newInterval[1], intervals[i][1]);
        ++i;
    }
    out.push_back(newInterval);
    while (i < n) out.push_back(intervals[i++]);
    return out;
}
