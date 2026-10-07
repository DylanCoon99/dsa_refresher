#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

// Approach: binary search on the length L; for a fixed L, roll a polynomial hash over all windows and look for a repeated hash,
//           confirming each hit by direct comparison.
// Key insight: if a length-L substring repeats, so does every shorter one, so "has a duplicate of length L" is monotone in L.
// Time: O(n log n) expected  Space: O(n)
// Brute force: compare every pair of start positions and measure the common length, O(n^2) or worse.
inline std::string longestDupSubstring(const std::string& s) {
    const int n = static_cast<int>(s.size());
    const std::uint64_t B = 0x9E3779B97F4A7C15ULL;
    std::vector<std::uint64_t> h(n + 1, 0), pw(n + 1, 1);
    for (int i = 0; i < n; ++i) {
        h[i + 1] = h[i] * B + static_cast<unsigned char>(s[i]) + 1;
        pw[i + 1] = pw[i] * B;
    }
    auto find = [&](int len) -> int {  // start of a repeated window of this length, or -1
        std::unordered_map<std::uint64_t, std::vector<int>> seen;
        seen.reserve(n * 2);
        for (int i = 0; i + len <= n; ++i) {
            const std::uint64_t v = h[i + len] - h[i] * pw[len];
            auto& bucket = seen[v];
            for (int j : bucket)
                if (s.compare(j, len, s, i, len) == 0) return i;
            bucket.push_back(i);
        }
        return -1;
    };
    int lo = 1, hi = n - 1, bestStart = -1, bestLen = 0;
    while (lo <= hi) {
        const int mid = (lo + hi) / 2;
        const int st = find(mid);
        if (st >= 0) {
            bestStart = st;
            bestLen = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return bestStart < 0 ? "" : s.substr(bestStart, bestLen);
}
