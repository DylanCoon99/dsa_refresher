#include <number_of_provinces.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <vector>

namespace {
using Matrix = std::vector<std::vector<int>>;

// Brute force: flood fill over the matrix from every unvisited city.
int brute(const Matrix& m) {
    int n = static_cast<int>(m.size());
    std::vector<bool> seen(n, false);
    int provinces = 0;
    for (int s = 0; s < n; ++s) {
        if (seen[s]) continue;
        ++provinces;
        std::vector<int> stack{s};
        seen[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int v = 0; v < n; ++v)
                if (m[u][v] == 1 && !seen[v]) {
                    seen[v] = true;
                    stack.push_back(v);
                }
        }
    }
    return provinces;
}

Matrix identity(int n) {
    Matrix m(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) m[i][i] = 1;
    return m;
}
}  // namespace

TEST_CASE("examples") {
    CHECK(findCircleNum({{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}) == 2);
    CHECK(findCircleNum({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}) == 3);
    CHECK(findCircleNum({{1}}) == 1);
}

TEST_CASE("edge cases") {
    SUBCASE("identity matrix returns n") {
        for (int n : {1, 2, 5, 12}) CHECK(findCircleNum(identity(n)) == n);
    }
    SUBCASE("all ones returns 1") {
        for (int n : {1, 2, 5, 12}) CHECK(findCircleNum(Matrix(n, std::vector<int>(n, 1))) == 1);
    }
    SUBCASE("n = 1") { CHECK(findCircleNum({{1}}) == 1); }
    SUBCASE("connected only through an intermediate city") {
        CHECK(findCircleNum({{1, 1, 0}, {1, 1, 1}, {0, 1, 1}}) == 1);
    }
    SUBCASE("a chain 0-1-2-3 and a lone city") {
        CHECK(findCircleNum({{1, 1, 0, 0, 0}, {1, 1, 1, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 1, 0}, {0, 0, 0, 0, 1}}) == 2);
    }
    SUBCASE("two pairs with interleaved labels") {
        CHECK(findCircleNum({{1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}}) == 2);
    }
}

TEST_CASE("randomized vs flood fill") {
    for (int trial = 0; trial < 300; ++trial) {
        int n = rand_int(1, 10);
        Matrix m = identity(n);
        int links = rand_int(0, 12);
        for (int i = 0; i < links; ++i) {
            int a = rand_int(0, n - 1), b = rand_int(0, n - 1);
            m[a][b] = m[b][a] = 1;
        }
        CHECK(findCircleNum(m) == brute(m));
    }
}
