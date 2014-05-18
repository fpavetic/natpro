#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;

list<int> graf[100100];
int init[100100];
int goal[100100];

void rec(int x, int anc, int flip_mask, int depth_parity,
        vector<int>& reconstruction) {
  init[x] ^= ((flip_mask>>depth_parity)&1);
  if (init[x] != goal[x]) {
    flip_mask ^= (1<<depth_parity);
    init[x] ^= 1;
    reconstruction.push_back(x);
  }
  
  for (list<int>::iterator it = graf[x].begin();
       it != graf[x].end(); ++it) {
    if (*it == anc) { continue; }
    rec(*it, x, flip_mask, 1-depth_parity, reconstruction);
  }
}

int main(void) {
  int n; scanf("%d", &n);
  
  for (int i = 1; i < n; ++i) {
    int a, b; scanf("%d%d", &a, &b);
    --a; --b;
    graf[a].push_back(b);
    graf[b].push_back(a);
  }
  for (int i = 0; i < n; ++i) scanf("%d", init+i);
  for (int i = 0; i < n; ++i) scanf("%d", goal+i);

  vector<int> recon;
  rec(0, -1, 0, 0, recon);
  printf("%d\n", (int)recon.size());
  for (int i = 0; i < recon.size(); ++i) {
    printf("%d\n", recon[i]+1);
  }

  return 0;
}
