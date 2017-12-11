// Circulation Problem
// ∀e∈E,
// l(v,w)<=f(v,w)<=u(v,w)
// and
// ∀u∈V,
// Σf(u,w)=0
struct Circular {
  Dinic mf;
  int S, T, lowsum;
  Circular(int V):mf(V+2), S(0), T(1), lowsum(0){}
  void add_edge(int from, int to, int lower, int upper) {
    lowsum += lower;
    mf.add_edge(from+2, to+2, upper-lower);
    mf.add_edge(S, to+2, lower);
    mf.add_edge(from+2, T, lower);
  }
  bool satisfy(int s, int t) {
    mf.add_edge(t+2, s+2, 1e9);
    return lowsum == mf.max_flow(0, 1);
  }
};
