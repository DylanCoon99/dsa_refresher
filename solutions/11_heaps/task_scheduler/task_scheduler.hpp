#pragma once
#include <algorithm>
#include <array>
#include <vector>

// Approach: the most frequent type forces (maxCount - 1) frames of length n + 1 followed by one last slot per type tied for max;
// every other task fits in the gaps, and if there are more tasks than that the schedule has no idle time at all.
// Key insight: only the most frequent letter(s) determine the idle time; the answer is max(total tasks, that frame count).
// Time: O(t)  Space: O(1)
// Brute force: simulate time unit by unit, always running the available type with the most tasks left (O(t * 26)).
inline int leastInterval(const std::vector<char>& tasks, int n) {
    std::array<int, 26> count{};
    for (char c : tasks) ++count[static_cast<std::size_t>(c - 'A')];
    int max_count = *std::max_element(count.begin(), count.end());
    int num_max = static_cast<int>(std::count(count.begin(), count.end(), max_count));
    int frames = (max_count - 1) * (n + 1) + num_max;
    return std::max(static_cast<int>(tasks.size()), frames);
}
