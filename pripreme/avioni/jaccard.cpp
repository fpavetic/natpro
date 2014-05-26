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

#define PB push_back
#define MP make_pair
#define SP samplePoints

vector<Point2i> samplePoints[7];

//PREPARE_SUBMISSION_HEADER
#include "helpers.part.h"
//PREPARE_SUBMISSION_HEADER
#include "pbm.part.h"
//PREPARE_SUBMISSION_HEADER
#include "geometry.part.h"
//PREPARE_SUBMISSION_HEADER
#include "training_data.part.h"

//#define LOCAL_DEBUG

double shapeSimilarity(const vector<Point2i>& boundary1,
                       const vector<Point2i>& boundary2) {
  int a = area(0, 479, 0, 639, &boundary1, NULL, NULL);
  int b = area(0, 479, 0, 639, NULL, &boundary2, NULL);
  int presjek = 
    area(0, 479, 0, 639, &boundary1, &boundary2, NULL);
  int unija = a + b - presjek;
  double jaccard = 1.0 * presjek / unija;
#ifdef LOCAL_DEBUG
  fprintf(stderr, "a=%d b=%d presjek=%d unija=%d jc=%lf\n", 
          a, b, presjek, unija, jaccard);
#endif
  return 1.0 * presjek / unija;
}

pair<double, int> estimateClass(const vector<Point2i>& query) {
  pair<double, int> estimate(-1, -1);

  for (int cl = 0; cl < 7; ++cl) {
    double similarity = 
      shapeSimilarity(query, samplePoints[cl]);
#ifdef LOCAL_DEBUG
    fprintf(stderr, "Class%d, similarity %lf\n", cl, similarity);
#endif

    if (similarity > estimate.first) {
      estimate.first = similarity;
      estimate.second = cl;
    }
  }
  return estimate;
}

int main(void) {
  srand(1603);
  fillSamplePoints();  

  const int kSample = 20;
  for (int cl = 0; cl < 7; ++cl) {
    // printf("cl=%d, points=%d\n", 
    //        cl, (int)samplePoints[cl][0].size());
    samplePoints[cl] = getBoundary(samplePoints[cl]);
    normalizeAngle(samplePoints[cl]);
    normalize(samplePoints[cl]);
    samplePoints[cl] = sample(samplePoints[cl], kSample);
    //outputPbm(samplePoints[cl][0], "debug1.pbm");
    // printf("cl=%d, points=%d\n", 
    //        cl, (int)samplePoints[cl][0].size());
    //normalize(samplePoints[cl][0]);
    //outputPbm(samplePoints[cl][0], "debug2.pbm");
    // printf("cl=%d, points=%d\n", 
    //        cl, (int)samplePoints[cl][0].size());
  }

  vector<Point2i> testImage = readPbm();
  testImage = getBoundary(testImage);
  normalizeAngle(testImage);
  normalize(testImage);
  testImage = sample(testImage, kSample);

#ifdef LOCAL_DEBUG
  for (int i = 0; i < 7; ++i) {
    if (samplePoints[i][0] == testImage) {
      fprintf(stderr, "Testna slika je jedna od samplova!\n");
      
      vector<Point2i> a = getBoundary(samplePoints[i]);
      vector<Point2i> b = getBoundary(testImage);
      
      fprintf(stderr, "Slicnost nenormaliziranih: %lf\n",
              shapeSimilarity(a, b));
      normalize(a);
      normalize(b);
      fprintf(stderr, "Slicnost normaliziranih: %lf\n",
              shapeSimilarity(a, b));
    }
  }
#endif
  
  pair<double, int> best_estimate(-1, -1);
  for (int angle_deg = 0; angle_deg < 360; angle_deg += 360) {
    double angle_rad = angle_deg / 180.0 * M_PI;
    vector<Point2i> rotated = rotate(testImage, angle_rad);
    normalize(rotated);

    pair<double, int> estimate = estimateClass(rotated);
    if (estimate.first > best_estimate.first) {
      best_estimate = estimate;
    }

#ifdef LOCAL_DEBUG
    char rotated_image_file[32];
    char rotated_result_file[32];
    sprintf(rotated_image_file, "debug/%03d.pbm", angle_iter);
    sprintf(rotated_result_file, "debug/%03d.res", angle_iter);

    vector<Point2i> angle_estimate = 
      samplePoints[estimate.second][0];
    normalize(angle_estimate);

    vector<Point2i> joint;
    joint.insert(joint.end(), 
                 rotatedBoundary.begin(), rotatedBoundary.end());
    joint.insert(joint.end(), 
                 angle_estimate.begin(), angle_estimate.end());
    outputPbm(joint, rotated_image_file);
    ofstream ofs(rotated_result_file);
    ofs << estimate.first << " " << estimate.second << endl;
    ofs.close();
#endif
  }

#ifdef LOCAL_DEBUG
  fprintf(stderr, "best estimate score=%lf\n", best_estimate.first);
#endif
  cout << best_estimate.second + 1 << endl;

  return 0;
}
