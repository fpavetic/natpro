#include <cstdio>
#include <cstring>

char tabla[2020][1010];
int x = 0, y = 1010;

int main(void) {
  memset(tabla, ' ', sizeof tabla);
  int n; scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    int a; scanf("%d", &a);
    
    int dx = 1;
    int dy = (i % 2 == 0? -1: +1);
    for (; a; --a) {
      tabla[y][x] = (i % 2 == 0? '/': '\\');
      //printf("%d %d %c\n", y, x, tabla[y][x]);
      y += dy;
      x += dx;
    }
    y -= dy;
    //x += dx;
  }

  for (int y = 0; y < 2020; ++y) {
    int prazna = true;
    for (int x = 1009; x > 0; --x) {
      if (tabla[y][x-1] != ' ') {
        tabla[y][::x] = '\0';
        prazna = false;
        break;
      }
    }
    if (!prazna) {
      printf("%s\n", tabla[y]);
    }
  }

  return 0;
}
