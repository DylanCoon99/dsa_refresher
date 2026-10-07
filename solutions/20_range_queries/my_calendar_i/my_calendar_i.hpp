#pragma once
#include <iterator>
#include <map>

// Approach: an ordered map start -> end of the accepted bookings. A new [s, e) can only collide with the
//           booking starting at or after s (needs that start < e) or the one starting just before s (needs its end > s).
// Key insight: accepted bookings are disjoint and sorted, so only the two neighbours of s need checking.
// Time: O(log n) per call  Space: O(n)
// Brute force: compare against every stored booking, O(n) per call.
class MyCalendar {
public:
    bool book(int start, int end) {
        auto next = booked_.lower_bound(start);  // first booking with start' >= start
        if (next != booked_.end() && next->first < end) return false;
        if (next != booked_.begin() && std::prev(next)->second > start) return false;
        booked_.emplace(start, end);
        return true;
    }

private:
    std::map<int, int> booked_;
};
