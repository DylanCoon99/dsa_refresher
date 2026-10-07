#pragma once
#include <string>

// Per key, set() timestamps are strictly increasing.
// get() returns the value with the largest timestamp <= the given one, or "" if none.
class TimeMap {
public:
    void set(const std::string& key, const std::string& value, int timestamp) {
        // TODO: implement
    }
    std::string get(const std::string& key, int timestamp) const {
        // TODO: implement
        return "";
    }
};
