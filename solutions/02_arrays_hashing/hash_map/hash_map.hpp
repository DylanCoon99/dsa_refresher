#pragma once
#include <cstddef>
#include <functional>
#include <list>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Approach: vector of chains (std::list) indexed by hash(key) % buckets; double and rehash
//           whenever an insert pushes size above 0.75 * buckets.
// Key insight: resizing keeps chains short (average length <= 0.75), so each operation is O(1) amortized.
// Time: O(1) expected per op, amortized  Space: O(n + buckets)
// Brute force: a table that never resizes (or one flat list) has O(n) chains, O(n) per operation.
class HashMap {
public:
    explicit HashMap(std::size_t initial_buckets = 8)
        : buckets_(initial_buckets == 0 ? 1 : initial_buckets) {}

    void put(const std::string& key, int value) {
        auto& chain = buckets_[indexFor(key, buckets_.size())];
        for (auto& kv : chain) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        chain.emplace_back(key, value);
        ++size_;
        if (static_cast<double>(size_) > 0.75 * static_cast<double>(buckets_.size())) rehash(buckets_.size() * 2);
    }

    std::optional<int> get(const std::string& key) const {
        for (const auto& kv : buckets_[indexFor(key, buckets_.size())])
            if (kv.first == key) return kv.second;
        return std::nullopt;
    }

    bool erase(const std::string& key) {
        auto& chain = buckets_[indexFor(key, buckets_.size())];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                --size_;
                return true;
            }
        }
        return false;
    }

    std::size_t size() const { return size_; }
    std::size_t bucketCount() const { return buckets_.size(); }

private:
    using Chain = std::list<std::pair<std::string, int>>;
    std::vector<Chain> buckets_;
    std::size_t size_ = 0;

    static std::size_t indexFor(const std::string& key, std::size_t n) { return std::hash<std::string>{}(key) % n; }

    void rehash(std::size_t new_count) {
        std::vector<Chain> next(new_count);
        for (auto& chain : buckets_) {
            while (!chain.empty()) {  // splice relinks the node: no allocation, no copy
                auto& dst = next[indexFor(chain.front().first, new_count)];
                dst.splice(dst.end(), chain, chain.begin());
            }
        }
        buckets_ = std::move(next);
    }
};
