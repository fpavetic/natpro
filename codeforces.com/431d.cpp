#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;

typedef unsigned long long int ull;

int bitWidth(ull m) {
  int bw = 0;
  for ( ; m; m >>= 1) {
    ++bw;
  }
  return bw;
}

ull memo[64][64][2];

ull rec(int bit, int rem1, int prefix_matches,
        const ull& n, const int bw) {
  if (rem1 < 0) return 0;
  if (bit == bw) return rem1 == 0;

  ull& ret = memo[bit][rem1][prefix_matches];
  if (ret != -1) return ret;
  ret = 0;

  int bith = (n & 1ULL<<(bw-1-bit)) > 0;

  // 0
  ret += rec(bit+1, rem1, prefix_matches && bith == 0, n, bw);

  // 1
  if (!prefix_matches || bith == 1) {
    ret += rec(bit+1, rem1-1, prefix_matches && bith == 1, n, bw);
  }

  return ret;
}

// koliko ih je u [0...n]
ull f(ull n, ull k) {
  int bw = bitWidth(n);
  //cout << "n:" << n << " bw:" << bw << endl;
  memset(memo, -1, sizeof memo);
  return rec(0, k, 1, n, bw);
}

int main(void) {
  //cout << f(7, 2) << " " << f(14, 2) << endl;
  //cout << f(2, 1) << " " << f(1, 1) << endl;
  //cout << f(4, 1) << " " << f(2, 1) << endl;
  ull m; int k;
  cin >> m >> k;

  ull lo = 1;
  ull hi = 1000000000000000000ULL;
  
  while (lo <= hi) {
    ull x = (lo + hi) / 2;

    ull fu = f(2*x, k);
    ull fl = f(x, k);
    ull fx = fu - fl;
    //cout << x << " fl:" << fl << " fu:" << fu << " fx:" << fx << endl;
    
    if (fx > m) {
      hi = x - 1;
    } else if (fx < m) {
      lo = x + 1;
    } else {
      cout << x << endl;
      break;
    }
  }
  return 0;
}
