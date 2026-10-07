#pragma once
#include <algorithm>
#include <vector>

// Approach: sort by right end; shoot at the first balloon's right end; every balloon whose start is
//           <= that position is burst too; the first one that starts after it needs a new arrow.
// Key insight: shooting at the earliest right end bursts the most balloons among those that must be
//              burst by the first arrow, and moving the arrow left would only lose some (exchange argument).
// Time: O(n log n)  Space: O(1) extra
// Brute force: try every subset of candidate positions (the right ends): O(2^n).
// Note: the comparator uses '<', never a subtraction, which overflows for INT_MIN / INT_MAX coordinates.
inline int findMinArrowShots(std::vector<std::vector<int>> points) {
    if (points.empty()) return 0;
    std::sort(points.begin(), points.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) { return a[1] < b[1]; });
    int arrows = 1;
    int pos = points[0][1];
    for (const auto& p : points) {
        if (p[0] > pos) {
            ++arrows;
            pos = p[1];
        }
    }
    return arrows;
}
