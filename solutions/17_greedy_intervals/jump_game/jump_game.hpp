#pragma once
#include <algorithm>
#include <vector>

// Approach: scan left to right keeping the farthest index reachable so far; if the scan gets to an
//           index beyond it, stop with false; otherwise extend it with i + nums[i].
// Key insight: reachable indices always form a prefix [0, far], so one number describes them all.
// Time: O(n)  Space: O(1)
// Brute force: BFS/DFS trying every jump length from every reachable index: O(n * max(nums)).
inline bool canJump(const std::vector<int>& nums) {
    const int n = static_cast<int>(nums.size());
    int far = 0;
    for (int i = 0; i < n; ++i) {
        if (i > far) return false;
        far = std::max(far, i + nums[i]);
    }
    return true;
}
