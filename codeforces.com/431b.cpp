#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int h[5][5];

int main(void) {
  vector<int> v(5);
  for (int i = 0; i < 5; ++i) {
    v[i] = i;
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      scanf("%d", &h[i][j]);
    }
  }

  int best = 0;
  do {
    int curr = 0;
    
    for (int start = 0; start < 5; ++start) {
      for (int i = start; i + 1 < 5; i += 2) {
        curr += h[v[i]][v[i+1]];
        curr += h[v[i+1]][v[i]];
      }
    }
    best = max(best, curr);
  } while(next_permutation(v.begin(), v.end()));

  printf("%d\n", best);
  return 0;
}
