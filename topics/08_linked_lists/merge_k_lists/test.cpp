#include <merge_k_lists.hpp>

#include <doctest.h>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
// Builds the lists, merges them, and compares with "concatenate everything and sort".
void check_merge(const std::vector<std::vector<int>>& inputs) {
    std::vector<ListNode*> heads;
    std::vector<int> all;
    for (const auto& vals : inputs) {
        heads.push_back(build_list(vals));
        all.insert(all.end(), vals.begin(), vals.end());
    }
    std::sort(all.begin(), all.end());
    CHECK(to_vector(mergeKLists(heads)) == all);
}
}  // namespace

TEST_CASE("examples") {
    check_merge({{1, 4, 5}, {1, 3, 4}, {2, 6}});
    std::vector<ListNode*> none;
    CHECK(mergeKLists(none) == nullptr);
    std::vector<ListNode*> one_null{nullptr};
    CHECK(mergeKLists(one_null) == nullptr);
}

TEST_CASE("edge cases") {
    SUBCASE("empty vector") {
        std::vector<ListNode*> none;
        CHECK(mergeKLists(none) == nullptr);
    }
    SUBCASE("vector of nullptrs") {
        std::vector<ListNode*> nulls(5, nullptr);
        CHECK(mergeKLists(nulls) == nullptr);
    }
    SUBCASE("one list") { check_merge({{1, 2, 3}}); }
    SUBCASE("one list among nullptrs") { check_merge({{}, {2, 5}, {}}); }
    SUBCASE("single-node lists in reverse order") { check_merge({{3}, {2}, {1}, {0}}); }
    SUBCASE("all values equal across lists") { check_merge({{5, 5}, {5}, {5, 5, 5}}); }
    SUBCASE("odd and even list counts") {
        check_merge({{1, 9}, {2, 8}, {3, 7}});
        check_merge({{1, 9}, {2, 8}, {3, 7}, {4, 6}});
    }
    SUBCASE("lists of very different lengths") { check_merge({{1, 2, 3, 4, 5, 6, 7, 8}, {4}, {}, {0, 9}}); }
    SUBCASE("extreme values") { check_merge({{-2147483647 - 1, 2147483647}, {0}}); }
}

TEST_CASE("randomized vs sort-all") {
    for (int trial = 0; trial < 300; ++trial) {
        int k = rand_int(0, 8);
        std::vector<std::vector<int>> inputs;
        for (int i = 0; i < k; ++i) {
            std::vector<int> vals = rand_vec(rand_int(0, 6), -20, 20);
            std::sort(vals.begin(), vals.end());
            inputs.push_back(vals);
        }
        check_merge(inputs);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^4 lists x 10 nodes. Merging lists one at a time into an accumulator is ~5*10^8 node steps.
    const int k = 10'000;
    std::vector<ListNode*> heads;
    std::vector<int> all;
    for (int i = 0; i < k; ++i) {
        std::vector<int> vals = rand_vec(10, -1'000'000, 1'000'000);
        std::sort(vals.begin(), vals.end());
        heads.push_back(build_list(vals));
        all.insert(all.end(), vals.begin(), vals.end());
    }
    std::sort(all.begin(), all.end());
    ListNode* merged = mergeKLists(heads);
    REQUIRE(merged != nullptr);
    CHECK(to_vector(merged) == all);
}
