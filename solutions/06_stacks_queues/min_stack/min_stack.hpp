#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// Approach: store each value together with the minimum of the stack up to and including it.
// Key insight: the minimum of what remains after a pop was already known when that element was pushed.
// Time: O(1) per operation  Space: O(n)
// Brute force: keep a plain stack and scan it for the minimum on every getMin, O(n) per call.
class MinStack {
public:
    void push(int val) {
        int m = data_.empty() ? val : std::min(val, data_.back().second);
        data_.emplace_back(val, m);
    }
    void pop() { data_.pop_back(); }
    int top() const { return data_.back().first; }
    int getMin() const { return data_.back().second; }

private:
    std::vector<std::pair<int, int>> data_;
};
