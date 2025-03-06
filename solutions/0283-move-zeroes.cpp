// HoNooD <honood@gmail.com>
// 2025.02.22 11:18

// 283. Move Zeroes
// https://leetcode.com/problems/move-zeroes/?envType=study-plan-v2&envId=leetcode-75

// Note that you must do this in-place without making a copy of the array.
// Follow up: Could you minimize the total number of operations done?

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  void moveZeroes(vector<int>& nums) {
    move_zeroes_v3(nums);
  }

private:
  void move_zeroes_v1(vector<int>& nums) {
    int first_zero_pos = -1;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != 0) {
        if (first_zero_pos != -1) {
          std::swap(nums[i], nums[first_zero_pos]);
          ++first_zero_pos;
        }
      } else {
        if (first_zero_pos == -1) {
          first_zero_pos = i;
        }
      }
    }
  }

  void move_zeroes_v2(vector<int>& nums) {
    int first_zero_pos = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] != 0) {
        if (i != first_zero_pos) {
          std::swap(nums[i], nums[first_zero_pos]);
        }
        ++first_zero_pos;
      }
    }
  }

  void move_zeroes_v3(vector<int>& nums) {
    int n = nums.size();
    int first_zero_pos = 0;

    // Move all non-zero elements to the front
    for (int i = 0; i < n; i++) {
      if (nums[i] != 0) {
        if (i != first_zero_pos) {
          nums[first_zero_pos] = nums[i];
        }
        ++first_zero_pos;
      }
    }

    // Fill the remaining positions with zeros
    for (int i = first_zero_pos; i < n; i++) {
      nums[i] = 0;
    }
  }
};
