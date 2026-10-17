#pragma once
#include <cstddef>
#include <list>
#include <optional>
#include <functional>
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
        _size = initial_buckets;
        _hash_map = std::vector<std::list<std::pair<std::string, int>>>(_size);
        _current_size = 0;
    }

    // Insert, or overwrite the value if the key exists.
    void put(const std::string& key, int value) {
        // TODO: implement
        std::size_t hash_value = _string_hasher(key);
        int list_num = hash_value % _size;

        // if key already exists -> update the value
        std::list<std::pair<std::string, int>>& list = _hash_map[list_num];

        for (auto& pair : list) {
            if (pair.first == key) {
                // the key exists; update the value
                pair.second = value;
                return;
            }
        }

        // otherwise -> insert the key value pair
        list.emplace_back(key, value);
        ++_current_size;

        // if size() > .75 * bucketCount -> call resize()
        if (size() > .75 * bucketCount()) {
            _resize();
        }
    }

    // The value for key, or std::nullopt if absent.
    std::optional<int> get(const std::string& key) const {
        // TODO: implement
        // hash the key to get what list it is located at
        std::size_t hash_value = _string_hasher(key);
        int list_num = hash_value % _size;

        std::optional<int> result = std::nullopt;
    
        for (auto pair : _hash_map[list_num]) {
            if (pair.first == key) {
                return std::make_optional(pair.second);
            }
        }
        return std::nullopt;
    }

    // Remove key. Return true if it was present.
    bool erase(const std::string& key) {
        // TODO: implement
        std::size_t hash_value = _string_hasher(key);
        int list_num = hash_value % _size;
    
        auto result = _hash_map[list_num].remove_if(
            [&key](std::pair<std::string, int> pair) { 
                return pair.first == key;
            });

        if (result == 0) {
            return false;
        } else {
            --_current_size;
            return true;
        }
 
    }

    // Number of distinct keys stored.
    std::size_t size() const {
        // TODO: implement
        return _current_size;
    }

    // Current number of buckets.
    std::size_t bucketCount() const {
        return _size;
    }



    // Add your own private members here.
    private:
        std::vector<std::list<std::pair<std::string,int>>> _hash_map;
        std::size_t _size;
        std::size_t _current_size;
        std::hash<std::string> _string_hasher;

        void _resize() {
            // doubles the current size of the hash map; only call this
            // when size() > .75 * bucketCount

            // double the size
            _size *= 2;
            std::vector<std::list<std::pair<std::string,int>>> new_hash_map(_size);

            // rehash every element
            for (auto list : _hash_map) {
                for (const auto& [key, value] : list) {
                    // hash the key; insert into new map
                    std::size_t hash_value = _string_hasher(key);
                    new_hash_map[hash_value % _size].emplace_back(key, value);

                }
            }

            // move ownership of the new hash map to _hash_map; deletes anything previously in _hash_map
            _hash_map = std::move(new_hash_map);

        }
};
