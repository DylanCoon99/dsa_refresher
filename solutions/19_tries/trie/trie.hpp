#pragma once
#include <array>
#include <string>

// Approach: each node stands for a prefix; it holds 26 child pointers and an "is a word" flag.
//           insert/search/startsWith all walk one node per letter.
// Key insight: the path from the root IS the prefix, so prefix queries cost O(length) with no scan.
// Time: O(L) per operation  Space: O(total characters * 26) pointers (a map would trade lookup speed for memory)
// Brute force: keep a list of words and scan all of them per query, O(words * L).
class Trie {
public:
    Trie() : root_(new Node()) {}
    ~Trie() { destroy(root_); }
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    void insert(const std::string& word) {
        Node* cur = root_;
        for (char ch : word) {
            Node*& next = cur->child[ch - 'a'];
            if (!next) next = new Node();
            cur = next;
        }
        cur->is_word = true;
    }
    bool search(const std::string& word) const {
        const Node* n = walk(word);
        return n && n->is_word;
    }
    bool startsWith(const std::string& prefix) const { return walk(prefix) != nullptr; }

private:
    struct Node {
        std::array<Node*, 26> child{};
        bool is_word = false;
    };
    Node* root_;

    const Node* walk(const std::string& s) const {
        const Node* cur = root_;
        for (char ch : s) {
            cur = cur->child[ch - 'a'];
            if (!cur) return nullptr;
        }
        return cur;
    }
    static void destroy(Node* n) {
        if (!n) return;
        for (Node* c : n->child) destroy(c);
        delete n;
    }
};
