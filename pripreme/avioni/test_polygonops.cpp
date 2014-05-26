#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <complex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> Point2i;
#define x first
#define y second

#include "helpers.part.h"
#include "pbm.part.h"
#include "geometry.part.h"

int main(int argc, char* argv[]) {
  vector<Point2i> img1 = readPbm(argv[1]);
  vector<Point2i> img2 = readPbm(argv[2]);

  double start_get_boundary = clock();
  vector<Point2i> boundary1 = getBoundary(img1);
  vector<Point2i> boundary2 = getBoundary(img2);
  normalize(boundary1);
  normalize(boundary2);
  // boundary1 = sample(boundary1, 20);
  // boundary2 = sample(boundary2, 20);
  outputPbm(boundary1, "boundary1.pbm");
  outputPbm(boundary2, "boundary2.pbm");
  fprintf(stderr, "Boundary calculation: %lf\n",
          (clock()-start_get_boundary)/CLOCKS_PER_SEC);

  vector<vector<char> > colored;

  double start_coloring = clock();
  puts("Bojam rekurzivno...");
  colored = vector<vector<char> > (480, vector<char>(640, 0));
  int a = area(0, 479, 0, 639, &boundary1, NULL, &colored);
  outputPbm(640, 480, colored, "colored1.pbm");
  colored = vector<vector<char> > (480, vector<char>(640, 0));
  int b = area(0, 479, 0, 639, NULL, &boundary2, &colored);
  outputPbm(640, 480, colored, "colored2.pbm");
  colored = vector<vector<char> > (480, vector<char>(640, 0));
  int presjek = 
    area(0, 479, 0, 639, &boundary1, &boundary2, &colored);
  outputPbm(640, 480, colored, "colored12.pbm");
  int unija = a + b - presjek;
  printf("Obojao! Slicnost %lf\n", 1.0 * presjek / unija);
  fprintf(stderr, "Coloring time: %lf\n",
          (clock()-start_coloring)/CLOCKS_PER_SEC);

  return 0;
}
