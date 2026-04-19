// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

static int Precedence(char oper) {
    if (oper == '(') return 0;
    if (oper == '+' || oper == '-') return 1;
    if (oper == '*' || oper == '/') return 2;
    return -1;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string output;

  for (size_t i = 0; i < inf.length(); i++) {
    char c = inf[i];
    if (isDigit(c)) {
      while (i < inf.length() && isDigit(inf[i])) {
        output += inf[i];
        i++;
      }
      output += ' ';
      i--;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        output += stack.pop();
        output += ' ';
      }
      stack.pop();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!stack.isEmpty() && Precedence(stack.top()) >= Precedence(c)) {
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

  if (!output.empty() && output[output.length() - 1] == ' ') {
    output.erase(output.length() - 1);
  }

  return output;
}

int eval(const std::string& pref) {
  TStack<int, 100> stack;

  for (size_t i = 0; i < pref.length(); i++) {
    char c = pref[i];

    if (isDigit(c)) {
      int n = 0;
      while (i < pref.length() && isDigit(pref[i])) {
        n = n * 10 + (pref[i] - '0');
        i++;
      }
      stack.push(n);
      i--;
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = stack.pop();
      int a = stack.pop();
      int r = 0;

      if (c == '+') {
        r = a + b;
      } else if (c == '-') {
        r = a - b;
      } else if (c == '*') {
        r = a * b;
      } else if (c == '/') {
        r = a / b;
      }

      stack.push(r);
    }
  }

  return stack.pop();
}
