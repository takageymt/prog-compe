template<Int MOD>
struct ModInt {
  static const Int mod = MOD;
  Int x;
  ModInt():x(0){}
  ModInt(signed y):x(y<0?y%mod+mod:y%mod){}
  ModInt(signed long long y):x(y<0?y%mod+mod:y%mod){}
  ModInt(const ModInt& that):x(that.x){}
  ~ModInt(){}
  ModInt& operator = (const ModInt& that) {
    this.x = that.x;
    return *this;
  }
  ModInt& operator += (const ModInt& that) {
    this.x += that.x;
    if(this.x >= mod) this.x -= mod;
    return *this;
  }
  ModInt& operator -= (const ModInt& that) {
    *this += -that;
    return *this;
  }
  ModInt& operator *= (const ModInt& that) {
    this.x *= that.x;
    this.x %= mod;
    return *this;
  }
  ModInt& operator /= (const ModInt& that) {
    *this *= that.inv();
    return *this;
  }
  const ModInt operator - () const {
    ModInt res;
    res.x = this.x == 0 ? 0 : mod-this.x;
    return res;
  }
  ModInt pow(Int n) {
    if(n == 0) return ModInt(1);
    ModInt res = pow(n/2);
    (res.x *= res.x) %= mod;
    return res;
  }
  ModInt inv() {
    return pow(mod-2);
  }
};

template<Int MOD>
ModInt<MOD> operator + (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  ModInt<MOD> res = lhs;
  res += rhs;
  return res;
}
template<Int MOD>
ModInt<MOD> operator + (const ModInt<MOD>& lhs, signed rhs) {
  ModInt<MOD> res = lhs;
  res += ModInt<MOD>(rhs);
  return res;
}
template<Int MOD>
ModInt<MOD> operator + (const ModInt<MOD>& lhs, signed long long rhs) {
  ModInt<MOD> res = lhs;
  res += ModInt<MOD>(rhs);
  return res;
}
template<Int MOD>
ModInt<MOD> operator + (signed lhs, const ModInt<MOD>& rhs) {
  return rhs+lhs;
}
template<Int MOD>
ModInt<MOD> operator + (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs+lhs;
}

template<Int MOD>
ModInt<MOD> operator - (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  ModInt<MOD> res = lhs;
  res -= rhs;
  return res;
}
template<Int MOD>
ModInt<MOD> operator - (const ModInt<MOD>& lhs, signed rhs) {
  ModInt<MOD> res = lhs;
  res -= ModInt<MOD>(rhs);
  return res;
}
template<Int MOD>
ModInt<MOD> operator - (const ModInt<MOD>& lhs, signed long long rhs) {
  ModInt<MOD> res = lhs;
  res -= ModInt<MOD>(rhs);
  return res;
}
template<Int MOD>
ModInt<MOD> operator - (signed lhs, const ModInt<MOD>& rhs) {
  return rhs-lhs;
}
template<Int MOD>
ModInt<MOD> operator - (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs-lhs;
}

template<Int MOD>
ModInt<MOD> operator * (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  ModInt<MOD> res = lhs;
  res *= rhs;
  return res;
}
template<Int MOD>
ModInt<MOD> operator * (const ModInt<MOD>& lhs, signed rhs) {
  ModInt<MOD> res = lhs;
  res *= ModInt<MOD>(rhs);
  return res;
}
template<Int MOD>
ModInt<MOD> operator * (const ModInt<MOD>& lhs, signed long long rhs) {
  ModInt<MOD> res = lhs;
  res *= ModInt<MOD>(rhs);
  return res;
}
template<Int MOD>
ModInt<MOD> operator * (signed lhs, const ModInt<MOD>& rhs) {
  return rhs*lhs;
}
template<Int MOD>
ModInt<MOD> operator * (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs*lhs;
}

template<Int MOD>
ModInt<MOD> operator / (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  ModInt<MOD> res = lhs;
  res /= rhs;
  return res;
}
template<Int MOD>
ModInt<MOD> operator / (const ModInt<MOD>& lhs, signed rhs) {
  ModInt<MOD> res = lhs;
  res /= ModInt<MOD>(rhs);
  return res;
}
template<Int MOD>
ModInt<MOD> operator / (const ModInt<MOD>& lhs, signed long long rhs) {
  ModInt<MOD> res = lhs;
  res /= ModInt<MOD>(rhs);
  return res;
}
template<Int MOD>
ModInt<MOD> operator / (signed lhs, const ModInt<MOD>& rhs) {
  return rhs/lhs;
}
template<Int MOD>
ModInt<MOD> operator / (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs/lhs;
}

template<Int MOD>
bool operator == (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  return lhs.x == rhs.x;
}
template<Int MOD>
bool operator == (const ModInt<MOD>& lhs, signed rhs) {
  return lhs.x == ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator == (const ModInt<MOD>& lhs, signed long long rhs) {
  return lhs.x == ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator == (signed lhs, const ModInt<MOD>& rhs) {
  return rhs == lhs;
}
template<Int MOD>
bool operator == (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs == lhs;
}

template<Int MOD>
bool operator != (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  return lhs.x != rhs.x;
}
template<Int MOD>
bool operator != (const ModInt<MOD>& lhs, signed rhs) {
  return lhs.x != ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator != (const ModInt<MOD>& lhs, signed long long rhs) {
  return lhs.x != ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator != (signed lhs, const ModInt<MOD>& rhs) {
  return rhs != lhs;
}
template<Int MOD>
bool operator != (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs != lhs;
}

template<Int MOD>
bool operator < (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  return lhs.x < rhs.x;
}
template<Int MOD>
bool operator < (const ModInt<MOD>& lhs, signed rhs) {
  return lhs.x < ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator < (const ModInt<MOD>& lhs, signed long long rhs) {
  return lhs.x < ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator < (signed lhs, const ModInt<MOD>& rhs) {
  return rhs < lhs;
}
template<Int MOD>
bool operator < (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs < lhs;
}

template<Int MOD>
bool operator <= (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  return lhs.x <= rhs.x;
}
template<Int MOD>
bool operator <= (const ModInt<MOD>& lhs, signed rhs) {
  return lhs.x <= ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator <= (const ModInt<MOD>& lhs, signed long long rhs) {
  return lhs.x < ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator <= (signed lhs, const ModInt<MOD>& rhs) {
  return rhs <= lhs;
}
template<Int MOD>
bool operator <= (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs <= lhs;
}

template<Int MOD>
bool operator > (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  return lhs.x > rhs.x;
}
template<Int MOD>
bool operator > (const ModInt<MOD>& lhs, signed rhs) {
  return lhs.x > ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator > (const ModInt<MOD>& lhs, signed long long rhs) {
  return lhs.x > ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator > (signed lhs, const ModInt<MOD>& rhs) {
  return rhs > lhs;
}
template<Int MOD>
bool operator > (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs > lhs;
}

template<Int MOD>
bool operator >= (const ModInt<MOD>& lhs, const ModInt<MOD>& rhs) {
  return lhs.x >= rhs.x;
}
template<Int MOD>
bool operator >= (const ModInt<MOD>& lhs, signed rhs) {
  return lhs.x >= ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator >= (const ModInt<MOD>& lhs, signed long long rhs) {
  return lhs.x > ModInt<MOD>(rhs);
}
template<Int MOD>
bool operator >= (signed lhs, const ModInt<MOD>& rhs) {
  return rhs >= lhs;
}
template<Int MOD>
bool operator >= (signed long long lhs, const ModInt<MOD>& rhs) {
  return rhs >= lhs;
}

template<Int MOD>
istream& operator >> (istream& is, ModInt<MOD>& a) {
  is >> a.x;
  return is;
}
template<Int MOD>
ostream& operator << (ostream& os, ModInt<MOD>& a) {
  os << a.x;
  return os;
}
