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
istream& operator>>(istream& is, const mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}

int main() {    
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> cnt(n+1);
    F0R(i, n) {
        int c; cin >> c;
        cnt[c]++;
    }
    vector<vector<mint>> dp(n+1, vector<mint>(n+1)), pref(n+1, vector<mint>(n+1));
    mint ans;
    vector<mint> inv(n+1);
    FOR(i, 1, n) inv[i] = mint(i).inv();
    pref[0] = vector<mint>(n+1, 1);
    FOR(len, 1, n) {
        FOR(last, 1, n) {
            dp[len][last] = pref[len-1][last-1]*cnt[last]*inv[n-len+1];
            // cout << len << " " << last << ": " << cnt[last] << " " << dp[len][last] << endl;
            pref[len][last] = pref[len][last-1] + dp[len][last];
            if(len < n) ans += dp[len][last]*(cnt[last]-1)*inv[n-len]; 
        }
    }
    cout << ans << "\n";
    return 0;
}


