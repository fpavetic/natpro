#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main(void) {
  int n, m; 
  scanf("%d%d", &n, &m);
  vector<int> points(n);
  for (int i = 0; i < n; ++i) scanf("%d", &points[i]);
  int dummy;
  for (int i = 0; i < m+m; ++i) scanf("%d", &dummy);
  
  vector<int> sorted = points;
  sort(sorted.begin(), sorted.end());
  vector<int> color(n);
  
  for (int i = 0; i < n; ++i) {
    int sorted_idx = 
      lower_bound(sorted.begin(), sorted.end(), points[i]) -
      sorted.begin();
    color[i] = sorted_idx%2;
  }
  
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", color[i]);
  }
  puts("");
  
  return 0;
}
