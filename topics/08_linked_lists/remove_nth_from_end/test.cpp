#include <remove_nth_from_end.hpp>

#include <doctest.h>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
std::vector<int> removed(const std::vector<int>& vals, int n) {
    return to_vector(removeNthFromEnd(build_list(vals), n));
}
}  // namespace

TEST_CASE("examples") {
    CHECK(removed({1, 2, 3, 4, 5}, 2) == std::vector<int>{1, 2, 3, 5});
    CHECK(removeNthFromEnd(build_list({1}), 1) == nullptr);
    CHECK(removed({1, 2}, 2) == std::vector<int>{2});
}

TEST_CASE("edge cases") {
    SUBCASE("single node becomes nullptr") { CHECK(removeNthFromEnd(build_list({5}), 1) == nullptr); }
    SUBCASE("remove the head (n = length)") {
        CHECK(removed({1, 2, 3}, 3) == std::vector<int>{2, 3});
        CHECK(removed({1, 2, 3, 4, 5}, 5) == std::vector<int>{2, 3, 4, 5});
    }
    SUBCASE("remove the tail (n = 1)") {
        CHECK(removed({1, 2, 3}, 1) == std::vector<int>{1, 2});
        CHECK(removed({1, 2}, 1) == std::vector<int>{1});
    }
    SUBCASE("remove a middle node") {
        CHECK(removed({1, 2, 3, 4}, 3) == std::vector<int>{1, 3, 4});
        CHECK(removed({1, 2, 3}, 2) == std::vector<int>{1, 3});
    }
    SUBCASE("duplicate values: the position decides, not the value") {
        CHECK(removed({4, 4, 4, 9}, 2) == std::vector<int>{4, 4, 9});
        CHECK(removed({9, 4, 4, 4}, 4) == std::vector<int>{4, 4, 4});
    }
    SUBCASE("the returned head is the original head when it is not removed") {
        ListNode* head = build_list({1, 2, 3});
        ListNode* r = removeNthFromEnd(head, 1);
        CHECK(r == head);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> vals = rand_vec(rand_int(1, 30), -50, 50);
        int n = rand_int(1, static_cast<int>(vals.size()));
        std::vector<int> expected = vals;
        expected.erase(expected.end() - n);
        CHECK(removed(vals, n) == expected);
    }
}
