#pragma once
#include <cstddef>
#include <random>
#include <string>
#include <vector>

// Fixed seed: a failing randomized test fails the same way every run.
inline std::mt19937& rng() {
    static std::mt19937 gen(20261006);
    return gen;
}

inline int rand_int(int lo, int hi) { return std::uniform_int_distribution<int>(lo, hi)(rng()); }

inline std::vector<int> rand_vec(std::size_t n, int lo, int hi) {
    std::vector<int> v(n);
    for (int& x : v) x = rand_int(lo, hi);
    return v;
}

inline std::string rand_string(std::size_t n, char lo = 'a', char hi = 'z') {
    std::string s(n, lo);
    for (char& c : s) c = static_cast<char>(rand_int(lo, hi));
    return s;
}
