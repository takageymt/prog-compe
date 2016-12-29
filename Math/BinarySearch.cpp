// binary search
// f(x) : monotonic function
// ask for x : f(x) = k
int f(int x)
{

}

int binary_search(int k)  
{
  int lb = 0, ub = inf;
  while(ub - lb > 1) {
    int mb = (lb + ub) / 2;
    if(f(mb) <= k) lb = mb;
    else ub = lb;
  }
  return lb;
}
