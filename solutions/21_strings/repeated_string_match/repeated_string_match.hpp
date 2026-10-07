#pragma once
#include <string>

// Approach: build a repeated just past |b| characters (the smallest k with k*|a| >= |b|); if b is not inside, try one more copy; else -1.
// Key insight: b can start anywhere in the first copy of a, so it needs at most one copy more than ceil(|b| / |a|).
// Time: O(|b| * (|a| + |b|)) with std::string::find; O(|a| + |b|) if the search is KMP  Space: O(|a| + |b|)
// Brute force: keep appending a and searching, with no principled stopping point.
inline int repeatedStringMatch(const std::string& a, const std::string& b) {
    std::string rep;
    int k = 0;
    while (rep.size() < b.size()) {
        rep += a;
        ++k;
    }
    if (rep.find(b) != std::string::npos) return k;
    rep += a;
    if (rep.find(b) != std::string::npos) return k + 1;
    return -1;
}
