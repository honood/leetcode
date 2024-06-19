// HoNooD <honood@gmail.com>
// 2024.06.19 13:49

// 135. Candy
// https://leetcode.com/problems/candy/description/?envType=study-plan-v2&envId=top-interview-150
//
// There are `n` children standing in a line. Each child is assigned a rating
// value given in the integer array `ratings`.
//
// You are giving candies to these children subjected to the following
// requirements:
// 1. Each child must have at least one candy.
// 2. Children with a higher rating get more candies than their neighbors.
//
// Return the minimum number of candies you need to have to distribute the
// candies to the children.

auto __unsync_ios_stdio = ios::sync_with_stdio(false);
auto __untie_cin = cin.tie(nullptr);

// https://en.wikipedia.org/wiki/Greedy_algorithm
class Solution {
public:
  int candy(vector<int>& ratings) {
    if (ratings.empty()) {
      return 0;
    }

    int n = ratings.size();
    vector<int> candies(n, 1);

    // first pass: left to right
    for (int i = 1; i < n; ++i) {
      // if the current child has a higher rating than the previous child, give
      // them more candies than the previous child
      if (ratings[i] > ratings[i - 1]) {
        candies[i] = candies[i - 1] + 1;
      }
    }

    // second pass: right to left
    for (int i = n - 2; i >= 0; --i) {
      // if the current child has a higher rating than the next child, and they
      // do not already have more candies, give them more candies than the next
      // child
      if (ratings[i] > ratings[i + 1]) {
        candies[i] = std::max(candies[i], candies[i + 1] + 1);
      }
    }

    int totalCandies = 0;
    for (auto const& candy : candies) {
      totalCandies += candy;
    }

    return totalCandies;
  }
};

// We use a minimum heap (priority queue) to ensure that each child is processed
// in increasing order of their ratings. This approach is chosen for the
// following reasons:
//
// 1. Order of Processing: The minimum heap ensures that we always process the
// child with the lowest rating first. This is crucial because, to minimize the
// number of candies distributed, we need to start from the smallest ratings and
// build up the solution incrementally. If we start from the smallest, we can
// ensure the minimum constraint satisfaction with the least number of candies.
//
// 2. Minimizing Candies Early: By processing children in ascending order of
// their ratings, we can assign the minimum required candies to the lower-rated
// children first. This guarantees that when we process a child, their neighbors
// have already received the minimum candies according to their respective
// constraints, ensuring we don't give out more candies than necessary early on.
//
// 3. Updating Neighbors: When we process a child and give them candies based on
// their rating, we then check if this child needs to give more candies compared
// to their neighbors. If a neighbor has a higher rating but fewer or equal
// candies, we update the neighbor's candies. This approach allows us to
// dynamically adjust the candy distribution based on the processed ratings,
// ensuring that all constraints are met as we move through the children in
// increasing order of their ratings.
//
// 4. Avoiding Reprocessing: By choosing the smallest rating first and updating
// its neighbors, we avoid repeatedly adjusting the candies for previously
// processed children. If we instead checked if the left or right neighbor had
// higher ratings and updated them, it could lead to a situation where we might
// have to reprocess already handled children multiple times, increasing
// complexity and inefficiency.
class Solution_2 {
public:
  int candy(vector<int>& ratings) {
    if (ratings.empty()) {
      return 0;
    }

    int n = ratings.size();
    vector<int> candies(n, 1);

    auto greater = [](pair<int, int> const& left, pair<int, int> const& right) {
      return left.first > right.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(greater)> pq{greater};
    for (int i = 0; i < n; ++i) {
      pq.emplace(ratings[i], i);
    }

    while (!pq.empty()) {
      auto const& [rating, idx] = pq.top();
      pq.pop();

      if (idx > 0 && rating > ratings[idx - 1]) {
        candies[idx] = std::max(candies[idx], candies[idx - 1] + 1);
      }
      if (idx < n - 1 && rating > ratings[idx + 1]) {
        candies[idx] = std::max(candies[idx], candies[idx + 1] + 1);
      }
    }

    int totalCandies = 0;
    for (auto const& candy : candies) {
      totalCandies += candy;
    }

    return totalCandies;
  }
};

// https://en.wikipedia.org/wiki/Dynamic_programming
//
// Dynamic programming (DP) is used to solve problems by breaking them down into
// simpler subproblems and storing the results of these subproblems to avoid
// redundant computations. The main idea is to build up solutions to larger
// problems using the results of smaller subproblems, exploiting the problem's
// overlapping substructure and optimal substructure properties.
//
// The DP approach here involves using two auxiliary arrays to store intermediate
// results for optimal candy distribution when moving from left to right and from
// right to left.
//
// - State Definition: `left[i]` and `right[i]` represent the optimal number of
// candies each child should get from left and right perspectives respectively.
// - Transition: Use relations between adjacent ratings to update candies counts
// in `left` and `right` arrays.
// - Initialization: Start with each child having at least one candy.
// - Combination: Merge the results from both perspectives to ensure all
// constraints are satisfied.
class Solution_3 {
public:
  int candy(vector<int>& ratings) {
    if (ratings.empty()) {
      return 0;
    }

    int n = ratings.size();

    // left to right
    vector<int> left(n, 1);
    for (int i = 1; i < n; ++i) {
      if (ratings[i] > ratings[i - 1]) {
        left[i] = left[i - 1] + 1;
      }
    }

    // right to left
    vector<int> right(n, 1);
    for (int i = n - 2; i >= 0; --i) {
      if (ratings[i] > ratings[i + 1]) {
        right[i] = right[i + 1] + 1;
      }
    }

    int totalCandies = 0;
    for (int i = 0; i < n; ++i) {
      totalCandies += std::max(left[i], right[i]);
    }

    return totalCandies;
  }
};
