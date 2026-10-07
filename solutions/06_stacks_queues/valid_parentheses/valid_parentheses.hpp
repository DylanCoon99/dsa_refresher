#pragma once
#include <string>
#include <vector>

// Approach: push each opening bracket; each closing bracket must match the stack top. Valid iff nothing is left.
// Key insight: the bracket that must be closed next is always the most recently opened one, which is LIFO.
// Time: O(n)  Space: O(n)
// Brute force: repeatedly erase adjacent "()", "[]", "{}" pairs until none remain, O(n^2).
inline bool isValid(const std::string& s) {
    std::vector<char> open;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            open.push_back(c);
        } else {
            if (open.empty()) return false;
            char o = open.back();
            open.pop_back();
            if ((c == ')' && o != '(') || (c == ']' && o != '[') || (c == '}' && o != '{')) return false;
        }
    }
    return open.empty();
}
