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

int ed[40][40];
vector<int> adj[40];

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n); F0R(i, n) {cin >> a[i]; a[i]--;}    
    vector<int> x(m); F0R(i, m) cin >> x[i];
    vector<int> g1, g2, p_g2(m);
    int base = x[a[0]] + (a[0] != a[n-1] ? x[a[n-1]] : 0);
    F0R(i, m) {
        if(i==a[0]||i==a[n-1]) continue;
        if(g1.size() < 20) {
            g1.push_back(i);
        }
        else {
            p_g2[i] = g2.size();
            g2.push_back(i);
        }
    }
    F0R(i, n-1) {
        int u = a[i], v = a[i+1];
        if(u==a[0] || v==a[0] || u == a[n-1] || v==a[n-1]) continue;
        if(ed[u][v]) continue;
        ed[u][v] = ed[v][u] = 1;
        if(u > v) swap(u, v);
        if(!g2.empty()) {
            if(u < g2[0] && v >= g2[0]) {
                adj[u].push_back(p_g2[v]);
            }
        }
    }

    if(g1.empty()) {
        cout << base << "\n";
        return 0;
    }   
    vector<int> g2dp(1<<g2.size(), mod);
    if(!g2.empty()) {
        F0R(i, 1<<g2.size()) {
            vector<int> y;
            int cost = 0;
            F0R(j, g2.size()) {
                if(~i>>j&1) y.push_back(g2[j]);
                else cost += x[g2[j]];
            }
            bool ed_found = false;
            F0R(i, y.size()) if(ed[y[i]][y[i]]) {ed_found=true; break;}
            F0R(i, y.size()) F0R(j, i) if(ed[y[i]][y[j]]) {ed_found=true; break;}
            if(ed_found) continue;
            g2dp[i] = cost;
        }
        F0R(j, g2.size()) ROF(i, (1<<g2.size())-1, 0) {
            if(i>>j&1) g2dp[i^(1<<j)] = min(g2dp[i], g2dp[i^(1<<j)]);
        }
    }
    int ans = mod;
    F0R(i, 1<<g1.size()) {
        vector<int> y;
        int cost = 0, msk=0;
        F0R(j, g1.size()) {
            if(~i>>j&1) {
                y.push_back(g1[j]);
                trav(pp, adj[g1[j]]) {
                    msk |= (1<<pp);
                }
            }
            else cost += x[g1[j]];
        }
        bool ed_found = false;

        F0R(i, y.size()) if(ed[y[i]][y[i]]) {ed_found=true; break;}
        F0R(i, y.size()) F0R(j, i) if(ed[y[i]][y[j]]) {ed_found=true; break;}
        if(ed_found) continue;
        if(!g2.empty()) cost += g2dp[msk];
        ans = min(ans, cost);
    }
    cout << ans+base << "\n";
    return 0;
}   
