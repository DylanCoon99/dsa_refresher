#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

// A FIFO queue built from two std::vector<int> used strictly as stacks
// (push_back / pop_back / back only). pop() and peek() on an empty queue
// throw std::out_of_range. Every operation must be amortized O(1).
class TwoStackQueue {
public:
    void push(int x) {
        // TODO: implement
    }
    int pop() {
        // TODO: implement
        return 0;
    }
    int peek() {
        // TODO: implement
        return 0;
    }
    bool empty() const {
        // TODO: implement
        return false;
    }
    std::size_t size() const {
        // TODO: implement
        return 0;
    }

private:
    std::vector<int> in_, out_;
};
