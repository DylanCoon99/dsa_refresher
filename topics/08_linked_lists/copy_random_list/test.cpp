#include <copy_random_list.hpp>

#include <doctest.h>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>

#include <unordered_set>
#include <utility>
#include <vector>

using Spec = std::vector<std::pair<int, int>>;

namespace {
// Copies the list built from spec and checks every property of a correct deep copy.
void check_copy(const Spec& spec) {
    RandomListNode* original = build_random_list(spec);
    std::unordered_set<const RandomListNode*> originals;
    for (const RandomListNode* p = original; p != nullptr; p = p->next) originals.insert(p);

    RandomListNode* copy = copyRandomList(original);
    if (spec.empty()) {
        CHECK(copy == nullptr);
        return;
    }
    REQUIRE(copy != nullptr);
    // A -2 entry would mean a random pointer leads outside the copy (e.g. into the original).
    CHECK(to_random_spec(copy) == spec);
    // No copied node may be an original node.
    bool shares = false;
    for (const RandomListNode* p = copy; p != nullptr; p = p->next) {
        if (originals.count(p)) shares = true;
    }
    CHECK_FALSE(shares);
    // The original is unchanged: same structure, values and random targets.
    CHECK(to_random_spec(original) == spec);
    // And its nodes are exactly the ones it started with.
    std::size_t count = 0;
    bool same_nodes = true;
    for (const RandomListNode* p = original; p != nullptr; p = p->next) {
        ++count;
        if (!originals.count(p)) same_nodes = false;
    }
    CHECK(same_nodes);
    CHECK(count == spec.size());
}
}  // namespace

TEST_CASE("examples") {
    check_copy({{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}});
    check_copy({{1, 0}});
    check_copy({});
}

TEST_CASE("edge cases") {
    SUBCASE("empty list") { CHECK(copyRandomList(nullptr) == nullptr); }
    SUBCASE("single node, random null") { check_copy({{5, -1}}); }
    SUBCASE("single node, random to itself") { check_copy({{5, 0}}); }
    SUBCASE("every random points to itself") { check_copy({{1, 0}, {2, 1}, {3, 2}}); }
    SUBCASE("every random is null") { check_copy({{1, -1}, {2, -1}, {3, -1}}); }
    SUBCASE("randoms point forward and backward") { check_copy({{1, 2}, {2, 0}, {3, 1}}); }
    SUBCASE("all randoms point to the same node") { check_copy({{1, 3}, {2, 3}, {3, 3}, {4, 3}}); }
    SUBCASE("duplicate values do not confuse the mapping") { check_copy({{4, 1}, {4, 0}, {4, -1}, {4, 2}}); }
    SUBCASE("extreme values") { check_copy({{-2147483647 - 1, 1}, {2147483647, 0}}); }
    SUBCASE("copy has the right length and terminates") {
        RandomListNode* copy = copyRandomList(build_random_list({{1, -1}, {2, 0}}));
        REQUIRE(copy != nullptr);
        REQUIRE(copy->next != nullptr);
        CHECK(copy->next->next == nullptr);
    }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(0, 20);
        Spec spec;
        for (int i = 0; i < n; ++i) spec.emplace_back(rand_int(-20, 20), rand_int(-1, n - 1));
        check_copy(spec);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 nodes with random targets spread over the whole list: finding each target by walking
    // from the head is ~5*10^9 steps in total.
    const int n = 100'000;
    Spec spec;
    spec.reserve(n);
    for (int i = 0; i < n; ++i) spec.emplace_back(i, rand_int(-1, n - 1));
    RandomListNode* original = build_random_list(spec);
    RandomListNode* copy = copyRandomList(original);
    REQUIRE(copy != nullptr);
    CHECK(to_random_spec(copy) == spec);
    CHECK(copy != original);
}
