#pragma once
#include <vector>

// Approach: one choose -> explore -> unchoose recursion per routine. Subsets record the path at every
//           node and only extend with later indices; combinations do the same with values and a
//           size-k stop; permutations track a used[] flag per position.
// Key insight: the three problems differ only in when you record and which choices are legal next.
// Time: O(n * 2^n) subsets, O(n * n!) permutations, O(k * C(n,k)) combinations  Space: O(n) beyond output
// Brute force: bitmask over 2^n for subsets/combinations; std::next_permutation for permutations.
namespace bt_detail {
using Rows = std::vector<std::vector<int>>;

inline void subsets_rec(const std::vector<int>& items, int start, std::vector<int>& path, Rows& out) {
    out.push_back(path);
    for (int i = start; i < static_cast<int>(items.size()); ++i) {
        path.push_back(items[i]);
        subsets_rec(items, i + 1, path, out);
        path.pop_back();
    }
}

inline void perms_rec(const std::vector<int>& items, std::vector<bool>& used, std::vector<int>& path,
                      Rows& out) {
    if (path.size() == items.size()) {
        out.push_back(path);
        return;
    }
    for (std::size_t i = 0; i < items.size(); ++i) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(items[i]);
        perms_rec(items, used, path, out);
        path.pop_back();
        used[i] = false;
    }
}

inline void combs_rec(int n, int k, int start, std::vector<int>& path, Rows& out) {
    if (static_cast<int>(path.size()) == k) {
        out.push_back(path);
        return;
    }
    // Prune: need k - path.size() more values, so the last useful start is n - need + 1.
    const int need = k - static_cast<int>(path.size());
    for (int v = start; v <= n - need + 1; ++v) {
        path.push_back(v);
        combs_rec(n, k, v + 1, path, out);
        path.pop_back();
    }
}
}  // namespace bt_detail

inline std::vector<std::vector<int>> allSubsets(const std::vector<int>& items) {
    bt_detail::Rows out;
    std::vector<int> path;
    bt_detail::subsets_rec(items, 0, path, out);
    return out;
}

inline std::vector<std::vector<int>> allPermutations(const std::vector<int>& items) {
    bt_detail::Rows out;
    std::vector<int> path;
    std::vector<bool> used(items.size(), false);
    bt_detail::perms_rec(items, used, path, out);
    return out;
}

inline std::vector<std::vector<int>> allCombinations(int n, int k) {
    bt_detail::Rows out;
    std::vector<int> path;
    bt_detail::combs_rec(n, k, 1, path, out);
    return out;
}
