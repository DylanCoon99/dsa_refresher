#pragma once
#include <algorithm>
#include <vector>

// Approach: BFS by levels without a queue. 'end' is the last index reachable with the current number
//           of jumps; while scanning up to it track the farthest reach 'far'; at 'end' take one more jump.
// Key insight: indices reachable with k jumps form a prefix, so the next level is just the farthest
//              reach seen within the current one.
// Time: O(n)  Space: O(1)
// Brute force: dp[j] = 1 + min dp[i] over all i that reach j (or BFS over every jump): O(n * max(nums)).
inline int jump(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    int jumps = 0, end = 0, far = 0;
    for (int i = 0; i + 1 < n; ++i) {
        far = std::max(far, i + nums[i]);
        if (i == end) {
            ++jumps;
            end = far;
        }
    }
    return jumps;
}
