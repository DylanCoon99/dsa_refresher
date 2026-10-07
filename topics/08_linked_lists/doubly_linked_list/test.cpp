#include <doubly_linked_list.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <climits>
#include <list>
#include <stdexcept>
#include <vector>

namespace {
void fill(DoublyLinkedList& d, const std::vector<int>& vals) {
    for (int v : vals) d.pushBack(v);
}
}  // namespace

TEST_CASE("examples") {
    DoublyLinkedList a;
    a.pushBack(1);
    a.pushBack(2);
    a.pushFront(0);
    CHECK(a.toVector() == std::vector<int>{0, 1, 2});
    CHECK(a.popFront() == 0);
    CHECK(a.popBack() == 2);
    CHECK(a.toVector() == std::vector<int>{1});

    DoublyLinkedList b;
    fill(b, {5, 7, 5});
    CHECK(b.remove(5) == true);
    CHECK(b.toVector() == std::vector<int>{7, 5});
    CHECK(b.remove(9) == false);
}

TEST_CASE("edge cases") {
    SUBCASE("empty list throws") {
        DoublyLinkedList d;
        CHECK(d.empty());
        CHECK(d.size() == 0);
        CHECK(d.toVector().empty());
        CHECK_THROWS_AS(d.popFront(), std::out_of_range);
        CHECK_THROWS_AS(d.popBack(), std::out_of_range);
        CHECK_THROWS_AS(d.front(), std::out_of_range);
        CHECK_THROWS_AS(d.back(), std::out_of_range);
    }
    SUBCASE("throws again after being emptied") {
        DoublyLinkedList d;
        d.pushBack(1);
        d.pushFront(2);
        CHECK(d.popBack() == 1);
        CHECK(d.popBack() == 2);
        CHECK(d.empty());
        CHECK_THROWS_AS(d.popBack(), std::out_of_range);
        CHECK_THROWS_AS(d.popFront(), std::out_of_range);
        d.pushBack(9);  // still usable afterwards
        CHECK(d.front() == 9);
        CHECK(d.back() == 9);
    }
    SUBCASE("front, back and size track pushes") {
        DoublyLinkedList d;
        d.pushBack(2);
        CHECK(d.front() == 2);
        CHECK(d.back() == 2);
        d.pushFront(1);
        d.pushBack(3);
        CHECK(d.front() == 1);
        CHECK(d.back() == 3);
        CHECK(d.size() == 3);
        CHECK(!d.empty());
        CHECK(d.toVector() == std::vector<int>{1, 2, 3});
    }
    SUBCASE("remove the head") {
        DoublyLinkedList d;
        fill(d, {1, 2, 3});
        CHECK(d.remove(1));
        CHECK(d.toVector() == std::vector<int>{2, 3});
        CHECK(d.front() == 2);
        CHECK(d.size() == 2);
        d.pushFront(0);  // links around the removed head must be intact
        CHECK(d.toVector() == std::vector<int>{0, 2, 3});
    }
    SUBCASE("remove the tail") {
        DoublyLinkedList d;
        fill(d, {1, 2, 3});
        CHECK(d.remove(3));
        CHECK(d.toVector() == std::vector<int>{1, 2});
        CHECK(d.back() == 2);
        d.pushBack(4);
        CHECK(d.toVector() == std::vector<int>{1, 2, 4});
    }
    SUBCASE("remove the only element") {
        DoublyLinkedList d;
        d.pushBack(42);
        CHECK(d.remove(42));
        CHECK(d.empty());
        CHECK(d.size() == 0);
        CHECK(d.toVector().empty());
        CHECK_THROWS_AS(d.front(), std::out_of_range);
        d.pushFront(7);
        CHECK(d.toVector() == std::vector<int>{7});
    }
    SUBCASE("remove a middle element, backward links stay correct") {
        DoublyLinkedList d;
        fill(d, {1, 2, 3, 4});
        CHECK(d.remove(2));
        CHECK(d.popBack() == 4);
        CHECK(d.popBack() == 3);
        CHECK(d.popBack() == 1);
        CHECK(d.empty());
    }
    SUBCASE("remove a missing value") {
        DoublyLinkedList d;
        fill(d, {1, 2, 3});
        CHECK(d.remove(99) == false);
        CHECK(d.toVector() == std::vector<int>{1, 2, 3});
        DoublyLinkedList e;
        CHECK(e.remove(1) == false);
    }
    SUBCASE("remove deletes only the first occurrence") {
        DoublyLinkedList d;
        fill(d, {4, 1, 4, 1, 4});
        CHECK(d.remove(4));
        CHECK(d.toVector() == std::vector<int>{1, 4, 1, 4});
        CHECK(d.remove(1));
        CHECK(d.toVector() == std::vector<int>{4, 1, 4});
    }
    SUBCASE("INT_MIN and INT_MAX are ordinary values") {
        DoublyLinkedList d;
        d.pushBack(INT_MAX);
        d.pushFront(INT_MIN);
        CHECK(d.front() == INT_MIN);
        CHECK(d.back() == INT_MAX);
        CHECK(d.remove(INT_MIN));
        CHECK(d.toVector() == std::vector<int>{INT_MAX});
    }
}

TEST_CASE("destructor runs on every list") {
    // Sanitizers catch a double free or use-after-free here. A leak is not detected on macOS arm64.
    for (int i = 0; i < 1000; ++i) {
        DoublyLinkedList d;
        for (int k = 0; k < 10; ++k) {
            if (k % 2 == 0) d.pushBack(k); else d.pushFront(k);
        }
        d.remove(4);
        d.popFront();
        if (i % 3 == 0) {
            while (!d.empty()) d.popBack();
        }
        CHECK(d.size() == (i % 3 == 0 ? 0u : 8u));
    }
    for (int i = 0; i < 1000; ++i) {
        DoublyLinkedList empty_list;  // destroying an empty list must also work
        CHECK(empty_list.empty());
    }
}

TEST_CASE("randomized vs std::list") {
    DoublyLinkedList d;
    std::list<int> ref;
    for (int op = 0; op < 100'000; ++op) {
        switch (rand_int(0, 9)) {
            case 0: case 1: {
                int v = rand_int(0, 99);
                d.pushFront(v);
                ref.push_front(v);
                break;
            }
            case 2: case 3: {
                int v = rand_int(0, 99);
                d.pushBack(v);
                ref.push_back(v);
                break;
            }
            case 4:
                if (ref.empty()) {
                    REQUIRE_THROWS_AS(d.popFront(), std::out_of_range);
                } else {
                    REQUIRE(d.popFront() == ref.front());
                    ref.pop_front();
                }
                break;
            case 5:
                if (ref.empty()) {
                    REQUIRE_THROWS_AS(d.popBack(), std::out_of_range);
                } else {
                    REQUIRE(d.popBack() == ref.back());
                    ref.pop_back();
                }
                break;
            case 6: case 7: {
                int v = rand_int(0, 99);
                auto it = std::find(ref.begin(), ref.end(), v);
                bool expected = it != ref.end();
                REQUIRE(d.remove(v) == expected);
                if (expected) ref.erase(it);
                break;
            }
            case 8:
                if (ref.empty()) {
                    REQUIRE_THROWS_AS(d.front(), std::out_of_range);
                    REQUIRE_THROWS_AS(d.back(), std::out_of_range);
                } else {
                    REQUIRE(d.front() == ref.front());
                    REQUIRE(d.back() == ref.back());
                }
                break;
            default:
                REQUIRE(d.size() == ref.size());
                REQUIRE(d.empty() == ref.empty());
                break;
        }
        if (op % 1000 == 0) {
            REQUIRE(d.toVector() == std::vector<int>(ref.begin(), ref.end()));
        }
    }
    CHECK(d.toVector() == std::vector<int>(ref.begin(), ref.end()));
}
