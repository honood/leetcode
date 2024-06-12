// HoNooD <honood@gmail.com>
// 2024.06.12 21:30

// 150. Evaluate Reverse Polish Notation
// https://leetcode.com/problems/evaluate-reverse-polish-notation/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Reverse_Polish_notation
// https://en.wikipedia.org/wiki/Infix_notation
// https://en.wikipedia.org/wiki/Polish_notation

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int evalRPN(vector<string>& tokens) {
    unordered_map<string, std::function<int(int const&, int const&)>> const ops{
      {"+", std::plus<int>{}},
      {"-", std::minus<int>{}},
      {"*", std::multiplies<int>{}},
      {"/", std::divides<int>{}}
    };

    stack<int> stack{};
    for (auto const& token : tokens) {
      if (!ops.contains(token)) {
        stack.emplace(std::stoi(token)); // `std::atoi(...)` is OK here
        continue;
      }

      assert(stack.size() >= 2);

      int right = stack.top();
      stack.pop();

      int left = stack.top();
      stack.pop();

      int res = ops.at(token)(left, right);
      stack.emplace(res);
    }

    assert(stack.size() == 1);
    return stack.top();
  }
};
