// HoNooD <honood@gmail.com>
// 2024.06.13 09:00

// 227. Basic Calculator II
// https://leetcode.com/problems/basic-calculator-ii/description/

// Constraints:
// `s` consists of integers and operators ('+', '-', '*', '/') separated by some
// number of spaces.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int calculate(string s) {
    // append a '+' to handle the last number in the string
    s += '+';

    stack<int> stack{};
    int num = 0;
    char op = '+';
    for (auto const& c : s) {
      if (std::isspace(c)) {
        continue;
      }

      if (std::isdigit(c)) {
        num = num * 10 + (c - '0');
      } else {
        // perform the previous operation
        if (op == '+') {
          stack.emplace(num);
        } else if (op == '-') {
          stack.emplace(-num);
        } else if (op == '*') {
          int top = stack.top();
          stack.pop();
          stack.emplace(top * num);
        } else if (op == '/') {
          int top = stack.top();
          stack.pop();
          stack.emplace(top / num);
        }

        op = c;
        num = 0;
      } // else
    }

    int res = 0;
    while (!stack.empty()) {
      res += stack.top();
      stack.pop();
    }

    return res;
  }
};

// Not use `std::stack`
class Solution_2 {
public:
  int calculate(string s) {
    int res = 0;
    int lastNum = 0;
    char op = '+';
    int n = s.size();
    for (int i = 0; i < n; ++i) {
      if (std::isspace(s[i])) {
        continue;
      }

      int num = 0;
      // read the full number
      while (i < n && std::isdigit(s[i])) {
        num = num * 10 + (s[i] - '0');
        ++i;
      }

      // apply the last seen operation
      if (op == '+' || op == '-') {
        res += lastNum;
        lastNum = op == '+' ? num : -num;
      } else if (op == '*') {
        lastNum *= num;
      } else if (op == '/') {
        lastNum /= num;
      }

      // update the operation
      if (i < n) {
        op = s[i];
      }
    }
    // add the last number to the result
    res += lastNum;

    return res;
  }
};
