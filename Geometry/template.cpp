#define EPS (1e-10)
#define equals(a, b) (fabs((a)-(b)) < EPS)

// 点/ベクトル
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

// 円
struct Circle {
  Point c;
  double r;
  Circle(Point c = Point(), double r = 0.0):c(c), r(r){}
};

// 多角形
typedef vector<Point> Polygon;

// 線分/直線
struct Segment {
  Point p1, p2;
};
typedef Segment Line;

// ベクトルのノルム
double norm(Vector v)
{
  return v.x*v.x + v.y*v.y;
}
// ベクトルの大きさ
double abs(Vector v)
{
  return sqrt(norm(v));
}
// ベクトルの内積
double dot(Vector a, Vector b)
{
  return a.x*b.x + a.y*b.y;
}
// ベクトルの外積の大きさ
double cross(Vector a, Vector b)
{
  return a.x*b.y - a.y*b.x;
}
// 直行判定
bool isOrthogonal(Vector a, Vector b)
{
  return equals(dot(a, b), 0.0);
}
bool isOrthogonal(Point a1, Point a2, Point b1, Point b2)
{
  return isOrthogonal(a1 - a2, b1 - b2);
}
bool isOrthogonal(Segment s1, Segment s2)
{
  return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}
// 平行判定
bool isParallel(Vector a, Vector b)
{
  return equals(cross(a, b), 0.0);
}
bool isParallel(Point a1, Point a2, Point b1, Point b2)
{
  return isParallel(a1 - a2, b1 - b2);
}
bool isParallel(Segment s1, Segment s2)
{
  return equals(cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}
// 射影
Point project(Segment s, Point p)
{
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / norm(base);
  return s.p1 + base * r;
}
// 反射
Point reflect(Segment s, Point p)
{
  return p + (project(s, p) - p) * 2.0;
}
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE         = -1;
static const int ONLINE_BACK       = 2;
static const int ONLINE_FRONT      = -2;
static const int ON_SEGMENT        = 0;
// 反時計回り
int ccw(Point p0, Point p1, Point p2)
{
  Vector a = p1 - p0;
  Vector b = p2 - p0;
  if(cross(a, b) > EPS) return COUNTER_CLOCKWISE;
  if(cross(a, b) < -EPS) return CLOCKWISE;
  if(dot(a, b) < -EPS) return ONLINE_BACK;
  if(a.norm() < b.norm()) return ONLINE_FRONT;
  return ON_SEGMENT;
}
// 交差判定
bool intersect(Point p1, Point p2, Point p3, Point p4)
{
  return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
	  ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}
bool intersect(Segment s1, Segment s2)
{
  return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}
// 二点間の距離
double getDistance(Point a, Point b)
{
  return abs(a - b);
}
// 直線と点との距離
double getDistanceLP(Line l, Point p)
{
  return abs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}
// 線分と点との距離
double getDistanceSP(Segment s, Point p)
{
  if(dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
  if(dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
  return getDistanceLP(s, p);
}
// 二線分間の距離
double getDistance(Segment s1, Segment s2)
{
  if(intersect(s1, s2)) return 0.0;
  return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
	     min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}
// 線分の交点
Point getCrossPoint(Segment s1, Segment s2)
{
  Vector base = s2.p2 - s2.p1;
  double d1 = abs(cross(base, s1.p1 - s2.p1));
  double d2 = abs(cross(base, s1.p2 - s2.p1));
  double t = d1 / (d1 + d2);
  return s1.p1 + (s1.p2 - s1.p1) * t;
}
// 円cと線分lの交点
pair<Point, Point> getCrossPoints(Circle c, Line l)
{
  // assert(intersect(c, l));
  Vector pr = project(l, c.c);
  Vector e = (l.p2 - l.p1) / abs(l.p2 - l.p1);
  double base = sqrt(c.r*c.r - norm(pr - c.c));
  return make_pair(pr + e * base, pr - e * base);
}
// 円c1と円c2の交点
double arg(Vector p) { return atan2(p.y, p.x); }
Vector polar(double a, double r) { return Point(cos(r) * a, sin(r) * a); }
pair<Point, Point> getCrossPoints(Circle c1, Circle c2)
{
  // assert(intersect(c1, c2));
  double d = abs(c1.c - c2.c);
  double a = acos((c1.r*c1.r + d*d - c2.r*c2.r) / (2*c1.r*d));
  double t = arg(c2.c - c1.c);
  return make_pair(c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a));
}
// 点の内包
static const int IN_POLYGON = 2;
static const int ON_POLYGON = 1;
static const int OUT_POLYGON = 0;
int contains(Polygon g, Point p)
{
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
// 凸包
Polygon andrewScan(Polygon s)
{
  Polygon u, l;
  if(s.size() < 3) return s;
  sort(s.begin(), s.end());
  u.push_back(s[0]);
  u.push_back(s[1]);
  l.push_back(s[s.size()-1]);
  l.push_back(s[s.size()-2]);

  for(int i = 2; i < s.size(); i++) {
    for(int n = u.size(); n >= 2 && ccw(u[n-2], u[n-1], s[i]) == COUNTER_CLOCKWISE; n--) {
      u.pop_back();
    }
    u.push_back(s[i]);
  }

  for(int i = s.size()-3; i >= 0; i--) {
    for(int n = l.size(); n >= 2 && ccw(l[n-2], l[n-1], s[i]) == COUNTER_CLOCKWISE; n--) {
      l.pop_back();
    }
    l.push_back(s[i]);
  }
  
  reverse(l.begin(), l.end());
  for(int i = u.size()-2; i >= 1; i--) l.push_back(u[i]);

  return l;
}

// ∠ABCを求める
double getAngle(Point a, Point b, Point c)
{
  Vector v = b - a, w = c - b;
  double alpha = atan2(v.y, v.x), beta = atan2(w.y, w.x);
  if(alpha > beta) swap(alpha, beta);
  double theta = (beta - alpha) * 180 / M_PI;
  return min(theta, 360 - theta);
}

// 線分併合（線分アレンジメントの前にやる）
bool mergeIfAble(Segment &s1, Segment s2)
{
  if(abs(cross(s1.p2 - s1.p1, s2.p2 - s2.p1)) > EPS) return false;
  if(ccw(s1.p1, s2.p1, s1.p2) == COUNTER_CLOCKWISE ||
     ccw(s1.p1, s2.p1, s1.p2) == CLOCKWISE) return false;
  if(ccw(s1.p1, s1.p2, s2.p1) == ONLINE_FRONT ||
     ccw(s2.p1, s2.p2, s1.p1) == ONLINE_FRONT) return false;
  s1 = Segment(min(s1.p1, s2.p1), max(s1.p2, s2.p2));
  return true;
}
void mergeSegments(vector<Segment>& segs)
{
  for(int i = 0; i < segs.size(); i++) {
    if(segs[i].p2 < segs[i].p1) swap(segs[i].p1, segs[i].p2);
  }
  for(int i = 0; i < segs.size(); i++) {
    for(int j = i+1; j < segs.size(); j++) {
      if(mergeIfAble(segs[i], segs[j])) {
	segs[j--] = segs.back(), segs.pop_back();
      }
    }
  }
}

// 線分アレンジメント
struct edge
{
  int to;
  double cost;
  edge(){}
  edge(int to, double cost):to(to), cost(cost){}

  bool operator < (const edge& e) const {
    return lt(cost, e.cost);
  }
};
typedef vector< vector<edge> > Graph;

Graph segmentArrangement(vector<Segment>& segs, vector<Point>& ps)
{
  for(int i = 0; i < segs.size(); i++) {
    ps.push_back(segs[i].p1);
    ps.push_back(segs[i].p2);
    for(int j = i+1; j < segs.size(); j++) {
      if(intersect(segs[i], segs[j])) ps.push_back(getCrossPoint(segs[i], segs[j]));
    }
  }
  sort(ps.begin(), ps.end());
  ps.erase(unique(ps.begin(), ps.end()), ps.end());
  Graph graph(ps.size());
  for(int i = 0; i < segs.size(); i++) {
    vector< pair<double, int> > ls;
    for(int j = 0; j < ps.size(); j++) {
      if(intersect(segs[i], ps[j])) {
	ls.emplace_back(getDistanceSP(segs[i], ps[j]), j);
      }
    }
    sort(ls.begin(), ls.end());
    for(int j = 0; j+1 < ls.size(); j++) {
      int u = ls[j].second, v = ls[j+1].second;
      graph[u].emplace_back(v, getDistance(ps[u], ps[v]));
      graph[v].emplace_back(u, getDistance(ps[u], ps[v]));
    }
  }
  return graph;
}
