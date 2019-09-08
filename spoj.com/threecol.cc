#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> ConstructTree(const string& tree_string) {
  vector<vector<int>> tree(tree_string.size());
  stack<int> S;

  for (int i = 0; i < tree_string.size(); ++i) {
    S.push(i);
    while (static_cast<int>(tree_string[S.top()] - '0') == tree[S.top()].size()) {
      if (S.size() == 1) {
        // The tree will be rooted at 0.
        return tree;
      }
      const int topop = S.top();
      S.pop();
      tree[S.top()].push_back(topop);
    }

  }
  assert(0);
}

std::pair<int, int> memo[10100][3];

std::pair<int, int> Compute(int x, int color, const vector<vector<int>>& tree) {
  const bool is_green = (color == 0);
  if (tree[x].empty()) {
    return make_pair(is_green, is_green);
  }

  auto& ret = memo[x][color];
  if (ret.first != -1) {
    return ret;
  }
  ret.first = 0;
  ret.second = 1000000;

  if (tree[x].size() == 1) {
    for (int child_color = 0; child_color < 3; ++child_color) {
      if (color != child_color) {
        auto sol = Compute(tree[x][0], child_color, tree);
        ret.first = max(ret.first, sol.first + is_green);
        ret.second = min(ret.second, sol.second + is_green);
      }
    }
  } else {
    assert(tree[x].size() == 2);
    for (int c1 = 0; c1 < 3; ++c1) {
      if (c1 == color) continue;
      for (int c2 = 0; c2 < 3; ++c2) {
        if (c2 == color || c2 == c1) continue;
        auto left = Compute(tree[x][0], c1, tree);
        auto right = Compute(tree[x][1], c2, tree);
        ret.first = max(ret.first, left.first + right.first + is_green);
        ret.second = min(ret.second, left.second + right.second + is_green);
      }
    }
  }

  return ret;
}

int main(void) {
  int num_test_cases;
  scanf("%d", &num_test_cases);
  for (int test_case = 0; test_case < num_test_cases; ++test_case) {
    static char buffer[10100]; scanf("%s", buffer);
    auto tree = ConstructTree(buffer);

    memset(memo, -1, sizeof memo);
    int max_green = 0;
    int min_green = 1000000;
    for (int color = 0; color < 3; ++color) {
      auto sol = Compute(0, color, tree);
      max_green = std::max(max_green, sol.first);
      min_green = std::min(min_green, sol.second);
    }
    printf("%d %d\n", max_green, min_green);
  }
  return 0;
}
