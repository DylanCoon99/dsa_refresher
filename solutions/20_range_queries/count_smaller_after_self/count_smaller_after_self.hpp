#pragma once
#include <algorithm>
#include <vector>

// Approach: compress values to ranks, sweep right to left, and use a Fenwick tree of counts to ask
//           "how many already-seen values have a smaller rank" before inserting the current one.
// Key insight: sweeping from the right turns "smaller elements after me" into a prefix count over what is already inserted.
// Time: O(n log n)  Space: O(n)
// Brute force: for each i, scan everything after it, O(n^2).
inline std::vector<int> countSmaller(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    std::vector<int> sorted(nums);
    std::sort(sorted.begin(), sorted.end());
    sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
    const int m = static_cast<int>(sorted.size());
    std::vector<int> tree(m + 1, 0);
    std::vector<int> counts(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        int rank = static_cast<int>(std::lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin());
        int c = 0;
        for (int j = rank; j > 0; j -= j & -j) c += tree[j];  // ranks 0..rank-1
        counts[i] = c;
        for (int j = rank + 1; j <= m; j += j & -j) ++tree[j];
    }
    return counts;
}
