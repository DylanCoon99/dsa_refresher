#pragma once
#include <cctype>
#include <string>

// Approach: two indices from the ends; skip non-alphanumerics, compare lowercase, move inward.
// Key insight: skipping junk in place avoids building a filtered copy.
// Time: O(n)  Space: O(1)
// Brute force: build the cleaned lowercase string, reverse it, and compare: O(n) time, O(n) space.
inline bool isPalindrome(const std::string& s) {
    int i = 0, j = static_cast<int>(s.size()) - 1;
    while (i < j) {
        if (!std::isalnum(static_cast<unsigned char>(s[i]))) { ++i; continue; }
        if (!std::isalnum(static_cast<unsigned char>(s[j]))) { --j; continue; }
        if (std::tolower(static_cast<unsigned char>(s[i])) != std::tolower(static_cast<unsigned char>(s[j]))) return false;
        ++i;
        --j;
    }
    return true;
}
