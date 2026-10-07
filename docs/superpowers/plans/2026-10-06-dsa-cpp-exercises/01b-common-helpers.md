# Stage 1a (continued): `common/` Helper Sources

Full source for Task 1, Steps 5–8 (see `01a-infrastructure.md`). It's kept in a separate file to keep each plan file under 500 lines.

- [ ] **Step 5: Write `common/printing.hpp`**

```cpp
#pragma once
// doctest printers, so failed CHECKs show container contents instead of "{?}".
#include <doctest.h>

#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace dsa_print {

inline std::string to_text(const std::string& s) { return "\"" + s + "\""; }
inline std::string to_text(char c) { return std::string("'") + c + "'"; }
inline std::string to_text(bool b) { return b ? "true" : "false"; }
template <typename T>
    requires std::is_arithmetic_v<T>
std::string to_text(T v) { return std::to_string(v); }

// Declared before the definitions so nested containers resolve each other.
template <typename T> std::string to_text(const std::optional<T>& o);
template <typename A, typename B> std::string to_text(const std::pair<A, B>& p);
template <typename T> std::string to_text(const std::vector<T>& v);

template <typename T>
std::string to_text(const std::optional<T>& o) { return o ? to_text(*o) : "null"; }

template <typename A, typename B>
std::string to_text(const std::pair<A, B>& p) {
    return "(" + to_text(p.first) + ", " + to_text(p.second) + ")";
}

template <typename T>
std::string to_text(const std::vector<T>& v) {
    std::string out = "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) out += ", ";
        out += to_text(static_cast<const T&>(v[i]));
    }
    return out + "]";
}

}  // namespace dsa_print

namespace doctest {
template <typename T> struct StringMaker<std::vector<T>> {
    static String convert(const std::vector<T>& v) { return dsa_print::to_text(v).c_str(); }
};
template <typename T> struct StringMaker<std::optional<T>> {
    static String convert(const std::optional<T>& o) { return dsa_print::to_text(o).c_str(); }
};
template <typename A, typename B> struct StringMaker<std::pair<A, B>> {
    static String convert(const std::pair<A, B>& p) { return dsa_print::to_text(p).c_str(); }
};
}  // namespace doctest
```

Note: `static_cast<const T&>(v[i])` turns `std::vector<bool>`'s proxy reference into a plain `bool`.

- [ ] **Step 6: Write `common/list_node.hpp`**

```cpp
#pragma once
#include <cstddef>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

// Tests never free nodes: solutions may delete nodes they remove.
inline ListNode* build_list(const std::vector<int>& vals) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

// The tail links back to the node at index `pos`; pos = -1 means no cycle.
inline ListNode* build_list_with_cycle(const std::vector<int>& vals, int pos) {
    ListNode* head = build_list(vals);
    if (pos < 0 || head == nullptr) return head;
    ListNode* target = head;
    for (int i = 0; i < pos; ++i) target = target->next;
    ListNode* tail = head;
    while (tail->next) tail = tail->next;
    tail->next = target;
    return head;
}

// Throws past `limit` nodes, so a list a buggy solution made cyclic fails the test instead of hanging it.
inline std::vector<int> to_vector(const ListNode* head, std::size_t limit = 1'000'000) {
    std::vector<int> out;
    for (; head != nullptr; head = head->next) {
        if (out.size() == limit) throw std::runtime_error("list exceeds node limit (cycle?)");
        out.push_back(head->val);
    }
    return out;
}

struct RandomListNode {
    int val;
    RandomListNode* next;
    RandomListNode* random;
    explicit RandomListNode(int x) : val(x), next(nullptr), random(nullptr) {}
};

// Each entry is {value, index of the random target or -1}.
inline RandomListNode* build_random_list(const std::vector<std::pair<int, int>>& spec) {
    std::vector<RandomListNode*> nodes;
    for (const auto& entry : spec) nodes.push_back(new RandomListNode(entry.first));
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (i + 1 < nodes.size()) nodes[i]->next = nodes[i + 1];
        if (spec[i].second >= 0) nodes[i]->random = nodes[spec[i].second];
    }
    return nodes.empty() ? nullptr : nodes[0];
}

// Inverse of build_random_list. A random pointer to a node outside the list becomes -2.
inline std::vector<std::pair<int, int>> to_random_spec(const RandomListNode* head,
                                                       std::size_t limit = 1'000'000) {
    std::vector<const RandomListNode*> nodes;
    std::unordered_map<const RandomListNode*, int> index;
    for (; head != nullptr; head = head->next) {
        if (nodes.size() == limit) throw std::runtime_error("list exceeds node limit (cycle?)");
        index[head] = static_cast<int>(nodes.size());
        nodes.push_back(head);
    }
    std::vector<std::pair<int, int>> out;
    for (const RandomListNode* n : nodes) {
        int r = -1;
        if (n->random) {
            auto it = index.find(n->random);
            r = it == index.end() ? -2 : it->second;
        }
        out.emplace_back(n->val, r);
    }
    return out;
}
```

- [ ] **Step 7: Write `common/tree_node.hpp`**

```cpp
#pragma once
#include <cstddef>
#include <optional>
#include <queue>
#include <stdexcept>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x = 0, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(x), left(l), right(r) {}
};

inline constexpr std::nullopt_t null = std::nullopt;
using LevelOrder = std::vector<std::optional<int>>;

// Builds a tree from level order with null gaps, e.g. {3, 9, 20, null, null, 15, 7}.
inline TreeNode* build_tree(const LevelOrder& vals) {
    if (vals.empty() || !vals[0]) return nullptr;
    TreeNode* root = new TreeNode(*vals[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    std::size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode* node = q.front();
        q.pop();
        if (i < vals.size() && vals[i]) { node->left = new TreeNode(*vals[i]); q.push(node->left); }
        ++i;
        if (i < vals.size() && vals[i]) { node->right = new TreeNode(*vals[i]); q.push(node->right); }
        ++i;
    }
    return root;
}

// Inverse of build_tree with trailing nulls trimmed. Throws past `limit` nodes (cycle guard).
inline LevelOrder to_level_order(const TreeNode* root, std::size_t limit = 1'000'000) {
    LevelOrder out;
    std::queue<const TreeNode*> q;
    q.push(root);
    std::size_t seen = 0;
    while (!q.empty()) {
        const TreeNode* n = q.front();
        q.pop();
        if (!n) { out.push_back(null); continue; }
        if (++seen > limit) throw std::runtime_error("tree exceeds node limit (cycle?)");
        out.push_back(n->val);
        q.push(n->left);
        q.push(n->right);
    }
    while (!out.empty() && !out.back()) out.pop_back();
    return out;
}

// First node with value `val` in level order, or nullptr.
inline TreeNode* find_node(TreeNode* root, int val) {
    std::queue<TreeNode*> q;
    if (root) q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        if (n->val == val) return n;
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
    return nullptr;
}

// Right-leaning chain with values 0..n-1, for deep-recursion tests.
inline TreeNode* build_chain(int n) {
    TreeNode dummy;
    TreeNode* tail = &dummy;
    for (int i = 0; i < n; ++i) { tail->right = new TreeNode(i); tail = tail->right; }
    return dummy.right;
}

// Height-balanced BST from strictly increasing values.
inline TreeNode* build_balanced_bst(const std::vector<int>& sorted, int lo = 0, int hi = -2) {
    if (hi == -2) hi = static_cast<int>(sorted.size()) - 1;
    if (lo > hi) return nullptr;
    int mid = lo + (hi - lo) / 2;
    return new TreeNode(sorted[mid], build_balanced_bst(sorted, lo, mid - 1),
                        build_balanced_bst(sorted, mid + 1, hi));
}
```

- [ ] **Step 8: Write `common/graph.hpp` and `common/random_utils.hpp`**

```cpp
// common/graph.hpp
#pragma once
#include <utility>
#include <vector>

using Graph = std::vector<std::vector<int>>;                           // adjacency list
using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>;  // {neighbor, weight}

// edges are {u, v}
inline Graph edges_to_graph(int n, const std::vector<std::vector<int>>& edges, bool directed) {
    Graph g(n);
    for (const auto& e : edges) {
        g[e[0]].push_back(e[1]);
        if (!directed) g[e[1]].push_back(e[0]);
    }
    return g;
}

// edges are {u, v, w}
inline WeightedGraph weighted_edges_to_graph(int n, const std::vector<std::vector<int>>& edges,
                                             bool directed) {
    WeightedGraph g(n);
    for (const auto& e : edges) {
        g[e[0]].emplace_back(e[1], e[2]);
        if (!directed) g[e[1]].emplace_back(e[0], e[2]);
    }
    return g;
}
```

```cpp
// common/random_utils.hpp
#pragma once
#include <cstddef>
#include <random>
#include <string>
#include <vector>

// Fixed seed: a failing randomized test fails the same way every run.
inline std::mt19937& rng() {
    static std::mt19937 gen(20261006);
    return gen;
}

inline int rand_int(int lo, int hi) { return std::uniform_int_distribution<int>(lo, hi)(rng()); }

inline std::vector<int> rand_vec(std::size_t n, int lo, int hi) {
    std::vector<int> v(n);
    for (int& x : v) x = rand_int(lo, hi);
    return v;
}

inline std::string rand_string(std::size_t n, char lo = 'a', char hi = 'z') {
    std::string s(n, lo);
    for (char& c : s) c = static_cast<char>(rand_int(lo, hi));
    return s;
}
```

