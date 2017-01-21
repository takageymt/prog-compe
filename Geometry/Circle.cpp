/*************************
 * Circle
 *************************/

// 円
struct Circle {
  Point c;
  double r;
  Circle(Point c = Point(), double r = 0.0):c(c), r(r){}
};

// 円cと線分lの交点
pair<Point, Point> getCrossPoints(Circle c, Line l);

// 円c1と円c2の交点
double arg(Vector p);
Vector polar(double a, double r);
pair<Point, Point> getCrossPoints(Circle c1, Circle c2);
