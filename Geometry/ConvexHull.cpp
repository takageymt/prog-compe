// 凸包
Polygon convexHull(Polygon ps)
{
  int N = ps.size(), j = 0;
  Polygon pg(N*2);

  sort(ps.begin(), ps.end(), [](Point p1, Point p2) -> bool {
      return p1.y != p2.y ? lt(p1.y, p2.y) : lt(p1.x, p2.x)});
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

// 螺旋本凸包
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
