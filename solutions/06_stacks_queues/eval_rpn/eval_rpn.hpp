#pragma once
#include <string>
#include <vector>

// Approach: push numbers; on an operator pop the right then left operand, apply, push the result.
// Key insight: a postfix operator always applies to the two most recent values, so a stack evaluates it in one pass.
// Time: O(n)  Space: O(n)
// Brute force: repeatedly scan for the first operator and collapse it with the two tokens before it, O(n^2).
inline int evalRPN(const std::vector<std::string>& tokens) {
    std::vector<int> st;
    for (const std::string& t : tokens) {
        if (t.size() == 1 && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
            int b = st.back();
            st.pop_back();
            int a = st.back();
            st.pop_back();
            switch (t[0]) {
                case '+': st.push_back(a + b); break;
                case '-': st.push_back(a - b); break;
                case '*': st.push_back(a * b); break;
                default: st.push_back(a / b); break;
            }
        } else {
            st.push_back(std::stoi(t));
        }
    }
    return st.back();
}
