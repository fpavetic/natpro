#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int R, C, m[1010][1010];
long long dolje_desno[1010][1010];
long long dolje_lijevo[1010][1010];
long long gore_desno[1010][1010];
long long gore_lijevo[1010][1010];

int main(void) {
  scanf("%d%d", &R, &C);
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      scanf("%d", &m[i][j]);
    }
  }
  
  dolje_desno[0][0] = m[0][0];
  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      if (r == 0 && c == 0) continue;
      
      long long best = 0;
      if (r-1 >= 0) best = max(best, dolje_desno[r-1][c]+m[r][c]);
      if (c-1 >= 0) best = max(best, dolje_desno[r][c-1]+m[r][c]);
      dolje_desno[r][c] = best;
    }
  }

  dolje_lijevo[0][C-1] = m[0][C-1];
  for (int r = 0; r < R; ++r) {
    for (int c = C-1; c >= 0; --c) {
      if (r == 0 && c == C-1) continue;
      
      long long best = 0;
      if (r-1 >= 0) best = max(best, dolje_lijevo[r-1][c]+m[r][c]);
      if (c+1 < C) best = max(best, dolje_lijevo[r][c+1]+m[r][c]);
      dolje_lijevo[r][c] = best;
    }
  }

  gore_desno[R-1][0] = m[R-1][0];
  for (int r = R-1; r >= 0; --r) {
    for (int c = 0; c < C; ++c) {
      if (r == R-1 && c == 0) continue;

      long long best = 0;
      if (r+1 < R) best = max(best, gore_desno[r+1][c]+m[r][c]);
      if (c-1 >= 0) best = max(best, gore_desno[r][c-1]+m[r][c]);
      gore_desno[r][c] = best;
    }
  }

  gore_lijevo[R-1][C-1] = m[R-1][C-1];
  for (int r = R-1; r >= 0; --r) {
    for (int c = C-1; c >= 0; --c) {
      if (r == R-1 && c == C-1) continue;
      
      long long best = 0;
      if (r+1 < R) best = max(best, gore_lijevo[r+1][c]+m[r][c]);
      if (c+1 < C) best = max(best, gore_lijevo[r][c+1]+m[r][c]);
      gore_lijevo[r][c] = best;
    }
  }

  long long best = 0;
  for (int r = 1; r+1 < R; ++r) {
    for (int c = 1; c+1 < C; ++c) {
      for (int m1 = 0; m1 < 2; ++m1) {
        long long tmp = 0;
        if (m1 == 0) {
          tmp += dolje_desno[r-1][c];
          tmp += gore_lijevo[r+1][c];
          tmp += gore_desno[r][c-1];
          tmp += dolje_lijevo[r][c+1];
        } else {
          tmp += dolje_desno[r][c-1];
          tmp += gore_lijevo[r][c+1];
          tmp += gore_desno[r+1][c];
          tmp += dolje_lijevo[r-1][c];
        }
        best = max(best, tmp);
      }
    }
  }

  cout << best << endl;
  return 0;
}
