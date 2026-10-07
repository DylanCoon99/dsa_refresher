#pragma once
#include <list>
#include <unordered_map>

// A cache holding at most `capacity` entries; evicts the least recently used one.
// get: value or -1 if missing; a hit makes the key most recent.
// put: insert or update, makes the key most recent; evicts the LRU entry only when
//      inserting a NEW key into a full cache. Both O(1).
class LRUCache {
public:
    explicit LRUCache(int capacity) {
        // TODO: implement
    }
    int get(int key) {
        // TODO: implement
        return -1;
    }
    void put(int key, int value) {
        // TODO: implement
    }
};
