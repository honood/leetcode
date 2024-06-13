// HoNooD <honood@gmail.com>
// 2024.06.12 11:00

// 224. Basic Calculator
// https://leetcode.com/problems/basic-calculator/description/?envType=study-plan-v2&envId=top-interview-150

// Constraints:
// 1. `s` consists of digits, '+', '-', '(', ')', and ' ';
// 2. '+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
// 3. '-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
// 4. There will be no two consecutive operators in the input.
// 5. Every number and running calculation will fit in a signed 32-bit integer.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// clearer logic
class Solution {
public:
  int calculate(string s) {
    stack<int> nums{};
    stack<int> ops{}; // store sign

    int res = 0;
    int sign = 1; // 1 for `+`, -1 for `-`
    int n = s.size();
    for (int i = 0; i < n; ++i) {
      char c = s[i];
      if (std::isdigit(c)) {
        int num = 0;
        while (i < n && std::isdigit((c = s[i]))) {
          num = num * 10 + (c - '0');
          ++i;
        }
        --i; // adjust for the next iteration of `i`
        res += sign * num;
      } else if (c == '+') {
        sign = 1;
      } else if (c == '-') {
        sign = -1;
      } else if (c == '(') {
        nums.emplace(res);
        res = 0;
        ops.emplace(sign);
        sign = 1;
      } else if (c == ')') {
        res = ops.top() * res + nums.top();
        ops.pop();
        nums.pop();
      }
      // skip space character
    }

    return res;
  }
};

// maybe more compact in handling multi-digit numbers, however, less intuitive
// and verbose.
class Solution_2 {
public:
  int calculate(string s) {
    stack<int> stack{};

    int res = 0;
    int num = 0;
    int sign = 1; // 1 for `+`, -1 for `-`
    for (auto const& c : s) {
      if (std::isdigit(c)) {
        num = num * 10 + (c - '0');
      } else if (c == '+') {
        res += sign * num;
        num = 0;
        sign = 1;
      } else if (c == '-') {
        res += sign * num;
        num = 0;
        sign = -1;
      } else if (c == '(') {
        stack.emplace(res);
        res = 0;
        stack.emplace(sign);
        sign = 1;
      } else if (c == ')') {
        res += sign * num; // calculate the current result
        num = 0;

        res *= stack.top(); // apply the sign before '('
        stack.pop();
        res += stack.top(); // add the result before '('
        stack.pop();
      }
      // skip space character
    }

    if (num != 0) {
      res += sign * num; // add the last number to the result
    }

    return res;
  }
};
