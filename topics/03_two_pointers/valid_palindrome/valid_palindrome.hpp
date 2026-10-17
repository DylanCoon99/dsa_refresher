#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

// Return true if s is a palindrome considering only letters and digits, ignoring case.
inline bool isPalindrome(const std::string& s) {
    // TODO: implement

    // remove all non alpha numeric characters
    std::string new_str = s;
    // lowercase everything

    new_str.erase(std::remove_if(new_str.begin(), new_str.end(), [](unsigned char c) {
        return !std::isalnum(c);
    }), new_str.end());

    std::transform(new_str.begin(), new_str.end(), new_str.begin(), 
                   [](unsigned char c) { return std::tolower(c); });


    // have a pointer at the beginning and a ptr at the end
    auto right_iter = std::prev(new_str.end());
    auto left_iter = new_str.begin();

    while (left_iter <= right_iter) {
        if (*right_iter != *left_iter) {
            return false;
        }
        --right_iter;
        ++left_iter;
    }

    return true;
}
