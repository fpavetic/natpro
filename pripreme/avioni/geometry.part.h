vector<Point2i> getBoundary(const vector<Point2i>& img) {
  int rows = 0;
  int cols = 0;
  for (size_t i = 0; i < img.size(); ++i) {
    rows = max(rows, img[i].y+1);
    cols = max(cols, img[i].x+1);
  }

  vector<vector<char> > bitmap(rows, vector<char>(cols, 0));
  for (size_t i = 0; i < img.size(); ++i) {
    bitmap[img[i].y][img[i].x] = 1;
  }

  int curr_r, curr_c;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (bitmap[r][c]) {
        curr_r = r;
        curr_c = c;
        break;
      }
    }
  }

  // Ovako su numerirani susjedi.
  // 123
  // 0X4
  // 765
  // opp je popis simetricnih susjeda obzirom
  // na X za svakog susjeda.
  const int dr[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
  const int dc[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
  const int opp[8] = { 4, 5, 6, 7, 0, 1, 2, 3 };

  bitmap[curr_r][curr_c] = 2;
  int prev = 0;

  vector<Point2i> boundary;
  for ( ;;) {
    //    printf("curr_r=%d, curr_c=%d\n", curr_r, curr_c);
    boundary.push_back(Point2i(curr_c, curr_r));

    bool found = false;
    for (int i = 1; i < 8; ++i) {
      int next = (prev + i) % 8;
      int nr = curr_r + dr[next];
      int nc = curr_c + dc[next];
      if (nr < 0 || nr >= rows) continue;
      if (nc < 0 || nc >= cols) continue;
      if (bitmap[nr][nc] == 2) break;
      if (bitmap[nr][nc] == 1) {
        curr_r = nr;
        curr_c = nc;
        prev = opp[next];
        found = true;
        break;
      }
    }
    
    if (!found) {
      break;
    }
  }

  return boundary;
}

int ccw(const Point2i& a, const Point2i& b, const Point2i& c) {
  int t = 
    (b.x-a.x)*(c.y-a.y) -
    (c.x-a.x)*(b.y-a.y);

  if (t > 0) return +1;
  if (t < 0) return -1;
  return 0;
}

bool inbox(const Point2i& a, const Point2i& b, const Point2i& c) {
  return 
    min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) &&
    min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

bool intersects(const Point2i& a, const Point2i& b,
                const Point2i& c, const Point2i& d) {
  int abc = ccw(a, b, c);
  int abd = ccw(a, b, d);
  int cda = ccw(c, d, a);
  int cdb = ccw(c, d, b);
  if (abc * abd < 0 && cda * cdb < 0) {
    return true;
  }

  if (abc == 0 && inbox(a, b, c)) return true;
  if (abd == 0 && inbox(a, b, d)) return true;
  if (cda == 0 && inbox(c, d, a)) return true;
  if (cdb == 0 && inbox(c, d, b)) return true;

  return false;
}


bool pointInsidePolygon(const Point2i& point, 
                        const vector<Point2i>& poly) {
  Point2i ref(-1023, -150);
  int cnt = 0;

  for (size_t i = 0; i < poly.size(); ++i) {
    cnt += intersects(point, ref, poly[i], poly[(i+1)%poly.size()]);
  }
  
  return cnt % 2 == 1;
}

int area(int lo_r, int hi_r, int lo_c, int hi_c,
         const vector<Point2i>* boundary1,
         const vector<Point2i>* boundary2,
         vector<vector<char> >* image) {
  if (lo_r > hi_r) return 0;
  if (lo_c > hi_c) return 0;
  //  printf("%d %d %d %d\n", lo_r, hi_r, lo_c, hi_c);

  int dr = hi_r - lo_r + 1;
  int dc = hi_c - lo_c + 1;
  const int dlimit = 5;

  Point2i a(lo_c, lo_r);
  Point2i b(lo_c, hi_r);
  Point2i c(hi_c, lo_r);
  Point2i d(hi_c, hi_r);
  
  if ((!boundary1 || pointInsidePolygon(a, *boundary1)) &&
      (!boundary1 || pointInsidePolygon(b, *boundary1)) &&
      (!boundary1 || pointInsidePolygon(c, *boundary1)) &&
      (!boundary1 || pointInsidePolygon(d, *boundary1)) &&
      (!boundary2 || pointInsidePolygon(a, *boundary2)) && 
      (!boundary2 || pointInsidePolygon(b, *boundary2)) &&
      (!boundary2 || pointInsidePolygon(c, *boundary2)) &&
      (!boundary2 || pointInsidePolygon(d, *boundary2))) {
    if (image != NULL) {
      for (int r = lo_r; r <= hi_r; ++r) {
        for (int c = lo_c; c <= hi_c; ++c) {
          (*image)[r][c] = 1;
        }
      }
    }
    return dr * dc;
  } else if (dr > dlimit && dc > dlimit) { // recursive split
    int mid_r = (lo_r+hi_r)/2;
    int mid_c = (lo_c+hi_c)/2;

    return
      + area(lo_r, mid_r, lo_c, mid_c, 
             boundary1, boundary2, image)
      + area(lo_r, mid_r, mid_c+1, hi_c, 
             boundary1, boundary2, image)
      + area(mid_r+1, hi_r, lo_c, mid_c, 
             boundary1, boundary2, image)
      + area(mid_r+1, hi_r, mid_c+1, hi_c, 
             boundary1, boundary2, image);
  }
  
  return 0;
}

vector<Point2i> sample(const vector<Point2i>& boundary,
                       const int sample_rate) {
  vector<Point2i> sampled;
  for (size_t i = 0; i < boundary.size(); i += sample_rate) {
    sampled.push_back(boundary[i]);
  }
  return sampled;
}

void normalize(vector<Point2i>& vec) {
  int mini_x = vec[0].x;
  int maxi_x = vec[0].x;
  int mini_y = vec[0].y;
  int maxi_y = vec[0].y;

  for (size_t i = 1; i < vec.size(); ++i) {
    mini_x = min(mini_x, vec[i].x);
    maxi_x = max(maxi_x, vec[i].x);
    mini_y = min(mini_y, vec[i].y);
    maxi_y = max(maxi_y, vec[i].y);
  }
  
  double ratio1 = 639.0 / (maxi_x - mini_x);
  double ratio2 = 479.0 / (maxi_y - mini_y);

  for (size_t i = 0; i < vec.size(); ++i) {
    vec[i].x -= mini_x;
    vec[i].y -= mini_y;

    vec[i].x = (int)(vec[i].x * ratio1);
    vec[i].y = (int)(vec[i].y * ratio2);
  }
}

double getAngle(const vector<Point2i>& points) {
  const int kAngleResolution = 360;

  int mincost = 1000000000;
  double angle = -400;

  for (int iter = 0; iter < kAngleResolution; ++iter) {
    double rot_angle = iter * 2 * M_PI / kAngleResolution;
    vector<Point2i> rotated = rotate(points, rot_angle);
    normalize(rotated);
    Point2i com(320, 240);
    //    Point2i com = centerOfMass(rotated);

    int upper_left = 0;
    int upper_right = 0;
    int lower_left = 0;
    int lower_right = 0;
    for (size_t i = 0; i < rotated.size(); ++i) {
      if (rotated[i].x < com.x && rotated[i].y < com.y) {
        ++lower_left;
      }
      if (rotated[i].x < com.x && rotated[i].y > com.y) {
        ++upper_left;
      }
      if (rotated[i].x > com.x && rotated[i].y < com.y) {
        ++lower_right;
      }
      if (rotated[i].x > com.x && rotated[i].y > com.y) {
        ++upper_right;
      }
    }
    //printf("angle=%lf, diff=%d\n", rot_angle, abs(left-right));
    double cost = 
      + sqr(lower_left-upper_left)
      + sqr(lower_right-upper_right);
    if (lower_left + upper_left < lower_right + upper_right &&
        cost < mincost) {
      mincost = cost;
      angle = rot_angle;
    }
  }
  return angle;
}

void normalizeAngle(vector<Point2i>& points) {
  double angle = getAngle(points);
  points = rotate(points, angle);
}
