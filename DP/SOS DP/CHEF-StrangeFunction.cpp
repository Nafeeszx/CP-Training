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

const ll mod = 1e9 + 7;

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

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<mint> A(n);
    F0R(i, n) {
        int u; cin >> u;
        A[i] = u;
    }
    int xx = __lg(n)+1;
    vector<vector<mint>> F2_sm(n, vector<mint>(xx+1)), G_sm(n, vector<mint>(xx+1));
    vector<mint> F(n), G(n);

    F0R(i, n) {

        vector<mint> nw(xx+1);
        F0R(j, xx) {
            if(i>>j&1) {
                nw[j+1] = nw[j] + G_sm[i^(1<<j)][j];
            }
            else {
                nw[j+1] = nw[j];
            }
        }

        mint gsum = nw[xx];
        F[i] = A[i]*A[i]+gsum*gsum;

        F2_sm[i][0] = F[i]*F[i];
        F0R(j, xx) {
            if(i>>j&1) {
                F2_sm[i][j+1] = F2_sm[i][j] + F2_sm[i^(1<<j)][j];
            }
            else {
                F2_sm[i][j+1] = F2_sm[i][j];
            }
        }
        G[i] = F2_sm[i][xx];

        G_sm[i][0] = F2_sm[i][xx];
        F0R(j, xx) {
            if(i>>j&1) {
                G_sm[i][j+1] = G_sm[i][j] + G_sm[i^(1<<j)][j];
            }
            else {
                G_sm[i][j+1] = G_sm[i][j];
            }
        }

    }

    mint ans = 0;
    F0R(i, n) {
        ans += F[i] * G[i] * i;
    }
    cout << ans << "\n";
    return 0;
}   
