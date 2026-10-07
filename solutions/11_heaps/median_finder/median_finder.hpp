#pragma once
#include <functional>
#include <queue>
#include <vector>

// Approach: keep the smaller half in a max-heap and the larger half in a min-heap, with the max-heap holding the extra element when the count is odd.
// Key insight: the median only depends on the two elements at the boundary between the halves, and each heap exposes exactly its boundary element.
// Time: O(log n) addNum, O(1) findMedian  Space: O(n)
// Brute force: keep a vector and sort it (or insert in order) on every query, O(n log n) per findMedian.
class MedianFinder {
public:
    void addNum(int num) {
        if (lo_.empty() || num <= lo_.top()) {
            lo_.push(num);
        } else {
            hi_.push(num);
        }
        if (lo_.size() > hi_.size() + 1) {
            hi_.push(lo_.top());
            lo_.pop();
        } else if (hi_.size() > lo_.size()) {
            lo_.push(hi_.top());
            hi_.pop();
        }
    }
    double findMedian() const {
        if (lo_.size() > hi_.size()) return static_cast<double>(lo_.top());
        return (static_cast<double>(lo_.top()) + static_cast<double>(hi_.top())) / 2.0;
    }

private:
    std::priority_queue<int> lo_;                                      // smaller half (max-heap)
    std::priority_queue<int, std::vector<int>, std::greater<>> hi_;    // larger half (min-heap)
};
