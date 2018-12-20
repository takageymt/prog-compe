#define EPS (1e-10)
#define eq(a, b) (fabs((a)-(b)) < EPS)
#define lt(a, b) ((a) - (b) < -EPS)
#define le(a, b) (eq(a, b) || lt(a, b))

struct Point {
  double x, y;
  Point(double x = 0.0, double y = 0.0):x(x), y(y){}

  Point operator + (Point p) { return Point(x + p.x, y + p.y); }
  Point operator - (Point p) { return Point(x - p.x, y - p.y); }
  Point operator * (double a) { return Point(x * a, y * a); }
  Point operator / (double a) { return Point(x / a, y / a); }

  double abs() { return sqrt(norm()); }
  double norm() { return x*x + y*y; }

  bool operator < (const Point& p) const {
    return x != p.x ? x < p.x : y < p.y;
  }
  bool operator == (const Point& p) const {
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};
typedef Point Vector;

double norm(Vector v) { return v.x*v.x + v.y*v.y; }
double abs(Vector v) { return sqrt(norm(v)); }
double dot(Vector a, Vector b) { return a.x*b.x + a.y*b.y; }
double cross(Vector a, Vector b) { return a.x*b.y - a.y*b.x; }

bool isOrthogonal(Vector a, Vector b) {
  return eq(dot(a, b), 0.0);
}
bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
  return isOrthogonal(a1 - a2, b1 - b2);
}
bool isParallel(Vector a, Vector b) {
  return eq(cross(a, b), 0.0);
}
bool isParallel(Point a1, Point a2, Point b1, Point b2) {
  return isParallel(a1 - a2, b1 - b2);
}

Point rotate(Point p, double th) {
  // th[rad]
  return Point(cos(th)*p.x-sin(th)*p.y, sin(th)*p.x+cos(th)*p.y);
}
Point rotate90(Point p) {
  return Point(-p.y, p.x);
}

#define COUNTER_CLOCKWISE +1
#define CLOCKWISE         -1
#define ONLINE_BACK       +2
#define ONLINE_FRONT      -2
#define ON_SEGMENT        +0
int ccw(Point p0, Point p1, Point p2) {
  Vector a = p1 - p0;
  Vector b = p2 - p0;
  if(cross(a, b) > EPS) return COUNTER_CLOCKWISE;
  if(cross(a, b) < -EPS) return CLOCKWISE;
  if(dot(a, b) < -EPS) return ONLINE_BACK;
  if(a.norm() < b.norm()) return ONLINE_FRONT;
  return ON_SEGMENT;
}
bool intersect(Point p1, Point p2, Point p3, Point p4) {
  return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
	  ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}

double getDistance(Point a, Point b) { return abs(a - b); }
double getAngle(Point a, Point b, Point c) {
  Vector v = b - a, w = c - b;
  double alpha = atan2(v.y, v.x), beta = atan2(w.y, w.x);
  if(alpha > beta) swap(alpha, beta);
  double theta = (beta - alpha) * 180 / M_PI;
  return min(theta, 360 - theta);
}
Vector getAngleBisectorVector(Point a, Point b, Point c) {
  Vector v = a - b, w = c - b;
  v = v / abs(v), w = w / abs(w);
  Vector u = v + w;
  return u / abs(u);
}

struct Segment {
  Point s, t;
  Segment(Point s = Point(), Point t = Point()):s(s), t(t){}
};
typedef Segment Line;

Point project(Segment s, Point p) {
  Vector base = s.t - s.s;
  double r = dot(p - s.s, base) / norm(base);
  return s.s + base * r;
}
Point reflect(Segment s, Point p) {
  return p + (project(s, p) - p) * 2.0;
}

bool intersect(Segment s1, Segment s2) {
  return intersect(s1.s, s1.t, s2.s, s2.t);
}

double getDistanceLP(Line l, Point p) {
  return abs(cross(l.t - l.s, p - l.s) / abs(l.t - l.s));
}
double getDistanceSP(Segment s, Point p) {
  if(dot(s.t - s.s, p - s.s) < 0.0) return abs(p - s.s);
  if(dot(s.s - s.t, p - s.t) < 0.0) return abs(p - s.t);
  return getDistanceLP(s, p);
}
double getDistance(Segment s1, Segment s2) {
  if(intersect(s1, s2)) return 0.0;
  return min(min(getDistanceSP(s1, s2.s), getDistanceSP(s1, s2.t)),
	     min(getDistanceSP(s2, s1.s), getDistanceSP(s2, s1.t)));
}

Point getCrossPoint(Segment s1, Segment s2) {
  Vector base = s2.t - s2.s;
  double d1 = abs(cross(base, s1.s - s2.s));
  double d2 = abs(cross(base, s1.t - s2.s));
  double t = d1 / (d1 + d2);
  return s1.s + (s1.t - s1.s) * t;
}
Point getCrossPointLL(Line l1, Line l2) {
  Vector v1 = l1.t - l1.s, v2 = l2.t - l2.s;
  double d = cross(v2, v1);
  if(abs(d) < EPS) return l2.s;
  return l1.s + v1 * cross(v2, l2.t - l1.s) * (1.0 / d);
}
Line getPerpendicularBisector(Point p1, Point p2) {
  Point c = (p1 + p2) / 2.0;
  Point q = Point(c.x + (p1.y - p2.y), c.y + (p2.x - p1.x));
  return Line(c, q);
}
vector<Vector> getNormalLineVector(Line l) {
  vector<Vector> vs;
  Vector v = l.t - l.s, p = v / abs(v);
  vs.emplace_back(-p.y, p.x);
  vs.emplace_back(p.y, -p.x);
  return vs;
}
vector<Line> getTranslation(Line l, double d) {
  vector<Vector> nlv = getNormalLineVector(l);
  vector<Line> nl;
  nl.emplace_back(l.s + nlv[0]*d, l.t + nlv[0]*d);
  nl.emplace_back(l.s + nlv[1]*d, l.t + nlv[1]*d);
  return nl;
}

struct Circle {
  Point p;
  double r;
  Circle(Point p = Point(), double r = 0.0):p(p), r(r){}
};

bool intersect(Circle c1, Circle c2) {
  double d = getDistance(c1.p, c2.p);
  return le(d, c1.r+c2.r) && !lt(d, fabs(c1.r-c2.r));
}

vector<Point> getCrossPointsCL(Circle c, Line l) {
  vector<Point> res;
  Vector pr = project(l, c.p);
  if(lt(c.r, abs(c.p-pr))) return res;
  Vector e = (l.t-l.s)/abs(l.t-l.s);
  double base = sqrt(c.r*c.r-norm(pr-c.p));
  res.push_back(pr+e*base);
  if(!eq(base, 0)) res.push_back(pr-e*base);
  return res;
}

vector<Point> getCrossPointsCS(Circle c, Segment s) {
  vector<Point> res;
  vector<Point> pl = getCrossPointsCL(c, s);
  for(Point p : pl) {
    if(ccw(s.s, s.t, p) == ON_SEGMENT) res.push_back(p);
  }
  return res;
}

double arg(Vector p) { return atan2(p.y, p.x); }
Vector polar(double a, double r) { return Point(cos(r) * a, sin(r) * a); }
vector<Point> getCrossPoints(Circle c1, Circle c2) {
  // assert(intersect(c1, c2));
  vector<Point> res;
  double d = abs(c1.p - c2.p);
  double a = acos((c1.r*c1.r + d*d - c2.r*c2.r) / (2*c1.r*d));
  double t = arg(c2.p - c1.p);
  res.push_back(c1.p + polar(c1.r, t + a));
  res.push_back(c1.p + polar(c1.r, t - a));
  return res;
}

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

typedef vector<Point> Polygon;

double getArea(Polygon p) {
  double ret = 0.0;
  for(int i = 0; i < (int)p.size(); i++) {
    ret += cross(p[i], p[(i+1)%p.size()]);
  }
  return abs(ret) / 2.0;
}

#define IN_POLYGON  2
#define ON_POLYGON  1
#define OUT_POLYGON 0
int contains(Polygon g, Point p) {
  int n = g.size();
  bool x = false;
  for(int i = 0; i < n; i++) {
    Point a = g[i] - p, b = g[(i+1) % n] - p;
    if(abs(cross(a, b)) < EPS && dot(a, b) < EPS) return ON_POLYGON;
    if(a.y > b.y) swap(a, b);
    if(a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;
  }
  return (x ? IN_POLYGON : OUT_POLYGON);
}

Polygon convexHull(Polygon ps) {
  int N = ps.size(), j = 0;
  Polygon pg(N*2);

  sort(ps.begin(), ps.end(), [&](Point p1, Point p2) -> bool {
      return p1.y != p2.y ? lt(p1.y, p2.y) : lt(p1.x, p2.x); });
  for(int i = 0; i < N; i++, j++) {
    while(j >= 2 && ccw(pg[j-2], pg[j-1], ps[i]) == -1) j--;
    pg[j] = ps[i];
  }
  int k = j+1;
  for(int i = N-2; i >= 0; i--, j++) {
    while(j >= k && ccw(pg[j-2], pg[j-1], ps[i]) == -1) j--;
    pg[j] = ps[i];
  }
  pg.resize(j-1);
  return pg;
}

Polygon convexCut(Polygon s, Line l) {
  Polygon t;
  for(int i = 0; i < (int)s.size(); i++) {
    Point a = s[i], b = s[(i+1)%s.size()];
    if(ccw(l.s, l.t, a) != -1) t.push_back(a);
    if(ccw(l.s, l.t, a) * ccw(l.s, l.t, b) < 0) {
      t.push_back(getCrossPointLL(Line(a, b), l));
    }
  }
  return t;
}

bool mergeIfAble(Segment &s1, Segment s2) {
  if(abs(cross(s1.t - s1.s, s2.t - s2.s)) > EPS) return false;
  if(ccw(s1.s, s2.s, s1.t) == COUNTER_CLOCKWISE ||
     ccw(s1.s, s2.s, s1.t) == CLOCKWISE) return false;
  if(ccw(s1.s, s1.t, s2.s) == ONLINE_FRONT ||
     ccw(s2.s, s2.t, s1.s) == ONLINE_FRONT) return false;
  s1 = Segment(min(s1.s, s2.s), max(s1.t, s2.t));
  return true;
}
void mergeSegments(vector<Segment>& segs) {
  for(int i = 0; i < segs.size(); i++) {
    if(segs[i].t < segs[i].s) swap(segs[i].s, segs[i].t);
  }
  for(int i = 0; i < segs.size(); i++) {
    for(int j = i+1; j < segs.size(); j++) {
      if(mergeIfAble(segs[i], segs[j])) {
	segs[j--] = segs.back(), segs.pop_back();
      }
    }
  }
}

struct edge {
  int to;
  double cost;
  edge(){}
  edge(int to, double cost):to(to), cost(cost){}

  bool operator < (const edge& e) const {
    return lt(cost, e.cost);
  }
};
typedef vector< vector<edge> > Graph;

Graph segmentArrangement(vector<Segment>& segs, vector<Point>& ps) {
  for(int i = 0; i < (int)segs.size(); i++) {
    ps.push_back(segs[i].s);
    ps.push_back(segs[i].t);
    for(int j = i+1; j < (int)segs.size(); j++) {
      if(intersect(segs[i], segs[j])) ps.push_back(getCrossPoint(segs[i], segs[j]));
    }
  }
  sort(ps.begin(), ps.end());
  ps.erase(unique(ps.begin(), ps.end()), ps.end());
  Graph graph(ps.size());
  for(int i = 0; i < (int)segs.size(); i++) {
    vector< pair<double, int> > ls;
    for(int j = 0; j < (int)ps.size(); j++) {
      if(ccw(segs[i].s, segs[i].t, ps[j]) == ON_SEGMENT) {
	ls.emplace_back(getDistance(segs[i].s, ps[j]), j);
      }
    }
    sort(ls.begin(), ls.end());
    for(int j = 0; j+1 < (int)ls.size(); j++) {
      int u = ls[j].second, v = ls[j+1].second;
      graph[u].emplace_back(v, getDistance(ps[u], ps[v]));
      graph[v].emplace_back(u, getDistance(ps[u], ps[v]));
    }
  }
  return graph;
}
