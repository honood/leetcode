// HoNooD <honood@gmail.com>
// 2025.03.20 14:20
// 2024.07.01 08:30

// 215. Kth Largest Element in an Array
// https://leetcode.com/problems/kth-largest-element-in-an-array/description/?envType=study-plan-v2&envId=leetcode-75
// https://leetcode.com/problems/kth-largest-element-in-an-array/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    return find_kth_largest_v3(nums, k);
  }

private:
  // - Time complexity: O(n * log(n))
  // - Space complexity: O(log n)
  int find_kth_largest_v1(vector<int>& nums, int k) {
    assert(k >= 1 && nums.size() >= k);

    std::sort(nums.rbegin(), nums.rend());
    return nums[k - 1];
  }

  // - Time complexity: O(n * log(k))
  // - Space complexity: O(log(k))
  int find_kth_largest_v2(vector<int>& nums, int k) {
    assert(k >= 1 && nums.size() >= k);

    std::partial_sort(nums.begin(), std::next(nums.begin(), k), nums.end(),
                      std::greater<>{});
    return nums[k - 1];
  }

  // - Time complexity: O(n)
  // - Space complexity: O(log(n))
  int find_kth_largest_v3(vector<int>& nums, int k) {
    assert(k >= 1 && nums.size() >= k);

    std::nth_element(nums.begin(), std::next(nums.begin(), k - 1), nums.end(),
                     std::greater<>{});
    return nums[k - 1];
  }

  // - Time complexity: O(n + k * log(n))
  // - Space complexity: O(n)
  int find_kth_largest_v4(vector<int> const& nums, int k) {
    assert(k >= 1 && nums.size() >= k);

    std::priority_queue<int> max_heap{nums.cbegin(), nums.cend()};
    while (k-- > 1) {
      max_heap.pop();
    }
    return max_heap.top();
  }

  // - Time complexity: O(n + k * log(n))
  // - Space complexity: O(1)
  int find_kth_largest_v5(vector<int>& nums, int k) {
    assert(k >= 1 && nums.size() >= k);

    std::make_heap(nums.begin(), nums.end());
    auto heap_end = nums.end();
    while (k-- > 0) {
      std::pop_heap(nums.begin(), heap_end);
      --heap_end;
    }
    return *heap_end;
  }

  // - Time complexity: O(n * log(k))
  // - Space complexity: O(k)
  int find_kth_largest_v6(vector<int> const& nums, int k) {
    assert(k >= 1 && nums.size() >= k);

    std::priority_queue<int, vector<int>, std::greater<>> min_heap{};
    for (int num : nums) {
      min_heap.emplace(num);
      if (min_heap.size() > k) {
        min_heap.pop();
      }
    }
    return min_heap.top();
  }

  // - Time complexity: O(n + range) where `range = max_value - min_value + 1`
  // - Space complexity: O(range)
  int find_kth_largest_v7(vector<int> const& nums, int k) {
    assert(k >= 1 && nums.size() >= k);

    auto const [min, max] = std::minmax_element(nums.cbegin(), nums.cend());
    vector<int> freq(*max - *min + 1, 0);
    for (int num : nums) {
      ++freq[num - *min];
    }

    for (int i = freq.size() - 1; i >= 0; --i) {
      k -= freq[i];
      if (k <= 0) {
        return i + *min;
      }
    }

    throw std::runtime_error("Unreachable code reached!");
    return -1;
  }

  // Quickselect
  // https://en.wikipedia.org/wiki/Quickselect
  // https://en.wikipedia.org/wiki/Selection_algorithm
  //
  // - Time complexity: Average O(n), Worst Case O(n^2)
  // - Space complexity: O(log n) for recursion stack
  int find_kth_largest_v8(vector<int>& nums, int k) {
    assert(k >= 1 && nums.size() >= k);

    return quick_select(nums, 0, nums.size() - 1, nums.size() - k);
  }

  int quick_select(vector<int>& nums, int left, int right, int k_smallest) {
    if (left == right) {
      return nums[left];
    }

    int pivot_index = median_of_three(nums, left, right);
    pivot_index = partition(nums, left, right, pivot_index);

    if (k_smallest == pivot_index) {
      return nums[k_smallest];
    } else if (k_smallest < pivot_index) {
      return quick_select(nums, left, pivot_index - 1, k_smallest);
    } else {
      return quick_select(nums, pivot_index + 1, right, k_smallest);
    }
  }

  int median_of_three(vector<int>& nums, int left, int right) {
    int mid = left + (right - left) / 2;

    if (nums[left] > nums[mid]) {
      std::swap(nums[left], nums[mid]);
    }
    if (nums[left] > nums[right]) {
      std::swap(nums[left], nums[right]);
    }
    if (nums[mid] > nums[right]) {
      std::swap(nums[mid], nums[right]);
    }

    return mid;
  }

  int partition(vector<int>& nums, int left, int right, int pivot_index) {
    int pivot = nums[pivot_index];
    std::swap(nums[pivot_index], nums[right]);

    int store_index = left;
    for (int i = left; i < right; ++i) {
      if (nums[i] < pivot) {
        std::swap(nums[i], nums[store_index]);
        ++store_index;
      }
    }

    std::swap(nums[store_index], nums[right]);
    return store_index;
  }
};
