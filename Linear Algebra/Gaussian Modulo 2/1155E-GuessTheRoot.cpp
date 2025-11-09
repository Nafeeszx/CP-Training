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

const ll mod = 1000003;
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

int Gauss(vector<vector<mint>> a, vector<mint> &ans) {
  int n = (int)a.size(), m = (int)a[0].size() - 1;
  vector<int> pos(m, -1);
  for(int col = 0, row = 0; col < m && row < n; ++col) {
    int mx = row;
    for(int i = row; i < n; i++) if(a[i][col].x > a[mx][col].x) mx = i;
    if(a[mx][col].x == 0) {continue;}
    swap(a[row], a[mx]);
    pos[col] = row;
    mint inv_pivot = a[row][col].inv();
    for(int j = col; j <= m; j++) {
        a[row][j] *= inv_pivot;
    }
    for(int i = 0; i < n; i++) {
      if(i != row && a[i][col].x != 0) {
        mint c = a[i][col];
        for(int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
      }
    }
    ++row; 
  }
  ans.assign(m, 0);
  for(int i = 0; i < m; i++) {
    if(pos[i] != -1) ans[i] = a[pos[i]][m];
  }
  return 1; //unique solution
}
int main() {    
    int n=11, m=11;
    vector<vector<mint>> v(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i==0&&j==0) v[i].push_back(1); 
            else v[i].push_back(mint(i).pow(j));
        }
        cout << "? " << i << endl;
        int k; cin >> k;
        if(k==0) {
            cout << "! " << i << endl;
            return 0;
        }
        v[i].emplace_back(k);
    }
    vector<mint> ans;
    Gauss(v, ans);
    FOR(i, 11, mod-1) {
        mint res;
        mint x = 1;
        trav(u, ans) {
            res += u * x;
            x *= i; 
        }
        if(res.x==0) {
            cout << "! " << i << endl;
            return 0;
        }
    }
    cout << "! " << -1 << endl;
    return 0;
}


