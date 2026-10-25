#pragma once
#include <string>
#include <array>
#include <algorithm>

// Return the length of the longest substring that can be turned into one repeated letter
// with at most k character changes.
inline int characterReplacement(const std::string& s, int k) {
    // TODO: implement

    if (s.size() == 1) return 1;

    int i = 0;
    int j = 1;

    // variable size window
    // count the most frequent letter in the window
    // need a frequency counter for each letter in the window
    // total_window_size - most_frequent_letter_count = total_number_replacements
    // if total_number_replacements is at most k, window is valid
    // if not, shrink the window until replacements is equal to k

    std::array<int, 26> freq{0}; // access each letter with freq[c - 'A']
    int max_length = 1;

    ++freq[s[i] - 'A'];

    while (j < static_cast<int>(s.size())) {
        // update the counts in the map
        char c = s[j];
        ++freq[c - 'A'];
        int max_val = *std::ranges::max_element(freq);

        while ((j - i + 1) - max_val > k) {
            // while in this loop, the window is invalid
            --freq[s[i] - 'A'];
            ++i;
            max_val = *std::ranges::max_element(freq);
        }
        max_length = std::max(j - i + 1, max_length);
        ++j;

    }

    return max_length;
}
