#include <cstdio>
#include <set>
#include <vector>
using namespace std;

int main(void) {
  int n, k;
  scanf("%d%d", &n, &k);
  set<int> alive;
  for (int i = 0; i < n; ++i) {
    int a; scanf("%d", &a);
    alive.insert(a);
  }

  set<int> dead;
  for (auto it = alive.begin(); it != alive.end(); ++it) {
    long long target = (long long)k * (*it);
    if (*it < target && target <= 1000000000 && !dead.count(*it)) {
      dead.insert((int)target);
    }
  }
  
  while (!dead.empty()) {
    alive.erase(*dead.begin());
    dead.erase(dead.begin());
  }

  // for (auto it = alive.begin(); it != alive.end(); ++it) {
  //   printf(":: %d\n", *it);
  // }

  printf("%d\n", (int)alive.size());

  return 0;
}
