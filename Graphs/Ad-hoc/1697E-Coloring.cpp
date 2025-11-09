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
    return fact[n]*ifact[n-k];
  }
};

const int N = 105;
int dist[N][N];

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> x(n), y(n);
    F0R(i, n) cin >> x[i] >> y[i];
    vector<vector<int>> adj(n);
    F0R(i, n) {
        F0R(j, n) {
            if(i==j) {dist[i][j] = mod; continue;}
            dist[i][j] = abs(x[i]-x[j])+abs(y[i]-y[j]);
        }
    }
    F0R(i, n) {
        int xx = *min_element(dist[i], dist[i]+n);
        F0R(j, n) if(xx==dist[i][j]) {
            adj[i].push_back(j);
        }
    }
    vector<int> vis(n);
    vector<vector<int>> comps;
    F0R(i, n) if(!vis[i]) {
        vector<int> x = adj[i];
        x.push_back(i);
        sort(all(x));
        int xx = *min_element(dist[i], dist[i]+n);
        bool ok = true;
        trav(pp, x) trav(qq, x) if(pp!=qq) {
            if(dist[pp][qq]!=xx) ok = false; 
        }
        trav(u, x) {
            vector<int> px = adj[u];
            px.push_back(u);
            sort(all(px));
            if(px != x) ok = false;
        }
        if(ok) {
            comps.push_back(x);
            trav(u, x) {vis[u] = 1; /*cout << u << " ";*/}
            // cout << "\n";
        }
        else {
            // cout << i << "\n";
            comps.push_back({i});
            vis[i] = 1;
        }
    }
    combination P(N);
    vector<mint> dp(n+1);
    dp[0] = 1;
    trav(u, comps) {
        vector<mint> pre(n+1);
        swap(pre, dp);
        FOR(i, 0, n-1) {
            if(u.size() > 1 && i+u.size() <= n) dp[i+u.size()] += pre[i];
            dp[i+1] += pre[i];
        }
    }
    mint ans;
    FOR(i, 1, n) {
        ans += dp[i] * P(n, i);
    }
    cout << ans << "\n";
    return 0;
}   
