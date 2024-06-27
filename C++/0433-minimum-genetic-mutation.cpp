// HoNooD <honood@gmail.com>
// 2024.06.27 08:30

// 433. Minimum Genetic Mutation
// https://leetcode.com/problems/minimum-genetic-mutation/description/?envType=study-plan-v2&envId=top-interview-150

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// The goal of the problem is to find the minimum number of mutations needed to
// transform a starting gene sequence (start) into a target gene sequence (end),
// with the condition that each mutation must produce a valid sequence found in
// the provided gene bank. Each mutation can only change one character at a
// time.
//
// We use Breadth-First Search (BFS) to ensure the shortest path.
//
// Note: BFS ensures the shortest path by exploring all sequences one mutation
// away from the current sequence before exploring sequences two mutations away.
// This guarantees that the first encounter with the end sequence is through the
// shortest possible path.
class Solution {
public:
  int minMutation(string start_gene, string end_gene, vector<string>& bank) {
    if (start_gene.empty() || end_gene.size() != start_gene.size() || end_gene.size() != 8 ||
        bank.empty() || std::any_of(bank.cbegin(), bank.cend(), [](auto const& e) { return e.size() != 8; })) {
      return -1;
    }

    unordered_set<string> bank_set{bank.cbegin(), bank.cend()};
    if (!bank_set.contains(end_gene)) {
      return -1;
    }

    queue<pair<string, int>> q{};
    q.emplace(start_gene, 0);
    while (!q.empty()) {
      // Note: `q.pop()` invalidates references, so do NOT use:
      // 1. auto const& [curr_gene, mut_count] = q.front();
      // 2. auto& [curr_gene, mut_count] = q.front();
      auto [curr_gene, mut_count] = q.front();
      q.pop();

      // try all possible single-character mutations of the current gene
      for (int i = 0; i < curr_gene.size(); ++i) {
        char original = curr_gene[i];
        for (auto const& c : {'A', 'C', 'G', 'T'}) {
          if (c == original) {
            continue;
          }

          curr_gene[i] = c;
          if (curr_gene == end_gene) {
            return mut_count + 1;
          }

          if (bank_set.contains(curr_gene)) {
            q.emplace(curr_gene, mut_count + 1);
            bank_set.erase(curr_gene);
          }
        }
        curr_gene[i] = original;
      } // for
    } // while

    return -1;
  }
};
