#pragma once
#include <cstddef>
#include <cstdint>
#include <string>

// A polynomial rolling hash over a fixed string.
//   RollingHash(s)    : O(n) preprocessing.
//   hash(pos, len)    : hash of s.substr(pos, len) in O(1); 0 <= len, pos + len <= s.size().
// The hash value of a string must depend only on its characters (not on where it sits in s,
// and not on which RollingHash object computed it), so equal substrings hash equal.
class RollingHash {
public:
    explicit RollingHash(const std::string& s) {
        // TODO: implement
    }
    std::uint64_t hash(std::size_t pos, std::size_t len) const {
        // TODO: implement
        return 0;
    }

private:
    // Add your fields here.
};
