#pragma once
#include <algorithm>
#include <vector>

// Approach: sort start times and end times separately; for each start in order, if the earliest unfinished
//           end is <= that start, a room frees up (advance the end pointer), otherwise open a new room.
// Key insight: rooms needed = maximum number of simultaneous meetings, and only the multiset of starts and
//              ends matters, not which start belongs to which end.
// Time: O(n log n)  Space: O(n)
// Brute force: for each start point count the meetings covering it: O(n^2).
inline int minMeetingRooms(const std::vector<std::vector<int>>& intervals) {
    std::vector<int> starts, ends;
    for (const auto& iv : intervals) {
        starts.push_back(iv[0]);
        ends.push_back(iv[1]);
    }
    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());
    int rooms = 0, e = 0;
    for (int s : starts) {
        if (ends[e] <= s)
            ++e;  // the earliest-ending meeting is over: reuse its room
        else
            ++rooms;
    }
    return rooms;
}
