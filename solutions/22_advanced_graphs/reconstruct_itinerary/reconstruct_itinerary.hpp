#pragma once
#include <algorithm>
#include <map>
#include <string>
#include <vector>

// Approach: Hierholzer's algorithm for an Euler path. Keep each airport's destinations sorted (smallest last, so
//           pop_back takes the smallest); DFS always takes the smallest unused ticket and appends an airport to the
//           answer only when it has no tickets left; reverse at the end.
// Key insight: a dead-end airport is finished first, so it lands at the END of the route automatically.
// Time: O(E log E)  Space: O(E) (recursion depth up to E; production code would use an explicit stack)
// Brute force: try the tickets in sorted order with backtracking, which is exponential in the worst case.
namespace itinerary_detail {
inline void visit(const std::string& at, std::map<std::string, std::vector<std::string>>& dest,
                  std::vector<std::string>& out) {
    auto& d = dest[at];
    while (!d.empty()) {
        std::string next = d.back();
        d.pop_back();
        visit(next, dest, out);
    }
    out.push_back(at);
}
}  // namespace itinerary_detail

inline std::vector<std::string> findItinerary(std::vector<std::vector<std::string>> tickets) {
    std::map<std::string, std::vector<std::string>> dest;
    for (const auto& t : tickets) dest[t[0]].push_back(t[1]);
    for (auto& [from, list] : dest) std::sort(list.begin(), list.end(), std::greater<std::string>());
    std::vector<std::string> out;
    itinerary_detail::visit("JFK", dest, out);
    std::reverse(out.begin(), out.end());
    return out;
}
