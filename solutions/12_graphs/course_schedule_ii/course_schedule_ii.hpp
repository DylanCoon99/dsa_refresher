#pragma once
#include <cstddef>
#include <queue>
#include <vector>

// Approach: Kahn's algorithm on the graph prerequisite -> course; the removal order is the study order, and a short result means a cycle.
// Key insight: a course with no unmet prerequisites can be taken now, so taking it and releasing its dependents builds a valid order one layer at a time.
// Time: O(V + E)  Space: O(V + E)
// Brute force: try every permutation of the courses and test each one against all prerequisites, O(V! * E).
inline std::vector<int> findOrder(int numCourses, const std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> next(static_cast<std::size_t>(numCourses));
    std::vector<int> indeg(static_cast<std::size_t>(numCourses), 0);
    for (const auto& p : prerequisites) {
        next[static_cast<std::size_t>(p[1])].push_back(p[0]);
        ++indeg[static_cast<std::size_t>(p[0])];
    }
    std::queue<int> ready;
    for (int c = 0; c < numCourses; ++c)
        if (indeg[static_cast<std::size_t>(c)] == 0) ready.push(c);
    std::vector<int> order;
    while (!ready.empty()) {
        int c = ready.front();
        ready.pop();
        order.push_back(c);
        for (int d : next[static_cast<std::size_t>(c)])
            if (--indeg[static_cast<std::size_t>(d)] == 0) ready.push(d);
    }
    if (static_cast<int>(order.size()) != numCourses) return {};
    return order;
}
