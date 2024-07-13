// HoNooD <honood@gmail.com>
// 2024.07.13 10:34

// 496. Next Greater Element I
// https://leetcode.com/problems/next-greater-element-i/description/

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

// Constraints:
// 1. `1 <= nums1.length <= nums2.length <= 1000`
// 2. `0 <= nums1[i], nums2[i] <= 104`
// 3. All integers in `nums1` and `nums2` are unique.
// 4. All the integers of `nums1` also appear in `nums2`.

class Solution {
public:
  vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    return next_greater_element_v2(nums1, nums2);
  }

private:
  // Brute Force
  //
  // - Time complexity: O(n * m), where `n` is the size of `nums1` and `m` is
  //    the size of `nums2`.
  vector<int> next_greater_element_v1(vector<int> const& nums1, vector<int> const& nums2) {
    vector<int> res(nums1.size(), -1);

    for (int i = 0; i < nums1.size(); ++i) {
      auto it = std::find(nums2.cbegin(), nums2.cend(), nums1[i]);
      assert(it != nums2.cend());
      it = std::find_if(std::next(it), nums2.cend(), [target = nums1[i]](int const& i) {
        return i > target;
      });
      if (it != nums2.cend()) {
        res[i] = *it;
      }
    }

    return res;
  }

  // using monotonic decreasing stack
  //
  // - Time Complexity: O(n + m), where `n` is the size of `nums1` and `m` is
  //   the size of `nums2`. We process each element in `nums2` exactly once.
  vector<int> next_greater_element_v2(vector<int> const& nums1, vector<int> const& nums2) {
    // store the next greater element for each element in `nums2`
    unordered_map<int, int> next_greater{};
    next_greater.reserve(nums2.size());

    // maintain the decreasing sequence of elements
    stack<int> stack{};
    for (int num : nums2) {
      while (!stack.empty() && num > stack.top()) {
        // the next greater element of `stack.top()` is `num`
        next_greater[stack.top()] = num;
        stack.pop();
      }

      stack.emplace(num);
    }

    // for elements left in the `stack`, there is no greater element, so map to
    // `-1`
    while (!stack.empty()) {
      next_greater[stack.top()] = -1;
      stack.pop();
    }

    vector<int> res(nums1.size(), -1);
    for (int i = 0; i < nums1.size(); ++i) {
      res[i] = next_greater[nums1[i]];
    }

    return res;
  }
};
