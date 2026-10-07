#include <k_closest_points.hpp>

#include <doctest.h>
#include <printing.hpp>
#include <random_utils.hpp>

#include <algorithm>
#include <vector>

namespace {
using Points = std::vector<std::vector<int>>;

int dist2(const std::vector<int>& p) { return p[0] * p[0] + p[1] * p[1]; }

// Sort by value so any order of the answer compares equal.
Points normalize(Points p) {
    std::sort(p.begin(), p.end());
    return p;
}

// Brute force: sort by distance and keep the first k.
Points brute(Points p, int k) {
    std::sort(p.begin(), p.end(), [](const auto& a, const auto& b) { return dist2(a) < dist2(b); });
    p.resize(static_cast<std::size_t>(k));
    return p;
}

// True when the k-th and (k+1)-th closest points tie, i.e. the answer would not be unique.
bool ambiguous(Points p, std::size_t k) {
    if (k >= p.size()) return false;
    std::sort(p.begin(), p.end(), [](const auto& a, const auto& b) { return dist2(a) < dist2(b); });
    return dist2(p[k - 1]) == dist2(p[k]);
}

void check(const Points& points, int k, const Points& expected) {
    Points got = kClosest(points, k);
    CHECK(normalize(got) == normalize(expected));
}
}  // namespace

TEST_CASE("examples") {
    check({{1, 3}, {-2, 2}}, 1, {{-2, 2}});
    check({{3, 3}, {5, -1}, {-2, 4}}, 2, {{3, 3}, {-2, 4}});
    check({{0, 0}, {1, 1}}, 2, {{0, 0}, {1, 1}});
}

TEST_CASE("edge cases") {
    SUBCASE("single point") { check({{7, -7}}, 1, {{7, -7}}); }
    SUBCASE("k equals n returns everything") {
        check({{5, 5}, {-1, 0}, {0, 3}, {2, 2}}, 4, {{5, 5}, {-1, 0}, {0, 3}, {2, 2}});
    }
    SUBCASE("negative coordinates") {
        check({{-5, -5}, {-1, -2}, {-3, 0}, {4, -4}}, 2, {{-1, -2}, {-3, 0}});
    }
    SUBCASE("extreme coordinates") {
        check({{10000, 10000}, {-10000, -10000}, {10000, -9999}, {0, 0}}, 2, {{0, 0}, {10000, -9999}});
    }
    SUBCASE("points on the origin and equal duplicates inside the answer") {
        check({{0, 0}, {0, 0}, {9, 9}}, 2, {{0, 0}, {0, 0}});
    }
    SUBCASE("the closest point is last") { check({{9, 9}, {8, 8}, {7, 7}, {1, 0}}, 1, {{1, 0}}); }
}

TEST_CASE("randomized vs brute force") {
    int tested = 0;
    while (tested < 300) {
        int n = rand_int(1, 25);
        Points pts;
        for (int i = 0; i < n; ++i) pts.push_back({rand_int(-30, 30), rand_int(-30, 30)});
        int k = rand_int(1, n);
        if (ambiguous(pts, static_cast<std::size_t>(k))) continue;  // the answer must be unique
        check(pts, k, brute(pts, k));
        ++tested;
    }
}

TEST_CASE("large input" * doctest::timeout(2.0)) {
    // 10^5 points, k = 10. The ten closest are planted at distinct small distances (squared
    // distance <= 200); every other point has |x|, |y| >= 100 (squared distance >= 20000), so the
    // answer is unique and known in advance. An O(n log n) sort also passes this test.
    const int n = 100'000, k = 10;
    Points pts;
    pts.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x = rand_int(100, 10'000), y = rand_int(100, 10'000);
        if (rand_int(0, 1)) x = -x;
        if (rand_int(0, 1)) y = -y;
        pts.push_back({x, y});
    }
    Points expected;
    for (int j = 1; j <= k; ++j) {
        std::size_t pos = static_cast<std::size_t>(j) * 9973 % n;  // 9973 is coprime to 10^5: distinct slots
        pts[pos] = {j, -j};
        expected.push_back({j, -j});
    }
    check(pts, k, expected);
}
