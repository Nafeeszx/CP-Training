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

struct S{
    ll ans, sm, pre, suf;
    S(ll a = 0) {sm = a, ans = max(a, 0LL), pre = ans, suf = ans;}
};

S combine(S a, S b) {
    S res;
    res.sm = a.sm+b.sm;
    res.pre = max(a.pre, a.sm+b.pre);
    res.suf = max(b.suf, b.sm+a.suf);
    res.ans = max(max(a.ans, b.ans), a.suf+b.pre);
    return res;
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    int n2 = 1<<n;
    vector<vector<S>> pre(n2);
    F0R(i, n2) {
        int u; cin >> u;
        pre[i].emplace_back(u);
    }
    F0R(i, n) {
        vector<vector<S>> cur(n2/(1<<(i+1)), vector<S>(1<<(i+1)));
        F0R(par, n2/(1<<(i+1))) {
            F0R(x, 1<<(i+1)) {
                if(x>>i&1) cur[par][x] = combine(pre[2*par+1][x^(1<<i)], pre[2*par][x^(1<<i)]); 
                else cur[par][x] = combine(pre[2*par][x], pre[2*par+1][x]);
            }
        }
        pre = cur;
    }
    int mask = 0, q;
    cin >> q;
    while(q--) {
        int x; cin >> x;
        mask ^= (1<<x);
        cout << pre[0][mask].ans << "\n";
    }
    return 0;
}   
