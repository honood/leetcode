// HoNooD
// 2024.05.23 23:54

// 20. Valid Parentheses
// https://leetcode.com/problems/valid-parentheses/description/

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  bool isValid(string s) {
    int sz = s.size();
    if (sz == 0 || (sz & 0x1) == 1) {
      return false;
    }

    stack<char> stk{};
    for (auto const& c: s) {
      if (c == '(' || c == '[' || c == '{') {
        stk.emplace(c);
      } else if (stk.empty()) {
        return false;
      } else {
        auto const& top = stk.top();
        if ((top == '(' && c == ')') ||
            (top == '[' && c == ']') ||
            (top == '{' && c == '}')) {
          stk.pop();
        } else {
          return false;
        }
      }
    }

    return stk.empty();
  }
};

class Solution_2 {
public:
  bool isValid(string s) {
    int sz = s.size();
    if (sz == 0 || (sz & 0x1) == 1) {
      return false;
    }

    unordered_map<char, char> const pairs{
      {')', '('},
      {']', '['},
      {'}', '{'}
    };

    stack<char> stk{};
    for (char const& c : s) {
      if (!pairs.contains(c)) {
        stk.emplace(c);
        continue;
      }

      if (stk.empty()) {
        return false;
      }

      if (stk.top() != pairs.at(c)) {
        return false;
      }

      stk.pop();
    }

    return stk.empty();
  }
};
