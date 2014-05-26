vector<complex<double> > toVecComplex(const vector<Point2i>& vec) {
  vector<complex<double> > cvec;
  for (size_t i = 0; i < vec.size(); ++i) {
    cvec.push_back(complex<double>(vec[i].first, vec[i].second));
  }
  return cvec;
}

vector<Point2i> toVecPoint2i(const vector<complex<double> >& cvec) {
  vector<Point2i> vec;
  for (size_t i = 0; i < cvec.size(); ++i) {
    vec.push_back(make_pair((int)cvec[i].real(),
                            (int)cvec[i].imag()));
  }
  return vec;
}

bool cmpComplex(const complex<double>& a,
                const complex<double>& b) {
  if (a.real() != b.real()) {
    return a.real() < b.real();
  }
  return a.imag() < b.imag();
}

double sqr(const double& x) { return x*x; }

// angle in radians
vector<Point2i> rotate(const vector<Point2i>& points,
                       const double& angle) {
  vector<Point2i> rotated;
  complex<double> rotnum(cos(angle), sin(angle));
  for (size_t i = 0; i < points.size(); ++i) {
    complex<double> point(1.0*points[i].x, 1.0*points[i].y);
    point *= rotnum;
    rotated.push_back(
      Point2i((int)point.real(), (int)point.imag()));
  }

  return rotated;
}

Point2i centerOfMass(const vector<Point2i>& points) {
  int sumx = 0;
  int sumy = 0;
  int n = points.size();
  for (size_t i = 0; i < points.size(); ++i) {
    sumx += points[i].x;
    sumy += points[i].y;
  }
  return Point2i(sumx/n, sumy/n);
}
