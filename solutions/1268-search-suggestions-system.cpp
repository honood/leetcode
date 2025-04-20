// HoNooD <honood@gmail.com>
// 2025.04.18 21:31
//
// 1268. Search Suggestions System
// https://leetcode.com/problems/search-suggestions-system/?envType=study-plan-v2&envId=leetcode-75

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

class Solution {
public:
  vector<vector<string>> suggestedProducts(vector<string>& products,
                                           string const& searchWord) {
    return suggested_products_v2(products, searchWord);
  }

private:
  // clang-format off
  // - Time complexity: O(N * L * log N + M * L * log N)
  //   - N: number of products
  //   - L: average/maximum length of a product
  //   - M: length of searchWord
  //   - O(N * L * log N): Time for sorting the products array. String comparison takes O(L).
  //   - O(M * L * log N): Time for M searches. Each std::lower_bound takes O(log N) string
  //     comparisons, and each comparison takes up to O(L). Checking the next 3 words takes
  //     O(L) or O(M).
  // - Space complexity: O(M * L + sort_space)
  //   - O(M * L): Space for the result list (M lists, up to 3 strings of length L each).
  //   - O(sort_space): Auxiliary space used by the sorting algorithm (e.g., O(log N) or O(N)).
  //   - O(M): Space for the prefix string.
  //   - Overall auxiliary space (excluding result) is dominated by sorting.
  // clang-format on
  vector<vector<string>> suggested_products_v1(vector<string>& products,
                                               string const& search_word) {
    std::sort(products.begin(), products.end());

    vector<vector<string>> result{};
    string prefix{};
    auto it = products.begin();

    for (char c : search_word) {
      prefix += c;

      it = std::lower_bound(products.begin(), products.end(), prefix);

      vector<string> suggestions{};
      for (int i = 0; i < 3 && it + i != products.end(); ++i) {
        string const& product = *(it + i);
        if (product.find(prefix) == 0) {
          suggestions.push_back(product);
        } else {
          break;
        }
      }
      result.push_back(std::move(suggestions));
    }

    return result;
  }

  // - Time Complexity: O(N * L * logN + M)
  //   - Sorting: O(N * L * logN) because comparing strings takes O(L).
  //   - Trie Building: O(N * L) to insert N strings of max length L.
  //   - Querying: O(M) to traverse the Trie according to search_word.
  // - Space complexity: O(N * L + M * L)
  //   - Trie Storage (Auxiliary): O(N * L) for Trie nodes and stored suggestions.
  //   - Sorting (Auxiliary): O(logN) or O(N) depending on implementation.
  //   - Result Storage: O(M * L) for the output list of suggestions.
  //
  // Constraints:
  // - products[i] consists of lowercase English letters.
  // - search_word consists of lowercase English letters.
  vector<vector<string>> suggested_products_v2(vector<string>& products,
                                               string const& search_word) {
    struct TrieNode {
      TrieNode* children[26];
      vector<string> suggestions{};

      TrieNode() {
        for (int i = 0; i < 26; ++i) {
          children[i] = nullptr;
        }
      }
      ~TrieNode() {
        for (int i = 0; i < 26; ++i) {
          delete children[i];
        }
      }

      static void insert(TrieNode* root, string const& word) {
        TrieNode* node = root;
        for (char c : word) {
          int index = c - 'a';
          if (node->children[index] == nullptr) {
            node->children[index] = new TrieNode{};
          }
          node = node->children[index];

          if (node->suggestions.size() < 3) {
            node->suggestions.push_back(word);
          }
        }
      }
    };

    std::sort(products.begin(), products.end());

    TrieNode root{};
    for (auto const& product : products) {
      TrieNode::insert(&root, product);
    }

    vector<vector<string>> result{};
    TrieNode* node = &root;
    for (char c : search_word) {
      if (node != nullptr) {
        node = node->children[c - 'a'];
      }

      if (node != nullptr) {
        result.push_back(std::move(node->suggestions));
      } else {
        result.push_back({});
      }
    }
    return result;
  }
};
