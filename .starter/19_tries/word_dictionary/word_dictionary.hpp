#pragma once
#include <string>

// A growing set of lowercase words that can be searched with '.' wildcards.
class WordDictionary {
public:
    // Add `word` (lowercase letters only, length >= 1). Adding a word twice is fine.
    void addWord(const std::string& word) {
        // TODO: implement
    }
    // True iff some added word matches `pattern`: same length, and every pattern character is
    // either '.' (matches any one letter) or equal to the word's letter at that position.
    // `pattern` has length >= 1 and uses only lowercase letters and '.'.
    bool search(const std::string& pattern) const {
        // TODO: implement
        return false;
    }

private:
    // Add your data members here.
};
