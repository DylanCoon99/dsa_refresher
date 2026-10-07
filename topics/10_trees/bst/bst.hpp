#pragma once
#include <cstddef>
#include <vector>

// Binary search tree of distinct ints. Add your own node struct and members below.
// insert/erase return whether the tree changed. erase uses successor replacement for two children.
class BST {
public:
    BST() {
        // TODO: implement
    }
    ~BST() {
        // TODO: implement (free your nodes)
    }
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    bool insert(int v) {
        // TODO: implement
        return false;
    }
    bool contains(int v) const {
        // TODO: implement
        return false;
    }
    bool erase(int v) {
        // TODO: implement
        return false;
    }
    std::vector<int> inorder() const {
        // TODO: implement
        return {};
    }
    std::size_t size() const {
        // TODO: implement
        return 0;
    }
};
