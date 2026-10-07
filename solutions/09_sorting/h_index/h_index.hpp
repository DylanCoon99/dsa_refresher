#pragma once
#include <algorithm>
#include <vector>

// Approach: counting sort. Bucket papers by min(citations, n), then sweep h from n down to 0 keeping
//           a running count of papers with at least h citations; the first h with count >= h wins.
// Key insight: the answer never exceeds n, so citation counts above n can be capped.
// Time: O(n)  Space: O(n)
// Brute force: for each h from n down, count papers with >= h citations, O(n^2); or sort in O(n log n).
inline int hIndex(const std::vector<int>& citations) {
    const int n = static_cast<int>(citations.size());
    std::vector<int> bucket(static_cast<std::size_t>(n) + 1, 0);
    for (int c : citations) ++bucket[static_cast<std::size_t>(std::min(c, n))];
    int papers = 0;
    for (int h = n; h >= 1; --h) {
        papers += bucket[static_cast<std::size_t>(h)];
        if (papers >= h) return h;
    }
    return 0;
}
