string  formula;
int idx;

int solve()
{
  int ret; char c = formula[idx];
  if(c == '(') {
    idx++, ret = solve();
    char op = formula[idx];
    if(op == '*') idx++, ret *= solve();
    else if(op == '+') idx++, ret += solve();
    idx++;
  }
  else if(c == ')') idx++;
  else if(c == '-') idx++, ret = -solve();
  else if(isdigit(c)) ret = c - '0', idx++;
  return ret;
}
