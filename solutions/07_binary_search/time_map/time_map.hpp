#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// Approach: per key keep a vector of (timestamp, value) in insertion order, which is already sorted
//           by timestamp; get() binary-searches for the first timestamp > t and steps back one.
// Key insight: strictly increasing timestamps mean no sorted structure is needed, only upper-bound search.
// Time: O(1) set, O(log k) get  Space: O(total entries)
// Brute force: scan the key's entries from the end for the first timestamp <= t, O(k) per get.
class TimeMap {
public:
    void set(const std::string& key, const std::string& value, int timestamp) {
        data_[key].emplace_back(timestamp, value);
    }
    std::string get(const std::string& key, int timestamp) const {
        auto it = data_.find(key);
        if (it == data_.end()) return "";
        const auto& v = it->second;
        std::size_t lo = 0, hi = v.size();  // first index with v[i].first > timestamp
        while (lo < hi) {
            std::size_t mid = lo + (hi - lo) / 2;
            if (v[mid].first <= timestamp) lo = mid + 1;
            else hi = mid;
        }
        return lo == 0 ? "" : v[lo - 1].second;
    }

private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> data_;
};
