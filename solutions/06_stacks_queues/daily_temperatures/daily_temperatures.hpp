#pragma once
#include <vector>

// Approach: keep a stack of indices whose answer is still unknown (temperatures non-increasing
//           from bottom to top). A new day pops every colder day and fills in their answers.
// Key insight: each day is pushed and popped at most once, so the monotonic stack is O(n) total.
// Time: O(n)  Space: O(n)
// Brute force: for each day scan forward for the first warmer day, O(n^2).
inline std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) {
    const int n = static_cast<int>(temperatures.size());
    std::vector<int> ans(n, 0), st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && temperatures[st.back()] < temperatures[i]) {
            ans[st.back()] = i - st.back();
            st.pop_back();
        }
        st.push_back(i);
    }
    return ans;
}
