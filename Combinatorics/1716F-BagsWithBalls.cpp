// S(k, i) * i! = number of array of length k with i distinct integers 

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
  mint(ll x=0):x(x){}
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

const int MX = 2005;
mint S[MX][MX];

int main() 
{	
    FOR(i, 1, MX-1) S[i][1] = 1; 
    FOR(i, 2, MX-1) FOR(j, 1, i) {
        S[i][j] = S[i-1][j-1] + S[i-1][j]*j;
    }       
    int t; 
    scanf("%d", &t);
    while(t--) {
        int n, m, k; 
        scanf("%d%d%d", &n, &m, &k);
        mint ans, P = 1;
        mint m2 = 1;
        mint mm = mint(m).pow(n);
        mint m_inv = mint(m).inv();
        FOR(i, 1, min(k, n)) {
            P *= (n-i+1);
            m2 *= (m+1)>>1;
            mm *= m_inv;
            ans += S[k][i] * P * m2 * mm;
        }
        int ff = ans.x;
        printf("%d\n", ff);
    }
    return 0;
}   
