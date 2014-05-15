// Guess the Tree

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <list>
#include <numeric>
using namespace std;

int n, size[24], rem[24], children[24], parent[24];

bool rec(int x, int rem_zero, int children1) {
  if (x == n) {
    return children1 == 0 && rem_zero == n;
  }

  if (x == 0) {
    return rec(1, rem_zero, 0);
  } else {
    int begin = 0;
    if (size[x] == size[x-1]) {
      begin = parent[x-1];
    }
    for (int p = begin; p < x; ++p) {
      if (rem[p] >= size[x]) {
	rem[p] -= size[x];
	++children[p];
	parent[x] = p;
	int new_children1 = children1;
	if (children[p] == 1) ++new_children1;
	if (children[p] == 2) --new_children1;
	int new_rem_zero = rem_zero;
	if (rem[p] == 0) ++new_rem_zero;
	bool ret = rec(x+1, new_rem_zero, new_children1);
	if (ret) {
	  return ret;
	}
	--children[p];
	rem[p] += size[x];
      }
    }
  }

  return false;
}

bool dummy_no() {
  for (int x = 0; x < n; ++x) {
    int remaining = accumulate(size+x+1, size+n, 0);
    if (remaining < size[x]-1) { return true; }
  }
  return false;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", size+i);
  }

  sort(size, size+n, greater<int>());
  int rem_zero = 0;
  for (int i = 0; i < n; ++i) {
    rem[i] = size[i] - 1;
    if (rem[i] == 0) { ++rem_zero; }
  }
  memset(children, 0, n*(sizeof (int)));

  if (dummy_no()) {
    puts("NO");
  } else {
    puts(rec(0, rem_zero, 0)? "YES" : "NO");
  }

  return 0;
}
