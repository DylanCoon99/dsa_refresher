#pragma once
#include <cstddef>
#include <stdexcept>
#include <vector>

// A doubly linked list of int. Use sentinel nodes (required by the exercise, not checkable by tests).
// popFront/popBack/front/back throw std::out_of_range when the list is empty.
// remove(v) deletes the first occurrence and returns whether one was found.
class DoublyLinkedList {
public:
    DoublyLinkedList() {
        // TODO: implement
    }
    ~DoublyLinkedList() {
        // TODO: implement
    }
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    void pushFront(int v) {
        // TODO: implement
    }
    void pushBack(int v) {
        // TODO: implement
    }
    int popFront() {
        // TODO: implement
        return 0;
    }
    int popBack() {
        // TODO: implement
        return 0;
    }
    int front() const {
        // TODO: implement
        return 0;
    }
    int back() const {
        // TODO: implement
        return 0;
    }
    bool remove(int v) {
        // TODO: implement
        return false;
    }
    std::size_t size() const {
        // TODO: implement
        return 0;
    }
    bool empty() const {
        // TODO: implement
        return true;
    }
    std::vector<int> toVector() const {
        // TODO: implement
        return {};
    }
};
