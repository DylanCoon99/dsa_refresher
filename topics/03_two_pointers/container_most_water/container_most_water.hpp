#pragma once
#include <vector>
#include <algorithm>

// Return the maximum of (j - i) * min(height[i], height[j]) over all pairs i < j.
inline int maxArea(const std::vector<int>& height) {
    // TODO: implement
    int max_water = 0;

    int i = 0;
    int j = height.size() - 1;

    while (i < j) {
        // compute the area
        int area = (j - i) * std::min(height[i], height[j]);
        // if the area is greater than max_water; update the max_water
        if (area > max_water) {
            max_water = area;
        }
        if (height[i] > height[j]) {
            --j;
        } else {
            ++i;
        }
    }

    return max_water;
}
