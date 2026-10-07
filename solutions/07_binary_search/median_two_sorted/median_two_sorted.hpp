#pragma once
#include <algorithm>
#include <climits>
#include <vector>

// Approach: binary-search how many elements i of the shorter array go in the left half; the other array
//           contributes (m+n+1)/2 - i. The split is right when each left max <= the other side's right min.
// Key insight: the median is defined by a partition, so search for the partition, not for the value.
// Time: O(log(min(m, n)))  Space: O(1)
// Brute force: merge both arrays and take the middle, O(m + n).
inline double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    const std::vector<int>& a = nums1.size() <= nums2.size() ? nums1 : nums2;
    const std::vector<int>& b = nums1.size() <= nums2.size() ? nums2 : nums1;
    const int m = static_cast<int>(a.size()), n = static_cast<int>(b.size());
    const int half = (m + n + 1) / 2;
    int lo = 0, hi = m;
    while (lo <= hi) {
        int i = lo + (hi - lo) / 2;  // elements taken from a
        int j = half - i;            // elements taken from b
        long long aLeft = i > 0 ? a[i - 1] : LLONG_MIN, aRight = i < m ? a[i] : LLONG_MAX;
        long long bLeft = j > 0 ? b[j - 1] : LLONG_MIN, bRight = j < n ? b[j] : LLONG_MAX;
        if (aLeft > bRight) hi = i - 1;
        else if (bLeft > aRight) lo = i + 1;
        else {
            long long leftMax = std::max(aLeft, bLeft);
            if ((m + n) % 2 == 1) return static_cast<double>(leftMax);
            long long rightMin = std::min(aRight, bRight);
            return static_cast<double>(leftMax + rightMin) / 2.0;
        }
    }
    return 0.0;  // unreachable for valid input
}
