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

struct DSU {
    int n;
    vector<int> par, e1, e2;
    vector<pair<int &, int>> hist;
    DSU (int n) : n(n), par(n), e1(n), e2(n) {
        iota(all(par), 0);
        F0R(x, n/2) e1[x] = 1;
        FOR(x, n/2, n-1) e2[x] = 1;
    }
    void set(int & x, int y) {
        hist.emplace_back(x, x);
        x = y;
    }
    int find (int x) {
        // assert(0 <= x && x < par.size());
        if(par[x]==x) return x;
        return find(par[x]);
    }
    void merge (int a, int b, ll& ans) {
        a = find(a);
        b = find(b);
        if(a==b) return;
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        if(e1[a]+e2[a] < e1[b]+e2[b]) swap(a, b);
        ans -= e1[a]*1LL*e2[a] + e1[b]*1LL*e2[b];
        set(e1[a], e1[a]+e1[b]);
        set(e2[a], e2[a]+e2[b]);
        set(par[b], a);
        ans += e1[a]*1LL*e2[a];
    }
    
    int timestamp() {return hist.size();}
    
    void rollback(int t) {
        while(hist.size() > t) {
            auto [u, v] = hist.back();
            u = v;
            hist.pop_back();
        }
    }
};

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    map<pair<int, int>, int> mp;
    const int MX = 300000;
    DSU d(2*MX);
    int c = __lg(2*MX)+1;
    vector<vector<pair<int, int>>> ed(2*(1<<c));
    auto add_edge = [&] (auto add_edge, pair<int, int> e, int l, int r, int x, int lx, int rx) -> void {
        if(l <= lx && rx <= r) {
            ed[x].push_back(e);
            // cout << "{" << e.f << " " << e.s << "} " << lx << " " << rx << "\n";
            return;
        }
        if(r <= lx || rx <= l) return;
        int m = (lx+rx)>>1;
        add_edge(add_edge, e, l, r, 2*x+1, lx, m);
        add_edge(add_edge, e, l, r, 2*x+2, m, rx);
    };
    F0R(i, n) {
        int x, y; cin >> x >> y;
        x--; y += -1+MX;
        if(mp.find({x, y}) != mp.end()) {
            add_edge(add_edge, {x, y}, mp[{x, y}], i, 0, 0, 1<<c);
            mp.erase({x, y});
        }
        else mp[{x, y}] = i;        
    }
    trav(u, mp) {
        add_edge(add_edge, u.first, u.second, n, 0, 0, 1<<c);    
        // cout << u.second << " " << n << "\n";
    }
    vector<ll> res(n);
    auto dfs = [&] (auto dfs, int x, int lx, int rx, ll ans) -> void {
        int t = d.timestamp();
        trav(v, ed[x]) {
            auto [aa, bb] = v;
            d.merge(aa, bb, ans);
        }
        if(lx+1==rx) {
            if(lx < n) res[lx] = ans;
        }
        else {
            int m = (lx+rx)>>1;
            dfs(dfs, 2*x+1, lx, m, ans);
            dfs(dfs, 2*x+2, m, rx, ans);
        }
        d.rollback(t);
    };
    dfs(dfs, 0, 0, 1<<c, 0);
    trav(u, res) cout << u << " ";
    return 0;
}   
