#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

// An array-backed binary min-heap of int. Do not use std::priority_queue or std::make_heap.
// The vector constructor must heapify in O(n) (bottom-up sift-down).
// pop() and top() on an empty heap throw std::out_of_range.
class MinHeap {
public:
    MinHeap() {}
    explicit MinHeap(std::vector<int> values) {
        // TODO: implement
    }
    void push(int v) {
        // TODO: implement
    }
    int pop() {
        // TODO: implement
        return 0;
    }
    int top() const {
        // TODO: implement
        return 0;
    }
    std::size_t size() const {
        // TODO: implement
        return 0;
    }
    bool empty() const {
        // TODO: implement
        return true;
    }

private:
    std::vector<int> data_;
};
