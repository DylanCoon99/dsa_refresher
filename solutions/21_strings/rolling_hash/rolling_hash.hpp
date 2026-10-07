#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// Approach: prefix hashes H[i+1] = H[i] * B + s[i] (mod 2^64, by unsigned wrap-around) plus a table of powers of B;
//           hash(pos, len) = H[pos+len] - H[pos] * B^len.
// Key insight: H[pos+len] is the substring's hash shifted left by `len` digits plus the prefix's hash, so subtracting H[pos] * B^len leaves only the substring.
// Time: O(n) preprocessing, O(1) per query  Space: O(n)
// Brute force: recompute the hash of each queried substring character by character, O(len) per query.
class RollingHash {
public:
    explicit RollingHash(const std::string& s) : h_(s.size() + 1, 0), pw_(s.size() + 1, 1) {
        for (std::size_t i = 0; i < s.size(); ++i) {
            h_[i + 1] = h_[i] * kBase + static_cast<unsigned char>(s[i]) + 1;
            pw_[i + 1] = pw_[i] * kBase;
        }
    }
    std::uint64_t hash(std::size_t pos, std::size_t len) const {
        return h_[pos + len] - h_[pos] * pw_[len];
    }

private:
    static constexpr std::uint64_t kBase = 0x9E3779B97F4A7C15ULL;  // odd, fixed
    std::vector<std::uint64_t> h_, pw_;
};
