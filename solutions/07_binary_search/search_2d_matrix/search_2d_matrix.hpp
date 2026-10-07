#pragma once
#include <vector>

// Approach: the grid read row by row is one sorted sequence; binary-search positions 0..m*n-1
//           and map a position p to (p / n, p % n).
// Key insight: the "first > previous last" rule makes the whole matrix a single sorted array.
// Time: O(log(m*n))  Space: O(1)
// Brute force: scan all m*n cells, O(m*n).
inline bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    const long long cols = static_cast<long long>(matrix[0].size());
    long long lo = 0, hi = static_cast<long long>(matrix.size()) * cols - 1;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        int v = matrix[static_cast<std::size_t>(mid / cols)][static_cast<std::size_t>(mid % cols)];
        if (v == target) return true;
        if (v < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}
