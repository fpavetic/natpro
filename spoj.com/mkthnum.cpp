#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

struct Orthogonal2d {
  vector<vector<int> > v;
  int offset, n;

  Orthogonal2d(const vector<int>& a) {
    n = a.size();
    for (offset = 1; offset < n; offset <<= 1);
    v.resize(2*offset);

    //printf("offset=%d\n", offset);
    int leaf_start = offset - 1;
    for (int i = 0; i < n; ++i) {
      v[leaf_start+i].push_back(a[i]);
    }

    for (int i = leaf_start - 1; i >= 0; --i) {
      createNonLeafNode(i);
    }
  }
  
  void createNonLeafNode(int x) {
    int l = 0;
    int r = 0;
    while (l < v[2*x+1].size() || r < v[2*x+2].size()) {
      if (l == v[2*x+1].size()) v[x].push_back(v[2*x+2][r++]);
      else if (r == v[2*x+2].size()) v[x].push_back(v[2*x+1][l++]);
      else if (v[2*x+1][l] < v[2*x+2][r]) v[x].push_back(v[2*x+1][l++]);
      else v[x].push_back(v[2*x+2][r++]);
    }
  }

  int getLessEqual(int x, int lo, int hi, int l, int r, int c) {
    // printf("x=%d, lo=%d, hi=%d, l=%d, r=%d, c=%d\n",
    //        x, lo, hi, l, r, c);
    if (l <= lo && hi <= r) {
      int ret = upper_bound(v[x].begin(), v[x].end(), c) - v[x].begin();
      //      printf("returning %d/%d\n", ret, (int)v[x].size());
      return ret;
    }
    if (hi < l || lo > r) {
      return 0;
    }

    int m = (lo+hi)/2;
    return 
      getLessEqual(2*x+1, lo, m, l, r, c) +
      getLessEqual(2*x+2, m+1, hi, l, r, c);
  }

  int getKth(int l, int r, int k) {
    int bs_lo = 0;
    int bs_hi = n;
    int kth = 0;

    while (bs_lo <= bs_hi) {
      int bs_mid = (int)((long long)(bs_lo + bs_hi) / 2);
      int how_many = getLessEqual(0, 0, offset-1, l, r, bs_mid);

      if (how_many >= k) {
        kth = bs_mid;
        bs_hi = bs_mid - 1;
      } else {
        bs_lo = bs_mid + 1;
      }
    }

    return kth;
  }
};

int main(void) {
  int n, m; scanf("%d%d", &n, &m);
  
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  vector<int> compr = a;
  sort(compr.begin(), compr.end());
  for (int i = 0; i < n; ++i) {
    a[i] = lower_bound(compr.begin(), compr.end(), a[i]) - compr.begin();
  }
  
  Orthogonal2d o2d(a);
  for (int i = 0; i < m; ++i) {
    int l, r, k; 
    scanf("%d%d%d", &l, &r, &k);
    --l; --r;
    printf("%d\n", compr[o2d.getKth(l, r, k)]);
  }

  return 0;
}
