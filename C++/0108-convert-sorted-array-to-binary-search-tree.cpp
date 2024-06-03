// HoNooD
// 2024.05.28 11:08

// 108. Convert Sorted Array to Binary Search Tree
// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/?envType=study-plan-v2&envId=top-interview-150

// https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm

// Note: A height-balanced binary tree is a binary tree in which the depth of
// the two subtrees of every node never differs by more than one.

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class Solution {
public:
  TreeNode* sortedArrayToBST(vector<int>& nums) {
    if (nums.empty()) {
      return nullptr;
    }

    return impl(nums, 0, nums.size() - 1);
  }

private:
  TreeNode* impl(vector<int> const& nums, int low, int high) {
    if (low > high) {
      return nullptr;
    }

    // Note: this way of calculating `mid` is safe from integer overflow.
    int mid = low + (high - low) / 2;
    return new TreeNode{
      nums[mid],
      impl(nums, low, mid - 1),
      impl(nums, mid + 1, high)
    };
  }
};
