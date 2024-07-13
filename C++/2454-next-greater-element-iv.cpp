// HoNooD <honood@gmail.com>
// 2024.07.13 16:30

// 2454. Next Greater Element IV
// https://leetcode.com/problems/next-greater-element-iv/description/

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
  vector<int> secondGreaterElement(vector<int>& nums) {
    return second_greater_element_v2(nums);
  }

private:
  // Brute Force
  //
  // - Time complexity: O(n^2)
  //
  // Note: result in Time Limit Exceeded (TLE)
  vector<int> second_greater_element_v1(vector<int> const& nums) {
    int n = nums.size();
    if (n <= 2) {
      return vector<int>(n, -1);
    }

    vector<int> res(n, -1);
    auto find_next_greater = [](auto begin, auto end, int target) {
      return std::find_if(begin, end, [target](int const& num) {
        return num > target;
      });
    };
    for (int i = 0; i < n; ++i) {
      auto it = find_next_greater(std::next(nums.cbegin(), i), nums.cend(), nums[i]);
      if (it == nums.cend()) {
        continue;
      }

      it = find_next_greater(std::next(it), nums.cend(), nums[i]);
      if (it != nums.cend()) {
        res[i] = *it;
      }
    }

    return res;
  }

  // using monotonic decreasing stack
  //
  // - Time Complexity: O(n)
  vector<int> second_greater_element_v2(vector<int> const& nums) {
    int n = nums.size();
    if (n <= 2) {
      return vector<int>(n, -1);
    }

    vector<int> res(n, -1);
    // find the first greater element
    stack<int> first_stack{};
    // find the second greater element
    stack<int> second_stack{};
    // transfer elements from `first_stack` to `second_stack`
    stack<int> temp_stack{};

    for (int i = 0; i < n; ++i) {
      while (!second_stack.empty() && nums[i] > nums[second_stack.top()]) {
        res[second_stack.top()] = nums[i];
        second_stack.pop();
      }

      // move elements from `first_stack` to `second_stack`
      while (!first_stack.empty() && nums[i] > nums[first_stack.top()]) {
        temp_stack.emplace(first_stack.top());
        first_stack.pop();
      }
      while (!temp_stack.empty()) {
        second_stack.emplace(temp_stack.top());
        temp_stack.pop();
      }

      first_stack.emplace(i);
    }

    return res;
  }
};
