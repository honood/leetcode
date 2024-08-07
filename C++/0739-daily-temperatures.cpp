// HoNooD <honood@gmail.com>
// 2024.07.13 23:41

// 739. Daily Temperatures
// https://leetcode.com/problems/daily-temperatures/description/

// Monotonic Stack
//
// A monotonic stack is a stack data structure that maintains its elements in
// either an increasing or decreasing order. Here are its key properties:
//
// 1. Order Maintenance:
//   - In a Monotonic Increasing Stack, each new element pushed onto the stack
//     is greater than or equal to the element at the top of the stack.
//   - In a Monotonic Decreasing Stack, each new element pushed onto the stack
//     is less than or equal to the element at the top of the stack.
// 2. Efficiency:
//   - It allows for efficient retrieval of the next greater or next smaller
//     element in a sequence, typically in linear time `O(n)`.
// 3. Dynamic Updates:
//   - As elements are added or removed, the stack dynamically maintains its
//     monotonic property, ensuring that the operations of pushing and popping
//     elements are efficient.
// 4. Application:
//   - Monotonic stacks are commonly used in problems involving the next greater
//     element, next smaller element, stock span problems, and histogram
//     problems.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  // using monotonic decreasing stack
  //
  // - Time Complexity: O(n)
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    if (n <= 1) {
      return vector<int>(n, 0);
    }

    vector<int> res(n, 0);
    stack<int> stack{};

    for (int i = 0; i < n; ++i) {
      while (!stack.empty() && temperatures[i] > temperatures[stack.top()]) {
        res[stack.top()] = i - stack.top();
        stack.pop();
      }

      stack.emplace(i);
    }

    return res;
  }
};
