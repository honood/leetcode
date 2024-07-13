// HoNooD <honood@gmail.com>
// 2024.07.13 13:30

// 503. Next Greater Element II
// https://leetcode.com/problems/next-greater-element-ii/description/

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
  vector<int> nextGreaterElements(vector<int>& nums) {
    return next_greater_elements_v2(nums);
  }

private:
  vector<int> next_greater_elements_v1(vector<int> const& nums) {
    int n = nums.size();
    // store the index of the next greater element for each index
    unordered_map<int, int> next_greater{};
    next_greater.reserve(n);

    // monotonic decreasing stack to store indices of elements
    stack<int> stack{};

    // first pass: process the array normally
    for (int i = 0; i < n; ++i) {
      while (!stack.empty() && nums[i] > nums[stack.top()]) {
        next_greater[stack.top()] = i;
        stack.pop();
      }

      stack.emplace(i);
    }

    // second pass: process the array to simulate circular behavior
    if (!stack.empty()) {
      for (int i = 0; i < n; ++i) {
        while (!stack.empty() && nums[i] > nums[stack.top()]) {
          next_greater[stack.top()] = i;
          stack.pop();
        }
      }
    }

    // set `next_greater` for remaining elements in the stack to `-1`
    while (!stack.empty()) {
      next_greater[stack.top()] = -1;
      stack.pop();
    }

    vector<int> res(n, -1);
    for (int i = 0; i < n; ++i) {
      if (next_greater[i] == -1) {
        res[i] = -1;
      } else {
        res[i] = nums[next_greater[i]];
      }
    }

    return res;
  }

  vector<int> next_greater_elements_v2(vector<int> const& nums) {
    int n = nums.size();
    vector<int> res(n, -1);
    // monotonic decreasing stack to store indices of elements
    stack<int> stack{};

    for (int i = 0; i < n * 2; ++i) {
      int curr_num = nums[i % n];
      while (!stack.empty() && curr_num > nums[stack.top()]) {
        res[stack.top()] = curr_num;
        stack.pop();
      }

      if (i < n) {
        stack.emplace(i);
      }
    }

    return res;
  }
};
