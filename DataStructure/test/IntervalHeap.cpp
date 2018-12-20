#include <bits/stdc++.h>

using namespace std;

const int MAXSIZE = 10100100;
struct IntervalHeap {
  vector<int> h;
  int size, r;
  IntervalHeap():h(MAXSIZE), size(1), r(0){}
  int& hof(int b, int i) { return h[b+2*i]; }
  void upheap(int i, int b) {
    for(int p; (p = i>>1) > 0; i = p) {
      if(b ^ (hof(b, p) <= hof(b, i))) break; // heap condition
      swap(hof(b, i), hof(b, p));
    }
  }
  void downheap(int i, int b) {
    for(int c; (c = i<<1) < size+r; i = c) {
      if(c+1 < size+r && b ^ (hof(b, c) > hof(b, c+1))) ++c;
      if(b ^ (hof(b, i) <= hof(b, c))) break; // heap condition
      swap(hof(b, i), hof(b, c));
      if(hof(0, c) > hof(1, c)) swap(hof(0, c), hof(1, c)); // interval condition
    }
  }
  void pop_min() {
    if(r ^= 1) --size; // if number of nodes will be odd, the last element will have only one element
    else hof(1, size) = hof(0, size); // else, the last node will be a sentinel
    hof(0, 1) = hof(r, size);
    downheap(1, 0);
  }
  void pop_max() {
    if(size == r) pop_min();
    if(r ^= 1) --size; // if number of nodes will be odd, the last element will have only one element
    else hof(1, size) = hof(0, size); // else, the last node will be a sentinel
    hof(1, 1) = hof(r, size);
    downheap(1, 1);
  }
  void push(int key) {
    hof(r, size) = key;
    if(r == 1) { // if number of nodes
      if(hof(0, size) > hof(1, size)) { // interval condition
	swap(hof(0, size), hof(1, size));
	upheap(size, 0);
      } else {
	upheap(size, 1);
      }
    } else {
      hof(1, size) = hof(0, size) = key;
      if(hof(0, size) < hof(0, size/2)) upheap(size, 0); // heap condition
      if(hof(1, size) > hof(1, size/2)) { // heap condition
	upheap(size, 1);
	hof(0, size) = hof(1, size);
      }
    }
    if(!(r ^= 1)) ++size;
  }
  int top_min() { return hof(0, 1); }
  int top_max() { return (size == r) ? hof(0, 1) : hof(1, 1); }
  bool empty() { return size+r == 1; }
};

int main() {
  int Q;
  cin >> Q;
  IntervalHeap heap;
  while(Q--) {
    int t;
    cin >> t;
    if(t == 0) {
      int x;
      cin >> x;
      heap.push(x);
    } else if(t == 1) {
      int x;
      cin >> x;
      if(x == 0) heap.pop_min();
      else heap.pop_max();
    } else if(t == 3) {
      cout << heap.top_max()-heap.top_min() << endl;
    }
  }

  return 0;
}
