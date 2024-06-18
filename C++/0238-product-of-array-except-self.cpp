// HoNooD <honood@gmail.com>
// 2024.06.18 14:50

// 238. Product of Array Except Self
// https://leetcode.com/problems/product-of-array-except-self/?envType=study-plan-v2&envId=top-interview-150

// Note: You must write an algorithm that runs in O(n) time and without using
// the division operation.

// https://en.wikipedia.org/wiki/Prefix_sum

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// We can use two auxiliary arrays to store the product of all elements to the
// left and right of each element, and then combine these two arrays to get the
// result.
//
// 1. Construct Left and right product arrays:
//   - `left_products[i]` stores the product of all elements from the start up
//     to `i - 1`.
//   - `right_products[i]` stores the product of all elements from `i + 1` to
//     the end.
// 2. Combine arrays: `answer[i] = left_products[i] * right_products[i]`
class Solution {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> leftProd(n, 1);
    vector<int> rightProd(n, 1);
    vector<int> res(n);

    for (int i = 1; i < n; ++i) {
      leftProd[i] = leftProd[i - 1] * nums[i - 1];
    }

    for (int i = n - 2; i >= 0; --i) {
      rightProd[i] = rightProd[i + 1] * nums[i + 1];
    }

    for (int i = 0; i < n; ++i) {
      res[i] = leftProd[i] * rightProd[i];
    }

    return res;
  }
};

// Great!
//
// solved with O(1) extra space complexity (The output array does not count as
// extra space for space complexity analysis.)
class Solution_2 {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 1);

    // Calculate left products: `res[i]` is the product of elements to the left
    // of `i`
    //
    // Note: `res[0]` remains `1` since there are no elements to the left
    for (int i = 1; i < n; ++i) {
      res[i] = res[i - 1] * nums[i - 1];
    }

    // Calculate right products: `rightProd` accumulates the product of elements
    // to the right of `i`
    int rightProd = 1;
    for (int i = n - 1; i >= 0; --i) {
      res[i] *= rightProd;
      rightProd *= nums[i];
    }

    return res;
  }
};
