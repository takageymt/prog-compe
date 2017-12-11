#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) (v).begin(), (v).end()
#define resz(v, ...) (v).clear(), (v).resize(__VA_ARGS__)
#define reps(i, m, n) for(int i = (int)(m); i < (int)(n); i++)
#define rep(i, n) reps(i, 0, n)

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

using Pi = pair<int, int>;
using Ti = tuple<int, int, int>;
using vint = vector<int>;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;
//*
// Fast Fourier Transform
namespace FFT {
  using dbl = double;

  struct num {
    dbl x, y;
    num():x(0), y(0){}
    num(dbl x, dbl y):x(x), y(y){}
  };
  inline num operator + (num a, num b) {
    return num(a.x+b.x, a.y+b.y);
  }
  inline num operator - (num a, num b) {
    return num(a.x-b.x, a.y-b.y);
  }
  inline num operator * (num a, num b) {
    return num(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
  }
  inline num conj(num a) {
    return num(a.x, -a.y);
  }

  int base = 1;
  vector<num> rts = {{0, 0}, {1, 0}};
  vector<int> rev = {0, 1};

  const dbl PI = acosl(-1.0);

  void init() {
    base = 1;
    rts = vector<num>{{0, 0}, {1, 0}};
    rev = vector<int>{0, 1};
  }

  void ensure_base(int nbase) {
    if(nbase <= base) return;

    rev.resize(1<<nbase);
    for(int i = 0; i < (1<<nbase); i++)
      rev[i] = (rev[i>>1]>>1) + ((i&1)<<(nbase-1));

    rts.resize(1<<nbase);
    while(base < nbase) {
      dbl angle = 2*PI/(1<<(base+1));
      for(int i = 1<<(base-1); i < (1<<base); i++) {
	rts[i<<1] = rts[i];
	dbl angle_i = angle*(2*i+1 - (1<<base));
	rts[(i<<1)+1] = num(cos(angle_i), sin(angle_i));
      }
      ++base;
    }
  }

  void fft(vector<num>& a, int n = -1) {
    if(n == -1) n = a.size();
    assert((n&(n-1)) == 0);

    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for(int i = 0; i < n; i++)
      if(i < (rev[i]>>shift)) swap(a[i], a[rev[i]>>shift]);

    for(int k = 1; k < n; k <<= 1) {
      for(int i = 0; i < n; i += (k<<1)) {
	for(int j = 0; j < k; j++) {
	  num z = a[i+j+k] * rts[j+k];
	  a[i+j+k] = a[i+j] - z;
	  a[i+j] = a[i+j] + z;
	}
      }
    }
  }

  vector<num> fa;

  vector<int> mul(vector<int>& a, vector<int>& b) {
    int n = a.size(), m = b.size();
    int need = n + m - 1;
    int nbase = 0;
    while((1<<nbase) < need) nbase++;
    ensure_base(nbase);

    int sz = 1<<nbase;
    if(sz > (int)fa.size()) fa.resize(sz);
    for(int i = 0; i < sz; i++) {
      int x = (i < n ? a[i] : 0);
      int y = (i < m ? b[i] : 0);
      fa[i] = num(x, y);
    }
    fft(fa, sz);

    num r(0, -0.25/sz);
    for(int i = 0; i <= (sz>>1); i++) {
      int j = (sz-i)&(sz-1);
      num z = (fa[j]*fa[j] - conj(fa[i]*fa[i]))*r;
      if(i != j) fa[j] = (fa[i]*fa[i] - conj(fa[j]*fa[j]))*r;
      fa[i] = z;
    }
    fft(fa, sz);

    vector<int> res(need);
    for(int i = 0; i < need; i++) res[i] = fa[i].x + 0.4;
    return res;
  }
};
/*/
namespace FastFourierTransform{
  using dbl = double;

  struct num{
    dbl x,y;
    num(){x=y=0;}
    num(dbl x,dbl y):x(x),y(y){}
  };

  inline num operator+(num a,num b){
    return num(a.x+b.x,a.y+b.y);
  }
  inline num operator-(num a,num b){
    return num(a.x-b.x,a.y-b.y);
  }
  inline num operator*(num a,num b){
    return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
  }
  inline num conj(num a){
    return num(a.x,-a.y);
  }

  int base=1;
  vector<num> rts={{0,0},{1,0}};
  vector<int> rev={0,1};

  const dbl PI=acosl(-1.0);

  void ensure_base(int nbase){
    if(nbase<=base) return;

    rev.resize(1<<nbase);
    for(int i=0;i<(1<<nbase);i++)
      rev[i]=(rev[i>>1]>>1)+((i&1)<<(nbase-1));

    rts.resize(1<<nbase);
    while(base<nbase){
      dbl angle=2*PI/(1<<(base+1));
      for(int i=1<<(base-1);i<(1<<base);i++){
    rts[i<<1]=rts[i];
    dbl angle_i=angle*(2*i+1-(1<<base));
    rts[(i<<1)+1]=num(cos(angle_i),sin(angle_i));
      }
      base++;
    }
  }

  void fft(vector<num> &a,int n=-1){
    if(n==-1) n=a.size();
    assert((n&(n-1))==0);

    int zeros=__builtin_ctz(n);
    ensure_base(zeros);
    int shift=base-zeros;
    for(int i=0;i<n;i++)
      if(i<(rev[i]>>shift))
    swap(a[i],a[rev[i]>>shift]);

    for(int k=1;k<n;k<<=1){
      for(int i=0;i<n;i+=2*k){
    for(int j=0;j<k;j++){
      num z=a[i+j+k]*rts[j+k];
      a[i+j+k]=a[i+j]-z;
      a[i+j]=a[i+j]+z;
    }
      }
    }
  }

  vector<num> fa;

  vector<int> multiply(vector<int> &a,vector<int> &b){
    int need=a.size()+b.size()-1;
    int nbase=0;
    while((1<<nbase)<need) nbase++;
    ensure_base(nbase);

    int sz=1<<nbase;
    if(sz>(int)fa.size()) fa.resize(sz);
    for(int i=0;i<sz;i++){
      int x=(i<(int)a.size()?a[i]:0);
      int y=(i<(int)b.size()?b[i]:0);
      fa[i]=num(x,y);
    }
    fft(fa,sz);

    num r(0,-0.25/sz);
    for(int i=0;i<=(sz>>1);i++){
      int j=(sz-i)&(sz-1);
      num z=(fa[j]*fa[j]-conj(fa[i]*fa[i]))*r;
      if(i!=j)
    fa[j]=(fa[i]*fa[i]-conj(fa[j]*fa[j]))*r;
      fa[i]=z;
    }
    fft(fa,sz);

    vector<int> res(need);
    for(int i=0;i<need;i++) res[i]=fa[i].x+0.4;

    return res;
  }

};
//*/
signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  const string dna = "AGCT";
  string s, t;
  while(cin >> s >> t) {
    int n = s.size(), m = t.size(), l = max(n, m);
    reps(i, n, l) s += 'Z';
    reps(i, m, l) t += 'Z';
    vint score(l*2, 0);
    for(auto&& x : dna) {
      vint a(l), b(l);
      rep(i, l) {
	a[i] = (s[i] == x);
	b[i] = (t[i] == x);
      }
      reverse(all(b));
      auto c = FFT::mul(a, b);
      //auto c = FastFourierTransform::multiply(a, b);
      rep(i, c.size()) score[i] += c[i];
    }
    //cout << *max_element(all(score)) << endl;
    int mxi = 0;
    rep(i, l*2) {
      if(score[mxi] <= score[i]) mxi = i;
    }
    cout << score[mxi] << endl;//<< " " << mxi << endl;
    if(score[mxi] == 0) {
      cout << "No matches" << endl;
      continue;
    }
    string ans = "";
    /*
    int si = 0, ti = 0;
    if(mxi < l) {
      while(si < n) {
	if(ti < l-mxi-1) ans += t[ti++];
	else if(ti >= m) ans += s[si++];
	else {
	  if(s[si] == t[ti]) ans += s[si];
	  else ans += 'X';
	  si++, ti++;
	}
      }
    } else {
      while(ti < m) {
	if(si < mxi-l+1) ans += s[si++];
	else if(si >= n) ans += t[ti++];
	else {
	  if(s[si] == t[ti]) ans += s[si];
	  else ans += 'X';
	  si++, ti++;
	}
      }
    }
    */
    if(mxi < l) {
      rep(i, l-mxi-1) s = 'Z'+s;
      rep(i, l-mxi-1) t = t+'Z';
    } else {
      rep(i, mxi-l+1) s = s+'Z';
      rep(i, mxi-l+1) t = 'Z'+t;
    }
    rep(i, s.size()) {
      if(s[i] == 'Z' && t[i] == 'Z') continue;
      if(s[i] == t[i]) ans += s[i];
      else if(max(s[i], t[i]) == 'Z') ans += min(s[i], t[i]);
      else ans += 'X';
    }
    assert(ans.find('Z') == string::npos);
    cout << ans << endl << endl;
  }

  return 0;
}
