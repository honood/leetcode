// HoNooD <honood@gmail.com>
// 2025.03.23 17:00

// 2300. Successful Pairs of Spells and Potions
// https://leetcode.com/problems/successful-pairs-of-spells-and-potions/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<int> successfulPairs(vector<int>& spells, vector<int>& potions,
                              long long success) {
    return successful_pairs_v2(spells, potions, success);
  }

private:
  // Time Limit Exceeded
  //
  // - Time complexity: O(n * m)
  // - Space complexity: O(n)
  vector<int> successful_pairs_v1(vector<int> const& spells,
                                  vector<int> const& potions,
                                  long long success) {
    vector<int> result(spells.size(), 0);
    for (int i = 0; i < spells.size(); ++i) {
      for (int j = 0; j < potions.size(); ++j) {
        if (static_cast<long long>(spells[i]) * potions[j] >= success) {
          ++result[i];
        }
      }
    }
    return result;
  }

  // - Time complexity: O((n + m) * log(m))
  // - Space complexity: O(n)
  vector<int> successful_pairs_v2(vector<int> const& spells,
                                  vector<int>& potions, long long success) {
    std::sort(potions.begin(), potions.end());

    vector<int> result(spells.size(), 0);
    for (int i = 0; i < spells.size(); ++i) {
      assert(spells[i] > 0);
      assert(success > 0);
      long long min_potion = (success + (spells[i] - 1)) / spells[i]; // ceil
      auto it = std::lower_bound(potions.cbegin(), potions.cend(), min_potion);
      result[i] += std::distance(it, potions.cend());
    }
    return result;
  }

  // - Time complexity: O(n * log(n) + m * log(m))
  // - Space complexity: O(n)
  vector<int> successful_pairs_v3(vector<int> const& spells,
                                  vector<int>& potions, long long success) {
    int n = spells.size();
    int m = potions.size();

    // Create pairs of (spell, index) to maintain original order
    vector<pair<int, int>> spells_with_index{};
    for (int i = 0; i < n; ++i) {
      spells_with_index.emplace_back(spells[i], i);
    }

    // Sort spells in ascending order
    std::sort(spells_with_index.begin(), spells_with_index.end());
    // Sort potions in ascending order
    std::sort(potions.begin(), potions.end());

    vector<int> result(n, 0);
    int potion_index = m - 1;

    for (int i = 0; i < n; ++i) {
      auto [spell, orig_index] = spells_with_index[i];
      while (potion_index >= 0
             && (long long)spell * potions[potion_index] >= success) {
        --potion_index;
      }
      result[orig_index] += m - potion_index - 1;
    }

    return result;
  }
};
