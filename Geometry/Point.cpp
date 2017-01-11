#define EPS (1e-10)
#define equals(a, b) (fabs((a)-(b)) < EPS)
#define lt(a, b) ((a) - (b) < -EPS)

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
// 平行判定
bool isParallel(Vector a, Vector b)
{
  return equals(cross(a, b), 0.0);
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
// 二点間の距離
double getDistance(Point a, Point b)
{
  return abs(a - b);
}
