#pragma once
#include <deque>
#include <vector>

// Approach: keep a deque of indices whose values decrease from front to back; pop smaller values off the
//           back as a new element arrives, pop the front when it leaves the window, and read the max at the front.
// Key insight: an element that is both older and smaller than a newcomer can never be a window maximum again.
// Time: O(n)  Space: O(k)
// Brute force: scan each window for its maximum, O(n * k).
inline std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
    const int n = static_cast<int>(nums.size());
    std::vector<int> out;
    std::deque<int> dq;
    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) out.push_back(nums[dq.front()]);
    }
    return out;
}
