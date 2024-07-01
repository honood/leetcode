// HoNooD <honood@gmail.com>
// 2024.07.01 08:30

// 215. Kth Largest Element in an Array
// https://leetcode.com/problems/kth-largest-element-in-an-array/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    if (k <= 0 || nums.empty() || k > nums.size()) {
      return std::numeric_limits<int>::min();
    }

    priority_queue<int> max_heap{nums.cbegin(), nums.cend()};
    for (int i = 0; i < k - 1; ++i) {
      max_heap.pop();
    }

    return max_heap.top();
  }

  // use min-heap
  /*
  int findKthLargest(vector<int>& nums, int k) {
    if (k <= 0 || nums.empty() || k > nums.size()) {
      return std::numeric_limits<int>::min();
    }

    priority_queue<int, vector<int>, std::greater<int>> min_heap{};
    for (auto const& num : nums) {
      min_heap.emplace(num);
      if (min_heap.size() > k) {
        min_heap.pop();
      }
    }

    return min_heap.top();
  }
  */
};

// https://en.wikipedia.org/wiki/Selection_algorithm
//   https://en.wikipedia.org/wiki/Quickselect
//   https://en.wikipedia.org/wiki/Median_of_medians
//   https://en.wikipedia.org/wiki/Introselect
class Solution_2 {
public:
  int findKthLargest(vector<int>& nums, int k) {
    if (k <= 0 || nums.empty() || k > nums.size()) {
      return std::numeric_limits<int>::min();
    }

    std::srand(std::time(0)); // use current time as seed for random generator
    return quickselect(nums, 0, nums.size() - 1, k - 1);
  }

private:
  int quickselect(vector<int>& nums, int left, int right, int k) {
    if (left == right) {
      return nums[left];
    }

    int pivot_idx = partition(nums, left, right);
    if (k == pivot_idx) {
      return nums[k];
    }

    if (k < pivot_idx) {
      return quickselect(nums, left, pivot_idx - 1, k);
    }

    return quickselect(nums, pivot_idx + 1, right, k);
  }

  int partition(vector<int>& nums, int left, int right) {
    int pivot_idx = left + std::rand() % (right - left + 1);
    int pivot_val = nums[pivot_idx];
    std::swap(nums[pivot_idx], nums[right]);

    int store_index = left;
    for (int i = left; i < right; ++i) {
      if (nums[i] > pivot_val) { // descending order
        std::swap(nums[store_index], nums[i]);
        ++store_index;
      }
    }
    std::swap(nums[store_index], nums[right]);

    return store_index;
  }
};

// `std::nth_element` is a function in the C++ Standard Library that rearranges
// the elements in the range `[first, last)` such that the element at the `nth`
// position is the same as if the entire range were sorted. Elements before this
// `nth` element are not necessarily in order, but they are less than or equal
// to the `nth` element. Similarly, elements after the `nt`h element are greater
// than or equal to the `nth` element.
//
// https://en.cppreference.com/w/cpp/algorithm/nth_element
// https://cplusplus.com/reference/algorithm/nth_element/
class Solution_3 {
public:
  int findKthLargest(vector<int>& nums, int k) {
    int n = nums.size();
    if (k <= 0 || nums.empty() || k > n) {
      return std::numeric_limits<int>::min();
    }

    if (k < n / 2) {
      std::nth_element(nums.begin(), std::next(nums.begin(), k - 1), nums.end(), std::greater<int>{});
      return nums[k - 1];
    } else {
      std::nth_element(nums.begin(), std::next(nums.begin(), n - k), nums.end());
      return nums[n - k];
    }
  }
};
