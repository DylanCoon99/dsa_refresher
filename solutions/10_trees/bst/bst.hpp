#pragma once
#include <cstddef>
#include <vector>

// Approach: unbalanced BST with pointer-to-link traversal; two-child erase copies the successor's key up and unlinks the successor.
// Key insight: the successor (leftmost node of the right subtree) has no left child, so removing it is the easy 0/1-child case.
// Time: O(h) per op (O(log n) expected on random keys)  Space: O(n)
// Brute force: keep a sorted std::vector, O(n) per insert/erase.
class BST {
    struct Node {
        int key;
        Node* left = nullptr;
        Node* right = nullptr;
        explicit Node(int k) : key(k) {}
    };
    Node* root_ = nullptr;
    std::size_t size_ = 0;

public:
    BST() = default;
    ~BST() {
        std::vector<Node*> st;
        if (root_) st.push_back(root_);
        while (!st.empty()) {
            Node* n = st.back();
            st.pop_back();
            if (n->left) st.push_back(n->left);
            if (n->right) st.push_back(n->right);
            delete n;
        }
    }
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    bool insert(int v) {
        Node** link = &root_;
        while (*link) {
            if (v == (*link)->key) return false;
            link = v < (*link)->key ? &(*link)->left : &(*link)->right;
        }
        *link = new Node(v);
        ++size_;
        return true;
    }
    bool contains(int v) const {
        const Node* n = root_;
        while (n) {
            if (v == n->key) return true;
            n = v < n->key ? n->left : n->right;
        }
        return false;
    }
    bool erase(int v) {
        Node** link = &root_;
        while (*link && (*link)->key != v) link = v < (*link)->key ? &(*link)->left : &(*link)->right;
        if (!*link) return false;
        Node* n = *link;
        if (!n->left) {
            *link = n->right;
            delete n;
        } else if (!n->right) {
            *link = n->left;
            delete n;
        } else {
            Node** succ = &n->right;
            while ((*succ)->left) succ = &(*succ)->left;
            Node* s = *succ;
            n->key = s->key;
            *succ = s->right;
            delete s;
        }
        --size_;
        return true;
    }
    std::vector<int> inorder() const {
        std::vector<int> out;
        std::vector<const Node*> st;
        const Node* cur = root_;
        while (cur || !st.empty()) {
            while (cur) { st.push_back(cur); cur = cur->left; }
            cur = st.back();
            st.pop_back();
            out.push_back(cur->key);
            cur = cur->right;
        }
        return out;
    }
    std::size_t size() const { return size_; }
};
