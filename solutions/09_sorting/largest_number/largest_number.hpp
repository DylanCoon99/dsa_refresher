#pragma once
#include <algorithm>
#include <string>
#include <vector>

// Approach: sort the decimal strings with the comparator "a before b if a+b > b+a", then concatenate.
// Key insight: compare the two concatenation orders directly; value order and string order are both wrong.
// Time: O(n log n * L)  Space: O(n * L)
// Brute force: try all n! orderings and keep the largest concatenation.
inline std::string largestNumber(const std::vector<int>& nums) {
    std::vector<std::string> parts;
    for (int x : nums) parts.push_back(std::to_string(x));
    std::sort(parts.begin(), parts.end(),
              [](const std::string& a, const std::string& b) { return a + b > b + a; });
    if (parts.empty() || parts[0] == "0") return "0";  // the largest piece is 0, so everything is 0
    std::string out;
    for (const std::string& p : parts) out += p;
    return out;
}
