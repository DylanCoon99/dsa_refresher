#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

// Approach: store the heap in a vector (children of i at 2i+1 and 2i+2); push sifts up, pop moves the
// last element to the root and sifts down; the vector constructor sifts down from the last parent to the root.
// Key insight: in bottom-up heapify most nodes sit near the leaves and sift down only a step or two, so the total is O(n).
// Time: O(log n) push/pop, O(1) top, O(n) build  Space: O(n)
// Brute force: keep a sorted vector and insert in order, O(n) per push (O(n^2) for n pushes).
class MinHeap {
public:
    MinHeap() {}
    explicit MinHeap(std::vector<int> values) : data_(std::move(values)) {
        for (std::size_t i = data_.size() / 2; i-- > 0;) sift_down(i);
    }
    void push(int v) {
        data_.push_back(v);
        std::size_t i = data_.size() - 1;
        while (i > 0) {
            std::size_t p = (i - 1) / 2;
            if (data_[p] <= data_[i]) break;
            std::swap(data_[p], data_[i]);
            i = p;
        }
    }
    int pop() {
        if (data_.empty()) throw std::out_of_range("pop on empty heap");
        int result = data_[0];
        data_[0] = data_.back();
        data_.pop_back();
        if (!data_.empty()) sift_down(0);
        return result;
    }
    int top() const {
        if (data_.empty()) throw std::out_of_range("top on empty heap");
        return data_[0];
    }
    std::size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }

private:
    void sift_down(std::size_t i) {
        const std::size_t n = data_.size();
        for (;;) {
            std::size_t smallest = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && data_[l] < data_[smallest]) smallest = l;
            if (r < n && data_[r] < data_[smallest]) smallest = r;
            if (smallest == i) return;
            std::swap(data_[i], data_[smallest]);
            i = smallest;
        }
    }
    std::vector<int> data_;
};
