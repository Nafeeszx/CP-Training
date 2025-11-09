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

ll mod = 998244353;

struct DSU {
    vi e; 
    void init(int N) { e = vi(N,-1); }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
    bool sameSet(int a, int b) { return get(a) == get(b); }
    int size(int x) { return -e[get(x)]; }
    bool unite(int x, int y) { 
        x = get(x), y = get(y); if (x == y) return 0;
        if (e[x] > e[y]) swap(x,y);
        e[x] += e[y]; e[y] = x; return 1;
    }
};

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj1(n), adj2(n);
    set<pair<int, int>> st;
    vector<pair<int, int>> res;
    F0R(i, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
        st.insert(minmax(u, v));
    }      
    vector<int> p(n);
    vector<int> mxp(n);
    F0R(i, n) {cin >> p[i]; p[i]--; mxp[p[i]] = i;}
    DSU d; d.init(n);
    ROF(i, n-1, 0) {
        int u = p[i];  
        int j = i+1;
        while(j <= mxp[u]) {
            auto nedge = minmax(p[j], u); 
            if(!st.count(nedge)) {
                res.push_back(nedge);
                st.insert(nedge);
            }
            int xx = p[j];
            j += d.size(p[j]);
            d.unite(u, xx);
        }
        trav(x, adj1[u]) {
            adj2[x].push_back(u);
            mxp[x] = max(mxp[x], i);
        }
    }
    cout << res.size() << "\n";
    trav(x, res) {
        cout << x.f+1 << " " << x.s+1 << "\n";
    }
    return 0;
}   
