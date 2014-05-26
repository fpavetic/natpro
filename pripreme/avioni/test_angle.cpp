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


int main(void) {
  vector<Point2i> img = readPbm();
  double angle = getAngle(img);
  printf("Angle in deg %lf\n", angle * 180 / M_PI);
  vector<Point2i> rotated = rotate(img, angle);
  normalize(rotated);
  outputPbm(rotated, "rotated.pbm");
  return 0;
}
