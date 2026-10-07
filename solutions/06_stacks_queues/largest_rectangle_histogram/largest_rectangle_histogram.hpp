#pragma once
#include <algorithm>
#include <vector>

// Approach: keep a stack of bar indices with strictly increasing heights. When a shorter bar (or a
//           sentinel zero at the end) arrives, pop each taller bar and score the rectangle it
//           spans: width runs from the new stack top + 1 to the current index - 1.
// Key insight: a bar's rectangle is bounded by the nearest shorter bar on each side, and the
//              monotonic stack finds both while each bar is pushed and popped once.
// Time: O(n)  Space: O(n)
// Brute force: for every pair l <= r take (r - l + 1) * min(heights[l..r]), O(n^2).
inline int largestRectangleArea(const std::vector<int>& heights) {
    const int n = static_cast<int>(heights.size());
    std::vector<int> st;
    int best = 0;
    for (int i = 0; i <= n; ++i) {
        int h = (i == n) ? 0 : heights[i];
        while (!st.empty() && heights[st.back()] >= h) {
            int height = heights[st.back()];
            st.pop_back();
            int left = st.empty() ? -1 : st.back();
            best = std::max(best, height * (i - left - 1));
        }
        st.push_back(i);
    }
    return best;
}
