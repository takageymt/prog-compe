// Fast LCS
#define MAX_LEN 100
int HuntSzymanski(string a, string b)
{
  int n = a.size(), m = b.size();
  map< int, vector<int> > mp;
  for(int j = m-1; j >= 0; j--) mp[b[j]].push_back(j);

}
