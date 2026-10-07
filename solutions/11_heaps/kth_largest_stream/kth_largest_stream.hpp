#pragma once
#include <cstddef>
#include <functional>
#include <queue>
#include <vector>

// Approach: keep a min-heap holding only the k largest values seen; its top is the k-th largest.
// Key insight: anything smaller than the current k-th largest can never become the answer again, so drop it.
// Time: O(log k) per add  Space: O(k)
// Brute force: append to a vector and sort (or nth_element) on every add, O(n log n) per call.
class KthLargest {
public:
    KthLargest(int k, const std::vector<int>& nums) : k_(static_cast<std::size_t>(k)) {
        for (int v : nums) add(v);
    }
    int add(int val) {
        if (heap_.size() < k_) {
            heap_.push(val);
        } else if (val > heap_.top()) {
            heap_.pop();
            heap_.push(val);
        }
        return heap_.top();
    }

private:
    std::size_t k_;
    std::priority_queue<int, std::vector<int>, std::greater<>> heap_;
};
