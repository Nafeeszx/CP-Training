// 3 tricks here
// SOS dp's difference array trick
// decomposition trick in query
// tie-breaking tricks
// here A before the query is the sum of A in the description

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
#define int ll

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
istream& operator>>(istream& is, const mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

signed main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int d, n, m; cin >> d >> n >> m;
    vector<int> a(m), b(n);
    F0R(i, n) cin >> b[i];
    F0R(i, m) cin >> a[i];
    sort(all(a));
    vector<mint> A(1<<m, 1);

    int al = (1<<m)-1;
    F0R(i, m) F0R(j, n) {
        int d = abs(a[i]-b[j]);
        int U;
        if(a[i] < b[j]) {
            int idx = lower_bound(all(a), b[j]+d) - a.begin();
            U = al^((1<<idx)-1)^((1<<(i+1))-1);
        }
        else {
            int idx = lower_bound(all(a), b[j]-d) - a.begin();
            U = al^((1<<idx)-1)^((1<<i)-1);
        }
        A[U] *= d;
        A[U^((1<<i))] /= d;
    }

    F0R(i, m) ROF(j, (1<<m)-1, 0) {
        if(j>>i&1) {
            A[j^(1<<i)] *= A[j];
        }
    }
    F0R(i, 1<<m) {
        A[i] *= (__builtin_popcount(i) & 1 ? mod-1 : 1);
    }
    F0R(i, m) FOR(j, 0, (1<<m)-1) {
        if(~j>>i&1) {
            A[j^(1<<i)] += A[j];
        }
    }

    int q; cin >> q;
    while(q--) {
        int f; cin >> f;
        mint ans = mint(d+1).pow(n+1);
        F0R(i, m) {
            int d = abs(a[i]-f);
            int U;
            if(a[i] < f) {
                int idx = lower_bound(all(a), f+d) - a.begin();
                U = al^((1<<idx)-1)^((1<<(i+1))-1);
            }
            else {
                int idx = lower_bound(all(a), f-d) - a.begin();
                U = al^((1<<idx)-1)^((1<<i)-1);
            }
            ans += (A[U]-A[U^(1<<i)])*d;
        }
        cout << ans << "\n";
    }
    return 0;
}   
