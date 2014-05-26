#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "pbm_to_vec <classId> <sampleId>" << endl;
    return 1;
  }

  int ClassNum; sscanf(argv[1], "%d", &ClassNum);
  string Class = argv[1];
  int SampleNum; sscanf(argv[2], "%d", &SampleNum);
  string Sample = argv[2];

  string filename = 
    string("Class")+Class+
    string("_Sample")+Sample+".pbm";
  cerr << "Reading image from " << filename << endl;
  ifstream inpbm(filename.c_str());

  string format; inpbm >> format;
  int width, height; inpbm >> width >> height;
  cerr << "Image size: " << width << " x " << height << endl;

  cout << "void fillSamplePointsClass" << Class <<
    "Sample" << Sample << "() {" << endl;

  vector<pair<int, int> > points;
  vector<int> serialized;

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      int pixel; inpbm >> pixel;
      if (pixel) {
        // cout << "  SP[" << (ClassNum-1) << "].PB(MP(" << c <<
        //   "," << r << "));" << endl;
        points.push_back(make_pair(c, r));
        serialized.push_back(c);
        serialized.push_back(r);
      }
    }
  }

  cout << "  int t["<<serialized.size()<<"] = {";
  for (int i = 0; i < serialized.size(); ++i) {
    if (i) cout << ",";
    cout << " " << serialized[i];
  }
  cout << " };" << endl;

  cout << "  for (int i = 0; i < " << 
    points.size() << "; ++i) {" << endl;
  cout << "    SP[" << (ClassNum-1) << "].push_back(make_pair("
       << "t[2*i], t[2*i+1]));" << endl;
  cout << "  }" << endl;
  cout << "}" << endl;

  return 0;
}
