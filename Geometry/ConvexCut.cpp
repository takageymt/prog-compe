// 凸多角形の切断
// 凸多角形をある直線で切断し，その左側だけ残す．
Polygon convexCut(Polygon s, Line l)
{
  Polygon t;
  for(int i = 0; i < (int)s.size(); i++) {
    Point a = s[i], b = s[(i+1)%s.size()];
    if(ccw(l.p1, l.p2, a) != -1) t.push_back(a);
    if(ccw(l.p1, l.p2, a) * ccw(l.p1, l.p2, b) < 0) {
      t.push_back(getCrossPointLL(Line(a, b), l));
    }
  }
  return t;
}
