// HoNooD
// 2024.05.23 22:40

// 22. Generate Parentheses
// https://leetcode.com/problems/generate-parentheses/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Backtracking

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// NOT recommended! 
// See `Solution_2` below.
class Solution {
public:
  vector<string> generateParenthesis(int n) {
    assert(n > 0);

    array<char, 2> const parenthesis{'(', ')'};

    vector<string> res{};
    string curr{};
    backtrack(res, curr, 0, parenthesis, n);

    return res;
  }

private:
  void backtrack(vector<string>& res, string& curr, int start, array<char, 2> const& parenthesis, int const& n) {
    if (curr.size() > n * 2) {
      return;
    }

    if (isDefinitelyInvalid(curr, n)) {
      return;
    }

    if (curr.size() == n * 2 && isValid(curr)) {
      res.emplace_back(curr);
      return;
    }

    for (int i = 0; i < parenthesis.size(); ++i) {
      curr.push_back(parenthesis[i]);
      backtrack(res, curr, i + 1, parenthesis, n);
      curr.pop_back();
    }
  }

  /*
  bool isValid(string const& s) {
    stack<char> stack{};
    for (char const& c : s) {
      if (c == '(') {
        stack.emplace(c);
        continue;
      }

      if (stack.empty()) {
        return false;
      }

      stack.pop();
    }

    return stack.empty();
  }
  */

  bool isValid(string const& s) {
    int count = 0;
    for (char const& c : s) {
      if (c == '(') {
        ++count;
        continue;
      }

      if (count == 0) {
        return false;
      }

      --count;
    }

    return count == 0;
  }

  bool isDefinitelyInvalid(string const& s, int const& n) {
    assert(n > 0);

    // Simulate a stack
    int count = 0;
    for (char const& c : s) {
      if (c == '(') {
        ++count;
        continue;
      }

      // No need to use `if (count <= 0)`
      if (count == 0) {
        return true;
      }

      --count;
    }

    return count > n;
  }
};

class Solution_2 {
public:
  vector<string> generateParenthesis(int n) {
    assert(n > 0);

    vector<string> res{};
    string curr{};
    backtrack(res, curr, n, n);

    return res;
  }

private:
  void backtrack(vector<string>& res, string& curr, int open, int close) {
    if (open == 0 && close == 0) {
      res.emplace_back(curr);
      return;
    }

    if (open > 0) {
      curr.push_back('(');
      backtrack(res, curr, open - 1, close);
      curr.pop_back();
    }

    if (close > open) {
      curr.push_back(')');
      backtrack(res, curr, open, close - 1);
      curr.pop_back();
    }
  }
};
