#pragma once
#include <string>

// A set of lowercase words supporting insert, whole-word search and prefix search.
// Not copyable (copying would double-free raw child pointers). Free all nodes in the destructor.
class Trie {
public:
    Trie() {
        // TODO: implement
    }
    ~Trie() {
        // TODO: implement
    }
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Add `word` (may be empty; inserting a word twice is fine).
    void insert(const std::string& word) {
        // TODO: implement
    }
    // True iff `word` was inserted exactly (a mere prefix of an inserted word is not a word).
    bool search(const std::string& word) const {
        // TODO: implement
        return false;
    }
    // True iff some inserted word starts with `prefix` (a word is a prefix of itself).
    // startsWith("") must be true once at least one word has been inserted.
    bool startsWith(const std::string& prefix) const {
        // TODO: implement
        return false;
    }

private:
    // Add your node structure and root here.
};
