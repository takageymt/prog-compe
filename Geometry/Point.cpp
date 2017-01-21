/*************************
 * POINT / VECTOR
 *************************/

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
double norm(Vector v);

// ベクトルの大きさ
double abs(Vector v);

// ベクトルの内積
double dot(Vector a, Vector b);

// ベクトルの外積の大きさ
double cross(Vector a, Vector b);

// 直行判定
bool isOrthogonal(Vector a, Vector b);
bool isOrthogonal(Point a1, Point a2, Point b1, Point b2);

// 平行判定
bool isParallel(Vector a, Vector b);
bool isParallel(Point a1, Point a2, Point b1, Point b2);

// 反時計回り
int ccw(Point p0, Point p1, Point p2);

// 交差判定
bool intersect(Point p1, Point p2, Point p3, Point p4);

// 二点間の距離
double getDistance(Point a, Point b);

// ∠ABCを求める
double getAngle(Point a, Point b, Point c);
