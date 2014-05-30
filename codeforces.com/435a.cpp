#include <cstdio>



int main(void) {
  int n, m; scanf("%d%d", &n, &m);

  int curr_bus = 0;
  int buses = 1;

  for (int i = 0; i < n; ++i) {
    int a; scanf("%d", &a);
    if (curr_bus + a <= m) curr_bus += a;
    else {
      ++buses;
      curr_bus = a;
    }
  }

  printf("%d\n", buses);
  return 0;
}
