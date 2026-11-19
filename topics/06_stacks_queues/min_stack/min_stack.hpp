#pragma once
#include <vector>

// A stack of int that also reports its minimum. All operations O(1).
// pop/top/getMin are never called on an empty stack.
class MinStack {
public:
    void push(int val) {
        // TODO: implement
        data_.push_back(val);

        if (min_.empty()) {
            min_.push_back(val);
        } else {
            if (min_.back() > val) {
                min_.push_back(val);
            } else {
                min_.push_back(min_.back());
            }
        }
    }
    void pop() {
        // TODO: implement
        data_.pop_back();
        min_.pop_back();
    }
    int top() const {
        // TODO: implement
        return data_.back();
    }
    int getMin() const {
        // TODO: implement
        return min_.back();
    }

private:
    std::vector<int> data_;
    std::vector<int> min_; // holds the min at each element of the stack, when an element of the stack is popped, pop from here as well

};
