#pragma once
#include <algorithm>
#include <string>
#include <vector>

// Approach: record each letter's last index; scan, growing the current piece's end to the farthest last
//           index of any letter seen; when the scan reaches that end, cut the piece.
// Key insight: each letter forces the piece to extend to its last occurrence, and cutting at the first
//              position where nothing forces it further gives the smallest (hence most) pieces.
// Time: O(n)  Space: O(1)
// Brute force: for every possible cut position check that no letter appears on both sides: O(26 n^2) or O(n^2).
inline std::vector<int> partitionLabels(const std::string& s) {
    int last[26] = {0};
    const int n = static_cast<int>(s.size());
    for (int i = 0; i < n; ++i) last[s[i] - 'a'] = i;
    std::vector<int> out;
    int start = 0, end = 0;
    for (int i = 0; i < n; ++i) {
        end = std::max(end, last[s[i] - 'a']);
        if (i == end) {
            out.push_back(end - start + 1);
            start = i + 1;
        }
    }
    return out;
}
