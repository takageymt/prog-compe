struct UF {
  vector<Pi> data;
  UF(int n):data(n, Pi(-1, 0)){}
  Pi find(int x) {
    //cout<<x<<" "<<data[x].first<<" "<<data[x].second<<endl;
    if(data[x].first < 0) return Pi(x, 0);
    Pi p = find(data[x].first);
    //cout<<p.first<<" "<<p.second<<endl;
    data[x].first = p.first;
    data[x].second += p.second;
    return data[x];//Pi(p.first, data[x].second);
  }
  void unite(int a, int b, int w) {
    int x = find(a).first, y = find(b).first;
    if(x == y) return;
    if(data[x].first > data[y].first) swap(x, y), swap(a, b), w = -w;
    w += data[a].second-data[b].second;
    data[x].first += data[y].first;
    data[y].first = x;
    data[y].second += w;
  }
};
