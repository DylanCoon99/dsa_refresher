#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

// Approach: a circular list with one sentinel node; head_.next is the front, head_.prev the back.
// Key insight: with a sentinel every real node has non-null prev/next, so insert-before and unlink need no end cases.
// Time: O(1) per operation except remove/toVector O(n)  Space: O(n)
// Brute force: a singly linked list with head/tail special cases (popBack is O(n)).
class DoublyLinkedList {
public:
    DoublyLinkedList() { sentinel_.prev = sentinel_.next = &sentinel_; }
    ~DoublyLinkedList() {
        Node* p = sentinel_.next;
        while (p != &sentinel_) {
            Node* next = p->next;
            delete p;
            p = next;
        }
    }
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    void pushFront(int v) { insertBefore(sentinel_.next, v); }
    void pushBack(int v) { insertBefore(&sentinel_, v); }
    int popFront() {
        requireNonEmpty();
        return unlink(sentinel_.next);
    }
    int popBack() {
        requireNonEmpty();
        return unlink(sentinel_.prev);
    }
    int front() const {
        requireNonEmpty();
        return sentinel_.next->val;
    }
    int back() const {
        requireNonEmpty();
        return sentinel_.prev->val;
    }
    bool remove(int v) {
        for (Node* p = sentinel_.next; p != &sentinel_; p = p->next) {
            if (p->val == v) {
                unlink(p);
                return true;
            }
        }
        return false;
    }
    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    std::vector<int> toVector() const {
        std::vector<int> out;
        for (const Node* p = sentinel_.next; p != &sentinel_; p = p->next) out.push_back(p->val);
        return out;
    }

private:
    struct Node {
        int val = 0;
        Node* prev = nullptr;
        Node* next = nullptr;
    };
    void requireNonEmpty() const {
        if (size_ == 0) throw std::out_of_range("empty list");
    }
    void insertBefore(Node* pos, int v) {
        Node* n = new Node{v, pos->prev, pos};
        pos->prev->next = n;
        pos->prev = n;
        ++size_;
    }
    int unlink(Node* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        int v = n->val;
        delete n;
        --size_;
        return v;
    }
    Node sentinel_;
    std::size_t size_ = 0;
};
