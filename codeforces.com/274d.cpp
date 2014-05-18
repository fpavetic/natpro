#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>
#include <queue>
#include <set>
#include <list>
#include <vector>
using namespace std;

int r, c;
vector<vector<int> > matr;
vector<int> graf[200100];
int color[200100], indegree[200100], n;

bool dfs_cycle(int s) {
  if (color[s] == 1) { return true; }
  if (color[s] == 2) { return false; }
  color[s] = 1;

  for (int u: graf[s]) {
    if (dfs_cycle(u)) {
      return true;
    }
  }

  color[s] = 2;
  return false;
}

int main(void) {
  scanf("%d%d", &r, &c);
  matr = vector<vector<int> >(r, vector<int>(c));
  n = c;

  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      scanf("%d", &matr[i][j]);
    }

    vector<pair<int, int> > nums;
    for (int j = 0; j < c; ++j) {
      if (matr[i][j] != -1) {
        nums.push_back(make_pair(matr[i][j], j));
      }
    }
    
    sort(nums.begin(), nums.end());
    //    printf("RED %d, sz=%d\n", i, (int)nums.size());
    for (size_t j = 1; j < nums.size(); ++j) {
      if (nums[j].first != nums[j-1].first) {
        for (int k = j-1; k >= 0 && nums[k].first == nums[j-1].first; --k) {
          //          printf("%d -> %d\n", nums[k].second, n);
          graf[nums[k].second].push_back(n);
        }
        for (int k = j; k < nums.size() && nums[k].first == nums[j].first; ++k) {
          //          print("%d -> %d\n", n, nums[k].second);
          graf[n].push_back(nums[k].second);
        }
        ++n;
        assert(n < 200100);
      }
    }
  }

  memset(color, 0, sizeof color);
  for (int i = 0; i < n; ++i) {
    if (color[i] == 0 && dfs_cycle(i)) {
      puts("-1");
      return 0;
    }
  }

  memset(indegree, 0, sizeof indegree);
  for (int s = 0; s < n; ++s) {
    for (int u : graf[s]) {
      ++indegree[u];
    }
  }

  queue<int> q;
  for (int s = 0; s < n; ++s) {
    if (indegree[s] == 0) {
      q.push(s);
    }
  }

  assert(!q.empty());

  vector<int> sol;
  while (!q.empty()) {
    int s = q.front();
    q.pop();

    if (s < c) {
      sol.push_back(s);
    }

    for (int x: graf[s]) {
      if (--indegree[x] == 0) {
          q.push(x);
      }
    }
  }

  assert(sol.size() == c);
  for (int i = 0; i < (int)sol.size(); ++i) {
    if (i) printf(" ");
    printf("%d", sol[i]+1);
  }
  puts("");

  return 0;
}
