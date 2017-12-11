#include <bits/stdc++.h>
using namespace std;
using Pi = pair<int, int>;

using Comparator = function<bool(int, int)>;
struct ConvexHullTrickAddQueryMono {
  bool isMonoX;
  Comparator comp;
  vector<Pi> lines;
  ConvexHullTrickAddQueryMono(bool isMonoX=false, Comparator comp=[](int l, int r){return l >= r;}):isMonoX(isMonoX), comp(comp) {
    lines.emplace_back(0, 0);
  }
  bool check(Pi l1, Pi l2, Pi l3) {
    if(l1 < l3) swap(l1, l3);
    return (l3.second-l2.second)*(l2.first-l1.first) >= (l2.second-l1.second)*(l3.first-l2.first);
  }
  void add(int a, int b) { // add f(x)=ax+b
    Pi line(a, b);
    while(lines.size() >= 2 && check(*(lines.end()-2), lines.back(), line)) lines.pop_back();
    lines.push_back(line);
  }
  int f(Pi l, int x) {return l.first*x + l.second; }
  int f(int i, int x) {return f(lines[i], x);}
  int get(int x) {
    if(isMonoX) {
      static int head = 0;
      while(lines.size()-head >= 2 && comp(f(head, x), f(head+1, x))) ++head;
      return f(head, x);
    } else {
      int lb = -1, ub = lines.size()-1;
      while(ub-lb > 1) {
	int mb = (lb+ub)/2;
	if(comp(f(mb, x), f(mb+1, x))) lb = mb;
	else ub = mb;
      }
      return f(ub, x);
    }
  }
};
