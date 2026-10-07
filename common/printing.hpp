#pragma once
// doctest printers, so failed CHECKs show container contents instead of "{?}".
#include <doctest.h>

#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace dsa_print {

inline std::string to_text(const std::string& s) { return "\"" + s + "\""; }
inline std::string to_text(char c) { return std::string("'") + c + "'"; }
inline std::string to_text(bool b) { return b ? "true" : "false"; }
template <typename T>
    requires std::is_arithmetic_v<T>
std::string to_text(T v) { return std::to_string(v); }

// Declared before the definitions so nested containers resolve each other.
template <typename T> std::string to_text(const std::optional<T>& o);
template <typename A, typename B> std::string to_text(const std::pair<A, B>& p);
template <typename T> std::string to_text(const std::vector<T>& v);

template <typename T>
std::string to_text(const std::optional<T>& o) { return o ? to_text(*o) : "null"; }

template <typename A, typename B>
std::string to_text(const std::pair<A, B>& p) {
    return "(" + to_text(p.first) + ", " + to_text(p.second) + ")";
}

template <typename T>
std::string to_text(const std::vector<T>& v) {
    std::string out = "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) out += ", ";
        out += to_text(static_cast<const T&>(v[i]));
    }
    return out + "]";
}

}  // namespace dsa_print

namespace doctest {
template <typename T> struct StringMaker<std::vector<T>> {
    static String convert(const std::vector<T>& v) { return dsa_print::to_text(v).c_str(); }
};
template <typename T> struct StringMaker<std::optional<T>> {
    static String convert(const std::optional<T>& o) { return dsa_print::to_text(o).c_str(); }
};
template <typename A, typename B> struct StringMaker<std::pair<A, B>> {
    static String convert(const std::pair<A, B>& p) { return dsa_print::to_text(p).c_str(); }
};
}  // namespace doctest
