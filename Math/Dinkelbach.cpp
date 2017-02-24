// 分数計画問題
// n個の組a_i, b_iが与えられるので、
// f(X):=Σa_i, g(X):=Σb_jとした時の
//      i∈X         j∈X
// f(X)/g(X)を最小化する
// (集合Xの大きさはk)
struct Cost {
  double a, b;
  Cost(){}
  Cost(double a, double b):a(a), b(b){}
};

vector<Cost> cost;
double fcost, gcost;
int n, k;

double check(double t)
{
  fcost = gcost = 0;
  sort(begin(cost), end(cost), [t](Cost c, Cost d) -> bool {
      return c.a - t*c.b < d.a - t*d.b;
    });
  for(int i = 0; i < k; i++) fcost += cost[i].a, gcost += cost[i].b;
  return fcost - t*gcost;
}

double Dinkelbach()
{
  double t = 0;
  for(t = 0; ; t = fcost / gcost)
    if(fabs(check(t)) < 1e-8) break;

  return t;
}

int main()
{

  return 0;
}
