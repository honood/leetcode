// HoNooD <honood@gmail.com>
// 2024.06.18 18:43

// 380. Insert Delete GetRandom O(1)
// https://leetcode.com/problems/insert-delete-getrandom-o1/description/?envType=study-plan-v2&envId=top-interview-150

// Note: You must implement the functions of the class such that each function
// works in average O(1) time complexity.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

class RandomizedSet {
public:
  RandomizedSet() {}

  bool insert(int val) {
    if (indices_.contains(val)) {
      return false;
    }

    nums_.emplace_back(val);
    indices_[val] = nums_.size() - 1;

    return true;
  }

  bool remove(int val) {
    if (!indices_.contains(val)) {
      return false;
    }

    int index = indices_[val];
    indices_.erase(val);
    if (index != nums_.size() - 1) {
      indices_[nums_.back()] = index;
      nums_[index] = nums_.back();
    }
    nums_.pop_back();

    return true;
  }

  int getRandom() {
    return nums_[randomIndex()];
  }

private:
  vector<int> nums_{};
  unordered_map<int, int> indices_{};

  std::mt19937 gen_{std::random_device{}()};
  int randomIndex() {
    std::uniform_int_distribution<> distrib(0, nums_.size() - 1);
    return distrib(gen_);
  }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
