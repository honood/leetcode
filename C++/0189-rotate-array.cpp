// HoNooD <honood@gmail.com>
// 2024.06.16 14:20

// 189. Rotate Array
// https://leetcode.com/problems/rotate-array/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// nums = [1, 2, 3, 4, 5, 6, 7]
// k = 3
//
// => [7, 6, 5, 4, 3, 2, 1]
// => [5, 6, 7, 4, 3, 2, 1]
// => [5, 6, 7, 1, 2, 3, 4]
class Solution {
public:
  void rotate(vector<int>& nums, int k) {
    if (k <= 0) {
      return;
    }

    int n = nums.size();
    if (n <= 1) {
      return;
    }

    k %= n;
    if (k == 0) {
      return;
    }

    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), std::next(nums.begin(), k));
    std::reverse(std::next(nums.begin(), k), nums.end());
  }
};

class Solution_2 {
public:
  void rotate(vector<int>& nums, int k) {
    if (k <= 0) {
      return;
    }

    int n = nums.size();
    if (n <= 1) {
      return;
    }

    k %= n;
    if (k == 0) {
      return;
    }

    // Note: `std::rotate` performs a LEFT rotation!
    std::rotate(nums.begin(), std::next(nums.begin(), n - k), nums.end());
  }
};

// Cyclic Replacements
//
// Moves elements to their new positions in a cyclic manner. Each element is
// placed directly into its correct position by a sequence of swaps.
//
// Note: potentially offers optimal time and space performance, but it is
// complex and difficult to understand.
class Solution_3 {
public:
  void rotate(vector<int>& nums, int k) {
    if (k <= 0) {
      return;
    }

    int n = nums.size();
    if (n <= 1) {
      return;
    }

    k %= n;
    if (k == 0) {
      return;
    }

    // count of elements moved to their correct positions
    int movedCount = 0;
    // Note: When `n` and `k` have a Greatest Common Divisor (GCD) greater than
    // `1`, a single inner loop is insufficient to move all elements,
    // necessitating multiple loops. For example, nums = [1, 2, 3, 4] and k = 2.
    for (int startIdx = 0; movedCount < n; ++startIdx) {
      int currIdx = startIdx;
      int toMoveVal = nums[startIdx];
      do {
        int moveToIdx = (currIdx + k) % n;

        std::swap(nums[moveToIdx], toMoveVal);

        currIdx = moveToIdx;
        ++movedCount;
      } while (startIdx != currIdx);
    } // for
  }
};

class Solution_4 {
public:
  void rotate(vector<int>& nums, int k) {
    if (k <= 0) {
      return;
    }

    int n = nums.size();
    if (n <= 1) {
      return;
    }

    k %= n;
    if (k == 0) {
      return;
    }

    // Note: Avoid defining `copy` as `std::vector<int> copy{std::move(nums)}`
    // because, although it moves ownership, it also sets `nums`'s capacity to
    // `0`, which is undesirable.
    vector<int> copy{nums};
    for (int i = 0; i < n; ++i) {
      nums[(i + k) % n] = copy[i];
    }
  }
};

class Solution_5 {
public:
  void rotate(vector<int>& nums, int k) {
    if (k <= 0) {
      return;
    }

    int n = nums.size();
    if (n <= 1) {
      return;
    }

    k %= n;
    if (k == 0) {
      return;
    }

    std::queue<int> q{};
    for (auto const& num : nums) {
      q.emplace(num);
    }

    int count = n - k;
    while (count-- > 0) {
      int popped = q.front();
      q.pop();
      q.emplace(popped);
    }

    for (int i = 0; i < n; ++i) {
      nums[i] = q.front();
      q.pop();
    }
  }
};
