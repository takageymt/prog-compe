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
