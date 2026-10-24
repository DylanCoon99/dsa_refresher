#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include <unordered_set>

// Return the length of the longest substring of s with no repeated character.
inline int lengthOfLongestSubstring(const std::string& s) {
    // TODO: implement

    // variable length window
    if (s.size() <= 1) return s.size();

    int i = 0;
    int j = 1;
    int max_length = 1;
    int current_length = max_length;

    std::unordered_set<unsigned char> freq;

    freq.insert(s[i]);

    while (j < static_cast<int>(s.size())) {
        
        char c = s[j];
        // if the char at j is not in the current substring -> increment max and j ptr; update the map
        if (!freq.contains(c)) {
            freq.insert(c);
            ++j;
        }
        // if the char at j is in the current substring -> i = j; set current length to 0; reset map for every other letter
        else {
            while (freq.contains(c)) {
                freq.erase(s[i]);
                ++i;
            }
            ++j;
            freq.insert(c);
        }

        max_length = ((j - i) > max_length) ? (j - i) : max_length; 
    }

    return max_length;
}
