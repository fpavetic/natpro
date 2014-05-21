#include <cstdio>
#include <cstring>



int memo[101][2];
int n, k, d;

int rec(int x, int hasd) {
  if (x == 0) return hasd;
  if (x < 0) return 0;
  
  int& ret = memo[x][hasd];
  if (ret >= 0) return ret;

  ret = 0;
  for (int c = 1; c <= k; ++c) {
    ret += rec(x-c, hasd||(c >= d));
    ret %= 1000000007;
  }
  return ret;
}

int main(void) {
  scanf("%d%d%d", &n, &k, &d);
  memset(memo, -1, sizeof memo);
  printf("%d\n", rec(n, 0));
  return 0;
}
