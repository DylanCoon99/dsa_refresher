#pragma once
#include <cstddef>
#include <list>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Hash map from string to int using separate chaining.
// Doubles the bucket count (and rehashes) when size() > 0.75 * bucketCount() after an insert.
// std::hash<std::string> is allowed; std::unordered_map is not.
class HashMap {
public:
    explicit HashMap(std::size_t initial_buckets = 8) {
        // TODO: implement
    }

    // Insert, or overwrite the value if the key exists.
    void put(const std::string& key, int value) {
        // TODO: implement
    }

    // The value for key, or std::nullopt if absent.
    std::optional<int> get(const std::string& key) const {
        // TODO: implement
        return std::nullopt;
    }

    // Remove key. Return true if it was present.
    bool erase(const std::string& key) {
        // TODO: implement
        return false;
    }

    // Number of distinct keys stored.
    std::size_t size() const {
        // TODO: implement
        return 0;
    }

    // Current number of buckets.
    std::size_t bucketCount() const {
        // TODO: implement
        return 0;
    }

    // Add your own private members here.
};
