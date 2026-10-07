#pragma once
#include <random>
#include <utility>
#include <vector>

// Approach: mergeSort splits in half and merges through one shared buffer; quickSort uses a random
//           pivot with a three-way (Dutch flag) partition and recurses only into the smaller side;
//           heapSort builds a max-heap in place, then repeatedly swaps the root to the end.
// Key insight: sorted and all-equal input only stay fast if the pivot is random and equal keys are
//              grouped instead of being split to one side.
// Time: O(n log n) (merge, heap) / expected O(n log n) (quick)  Space: O(n) / O(1) / O(log n)
// Brute force: selection or insertion sort, O(n^2); first-element-pivot Lomuto quicksort is O(n^2)
//              on sorted or all-equal input.
namespace sort_detail {
inline void merge_rec(std::vector<int>& a, std::vector<int>& buf, std::size_t lo, std::size_t hi) {
    if (hi - lo < 2) return;
    std::size_t mid = lo + (hi - lo) / 2;
    merge_rec(a, buf, lo, mid);
    merge_rec(a, buf, mid, hi);
    std::size_t i = lo, j = mid, k = lo;
    while (i < mid && j < hi) buf[k++] = (a[j] < a[i]) ? a[j++] : a[i++];  // take left on ties: stable
    while (i < mid) buf[k++] = a[i++];
    while (j < hi) buf[k++] = a[j++];
    for (k = lo; k < hi; ++k) a[k] = buf[k];
}

inline void quick_rec(std::vector<int>& a, std::ptrdiff_t lo, std::ptrdiff_t hi, std::mt19937& gen) {
    while (lo < hi) {  // sorts a[lo..hi]
        int pivot = a[static_cast<std::size_t>(
            lo + static_cast<std::ptrdiff_t>(gen() % static_cast<unsigned>(hi - lo + 1)))];
        std::ptrdiff_t lt = lo, i = lo, gt = hi;  // a[lo..lt) < pivot, a[lt..i) == pivot, a(gt..hi] > pivot
        while (i <= gt) {
            if (a[static_cast<std::size_t>(i)] < pivot) {
                std::swap(a[static_cast<std::size_t>(lt++)], a[static_cast<std::size_t>(i++)]);
            } else if (a[static_cast<std::size_t>(i)] > pivot) {
                std::swap(a[static_cast<std::size_t>(i)], a[static_cast<std::size_t>(gt--)]);
            } else {
                ++i;
            }
        }
        if (lt - lo < hi - gt) {  // recurse into the smaller side, loop on the larger
            quick_rec(a, lo, lt - 1, gen);
            lo = gt + 1;
        } else {
            quick_rec(a, gt + 1, hi, gen);
            hi = lt - 1;
        }
    }
}

inline void sift_down(std::vector<int>& a, std::size_t i, std::size_t n) {
    while (true) {
        std::size_t child = 2 * i + 1;
        if (child >= n) return;
        if (child + 1 < n && a[child + 1] > a[child]) ++child;
        if (a[i] >= a[child]) return;
        std::swap(a[i], a[child]);
        i = child;
    }
}
}  // namespace sort_detail

inline void mergeSort(std::vector<int>& a) {
    std::vector<int> buf(a.size());
    sort_detail::merge_rec(a, buf, 0, a.size());
}

inline void quickSort(std::vector<int>& a) {
    if (a.size() < 2) return;
    std::mt19937 gen(12345);
    sort_detail::quick_rec(a, 0, static_cast<std::ptrdiff_t>(a.size()) - 1, gen);
}

inline void heapSort(std::vector<int>& a) {
    const std::size_t n = a.size();
    for (std::size_t i = n / 2; i-- > 0;) sort_detail::sift_down(a, i, n);
    for (std::size_t end = n; end-- > 1;) {
        std::swap(a[0], a[end]);
        sort_detail::sift_down(a, 0, end);
    }
}
