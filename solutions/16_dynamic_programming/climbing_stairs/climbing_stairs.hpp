#pragma once

// Approach: ways[i] = ways[i-1] + ways[i-2] with ways[0] = ways[1] = 1, keeping only two values.
// Key insight: the last move was 1 or 2 steps, so the count is the sum of the two smaller counts.
// Time: O(n)  Space: O(1)
// Brute force: recurse on n-1 and n-2 without caching: O(phi^n).
inline int climbStairs(int n) {
    int prev = 1, cur = 1;  // ways to reach step 0 and step 1
    for (int i = 2; i <= n; ++i) {
        int next = prev + cur;
        prev = cur;
        cur = next;
    }
    return cur;
}
