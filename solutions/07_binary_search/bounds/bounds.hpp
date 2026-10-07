#pragma once
#include <cstddef>
#include <vector>

// Approach: half-open range [lo, hi); each step discards the half that cannot contain the first
//           index satisfying the predicate (a[i] >= x, resp. a[i] > x).
// Key insight: both functions are the same loop with one comparison changed.
// Time: O(log n)  Space: O(1)
// Brute force: linear scan for the first qualifying element, O(n).
inline std::size_t lowerBound(const std::vector<int>& a, int x) {
    std::size_t lo = 0, hi = a.size();
    // Invariant: every a[i] with i < lo is < x, and every a[i] with i >= hi is >= x.
    // Init: lo = 0, hi = n, both sets empty. Step: a[mid] < x => lo = mid+1 keeps it,
    // else hi = mid keeps it. End: lo == hi, so the first index with a[i] >= x is lo.
    while (lo < hi) {
        std::size_t mid = lo + (hi - lo) / 2;
        if (a[mid] < x) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

inline std::size_t upperBound(const std::vector<int>& a, int x) {
    std::size_t lo = 0, hi = a.size();
    // Invariant: every a[i] with i < lo is <= x, and every a[i] with i >= hi is > x.
    while (lo < hi) {
        std::size_t mid = lo + (hi - lo) / 2;
        if (a[mid] <= x) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
