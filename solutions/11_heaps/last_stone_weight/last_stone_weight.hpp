#pragma once
#include <queue>
#include <vector>

// Approach: keep the stones in a max-heap; repeatedly pop the two heaviest and push back their difference if non-zero.
// Key insight: each round only touches the current maximum, which is exactly what a heap offers.
// Time: O(n log n)  Space: O(n)
// Brute force: re-sort the stones every round and take the last two, O(n^2 log n).
inline int lastStoneWeight(const std::vector<int>& stones) {
    std::priority_queue<int> heap(stones.begin(), stones.end());
    while (heap.size() > 1) {
        int y = heap.top();
        heap.pop();
        int x = heap.top();
        heap.pop();
        if (y != x) heap.push(y - x);
    }
    return heap.empty() ? 0 : heap.top();
}
