#include <cstdio>
#include <algorithm>
using namespace std;

long long count_factors(int n, int p) {
  long long num_zeros = 0;
  long long p_power = 1;
  for (int i = 1; p_power <= n; ++i) {
    p_power *= p;
    long long contrib = n / p_power;
    num_zeros += contrib;
  }
  return num_zeros;

}

long long z(int n) {
  return std::min(count_factors(n, 2), count_factors(n, 5));
}

int main(void) {
  int num_test_cases;
  scanf("%d", &num_test_cases);
  for (int test_case = 0; test_case < num_test_cases; ++test_case) {
    int n; scanf("%d", &n);
    printf("%lld\n", z(n));
  }
  return 0;
}
