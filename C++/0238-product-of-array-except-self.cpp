// HoNooD <honood@gmail.com>
// 2024.06.18 14:50

// 238. Product of Array Except Self
// https://leetcode.com/problems/product-of-array-except-self/?envType=study-plan-v2&envId=top-interview-150

// Note: You must write an algorithm that runs in O(n) time and without using
// the division operation.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    return product_except_self_v2(nums);
  }

private:
  // Prefix Sum
  // https://leetcode.com/tag/prefix-sum/
  //
  // We can use two auxiliary arrays to store the product of all elements to the
  // left and right of each element, and then combine these two arrays to get
  // the result.
  //
  // 1. Construct left and right product arrays:
  //   - `left_products[i]` stores the product of all elements from the start up
  //     to `i - 1`.
  //   - `right_products[i]` stores the product of all elements from `i + 1` to
  //     the end.
  // 2. Combine arrays: `answer[i] = left_products[i] * right_products[i]`
  //
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  vector<int> product_except_self_v1(vector<int> const& nums) {
    int n = nums.size();

    vector<int> left_products(n, 1);
    for (int i = 1; i < n; ++i) {
      left_products[i] = left_products[i - 1] * nums[i - 1];
    }

    vector<int> right_products(n, 1);
    for (int i = n - 2; i >= 0; --i) {
      right_products[i] = right_products[i + 1] * nums[i + 1];
    }

    vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
      answer[i] = left_products[i] * right_products[i];
    }

    return answer;
  }

  // Prefix Sum
  // https://leetcode.com/tag/prefix-sum/
  //
  // Follow up: Can you solve the problem in `O(1)` extra space complexity? (The
  // output array does not count as extra space for space complexity analysis.)
  //
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  vector<int> product_except_self_v2(vector<int> const& nums) {
    int n = nums.size();
    vector<int> answer(n, 1);

    // Calculate left products: `answer[i]` is the product of elements to the
    // left of `i`
    //
    // Note: `answer[0]` remains `1` since there are no elements to the left
    for (int i = 1; i < n; ++i) {
      answer[i] = answer[i - 1] * nums[i - 1];
    }

    // Calculate right products: `right_products` accumulates the product of
    // elements to the right of `i`
    int right_products = 1;
    for (int i = n - 1; i >= 0; --i) {
      answer[i] *= right_products;
      right_products *= nums[i];
    }

    return answer;
  }
};
