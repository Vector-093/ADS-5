// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <cctype>

static int Precedence(char oper) {
    if (oper == '+'  oper == '-') return 1;
    if (oper == '*'  oper == '/') return 2;
    return 0;
}

static bool isOperator(char c) {
    return c == '+'  c == '-'  c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    std::string output;
    TStack<char, 100> stack;

    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];

        if (std::isdigit(c)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                output += inf[i];
                ++i;
            }
            output += ' ';
            --i;
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                output += stack.pop();
                output += ' ';
            }
            if (!stack.isEmpty() && stack.top() == '(') {
                stack.pop();
            }
        }
        else if (isOperator(c)) {
            while (!stack.isEmpty() && stack.top() != '(' &&
                   Precedence(c) <= Precedence(stack.top())) {
                output += stack.pop();
                output += ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        output += stack.pop();
        output += ' ';
    }

    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }
    return output;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < pref.length(); ++i) {
        char c = pref[i];

        if (std::isspace(c)) {
            continue;
        }

        if (std::isdigit(c)) {
            int n = 0;
            while (i < pref.length() && std::isdigit(pref[i])) {
                n = n * 10 + (pref[i] - '0');
                ++i;
            }
            --i;
            stack.push(num);
        }
        else if (isOperator(c)) {
            int b = stack.pop();
            int a = stack.pop();
            int result = 0;
            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            stack.push(result);
        }
    }

    return stack.pop();
}
