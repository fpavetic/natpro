#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


vector<int> v[100100];
int a[100100];

long long get(int r, int med) {
  long long ret = 0;
  for (int i = 0; i < v[r].size(); ++i) {
    ret += abs(med-v[r][i]);
  }
  
  //  cout << r << " " << med << " " << ret << endl;
  return ret;
}

int main(void) {
  int n, m; scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) scanf("%d", a+i);
  
  long long sol = 0;
  for (int i = 0; i < m; ++i) {
    //v[a[i]].push_back(a[i]);
    if (i && a[i] != a[i-1]) v[a[i]].push_back(a[i-1]);
    if (i+1 < m && a[i] != a[i+1]) v[a[i]].push_back(a[i+1]);
    
    if (i > 0) {
      sol += abs(a[i]-a[i-1]);
    }
    //    cerr << "sol: "<< sol << " a[i]:" << a[i] << endl;
  }

  long long anchor = sol;
  for (int i = 0; i <= n; ++i) {
    if (v[i].empty()) continue;
    
    //    printf("%d:", i);
    //    for (int j = 0; j < v[i].size(); ++j) printf(" %d", v[i][j]); puts("");

    long long tmp = anchor;
    tmp -= get(i, i);
    sort(v[i].begin(), v[i].end());
    tmp += get(i, v[i][((int)v[i].size()-1)/2]);
    sol = min(sol, tmp);
    //    cout << "sol: " << sol << endl;
  }

  cout << sol << endl;

  return 0;
}
