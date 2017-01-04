const int MAX_H = 100;
const int MAX_W = 100;
int grundy[MAX_H][MAX_W];

int calcGrundy1(int h, int w)
{
  int &g = grundy[h][w];
  if (g != -1) return g;
  if (h == 0 && w == 0) return g = 0;
  set<int> V;
  V.insert(calcGrundy1(0, 0));
  for (int i = 1; i < h; ++i)
    V.insert(calcGrundy1(i, w));
  for (int i = 1; i < w; ++i)
    V.insert(calcGrundy1(h, i));
  g = 0;
  while (V.count(g)) ++g;
  return g;
}

// 分割のグランディ数
// g(s, t) = g(s) XOR g(t)
int calcGrundy2(int h, int w)
{
  int &g = grundy[h][w];
  if (g != -1) return g;
  if (h == 1 && w == 1) return g = 0;
  set<int> V;
  V.insert(calcGrundy2(0, 0));
  for (int i = 1; i < h; ++i)
    V.insert(calcGrundy2(i, w) ^ calcGrundy2(h - i, w));
  for (int i = 1; i < w; ++i)
    V.insert(calcGrundy2(h, i) ^ calcGrundy2(h, w - i));
  g = 0;
  while (V.count(g)) ++g;
  return g;
}
