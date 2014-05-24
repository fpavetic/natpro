#include <cassert>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

struct intervalna {
  set<pair<int, int> > S;

  void insert(int x) {
    pair<int, int> prev(-10, -10);
    pair<int, int> next(-10, -10);
    auto it = S.insert(make_pair(x, x)).first;
    auto pit = it;
    if (pit != S.begin()) { --pit; prev = *pit; }
    auto nit = it; ++nit;
    if (nit != S.end()) { next = *nit; }

    S.erase(it);
    pair<int, int> to_insert(x, x);
    if (prev.second + 1 == x) {
      S.erase(prev);
      to_insert.first = prev.first;
    }
    if (next.first - 1 == x) {
      S.erase(next);
      to_insert.second = next.second;
    }
    S.insert(to_insert);
  }

  pair<int, int> get(int x) {
    if (S.empty()) return make_pair(-1, -1);
    pair<int, int> ret = *--S.upper_bound(make_pair(x,1000000000));
    if (ret.first <= x && x <= ret.second) return ret;
    return make_pair(-1, -1);
  }

  void remove(int x) {
    pair<int, int> ima_x = get(x);
    assert(ima_x.first != -1);
    pair<int, int> left(ima_x.first, x-1);
    pair<int, int> right(x+1, ima_x.second);
    S.erase(ima_x);
    if (left.first <= left.second) S.insert(left);
    if (right.first <= right.second) S.insert(right);
  }
};

int solve(const vector<pair<int, int> >& v) {
  if (v.empty()) return 0;
  int sol = v[0].second-v[0].first+1;
  pair<int, int> b = v[0];

  for (size_t i = 0; i < v.size(); ++i) {
    b.first = max(b.first, v[i].first);
    b.second = min(b.second, v[i].second);
    int tmp = (i+1) * (b.second-b.first+1);
    sol = max(sol, tmp);
  }

  return sol;
}

int tabla[1010][1010], r, s, q;
intervalna retkasta[1010];
intervalna stupcasta[1010];

int main(void) {
  scanf("%d%d%d", &r, &s, &q);
  
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < s; ++j) {
      scanf("%d", &tabla[i][j]);
      if (tabla[i][j]) {
        retkasta[i].insert(j);
        stupcasta[j].insert(i);
      }
    }
  }

  for (int op = 0; op < q; ++op) {
    int o, x, y; scanf("%d%d%d", &o, &x, &y);
    --x; --y;

    if (o == 1) {
      if (tabla[x][y] == 0) {
        retkasta[x].insert(y);
        stupcasta[y].insert(x);
        tabla[x][y] = 1;
      } else {
        retkasta[x].remove(y);
        stupcasta[y].remove(x);
        tabla[x][y] = 0;
      }
    } else {
      vector<pair<int, int> > a, b, c, d;
      for (int i = x; i < r; ++i) {
        auto p = retkasta[i].get(y);
        //printf("a %d %d %d\n", i, p.first, p.second);
        if (p.first != -1) a.push_back(p);
        else break;
      }
      for (int i = x; i >= 0; --i) {
        auto p = retkasta[i].get(y);
        //printf("b %d %d %d\n", i, p.first, p.second);
        if (p.first != -1) b.push_back(p);
        else break;
      }
      for (int j = y; j < s; ++j) {
        auto p = stupcasta[j].get(x);
        //printf("c %d %d %d\n", j, p.first, p.second);
        if (p.first != -1) c.push_back(p);
        else break;
      }
      for (int j = y; j >= 0; --j) {
        auto p = stupcasta[j].get(x);
        //printf("d %d %d %d\n", j, p.first, p.second);
        if (p.first != -1) d.push_back(p);
        else break;
      }

      int sola = solve(a);
      int solb = solve(b);
      int solc = solve(c);
      int sold = solve(d);

      printf("%d\n", max(max(sola, solb), max(solc, sold)));
    }
  }
  return 0;
}
