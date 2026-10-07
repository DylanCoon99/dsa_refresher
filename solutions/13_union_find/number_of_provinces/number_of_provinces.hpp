#pragma once
#include <numeric>
#include <vector>

// Approach: union-find over the cities; start with n provinces and subtract one each time a 1 in the upper triangle joins two different sets.
// Key insight: the matrix is just an adjacency matrix, so provinces are connected components and each successful union removes exactly one.
// Time: O(n^2 alpha(n))  Space: O(n)
// Brute force: DFS/BFS from each unvisited city, also O(n^2) because of the matrix scan; union-find is the version that extends to edges arriving over time.
inline int findCircleNum(const std::vector<std::vector<int>>& isConnected) {
    int n = static_cast<int>(isConnected.size());
    std::vector<int> parent(n);
    std::iota(parent.begin(), parent.end(), 0);
    auto find = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };
    int count = n;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (isConnected[i][j]) {
                int a = find(i), b = find(j);
                if (a != b) {
                    parent[a] = b;
                    --count;
                }
            }
    return count;
}
