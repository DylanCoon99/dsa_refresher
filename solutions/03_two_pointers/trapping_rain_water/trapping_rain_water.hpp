#pragma once
#include <algorithm>
#include <vector>

// Approach: pointers at both ends with a running maximum for each side; always advance the side whose maximum is smaller
//           and add (that side's max - current height).
// Key insight: the water above a bar is fixed by the smaller of the two side maxima, so the side with the smaller max is already decided.
// Time: O(n)  Space: O(1)
// Brute force: for each bar scan left and right for the maxima, O(n^2); or precompute prefix/suffix max arrays, O(n) space.
inline int trap(const std::vector<int>& height) {
    int i = 0, j = static_cast<int>(height.size()) - 1;
    int left_max = 0, right_max = 0, total = 0;
    while (i < j) {
        if (height[i] < height[j]) {
            left_max = std::max(left_max, height[i]);
            total += left_max - height[i];
            ++i;
        } else {
            right_max = std::max(right_max, height[j]);
            total += right_max - height[j];
            --j;
        }
    }
    return total;
}
