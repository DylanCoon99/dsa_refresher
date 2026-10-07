#pragma once
#include <array>
#include <queue>
#include <set>
#include <string>
#include <vector>

// Approach: compare each adjacent pair of words; the first differing letters give an edge a -> b ("a before b").
//           A word that is longer than the next word but has it as a prefix is immediately invalid. Then topologically
//           sort the letters with Kahn's algorithm; if some letter is never released there is a cycle, so return "".
// Key insight: only adjacent words and only the FIRST differing position give constraints, and letters with no
//              constraint still have to be output, so every appearing letter is a vertex.
// Time: O(total characters + 26^2)  Space: O(26^2)
// Brute force: try every permutation of the distinct letters and check the dictionary against it, O(L! * total chars).
inline std::string alienOrder(const std::vector<std::string>& words) {
    std::array<bool, 26> present{};
    for (const auto& w : words)
        for (char c : w) present[c - 'a'] = true;
    std::array<std::set<int>, 26> out;
    std::array<int, 26> indeg{};
    for (std::size_t i = 0; i + 1 < words.size(); ++i) {
        const std::string &a = words[i], &b = words[i + 1];
        std::size_t k = 0;
        while (k < a.size() && k < b.size() && a[k] == b[k]) ++k;
        if (k == a.size() || k == b.size()) {
            if (a.size() > b.size()) return "";
            continue;
        }
        if (out[a[k] - 'a'].insert(b[k] - 'a').second) ++indeg[b[k] - 'a'];
    }
    std::queue<int> q;
    int total = 0;
    for (int c = 0; c < 26; ++c) {
        if (!present[c]) continue;
        ++total;
        if (indeg[c] == 0) q.push(c);
    }
    std::string order;
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        order += static_cast<char>('a' + c);
        for (int d : out[c])
            if (--indeg[d] == 0) q.push(d);
    }
    return static_cast<int>(order.size()) == total ? order : "";
}
