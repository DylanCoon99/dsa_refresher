#pragma once
#include <algorithm>
#include <vector>

// Approach: sort by start, then sweep once, extending the interval being built while the next start is
//           <= its end (closed intervals: touching merges), otherwise emit it and start a new one.
// Key insight: after sorting by start, an interval can only overlap the one being built, so a single
//              pass suffices.
// Time: O(n log n)  Space: O(n) for the output
// Brute force: repeatedly merge any overlapping pair until nothing changes: O(n^2) or worse.
inline std::vector<std::vector<int>> merge(std::vector<std::vector<int>> intervals) {
    std::sort(intervals.begin(), intervals.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) { return a[0] < b[0]; });
    std::vector<std::vector<int>> out;
    for (const auto& iv : intervals) {
        if (!out.empty() && iv[0] <= out.back()[1])
            out.back()[1] = std::max(out.back()[1], iv[1]);
        else
            out.push_back(iv);
    }
    return out;
}
