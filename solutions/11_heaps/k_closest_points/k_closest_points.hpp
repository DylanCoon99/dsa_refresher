#pragma once
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

// Approach: keep a max-heap of the k closest points so far (keyed on squared distance); evict the top when a closer point arrives.
// Key insight: the farthest of the current k candidates is the only one that can be replaced, and the max-heap exposes it.
// Time: O(n log k)  Space: O(k)
// Brute force: sort all points by squared distance and take the first k, O(n log n).
inline std::vector<std::vector<int>> kClosest(const std::vector<std::vector<int>>& points, int k) {
    std::priority_queue<std::pair<int, std::size_t>> heap;  // (squared distance, index)
    for (std::size_t i = 0; i < points.size(); ++i) {
        int d = points[i][0] * points[i][0] + points[i][1] * points[i][1];
        if (heap.size() < static_cast<std::size_t>(k)) {
            heap.push({d, i});
        } else if (d < heap.top().first) {
            heap.pop();
            heap.push({d, i});
        }
    }
    std::vector<std::vector<int>> result;
    while (!heap.empty()) {
        result.push_back(points[heap.top().second]);
        heap.pop();
    }
    return result;
}
