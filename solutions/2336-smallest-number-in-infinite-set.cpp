// HoNooD <honood@gmail.com>
// 2025.03.21 15:10

// 2336. Smallest Number in Infinite Set
// https://leetcode.com/problems/smallest-number-in-infinite-set/?envType=study-plan-v2&envId=leetcode-75

namespace v1 {
class SmallestInfiniteSet;
}
namespace v2 {
class SmallestInfiniteSet;
}

using SmallestInfiniteSet = v1::SmallestInfiniteSet;

namespace v1 {

// Min-heap with hash set for existence check
//
// - Time complexity: O(log n) for both operations
// - Space complexity: O(n)
class SmallestInfiniteSet {
public:
  SmallestInfiniteSet() = default;

  int popSmallest() {
    if (added_numbers_.empty()) {
      return current_smallest_++;
    }

    int smallest = added_numbers_.top();
    added_numbers_.pop();
    number_exists_.erase(smallest);
    return smallest;
  }

  void addBack(int num) {
    if (num < current_smallest_ && !number_exists_.contains(num)) {
      added_numbers_.push(num);
      number_exists_.insert(num);
    }
  }

private:
  int current_smallest_{1};
  std::priority_queue<int, std::vector<int>, std::greater<>> added_numbers_{};
  std::unordered_set<int> number_exists_{};
};

} // namespace v1

namespace v2 {

// Ordered set (automatically maintains order)
//
// - Time complexity: O(log n) for both operations
// - Space complexity: O(n)
class SmallestInfiniteSet {
public:
  SmallestInfiniteSet() = default;

  int popSmallest() {
    if (added_back_.empty()) {
      return current_smallest_++;
    }

    int smallest = *added_back_.cbegin();
    added_back_.erase(added_back_.cbegin());
    return smallest;
  }

  void addBack(int num) {
    if (num < current_smallest_ && !added_back_.contains(num)) {
      added_back_.insert(num);
    }
  }

private:
  int current_smallest_{1};
  std::set<int> added_back_{};
};

} // namespace v2

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
