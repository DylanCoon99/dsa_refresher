#pragma once
#include <vector>

// Approach: difference array: add seats at index first-1 and subtract it at index last, then take a running sum.
// Key insight: a range update is two point updates on the difference array; one prefix pass rebuilds all totals.
// Time: O(n + bookings)  Space: O(n)
// Brute force: add seats to every flight in each booking's range, O(n * bookings).
inline std::vector<int> corpFlightBookings(const std::vector<std::vector<int>>& bookings, int n) {
    std::vector<int> diff(n + 1, 0);
    for (const auto& b : bookings) {
        diff[b[0] - 1] += b[2];
        diff[b[1]] -= b[2];
    }
    std::vector<int> answer(n);
    int running = 0;
    for (int i = 0; i < n; ++i) {
        running += diff[i];
        answer[i] = running;
    }
    return answer;
}
