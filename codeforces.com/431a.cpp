#include <cstdio>

int cal[4];
char s[100100];

int main(void) {
  scanf("%d%d%d%d", cal, cal+1, cal+2, cal+3);
  scanf("%s", s);
  
  int total = 0;
  for (char* p = s; *p; ++p) {
    total += cal[*p-'1'];
  }

  printf("%d\n", total);
  return 0;
}
