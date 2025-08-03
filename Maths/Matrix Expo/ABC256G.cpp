#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for(auto& a : x)
#define FOR(i, a, b) for (int i=(a); i<=(signed)(b); i++)
#define ROF(i, a, b) for (int i=(a); i>=(signed)(b); i--)
#define F0R(i, a) for (int i=0; i<(signed)(a); i++)
#define vi vector<int>
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

const ll mod = 998244353;

struct mint {
  ll x; // typedef long long ll;
  mint(ll x=0):x((x%mod+mod)%mod){}
  mint operator-() const { return mint(-x);}
  mint& operator+=(const mint a) {
    if ((x += a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator-=(const mint a) {
    if ((x += mod-a.x) >= mod) x -= mod;
    return *this;
  }
  mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
  mint operator+(const mint a) const { return mint(*this) += a;}
  mint operator-(const mint a) const { return mint(*this) -= a;}
  mint operator*(const mint a) const { return mint(*this) *= a;}
  mint pow(ll t) const {
    if (!t) return 1;
    mint a = pow(t>>1);
    a *= a;
    if (t&1) a *= *this;
    return a;
  }

  // for prime mod
  mint inv() const { return pow(mod-2);}
  mint& operator/=(const mint a) { return *this *= a.inv();}
  mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}
struct combination {
  vector<mint> fact, ifact;
  combination(int n):fact(n+1),ifact(n+1) {
    assert(n < mod);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
  }
  mint operator()(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n]*ifact[k]*ifact[n-k];
  }
};


template<typename T>
struct Matrix {
  int h, w;
  vector<vector<T>> d;
  Matrix() {}
  Matrix(int h, int w, T val=0): h(h), w(w), d(h, vector<T>(w,val)) {}
  Matrix& unit() {
    assert(h == w);
    F0R(i,h) d[i][i] = 1;
    return *this;
  }
  const vector<T>& operator[](int i) const { return d[i];}
  vector<T>& operator[](int i) { return d[i];}
  Matrix operator*(const Matrix& a) const {
    assert(w == a.h);
    Matrix r(h, a.w);
    F0R(i,h)F0R(k,w)F0R(j,a.w) {
      r[i][j] += d[i][k]*a[k][j];
    }
    return r;
  }
  Matrix pow(long long t) const {
    assert(h == w);
    if (!t) return Matrix(h,h).unit();
    if (t == 1) return *this;
    Matrix r = pow(t>>1);
    r = r*r;
    if (t&1) r = r*(*this);
    return r;
  }
};



int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll n, d; cin >> n >> d;
    combination C(d);
    mint ans;
    F0R(k, d+2) {
        Matrix<mint> M(2, 2);
        M[0][0] = C(d-1, k);
        M[0][1] = C(d-1, k-1);
        M[1][0] = C(d-1, k-1);
        M[1][1] = C(d-1, k-2);
        M = M.pow(n);
        ans += M[0][0] + M[1][1];
    }
    cout << ans;
    return 0;
}   
