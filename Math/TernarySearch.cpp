// ternary search
// f(x) : convex function
// ask for x : f(x) = maximal or minimal
double f(double x)
{
}

double ternary_search()
{
  double l = 0.0, r = DOUBLE_MAX;
  for(int i = 0; i < 200; i++) {
    double a = (l + l + r) / 3.0;
    double b = (l + r + r) / 3.0;
    if(f(a) > f(b)) l = a;
    else r = b;
  }
  return l;
}
