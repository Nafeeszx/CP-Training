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

struct Matrix{
    vector<vector<ll>> m;
    int n;
    Matrix(int n) : n(n), m(n, vector<ll>(n)) {

    }
    Matrix operator*(const Matrix&A) {
        Matrix res(A.m.size());
        int n = A.m.size();
        F0R(i, n) F0R(j, n) F0R(k, n) {
            res.m[i][j] = max(res.m[i][j], m[i][k]+A.m[k][j]);
        }
        return res;
    }
    Matrix pow(int k) {
        Matrix base(n), res(n);
        base.m = m;
        while(k) {
            int x = k&1;
            if(x) res = res*base;
            k>>=1;
            base = base*base;
        }
        return res;
    }
};

void solve()
{
    int n, m, __k, r; cin >> n >> m >> __k >> r;
    vector<int> a(n), c(n);
    F0R(i, n) cin >> a[i] >> c[i];
    Matrix A(1<<n);
    F0R(i, 1<<n) F0R(j, 1<<n) {
        ll cost = 0, dam = 0;
        F0R(k, n) {
            if(j>>k&1) {
                dam += a[k];
                cost += c[k];
                if(i>>k&1) cost += __k;
            }
        }
        if(cost <= m) A.m[i][j] = dam; 
    }
    A = A.pow(r);
    ll ans = 0;
    F0R(j, 1<<n) ans = max(ans, A.m[0][j]);
    cout << ans << "\n";
}   

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();    
    return 0;
}   
