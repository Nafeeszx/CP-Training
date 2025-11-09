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

const ll mod = 1e9+7;

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

int n, m;

mint small(combination &C,  vector<pair<int, int>> &ap) {
    // cout << "====\n";
    sort(all(ap), [&] (auto &x, auto &y){
        return x.f+x.s < y.f+y.s;
    });
    if(ap[0]==pair<int, int>(0, 0) || ap.back()==pair<int, int>(n-1, m-1)) return 0;
    ap.push_back({n-1, m-1});
    vector<mint> dp(ap.size());
    F0R(i, ap.size()) {
        auto [tx, ty] = ap[i];
        dp[i] = C(tx+ty,ty);
        // cout << "start " << i << ": " << dp[i] << "\n";
        ROF(j, i-1, 0) {
            auto [sx, sy] = ap[j];
            int dx = tx-sx, dy = ty-sy;
            if(dx>=0 && dy>=0) dp[i] += (-dp[j])*C(dx+dy, dx); 
            // cout << j << ": " << dp[i] << "\n";
        }
    }
    return dp.back();
}

void solve() {
    cin >> n >> m;
    int k; cin >> k;
    vector<pair<int, int>> ap;
    F0R(_, k) {
        int u, v; cin >> u >> v; u--; v--;
        ap.emplace_back(u, v);
    }
    combination C(n+m);
    cout << small(C, ap) << "\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t=1; //cin >> t;
    while(t--) solve();
    return 0;
}   
