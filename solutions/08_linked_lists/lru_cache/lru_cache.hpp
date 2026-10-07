#pragma once
#include <list>
#include <unordered_map>
#include <utility>

// Approach: a std::list of (key, value) ordered by recency (front = newest) plus a hash map key -> list iterator.
// Key insight: the map finds the entry and splice() moves it to the front, both in O(1), because list iterators stay valid.
// Time: O(1) per operation  Space: O(capacity)
// Brute force: scan a recency-ordered list on every operation, O(capacity) each.
class LRUCache {
public:
    explicit LRUCache(int capacity) : capacity_(static_cast<std::size_t>(capacity)) {}
    int get(int key) {
        auto it = index_.find(key);
        if (it == index_.end()) return -1;
        items_.splice(items_.begin(), items_, it->second);
        return it->second->second;
    }
    void put(int key, int value) {
        auto it = index_.find(key);
        if (it != index_.end()) {
            it->second->second = value;
            items_.splice(items_.begin(), items_, it->second);
            return;
        }
        if (items_.size() == capacity_) {
            index_.erase(items_.back().first);
            items_.pop_back();
        }
        items_.emplace_front(key, value);
        index_[key] = items_.begin();
    }

private:
    std::size_t capacity_;
    std::list<std::pair<int, int>> items_;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> index_;
};
