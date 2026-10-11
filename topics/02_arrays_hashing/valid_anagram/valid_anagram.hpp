#pragma once
#include <string>
#include <unordered_map>

// Return true if t is a rearrangement of the letters of s.
inline bool isAnagram(const std::string& s, const std::string& t) {
    // TODO: implement

    // maps letter to frequency for each word
    std::unordered_map<char, int> s_map;
    std::unordered_map<char, int> t_map;

    for (char c : s) {
        s_map[c] += 1;
    }

    for (char c : t) {
        t_map[c] += 1;
    }

    return s_map == t_map;

}
