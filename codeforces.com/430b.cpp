#include <cstdio>
#include <vector>
using namespace std;

void destroy(vector<int>& balls) {
  while (balls.size() >= 3) {
    int n = balls.size();
    vector<int> d(n, 0);
    
    for (int i = 2; i < n; ++i) {
      if (balls[i] == balls[i-1] && balls[i-1] == balls[i-2]) {
        d[i] = d[i-1] = d[i-2] = 1;
      }
    }

    vector<int> new_balls;
    for (int i = 0; i < n; ++i) {
      if (!d[i]) {
        new_balls.push_back(balls[i]);
      }
    }
    
    if (balls == new_balls) {
      return;
    }
    balls = new_balls;
  }
}

int main(void) {
  int n, k, x;
  scanf("%d%d%d", &n, &k, &x);

  vector<int> balls(n);
  for (int i = 0; i < n; ++i) scanf("%d", &balls[i]);

  int sol = 0;
  for (int i = 1; i < balls.size(); ++i) {
    vector<int> new_balls;
    for (int j = 0; j < i; ++j) {
      new_balls.push_back(balls[j]);
    }
    new_balls.push_back(x);
    for (int j = i; j < balls.size(); ++j) {
      new_balls.push_back(balls[j]);
    }

    destroy(new_balls);
    sol = max(sol, (int)(balls.size()-new_balls.size()));
  }

  printf("%d\n", sol);
  return 0;
}
