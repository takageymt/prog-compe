vector<Point> tangentCP(Circle c, Point p) {
  Vector a = p-c.p;
  vector<Point> res;
  double x = norm(a);
  double d = x-c.r*c.r;
  if(d < -EPS) return res;
  d = max(d, 0.0);
  Point p1 = a*(c.r*c.r/x);
  Point p2 = rotate90(a)*(-c.r*sqrt(d)/x);
  res.emplace_back(c.p+p1-p2);
  res.emplace_back(c.p+p1+p2);
  return res;
}

vector<Line> tangentCC(Circle c1, Circle c2) {
  vector<Line> res;
  vector<Point> ps, qs;
  if(abs(c2.p-c1.p) < EPS) return res;
  // 外接線
  if(abs(c1.r-c2.r) < EPS) {
    Point dir = c2.p-c1.p;
    dir = rotate90(dir*(c1.r/abs(dir)));
    res.emplace_back(c1.p+dir, c2.p+dir);
    res.emplace_back(c1.p-dir, c2.p-dir);
  } else {
    Point p = c1.p*(-c2.r)+c2.p*c1.r;
    p = p*(1.0/(c1.r-c2.r));
    ps = tangentCP(c1, p);
    qs = tangentCP(c2, p);
    int n = ps.size(), m = qs.size();
    for(int i = 0; i < min(n, m); i++) {
      res.emplace_back(ps[i], qs[i]);
    }
  }
  // 内接線
  Point p = c1.p*c2.r+c2.p*c1.r;
  p = p*(1.0/(c1.r+c2.r));
  ps = tangentCP(c1, p);
  qs = tangentCP(c2, p);
  int n = ps.size(), m = qs.size();
  for(int i = 0; i < min(n, m); i++) {
    res.emplace_back(ps[i], qs[i]);
  }
  return res;
}
