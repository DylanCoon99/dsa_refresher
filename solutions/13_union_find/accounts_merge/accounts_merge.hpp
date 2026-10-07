#pragma once
#include <algorithm>
#include <map>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

// Approach: union-find over account indices; the first account to list an email owns it, and a later account listing it is united with the owner. Then group the emails by root, sort, and prepend the name.
// Key insight: shared emails are the edges between accounts, so connected components of accounts are exactly the people.
// Time: O(N alpha(N) + N log N) for N emails  Space: O(N)
// Brute force: repeatedly merge any two accounts that share an email until no pair does, O(accounts^2 * emails) per pass.
inline std::vector<std::vector<std::string>> accountsMerge(const std::vector<std::vector<std::string>>& accounts) {
    int n = static_cast<int>(accounts.size());
    std::vector<int> parent(n);
    std::iota(parent.begin(), parent.end(), 0);
    auto find = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };
    std::unordered_map<std::string, int> owner;
    for (int i = 0; i < n; ++i)
        for (std::size_t j = 1; j < accounts[i].size(); ++j) {
            auto [it, inserted] = owner.emplace(accounts[i][j], i);
            if (!inserted) parent[find(i)] = find(it->second);
        }
    std::map<int, std::vector<std::string>> groups;
    for (const auto& [email, acc] : owner) groups[find(acc)].push_back(email);
    std::vector<std::vector<std::string>> result;
    for (auto& [root, emails] : groups) {
        std::sort(emails.begin(), emails.end());
        std::vector<std::string> row{accounts[root][0]};
        row.insert(row.end(), emails.begin(), emails.end());
        result.push_back(std::move(row));
    }
    return result;
}
