#pragma once
#include <string>
#include <vector>
#include <map>

// Return true if every bracket in s ("()[]{}") is closed by the same type, in the right order.
// The empty string is balanced.
inline bool isValid(const std::string& s) {
    // TODO: implement

    // assume string only contains bracket chars

    // define a map (close -> open bracket)
    std::map<char, char> brackets = {{')', '('}, {']', '['}, {'}', '{'}};
    std::vector<char> stack;

    for (const auto c : s) {
        if (!brackets.contains(c)) {
            // it is an open bracket
            stack.push_back(c);
        } else {
            if (!stack.empty()) {
                // check if the bracket on the top of the stack matches the opening bracket for current c
                if (stack.back() == brackets[c]) {
                    // pop from the stack
                    stack.pop_back();
                } else {
                    return false;
                }
            } else {
                return false;
            }
            
        }     
    }

    return stack.empty();
}
