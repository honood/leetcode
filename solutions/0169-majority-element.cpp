// HoNooD <honood@gmail.com>
// 2024.08.06 12:00

// 169. Majority Element
// https://leetcode.com/problems/majority-element/description/?envType=study-plan-v2&envId=top-interview-150

// Follow-up: Could you solve the problem in linear time and in `O(1)` space?

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  int majorityElement(vector<int>& nums) {
    return majority_element_v3(nums);
  }

private:
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  int majority_element_v1(vector<int> const& nums) {
    unordered_map<int, int> counts{};
    int n = nums.size();
    for (auto const& num : nums) {
      ++counts[num];
      if (counts[num] > n / 2) {
        return num;
      }
    }

    // Return a minimum integer value if no majority element is found
    return std::numeric_limits<int>::min();
  }

  // Complexity Analysis:
  // - Time complexity: O(n * log(n)) due to sorting
  // - Space complexity: O(1) or O(n) depending on the sorting algorithm used
  int majority_element_v2(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    // Note: You may assume that the majority element always exists in the array
    return nums[nums.size() / 2];
  }

  // Boyer–Moore Majority Vote Algorithm
  // https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm
  //
  // ## Pseudocode
  //
  // - Initialize an element `m` and a counter `c` with `c = 0`
  // - For each element `x` of the input sequence:
  //   - If `c = 0`, then assign `m = x` and `c = 1`
  //   - else if `m = x`, then assign `c = c + 1`
  //   - else assign `c = c − 1`
  // - Return `m`
  //
  // ## Correctness
  //
  // Suppose that the input contains a majority element `x`, whose number of
  // copies is more than half of the input length. Then the algorithm should
  // return `x` as its final value `m`. Boyer and Moore prove the following
  // stronger statement: For the final values `m` and `c` of the algorithm, on a
  // sequence of length `n`, it is always possible to partition the input values
  // into `c` copies of `m` and `(n − c)/2` pairs of unequal items. From this it
  // follows that no element `x != m` can have a majority, because `x` can have
  // at most half of the elements in the unequal pairs and none of the remaining
  // `c` copies of `m`. Thus, if there is a majority element, it can only be `m`.
  //
  // Note: Not to be confused with the "Boyer–Moore string-search algorithm"
  // https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm
  //
  // Complexity Analysis:
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  int majority_element_v3(vector<int> const& nums) {
    // a minimum integer value if no majority element is found
    int candidate = std::numeric_limits<int>::min();
    int count = 0;

    // First pass: Find a potential candidate for the majority element
    for (auto const& num : nums) {
      if (count == 0) {
        candidate = num;
      }

      if (num == candidate) {
        ++count;
      } else {
        --count;
      }
    }

    // Note: If the problem does not guarantee the existence of a majority
    // element, a second pass is necessary to confirm that the candidate found
    // in the first pass is indeed the majority.

    // // Second pass: Verify if the candidate is indeed the majority element
    // count = 0;
    // for (auto const& num : nums) {
    //   if (num == candidate) {
    //     ++count;
    //     if (count > nums.size() / 2) {
    //       return candidate;
    //     }
    //   }
    // }

    return candidate;
  }
};
