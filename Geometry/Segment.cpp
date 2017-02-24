/*************************
 * SEGMENT / LINE
 *************************/

// 線分/直線
struct Segment {
  Point p1, p2;
  Segment(Point p1 = Point(), Point p2 = Point()):p1(p1), p2(p2){}
};
typedef Segment Line;

// 直行判定
bool isOrthogonal(Segment s1, Segment s2);

// 平行判定
bool isParallel(Segment s1, Segment s2);

// 射影
Point project(Segment s, Point p);

// 反射
Point reflect(Segment s, Point p);

// 交差判定
bool intersect(Segment s1, Segment s2);

// 直線と点との距離
double getDistanceLP(Line l, Point p);

// 線分と点との距離
double getDistanceSP(Segment s, Point p);

// 二線分間の距離
double getDistance(Segment s1, Segment s2);

// 線分の交点
Point getCrossPoint(Segment s1, Segment s2);

// 直線の交点
Point getCrossPointLL(Line l1, Line l2);

// 垂直二等分線
Line getPerpendicularBisector(Point p1, Point p2);

// 直線の法線ベクトル(方向2つ)
vector<Vector> getNormalVector(Line l);

// 直線の平行移動
vector<Line> getTranslation(Line l, double d);
