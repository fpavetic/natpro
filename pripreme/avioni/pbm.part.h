vector<Point2i> readPbm() {
  vector<Point2i> image;
  
  string format; cin >> format;
  int width, height;
  cin >> width >> height;

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      int pixel; cin >> pixel;
      if (pixel) {
        image.push_back(Point2i(c, r));
      }
    }
  }

  return image;
}

vector<Point2i> readPbm(const string& filename) {
  vector<Point2i> image;
  ifstream isimage(filename.c_str());

  string format; isimage >> format;
  int width, height;
  isimage >> width >> height;

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      int pixel; isimage >> pixel;
      if (pixel) {
        image.push_back(Point2i(c, r));
      }
    }
  }

  return image;
}

void outputPbm(const int width, const int height,
               const vector<vector<char> >& image, 
               const string& outpath) {
  ofstream out(outpath.c_str());
  out << "P1" << endl;
  out << width << " " << height << endl;
  for (int row = 0; row < height; ++row, out << endl) {
    for (int col = 0; col < width; ++col) {
      if (col) { out << " "; }
      out << (int)image[row][col];
    }
  }
}

void outputPbm(const int width, const int height,
               const vector<Point2i>& ones, 
               const string& outpath) {
  vector<vector<char> > image(height, vector<char>(width, 0));
  for (size_t i = 0; i < ones.size(); ++i) {
    image[ones[i].second][ones[i].first] = 1;
  }
  outputPbm(width, height, image, outpath);
}

void outputPbm(const vector<Point2i>& vec,
               const string& outpath) {
  for (size_t i = 0; i < vec.size(); ++i) {
    assert(vec[i].x < 640);
    assert(vec[i].y < 480);
  }
  outputPbm(640, 480, vec, outpath);
}

void outputPbm(const vector<complex<double> >& cvec,
               const string& outpath) {
  vector<Point2i> vec = toVecPoint2i(cvec);
  outputPbm(vec, outpath);
}
