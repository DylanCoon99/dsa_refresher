#pragma once
#include <vector>

// result[i] = smallest k > 0 with temperatures[i + k] > temperatures[i], or 0 if none.
// Equal temperatures are not warmer.
inline std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) {
    // TODO: implement
    std::vector<int> result(temperatures.size(), 0);
    std::vector<int> stack;

    for (int i = 0; i < static_cast<int>(temperatures.size()); ++i) {
        // check if this day resolves any waiting days
        while (stack.size() > 0 && temperatures[stack.back()] < temperatures[i]) {
            int idx = stack.back();
            stack.pop_back();
            result[idx] = i - idx;
        }
        stack.push_back(i);
        
    }

    return result;
}
