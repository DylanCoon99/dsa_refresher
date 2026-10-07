#pragma once
#include <array>
#include <memory>
#include <string>

// Approach: a trie of the words; search recurses over (node, position), and a '.' tries every child.
// Key insight: a wildcard turns the single trie walk into a DFS that branches only at the dots.
// Time: addWord O(L); search O(L) without dots, up to O(26^dots * L) worst case but bounded by the trie size
// Space: O(total characters)
// Brute force: scan every stored word against the pattern, O(words * L) per search.
class WordDictionary {
public:
    WordDictionary() : root_(std::make_unique<Node>()) {}

    void addWord(const std::string& word) {
        Node* cur = root_.get();
        for (char ch : word) {
            auto& next = cur->child[ch - 'a'];
            if (!next) next = std::make_unique<Node>();
            cur = next.get();
        }
        cur->is_word = true;
    }
    bool search(const std::string& pattern) const { return dfs(root_.get(), pattern, 0); }

private:
    struct Node {
        std::array<std::unique_ptr<Node>, 26> child;
        bool is_word = false;
    };
    std::unique_ptr<Node> root_;

    static bool dfs(const Node* node, const std::string& p, std::size_t i) {
        if (i == p.size()) return node->is_word;
        if (p[i] == '.') {
            for (const auto& c : node->child)
                if (c && dfs(c.get(), p, i + 1)) return true;
            return false;
        }
        const Node* next = node->child[p[i] - 'a'].get();
        return next && dfs(next, p, i + 1);
    }
};
