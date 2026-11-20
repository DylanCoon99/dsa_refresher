#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

// Evaluate a postfix expression. Tokens are decimal integers (maybe negative) or + - * /.
// Division truncates toward zero. The input is valid; no division by zero; results fit in int.
inline int evalRPN(const std::vector<std::string>& tokens) {
    // TODO: implement

    std::vector<int> stack;
    std::unordered_set<std::string> operators = {"+", "-", "*", "/"};

    for (std::string token : tokens) {
        // if the token is an operator, pop 2 items from the stack and push the result
        if (operators.contains(token)) {


            int operand2 = stack.back();
            stack.pop_back();
            int operand1 = stack.back();
            stack.pop_back();

            if (token == "+") {
                // addition
                stack.push_back(operand1 + operand2);
            } else if (token == "-") {
                // subtraction
                stack.push_back(operand1 - operand2);
            } else if (token == "*") {
                // multiplication
                stack.push_back(operand1 * operand2);
            } else {
                // division
                stack.push_back(operand1 / operand2);
            }
        } else {
            stack.push_back(std::stoi(token));
        }   
    }

    return stack.back();
}
