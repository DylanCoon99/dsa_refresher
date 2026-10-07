#pragma once
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Approach: BFS from beginWord, finding neighbors through wildcard buckets: every word is filed under each pattern formed by replacing one letter with '*', and two words differ in one letter exactly when they share a bucket.
// Key insight: the buckets give each word its neighbors in O(L) bucket lookups instead of comparing it to every other word, and BFS layers give the shortest ladder.
// Time: O(n * L^2)  Space: O(n * L^2)
// Brute force: BFS where each dequeued word is compared with every word in the list to find its one-letter neighbors, O(n^2 * L).
inline int ladderLength(const std::string& beginWord, const std::string& endWord, const std::vector<std::string>& wordList) {
    std::unordered_map<std::string, std::vector<std::string>> buckets;
    bool hasEnd = false;
    for (const std::string& w : wordList) {
        if (w == endWord) hasEnd = true;
        for (std::size_t i = 0; i < w.size(); ++i) {
            std::string key = w;
            key[i] = '*';
            buckets[key].push_back(w);
        }
    }
    if (!hasEnd) return 0;
    std::unordered_set<std::string> seen{beginWord};
    std::queue<std::string> q;
    q.push(beginWord);
    int length = 1;
    while (!q.empty()) {
        for (std::size_t left = q.size(); left > 0; --left) {
            std::string w = q.front();
            q.pop();
            if (w == endWord) return length;
            for (std::size_t i = 0; i < w.size(); ++i) {
                std::string key = w;
                key[i] = '*';
                for (const std::string& nb : buckets[key]) {
                    if (seen.insert(nb).second) q.push(nb);
                }
            }
        }
        ++length;
    }
    return 0;
}
