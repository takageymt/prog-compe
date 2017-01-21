// 点の内包
#define IN_POLYGON  2
#define ON_POLYGON  1
#define OUT_POLYGON 0
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
