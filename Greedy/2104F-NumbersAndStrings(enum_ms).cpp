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

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    const int lim = 1'000'000'000-2;
    vector<ll> canon_pref;
    FOR(i, 1, 9) {
        canon_pref.push_back(i);
    }
    auto enum_ms = [&] (int n, int k) -> void {
        vector<int> A(k);
        auto process = [&] (vector<int> v) -> void {
            if(v[0]==n) return;
            ll x = 0;
            ROF(i, 9, 1) {
                if(v[i] > 0) x = i;
            }
            v[x]--;
            F0R(i, 10) F0R(j, v[i]){
                x = 10*x+i;
            }
            F0R(i, 10) {
                canon_pref.push_back(10*x+i);
            }
        };
        auto dfs = [&] (auto dfs, int p, int sm) -> void {
            if(p==k) {
                if(sm==0) process(A);
                return;
            }
            F0R(x, sm+1) {
                A[p] = x;
                dfs(dfs, p+1, sm-x);
            }
        };
        dfs(dfs, 0, n);
    };
    FOR(L, 1, 9) {
        enum_ms(L, 10);
    }
    vector<int> cand;
    trav(x, canon_pref) {
        while(x <= lim) {
            cand.push_back(x);
            x = 10*x+9;
        }
    }

    sort(all(cand));
    cand.erase(unique(all(cand)), cand.end());
    set<string> S;
    vector<int> A;
    trav(u, cand) {
        string g = "";
        g += to_string(u);
        g += to_string(u+1);
        sort(all(g));
        if(S.count(g)) continue;
        S.insert(g);
        A.push_back(u);
    }
    int t; cin >> t;
    while(t--) {
        int x; cin >> x;
        int ans = upper_bound(all(A), x) - A.begin();
        cout << ans << "\n";
    }
    return 0;
}   