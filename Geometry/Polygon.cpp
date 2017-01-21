/*************************
 * POLYGON
 *************************/

// 多角形
typedef vector<Point> Polygon;

// 単純多角形の面積
double getArea(Polygon p);

// 点の内包
int contains(Polygon g, Point p);

// 凸包
Polygon convexHull(Polygon ps);

// 凸多角形の切断
// 凸多角形をある直線で切断し，その左側だけ残す．
Polygon convexCut(Polygon s, Line l);
