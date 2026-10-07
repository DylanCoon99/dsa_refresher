#pragma once
#include <cstddef>
#include <queue>
#include <vector>

// Approach: build the prerequisite graph b -> a and run Kahn's algorithm; all courses can be finished exactly when every course gets removed.
// Key insight: the schedule is possible if and only if the dependency graph has no cycle, and a cycle is what leaves courses with unmet prerequisites forever.
// Time: O(V + E)  Space: O(V + E)
// Brute force: repeatedly sweep all prerequisites, finishing every course whose prerequisites are all finished, until nothing changes: O(V * (V + E)) on a chain.
inline bool canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> next(static_cast<std::size_t>(numCourses));
    std::vector<int> indeg(static_cast<std::size_t>(numCourses), 0);
    for (const auto& p : prerequisites) {
        next[static_cast<std::size_t>(p[1])].push_back(p[0]);
        ++indeg[static_cast<std::size_t>(p[0])];
    }
    std::queue<int> ready;
    for (int c = 0; c < numCourses; ++c)
        if (indeg[static_cast<std::size_t>(c)] == 0) ready.push(c);
    int done = 0;
    while (!ready.empty()) {
        int c = ready.front();
        ready.pop();
        ++done;
        for (int d : next[static_cast<std::size_t>(c)])
            if (--indeg[static_cast<std::size_t>(d)] == 0) ready.push(d);
    }
    return done == numCourses;
}
