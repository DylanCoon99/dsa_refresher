#pragma once
#include <algorithm>
#include <vector>

// Approach: pointers at both ends; record the area, then move the pointer at the shorter wall inward.
// Key insight: the shorter wall caps the height, so keeping it while shrinking the width can only lose area; discarding it is safe.
// Time: O(n)  Space: O(1)
// Brute force: evaluate every pair, O(n^2).
inline int maxArea(const std::vector<int>& height) {
    int i = 0, j = static_cast<int>(height.size()) - 1, best = 0;
    while (i < j) {
        best = std::max(best, (j - i) * std::min(height[i], height[j]));
        if (height[i] < height[j]) ++i; else --j;
    }
    return best;
}
