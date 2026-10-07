#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

// Approach: push onto `in_`; when `out_` is empty, pour all of `in_` into it (reversing the
//           order) so the oldest element is on top. pop/peek read from `out_`.
// Key insight: each element is moved at most once from in_ to out_, so n operations cost O(n) total.
// Time: O(1) amortized per operation  Space: O(n)
// Brute force: on every push/pop move all elements between the stacks, O(n) per operation.
class TwoStackQueue {
public:
    void push(int x) { in_.push_back(x); }
    int pop() {
        refill();
        int v = out_.back();
        out_.pop_back();
        return v;
    }
    int peek() {
        refill();
        return out_.back();
    }
    bool empty() const { return in_.empty() && out_.empty(); }
    std::size_t size() const { return in_.size() + out_.size(); }

private:
    void refill() {
        if (out_.empty()) {
            if (in_.empty()) throw std::out_of_range("queue is empty");
            while (!in_.empty()) {
                out_.push_back(in_.back());
                in_.pop_back();
            }
        }
    }
    std::vector<int> in_, out_;
};
