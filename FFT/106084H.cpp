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

void setIO(string name = "") { 
    ios_base::sync_with_stdio(0); cin.tie(0);
    if(name.size()){
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}
 

namespace NTT {
    vector<int> perm, wp[2];
    const int mod = 998244353, G = 3;    ///G is the primitive root of M
    int root, inv, N, invN;

    int power(int a, int p) {
        int ans = 1;
        while (p) {
            if (p & 1) ans = (1LL*ans*a)%mod;
            a = (1LL*a*a)%mod;
            p >>= 1;
        }
        return ans;
    }

    void precalculate(int n) {
        assert( (n&(n-1)) == 0 && (mod-1)%n==0);
        N = n;
        invN = power(N, mod-2);
        perm = wp[0] = wp[1] = vector<int>(N);

        perm[0] = 0;
        for (int k=1; k<N; k<<=1)
            for (int i=0; i<k; i++) {
                perm[i] <<= 1;
                perm[i+k] = 1 + perm[i];
            }

        root = power(G, (mod-1)/N);
        inv = power(root, mod-2);
        wp[0][0]=wp[1][0]=1;

        for (int i=1; i<N; i++) {
            wp[0][i] = (wp[0][i-1]*1LL*root)%mod;
            wp[1][i] = (wp[1][i-1]*1LL*inv)%mod;
        }
    }

    void fft(vector<int> &v, bool invert = false) {
        if (v.size() != perm.size())   precalculate(v.size());
        for (int i=0; i<N; i++)
            if (i < perm[i])
                swap(v[i], v[perm[i]]);

        for (int len = 2; len <= N; len *= 2) {
            for (int i=0, d = N/len; i<N; i+=len) {
                for (int j=0, idx=0; j<len/2; j++, idx += d) {
                    int x = v[i+j];
                    int y = (wp[invert][idx]*1LL*v[i+j+len/2])%mod;
                    v[i+j] = (x+y>=mod ? x+y-mod : x+y);
                    v[i+j+len/2] = (x-y>=0 ? x-y : x-y+mod);
                }
            }
        }
        if (invert) {
            for (int &x : v) x = (x*1LL*invN)%mod;
        }
    }

    vector<int> multiply(vector<int> a, vector<int> b) {
        int n = 1;
        while (n < a.size()+ b.size())  n<<=1;
        a.resize(n);
        b.resize(n);

        fft(a);
        fft(b);
        for (int i=0; i<n; i++) a[i] = (a[i] * 1LL * b[i])%mod;
        fft(a, true);
        return a;
    }
};

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
    setIO();
    int n, m; cin >> n >> m;
    vector<mint> fac(2*n+1);
    fac[0] = 1;
    FOR(i, 1, 2*n) {
        fac[i] = fac[i-1]*i;
    }
    ll s = 0;
    vector<int> k(m);
    F0R(_, m) {
        cin >> k[_];
        s += k[_];
    }
    vector<mint> nff(2*n+1);
    nff[2*n] = s-2*n+1;
    ROF(i, 2*n-1, 0) {
        nff[i] = nff[i+1] * (s-i+1);
    }
    vector<mint> s_2n(2*n+1), s_(2*n+1), two_n(2*n+1);
    s_2n[0] = 1, s_[0] = 1, two_n[0] = 1;
    FOR(i, 1, 2*n) {
        if(s-2*n >= i) s_2n[i] = s_2n[i-1]*(s-2*n-i+1)/i;
        if(s >= i) s_[i] = s_[i-1]*(s-i+1)/i;
        two_n[i] = two_n[i-1] * (2*n-i+1) / i;
    }
    vector<int> a(2*n), b(2*n);
    F0R(i, 2*n) a[i] = (i%2 ? two_n[i].x : 0), b[i] = s_2n[i].x;
    // F0R(i, 2*n) {
    //     cout << a[i] << " " << b[i] << "\n";
    // }
    auto x = NTT::multiply(a, b);
    mint ans;
    F0R(i, m) {
        mint curr = x[k[i]];
        ans += curr * nff[k[i]+1] * (fac[k[i]] / fac[2*n]);
        // cout << s_[k[i]] << "\n";
    }
    cout << ans/2 << "\n";
    return 0;
}