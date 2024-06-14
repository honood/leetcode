// HoNooD <honood@gmail.com>
// 2024.06.14 09:00

// 772. Basic Calculator III
// https://leetcode.com/problems/basic-calculator-iii/description/

// Constraints:
// The expression string contains only non-negative integers, `+`, `-`, `*`, `/`
// operators, and parentheses `(` and `)`.

#include <stack>
#include <cctype>
#include <cassert>
#include <iostream>
#include <iomanip>

using namespace std;

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int calculate(string s) {
    stack<int> nums{};
    stack<char> ops{};

    int n = s.size();
    for (int i = 0; i < n; ++i) {
      char c = s[i];
      if (std::isspace(c)) {
        continue;
      }

      if (std::isdigit(c)) {
        int num = 0;
        while (i < n && std::isdigit((c = s[i]))) {
          num = num * 10 + (c - '0');
          ++i;
        }
        nums.emplace(num);
        --i;
      } else if (c == '(') {
        ops.emplace(c);
      } else if (c == ')') {
        while (!ops.empty() && ops.top() != '(') {
          compute(nums, ops);
        }
        ops.pop();
      } else {
        while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
          compute(nums, ops);
        }
        ops.push(c);
      }
    }

    while (!ops.empty()) {
      compute(nums, ops);
    }

    return nums.top();
  }

private:
  void compute(stack<int>& nums, stack<char>& ops) {
    if (nums.size() < 2 || ops.empty()) {
      return;
    }

    int right = nums.top();
    nums.pop();
    int left = nums.top();
    nums.pop();

    char op = ops.top();
    ops.pop();

    int res = 0;
    switch (op) {
      case '+':
        res = left + right;
        break;
      case '-':
        res = left - right;
        break;
      case '*':
        res = left * right;
        break;
      case '/':
        res = left / right;
        break;
      default:
        assert(false);
    }

    nums.emplace(res);
  }

  int precedence(char op) {
    if (op == '+' || op == '-') {
      return 1;
    }

    if (op == '*' || op == '/') {
      return 2;
    }

    return 0;
  }
};

int main() {
  for (auto const& s: {"1+1", "6-4/2", "2*(5+5*2)/3+(6/2+8)", "(2+6* 3+5- (3*14/7+2)*5)+3"}) {
    int res = Solution{}.calculate(s);
    cout << std::quoted(s) << " = " << res << '\n';
  }

  return 0;
}
