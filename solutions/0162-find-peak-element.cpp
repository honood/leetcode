// HoNooD <honood@gmail.com>
// 2025.03.23 21:00
// 2024.06.14 15:45

// 162. Find Peak Element
// https://leetcode.com/problems/find-peak-element/description/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/find-peak-element/description/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  // Constraints: `nums[i] != nums[i + 1]` for all valid `i`.
  int findPeakElement(vector<int>& nums) {
    return find_peak_element_v1(nums);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int find_peak_element_v1(vector<int> const& nums) {
    int n = nums.size();
    assert(n > 0);
    if (n == 1) {
      return 0;
    }

    if (nums[0] > nums[1]) {
      return 0;
    }

    if (nums[n - 1] > nums[n - 2]) {
      return n - 1;
    }

    for (int i = 1; i < n - 1; ++i) {
      if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
        return i;
      }
    }

    throw std::runtime_error("Unreachable code reached!");
    return -1;
  }

  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int find_peak_element_v2(vector<int> const& nums) {
    return std::distance(nums.cbegin(),
                         std::max_element(nums.cbegin(), nums.cend()));
  }

  // - Time complexity: O(log(n))
  // - Space complexity: O(1)
  int find_peak_element_v3(vector<int> const& nums) {
    assert(!nums.empty());

    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;

      // If mid element is less than its right neighbor, then a peak must exist
      // on the right side
      if (nums[mid] < nums[mid + 1]) {
        left = mid + 1;
      }
      // Otherwise, a peak must exist on the left side or at mid
      else if (nums[mid] > nums[mid + 1]) {
        right = mid;
      } else {
        // Note: one constraint of this problem is: `nums[i] != nums[i + 1]` for
        // all valid `i`.
        assert(nums[mid] != nums[mid + 1]);
        throw std::runtime_error("Unreachable code reached!");
      }
    }

    // When left == right, we've found a peak
    return left;
  }

  // - Time complexity: O(log(n))
  // - Space complexity: O(log(n))
  int find_peak_element_v4(vector<int> const& nums) {
    function<int(int, int)> binary_search
        = [&binary_search, &nums](int left, int right) {
            if (left == right) {
              return left;
            }

            int mid = left + (right - left) / 2;

            // If mid element is less than its right neighbor, then a peak must
            // exist on the right side
            if (nums[mid] < nums[mid + 1]) {
              return binary_search(mid + 1, right);
            }

            // Otherwise, a peak must exist on the left side or at mid
            if (nums[mid] > nums[mid + 1]) {
              return binary_search(left, mid);
            }

            // Note: one constraint of this problem is: `nums[i] != nums[i + 1]`
            // for all valid `i`.
            assert(nums[mid] != nums[mid + 1]);
            throw std::runtime_error("Unreachable code reached!");
          };

    return binary_search(0, nums.size() - 1);
  }

  // https://en.wikipedia.org/wiki/Ternary_search
  //
  // - Time complexity: O(log(n))
  // - Space complexity: O(1)
  int find_peak_element_v5(vector<int> const& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
      int mid1 = left + (right - left) / 3;
      int mid2 = right - (right - left) / 3;
      if (nums[mid1] < nums[mid2]) {
        left = mid1 + 1;
      } else {
        right = mid2 - 1;
      }
    }

    // When left == right, we've found a peak
    return left;
  }
};
