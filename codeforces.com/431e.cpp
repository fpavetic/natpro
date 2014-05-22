#include <cassert>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct Sazimaljka {
  vector<long long> vec;
  
  void add(long long x) {
    vec.push_back(x);
  }
  
  void init() {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
  }

  int getIndex(long long x) {
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin();
  }
};

struct Node {
  long long sum;
  int alive;
  long long mx;

  Node() {
    sum = 0;
    alive = 0;
    mx = 0;
  }
};

struct Tournament {
  vector<Node> v;
  int offset;
  
  Tournament(int n) {
    for (offset = 1; offset < n; offset <<= 2);
    v.resize(2*offset);
  }

  void updateNode(int x) {
    v[x].sum = v[x*2+1].sum + v[x*2+2].sum;
    v[x].alive = v[x*2+1].alive + v[x*2+2].alive;
    v[x].mx = max(v[x*2+1].mx, v[x*2+2].mx);
  }

  void update(int x, int lo, int hi, int pos, 
              int sgn, long long val) {
    if (hi < pos || lo > pos) return;
    if (pos <= lo && hi <= pos) {
      v[x].sum += sgn*val;
      v[x].alive += sgn;
      v[x].mx = (v[x].alive == 0? 0: val);
    } else {
      update(x*2+1, lo, (lo+hi)/2, pos, sgn, val);
      update(x*2+2, (lo+hi)/2+1, hi, pos, sgn, val);
      updateNode(x);
    }
  }

  void add(int pos, long long val) {
    update(0, 0, offset-1, pos, +1, val);
  }
  void remove(int pos, long long val) {
    update(0, 0, offset-1, pos, -1, val);
  }
 

  double query(int x, int lo, int hi, long long val, 
               long long pending_sum, long long pending_alive) {
    if (lo == hi) {
      assert(v[x].alive);
      return (val + pending_sum) / (double)pending_alive;
    } else {
      const Node& left = v[x*2+1];
      long long sum = pending_sum + left.sum;
      long long alive = pending_alive + left.alive;

      if (sum + val <= alive * left.mx) {
        return query(x*2+1, lo, (lo+hi)/2, val, 
                     pending_sum, pending_alive);
      } else {
        return query(x*2+2, (lo+hi)/2+1, hi, val,
                     sum, alive);
      }
    }
  }

  double query(long long val) {
    return query(0, 0, offset-1, val, 0, 0);
  }
};

int main(void) {
  vector<pair<int, long long> > ops;
  int n, q; scanf("%d%d", &n, &q);

  Sazimaljka sazimaljka;  
  vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
    sazimaljka.add(h[i]);
  }
  for (int i = 0; i < q; ++i) {
    int comm; cin >> comm;
    if (comm == 1) {
      int p, x;
      cin >> p >> x;
      sazimaljka.add(x);
      ops.push_back(make_pair(p-1, x));
    } else {
      long long v;
      cin >> v;
      ops.push_back(make_pair(-1, v));
    }
  }

  const long long brana = (long long)1e16;
  sazimaljka.add(brana); // brana s desna
  sazimaljka.init();

  Tournament t(sazimaljka.vec.size());

  t.add(sazimaljka.getIndex(brana), brana);
  for (int i = 0; i < n; ++i) {
    t.add(sazimaljka.getIndex(h[i]), h[i]);
  }

  for (int i = 0; i < q; ++i) {
    if (ops[i].first != -1) {
      int p = ops[i].first;
      t.remove(sazimaljka.getIndex(h[p]), h[p]);
      h[p] = ops[i].second;
      t.add(sazimaljka.getIndex(h[p]), h[p]);
    } else {
      printf("%0.5lf\n", t.query(ops[i].second));
    }
  }

  return 0;
}
