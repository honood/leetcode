// HoNooD <honood@gmail.com>
// 2024.06.15 10:05

// 34. Find First and Last Position of Element in Sorted Array
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// Best (and magic)
class Solution {
public:
  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res{-1, -1};
    if (nums.empty()) {
      return res;
    }

    // Find the left boundary
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    assert(left == right);
    if (nums[left] != target) {
      return res;
    }
    res[0] = left;

    // Find the right boundary
    right = nums.size() - 1;
    while (left < right) {
      // When using binary search to find the right boundary of a target element
      // in a sorted array, the update rule for `mid` as
      // `int mid = left + (right - left) / 2 + 1` is designed to ensure that
      // the search advances towards the right and avoids infinite loops or
      // redundant checks.
      //
      // 1. Avoiding Stagnation in `left`
      // When `left` and `right` are close (especially when `left + 1 == right`),
      // the standard midpoint calculation `mid = left + (right - left) / 2`
      // results in `mid` being equal to `left`. This can cause the search to
      // repeatedly check the same `left` value without progressing, potentially
      // leading to an infinite loop if `left` does not move past `mid`.
      //
      // 2. Ensuring Progression
      // By adding `1` to the midpoint calculation,
      // `mid = left + (right - left) / 2 + 1`, you ensure that `mid` always
      // moves towards the right half. This guarantees that `left` is updated
      // to a position strictly greater than the previous midpoint, which helps
      // in effectively narrowing down the search space towards the right
      // boundary.
      //
      // 3. Handling Edge Cases
      // When the array segment has only two elements (`left` and `right`),
      // using `mid = left + (right - left) / 2 + 1` ensures that `mid` is pushed
      // to the rightmost element, allowing `left` to move forward and converge
      // correctly. This method helps prevent getting stuck when the target is
      // the last occurrence in the array.
      int mid = left + (right - left) / 2 + 1;
      if (nums[mid] > target) {
        right = mid - 1;
      } else {
        left = mid;
      }
    }
    assert(left == right);
    res[1] = right;

    return res;
  }
};

// DO NOT USE, for comparison with `Solution` only.
class Solution_2 {
public:
  std::vector<int> searchRange(const std::vector<int>& nums, int target) {
    std::vector<int> res{-1, -1};
    if (nums.empty()) {
      return res;
    }

    // Find the left boundary
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    // Check if left boundary is valid
    if (left >= nums.size() || nums[left] != target) {
      return res;
    }
    res[0] = left;

    // Find the right boundary
    right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] > target) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    res[1] = right;

    return res;
  }
};

class Solution_3 {
public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int start = findFirstPosition(nums, target);
    int end = findLastPosition(nums, target);
    return {start, end};
  }

private:
  int findFirstPosition(vector<int>& nums, int target) {
    int res = -1;
    if (nums.empty()) {
      return res;
    }

    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] >= target) {
        right = mid - 1;
        if (nums[mid] == target) {
          res = mid;
        }
      } else {
        left = mid + 1;
      }
    }

    return res;
  }

  int findLastPosition(vector<int>& nums, int target) {
    int res = -1;
    if (nums.empty()) {
      return res;
    }

    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] <= target) {
        left = mid + 1;
        if (nums[mid] == target) {
          res = mid;
        }
      } else {
        right = mid - 1;
      }
    }

    return res;
  }
};
