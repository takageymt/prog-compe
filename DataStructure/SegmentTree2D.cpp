struct SegmentTree2D
{
  int H, W;
  int wid;
  vector< vector<int> > data;
  SegmentTree2D(){}
  SegmentTree2D(const vector< vector<int> > &f)
  {
    H = W = 1;
    while(H < (int)f.size()) H <<= 1;
    while(W < (int)f[0].size()) W <<= 1;
    data.resize(2*H-1, vector<int>(2*W-1, inf));
    init(f);
  }
  void init(const vector< vector<int> > &f)
  {
    for(int i = 0; i < (int)f.size(); i++)
      for(int j = 0; j < (int)f[i].size(); j++)
	data[i+H-1][j+W-1] = f[i][j];

    for(int i = 2*H-2; i > H-2; i--)
      for(int j = W-2; j >= 0; j--)
	data[i][j] = min(data[i][2*j+1], data[i][2*j+2]);

    for(int i = H-2; i >= 0; i--)
      for(int j = 0; j < 2*W-1; j++)
	data[i][j] = min(data[2*i+1][j], data[2*i+2][j]);
  }
  int query(int li, int lj, int ri, int rj)
  {
    return query_h(li, lj, ri, rj, 0, H, 0);
  }
  int query_h(int li, int lj, int ri, int rj, int ai, int bi, int k)
  {
    if(ri <= ai || bi <= li) return inf;
    if(li <= ai && bi <= ri) return query_w(lj, rj, 0, W, k, 0);
    return min(query_h(li, lj, ri, rj, ai, (ai+bi)/2, 2*k+1),
	       query_h(li, lj, ri, rj, (ai+bi)/2, bi, 2*k+2));
  }
  int query_w(int lj, int rj, int aj, int bj, int i, int k)
  {
    if(rj <= aj || bj <= lj) return inf;
    if(lj <= aj && bj <= rj) return data[i][k];
    return min(query_w(lj, rj, aj, (aj+bj)/2, i, 2*k+1),
	       query_w(lj, rj, (aj+bj)/2, bj, i, 2*k+2));
  }
};
