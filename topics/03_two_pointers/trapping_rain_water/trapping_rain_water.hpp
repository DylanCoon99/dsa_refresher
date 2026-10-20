#pragma once
#include <vector>
#include <algorithm>

// Return the total units of rain water trapped between the bars.
inline int trap(const std::vector<int>& height) {
    // TODO: implement

    int i = 0;
    int j = height.size() - 1;

    int total_water = 0;

    // tallest values are initialized at zero; these are not indices
    int tallest_left = 0;
    int tallest_right = 0;

    while (i < j) {

        if (height[i] > tallest_left) {
            tallest_left = height[i];
        }

        if (height[j] > tallest_right) {
            tallest_right = height[j];
        }

        if (tallest_left <= tallest_right) {
            total_water += (tallest_left - height[i]);
            ++i;
        } else {
            total_water += (tallest_right - height[j]);
            --j;
        }
        
    }
        


    return total_water;
}
