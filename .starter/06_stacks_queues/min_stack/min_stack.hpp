#pragma once
#include <vector>

// A stack of int that also reports its minimum. All operations O(1).
// pop/top/getMin are never called on an empty stack.
class MinStack {
public:
    void push(int val) {
        // TODO: implement
    }
    void pop() {
        // TODO: implement
    }
    int top() const {
        // TODO: implement
        return 0;
    }
    int getMin() const {
        // TODO: implement
        return 0;
    }

private:
    std::vector<int> data_;
};
