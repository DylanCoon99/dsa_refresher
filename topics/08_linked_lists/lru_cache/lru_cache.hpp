#pragma once
#include <list>
#include <utility>
#include <unordered_map>

// A cache holding at most `capacity` entries; evicts the least recently used one.
// get: value or -1 if missing; a hit makes the key most recent.
// put: insert or update, makes the key most recent; evicts the LRU entry only when
//      inserting a NEW key into a full cache. Both O(1).
class LRUCache {
public:
    explicit LRUCache(int capacity) : _capacity(capacity) { }

    int get(int key) {
        // TODO: implement
        if (_cache.contains(key)) {
            // need to have a way to mark the key most recent
            // find location of the key in list
            auto it = _cache[key].second;
            // update the lru list; mark the key most recently used
            _lru_list.erase(it);
            _lru_list.push_back(key);
            _cache[key].second = std::prev(_lru_list.end());

            return _cache[key].first;
        }
        return -1;
    }
    void put(int key, int value) {
        // TODO: implement

        if (_cache.contains(key)) {
            // update it's value
            auto it = _cache[key].second;
            // update the lru list; mark the key most recently used
            _lru_list.erase(it);
            _lru_list.push_back(key);
            _cache[key] = std::make_pair(value, std::prev(_lru_list.end()));
        }
        else {
            if (_capacity == static_cast<int>(_lru_list.size())) {
                // evict lru
                int lru_key = _lru_list.front();

                _lru_list.pop_front(); // pop from the list;
                _cache.erase(lru_key);     // erase from the map
            }
            _lru_list.push_back(key);
            _cache[key] = std::make_pair(value, std::prev(_lru_list.end()));
        }

    }

private:
    int _capacity;
    std::unordered_map<int, std::pair<int, std::list<int>::iterator>> _cache; // maps key to std::pair<value, location_of_key in list>
    std::list<int> _lru_list; // least recently used entry should be at the front of the list

};
