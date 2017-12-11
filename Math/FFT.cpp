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

  vector<int> multiply(vector<int>& a, vector<int>& b) {
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
