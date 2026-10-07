# Stage 1a: Build Infrastructure (Tasks 1–2)

Read `00-index.md` first. Its Global Constraints apply to every task here.

---

### Task 1: CMake, doctest, and `common/` helpers

**Files:**
- Create: `CMakeLists.txt`
- Create: `third_party/doctest/doctest.h` (downloaded)
- Create: `common/test_main.cpp`, `common/printing.hpp`, `common/list_node.hpp`, `common/tree_node.hpp`, `common/graph.hpp`, `common/random_utils.hpp`
- Test: `tests/common_test.cpp`

**Interfaces:**
- Produces (used by every later task):
  - CMake targets `ex_NN_<name>` / `sol_NN_<name>`, with binaries in `build/bin/`, plus the library `dsa_test_main`.
  - `printing.hpp`: `dsa_print::to_text(...)`, and doctest `StringMaker` specializations for `std::vector<T>`, `std::optional<T>` and `std::pair<A,B>`.
  - `list_node.hpp`:
    - `struct ListNode { int val; ListNode* next; }`;
    - `ListNode* build_list(const std::vector<int>&)`;
    - `ListNode* build_list_with_cycle(const std::vector<int>&, int pos)`;
    - `std::vector<int> to_vector(const ListNode*, std::size_t limit = 1'000'000)`, which throws `std::runtime_error` past `limit`;
    - `struct RandomListNode { int val; RandomListNode* next; RandomListNode* random; }`;
    - `RandomListNode* build_random_list(const std::vector<std::pair<int,int>>&)`;
    - `std::vector<std::pair<int,int>> to_random_spec(const RandomListNode*, std::size_t limit = 1'000'000)`.
  - `tree_node.hpp`:
    - `struct TreeNode { int val; TreeNode* left; TreeNode* right; }`;
    - `inline constexpr std::nullopt_t null`;
    - `using LevelOrder = std::vector<std::optional<int>>`;
    - `TreeNode* build_tree(const LevelOrder&)`;
    - `LevelOrder to_level_order(const TreeNode*, std::size_t limit = 1'000'000)`;
    - `TreeNode* find_node(TreeNode*, int)`;
    - `TreeNode* build_chain(int n)`;
    - `TreeNode* build_balanced_bst(const std::vector<int>& sorted)`.
  - `graph.hpp`:
    - `using Graph = std::vector<std::vector<int>>`;
    - `using WeightedGraph = std::vector<std::vector<std::pair<int,int>>>`;
    - `Graph edges_to_graph(int n, const std::vector<std::vector<int>>& edges, bool directed)`;
    - `WeightedGraph weighted_edges_to_graph(int n, const std::vector<std::vector<int>>& edges, bool directed)`.
  - `random_utils.hpp`:
    - `std::mt19937& rng()`;
    - `int rand_int(int lo, int hi)`;
    - `std::vector<int> rand_vec(std::size_t n, int lo, int hi)`;
    - `std::string rand_string(std::size_t n, char lo = 'a', char hi = 'z')`.

- [ ] **Step 1: Vendor doctest**

```bash
mkdir -p third_party/doctest
curl -fsSL https://raw.githubusercontent.com/doctest/doctest/v2.4.11/doctest/doctest.h -o third_party/doctest/doctest.h
head -c 400 third_party/doctest/doctest.h | grep -q "doctest" && echo ok
```
Expected: `ok`

- [ ] **Step 2: Write `CMakeLists.txt`**

```cmake
cmake_minimum_required(VERSION 3.20)
project(dsa_refresher CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_compile_options(-Wall -Wextra -Wno-unused-parameter)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

# doctest's main(), compiled once and linked into every test binary.
add_library(dsa_test_main STATIC common/test_main.cpp)
target_include_directories(dsa_test_main PUBLIC third_party/doctest common)

add_executable(common_tests tests/common_test.cpp)
target_link_libraries(common_tests PRIVATE dsa_test_main)

# Each topics/NN_topic/<name>/test.cpp becomes ex_NN_<name> (built against the
# learner's header) and, if a reference exists, sol_NN_<name> (built against
# solutions/). Tests include the header with <angle brackets>, so only the -I
# path decides which one is used.
file(GLOB EXERCISE_TESTS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/topics/*/*/test.cpp)
file(GLOB SOLUTION_HEADERS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/solutions/*/*/*.hpp)

foreach(test_cpp IN LISTS EXERCISE_TESTS)
  get_filename_component(ex_dir ${test_cpp} DIRECTORY)
  get_filename_component(ex_name ${ex_dir} NAME)
  get_filename_component(topic_dir ${ex_dir} DIRECTORY)
  get_filename_component(topic_name ${topic_dir} NAME)
  string(SUBSTRING ${topic_name} 0 2 topic_num)

  add_executable(ex_${topic_num}_${ex_name} ${test_cpp})
  target_include_directories(ex_${topic_num}_${ex_name} PRIVATE ${ex_dir})
  target_link_libraries(ex_${topic_num}_${ex_name} PRIVATE dsa_test_main)

  set(sol_dir ${CMAKE_SOURCE_DIR}/solutions/${topic_name}/${ex_name})
  if(EXISTS ${sol_dir}/${ex_name}.hpp)
    add_executable(sol_${topic_num}_${ex_name} ${test_cpp})
    target_include_directories(sol_${topic_num}_${ex_name} PRIVATE ${sol_dir})
    target_link_libraries(sol_${topic_num}_${ex_name} PRIVATE dsa_test_main)
  endif()
endforeach()
```

- [ ] **Step 3: Write the failing helper tests (`tests/common_test.cpp`)**

```cpp
#include <doctest.h>
#include <graph.hpp>
#include <list_node.hpp>
#include <printing.hpp>
#include <random_utils.hpp>
#include <tree_node.hpp>

#include <stdexcept>

TEST_CASE("list round trip") {
    CHECK(to_vector(build_list({1, 2, 3})) == std::vector<int>{1, 2, 3});
    CHECK(build_list({}) == nullptr);
    CHECK(to_vector(nullptr).empty());
}

TEST_CASE("cyclic list fails instead of hanging") {
    ListNode* head = build_list_with_cycle({1, 2, 3}, 1);
    REQUIRE(head->next->next->next == head->next);
    CHECK_THROWS_AS(to_vector(head, 100), std::runtime_error);
    CHECK(to_vector(build_list_with_cycle({1, 2}, -1)) == std::vector<int>{1, 2});
}

TEST_CASE("random list round trip") {
    std::vector<std::pair<int, int>> spec{{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}};
    CHECK(to_random_spec(build_random_list(spec)) == spec);
    CHECK(build_random_list({}) == nullptr);
}

TEST_CASE("tree round trip") {
    LevelOrder lo{3, 9, 20, null, null, 15, 7};
    CHECK(to_level_order(build_tree(lo)) == lo);
    CHECK(to_level_order(build_tree({1, null, 2, null, null})) == LevelOrder{1, null, 2});
    CHECK(build_tree({}) == nullptr);
    CHECK(to_level_order(nullptr).empty());
}

TEST_CASE("cyclic tree fails instead of hanging") {
    TreeNode* root = build_tree({1, 2});
    root->left->left = root;
    CHECK_THROWS_AS(to_level_order(root, 100), std::runtime_error);
}

TEST_CASE("tree helpers") {
    TreeNode* root = build_tree({6, 2, 8, 0, 4, 7, 9});
    REQUIRE(find_node(root, 4) != nullptr);
    CHECK(find_node(root, 4)->val == 4);
    CHECK(find_node(root, 5) == nullptr);
    TreeNode* chain = build_chain(100000);
    int depth = 0;
    for (TreeNode* n = chain; n; n = n->right) ++depth;
    CHECK(depth == 100000);
    CHECK(to_level_order(build_balanced_bst({1, 2, 3})) == LevelOrder{2, 1, 3});
}

TEST_CASE("printing") {
    CHECK(dsa_print::to_text(std::vector<int>{1, 2}) == "[1, 2]");
    CHECK(dsa_print::to_text(std::vector<std::vector<int>>{{1}, {}}) == "[[1], []]");
    CHECK(dsa_print::to_text(LevelOrder{1, null}) == "[1, null]");
    CHECK(dsa_print::to_text(std::vector<std::string>{"a"}) == "[\"a\"]");
    CHECK(dsa_print::to_text(std::pair<int, char>{1, 'x'}) == "(1, 'x')");
}

TEST_CASE("graph helpers") {
    Graph g = edges_to_graph(3, {{0, 1}, {1, 2}}, false);
    CHECK(g == Graph{{1}, {0, 2}, {1}});
    Graph d = edges_to_graph(3, {{0, 1}, {1, 2}}, true);
    CHECK(d == Graph{{1}, {2}, {}});
    WeightedGraph w = weighted_edges_to_graph(2, {{0, 1, 5}}, true);
    CHECK(w[0] == std::vector<std::pair<int, int>>{{1, 5}});
}

TEST_CASE("random utils stay in range") {
    for (int v : rand_vec(1000, -5, 5)) { CHECK(v >= -5); CHECK(v <= 5); }
    for (char c : rand_string(1000, 'a', 'c')) { CHECK(c >= 'a'); CHECK(c <= 'c'); }
}
```

- [ ] **Step 4: Run it to see it fail**

```bash
printf '#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN\n#include <doctest.h>\n' > common/test_main.cpp
cmake -S . -B build && cmake --build build --target common_tests
```
Expected: the build fails with `'graph.hpp' file not found` (the helpers don't exist yet).

- [ ] **Steps 5–8: Write the five helper headers**

Create `common/printing.hpp`, `common/list_node.hpp`, `common/tree_node.hpp`, `common/graph.hpp` and `common/random_utils.hpp` **exactly** as given in `01b-common-helpers.md`, which holds the full source for each file.

- [ ] **Step 9: Run the helper tests**

```bash
cmake -S . -B build && cmake --build build --target common_tests && build/bin/common_tests
```
Expected: `[doctest] test cases: 9 | 9 passed | 0 failed`

- [ ] **Step 10: Commit**

```bash
git add CMakeLists.txt third_party common tests/common_test.cpp
git commit -m "Add CMake build, vendored doctest, and shared test helpers"
```

---

### Task 2: Worked example `02_arrays_hashing/two_sum`

This is the reference exercise. Every later exercise is modelled on these four files.

**Files:**
- Create: `topics/02_arrays_hashing/two_sum/PROBLEM.md`, `two_sum.hpp`, `test.cpp`
- Create: `solutions/02_arrays_hashing/two_sum/two_sum.hpp`
- Create: `.starter/02_arrays_hashing/two_sum/two_sum.hpp`

**Interfaces:**
- Consumes: `dsa_test_main`, `printing.hpp`, `random_utils.hpp` (Task 1).
- Produces: `std::vector<int> twoSum(const std::vector<int>& nums, int target)` and targets `ex_02_two_sum` / `sol_02_two_sum` (Task 3's script and self-test refer to these by name).

- [ ] **Step 1: Write `PROBLEM.md`**

```markdown
# Two Sum
**Topic:** 02 Arrays and Hashing · **Kind:** Practice · **Difficulty:** Easy
**Plan reference:** LeetCode "Two Sum" (title kept for cross-reference only)

## Problem
You are given a list of integers `nums` and an integer `target`. Find two *different
positions* `i` and `j` with `i < j` such that `nums[i] + nums[j] == target`, and return
them as `{i, j}`. At least one such pair exists. If more than one does, any is accepted.
A single element may not be paired with itself.

## Examples
- `nums = {2, 7, 11, 15}, target = 9` → `{0, 1}` (2 + 7 = 9)
- `nums = {3, 2, 4}, target = 6` → `{1, 2}`; positions 0 and 0 would reuse the 3
- `nums = {3, 3}, target = 6` → `{0, 1}`

## Constraints
- 2 ≤ n ≤ 2·10⁵
- −10⁹ ≤ nums[i], target ≤ 10⁹

## Target
Time: O(n) · Space: O(n)

## CLRS (optional, ≈10 min)
- §11.2 (3e) / §11.2 (4e), "Hash tables": read the intro and the theorem statements on expected search time with chaining. Skip the proofs.
- Skip if: you can explain why a hash-map lookup is O(1) on average but O(n) in the worst case.

## Hints
<details><summary>Hint 1</summary>For a fixed j, which value would nums[i] have to be?</details>
<details><summary>Hint 2</summary>Can you remember the values you've already passed so that question becomes an O(1) lookup?</details>
```

- [ ] **Step 2: Write `test.cpp`**

```cpp
#include <two_sum.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
// Several pairs may be valid, so check the contract rather than one exact answer.
void check_pair(const std::vector<int>& nums, int target) {
    std::vector<int> got = twoSum(nums, target);
    REQUIRE(got.size() == 2);
    const int i = got[0], j = got[1];
    REQUIRE(0 <= i);
    REQUIRE(i < j);
    REQUIRE(j < static_cast<int>(nums.size()));
    CHECK(static_cast<long long>(nums[i]) + nums[j] == target);
}
}  // namespace

TEST_CASE("examples") {
    CHECK(twoSum({2, 7, 11, 15}, 9) == std::vector<int>{0, 1});
    CHECK(twoSum({3, 2, 4}, 6) == std::vector<int>{1, 2});
    CHECK(twoSum({3, 3}, 6) == std::vector<int>{0, 1});
}

TEST_CASE("edge cases") {
    SUBCASE("minimum size") { check_pair({1, 2}, 3); }
    SUBCASE("negatives and zero target") { check_pair({-3, 4, 3, 90}, 0); }
    SUBCASE("pair at the end") { check_pair({5, 6, 7, 1, 9}, 10); }
    SUBCASE("duplicates where only one copy is usable") { check_pair({4, 4, 1}, 5); }
    SUBCASE("extreme values") { check_pair({-1'000'000'000, 7, 1'000'000'000}, 0); }
}

TEST_CASE("randomized vs brute force") {
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<int> nums = rand_vec(rand_int(2, 40), -50, 50);
        int i = rand_int(0, static_cast<int>(nums.size()) - 2);
        int j = rand_int(i + 1, static_cast<int>(nums.size()) - 1);
        check_pair(nums, nums[i] + nums[j]);
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // Evens 0, 2, 4, ... plus two odd values at the end: the only valid pair is the last two,
    // so an O(n^2) pair scan has to do ~2·10^10 checks.
    const int n = 200'000;
    std::vector<int> nums;
    for (int k = 0; k < n - 2; ++k) nums.push_back(2 * k);
    nums.push_back(500'000'001);
    nums.push_back(500'000'003);
    CHECK(twoSum(nums, 1'000'000'004) == std::vector<int>{n - 2, n - 1});
}
```

- [ ] **Step 3: Write the stub `two_sum.hpp` and its starter copy**

```cpp
#pragma once
#include <vector>

// Return {i, j} with i < j and nums[i] + nums[j] == target.
// At least one valid pair exists; return any of them.
inline std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    // TODO: implement
    return {};
}
```

```bash
mkdir -p .starter/02_arrays_hashing/two_sum
cp topics/02_arrays_hashing/two_sum/two_sum.hpp .starter/02_arrays_hashing/two_sum/
```

- [ ] **Step 4: Run against the stub (red)**

```bash
cmake -S . -B build && cmake --build build --target ex_02_two_sum && build/bin/ex_02_two_sum
```
Expected: exit code 1 and `test cases: 4 | 0 passed | 4 failed`, with no sanitizer report. The REQUIREs stop each case before it reads an index.

- [ ] **Step 5: Write the reference solution**

`solutions/02_arrays_hashing/two_sum/two_sum.hpp`:

```cpp
#pragma once
#include <unordered_map>
#include <vector>

// Approach: one pass; a hash map from value to its earliest index answers
//           "have I already seen target - x?" in O(1).
// Key insight: remembering the values you've passed turns the inner search loop into a lookup.
// Time: O(n) average  Space: O(n)
// Brute force: check every pair i < j, O(n^2) time.
inline std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<long long, int> seen;
    for (int j = 0; j < static_cast<int>(nums.size()); ++j) {
        auto it = seen.find(static_cast<long long>(target) - nums[j]);
        if (it != seen.end()) return {it->second, j};
        seen.emplace(nums[j], j);  // emplace keeps the earliest index for duplicates
    }
    return {};
}
```

- [ ] **Step 6: Run against the solution (green)**

```bash
cmake -S . -B build && cmake --build build --target sol_02_two_sum && build/bin/sol_02_two_sum --duration=true
```
Expected: `test cases: 4 | 4 passed | 0 failed`, and the "large input" case takes under 0.5 s.

- [ ] **Step 7: Commit**

```bash
git add topics/02_arrays_hashing/two_sum solutions/02_arrays_hashing/two_sum .starter/02_arrays_hashing/two_sum
git commit -m "Add worked example exercise: two_sum"
```
