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
    int k, n, m; cin >> k >> n >> m;
    vector<ll> jpos, jneg, gpos, gneg;
    F0R(i, n) {
        int u; cin >> u;
        if(u > 0) jpos.push_back(u);
        else jneg.push_back(u);
    }
    F0R(i, m) {
        int u; cin >> u;
        if(u > 0) gpos.push_back(u);
        else gneg.push_back(u);
    }
    sort(all(gpos)), sort(all(gneg)), sort(all(jpos)), sort(all(jneg));
    reverse(all(gneg));
    reverse(all(jneg));
    priority_queue<ll> ps;
    while(!gpos.empty() && !jpos.empty()) {
        ps.push(gpos.back()*jpos.back());
        gpos.pop_back();
        jpos.pop_back();
    }
    while(!gneg.empty() && !jneg.empty()) {
        ps.push(gneg.back()*jneg.back());
        gneg.pop_back();
        jneg.pop_back();
    }
    
    ll ans = 0;
    int curr = 0;
    while(true) {
        if(ps.empty()) break;
        if(curr == k) break;
        curr++;
        ans += ps.top();
        ps.pop();
    }
    // cout << ps.size() << "\n";
    // T-124
    int kk = min(k-curr, int(min(gpos.size(), jneg.size())));
    F0R(i, kk) {
        ps.push(gpos[i]*jneg[kk-1-i]);
    }

    kk = min(k-curr, int(min(gneg.size(), jpos.size())));
    F0R(i, kk) {
        ps.push(gneg[i]*jpos[kk-1-i]);
    }
    while(true) {
        if(ps.empty()) break;
        if(curr == k) break;
        curr++;
        ans += ps.top();
        ps.pop();
    }
    cout << ans << "\n";
    return 0;
}   
