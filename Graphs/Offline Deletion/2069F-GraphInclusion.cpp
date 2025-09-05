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

struct DSU {
    std::vector<std::pair<int &, int>> his;
    
    int n;
    std::vector<int> f, g, bip;
    
    DSU(int n_) : n(n_), f(n, -1), g(n), bip(n, 1) {}
    
    std::pair<int, int> find(int x) {
        if (f[x] < 0) {
            return {x, 0};
        }
        auto [u, v] = find(f[x]);
        return {u, v ^ g[x]};
    }
    
    void set(int &a, int b) {
        his.emplace_back(a, a);
        a = b;
    }
    
    void merge(int a, int b, int &comp) {
        auto [u, xa] = find(a);
        auto [v, xb] = find(b);
        int w = xa ^ xb ^ 1;
        if (u == v) {
            return;
        }
        if (f[u] > f[v]) {
            std::swap(u, v);
        }
        comp--;
        set(bip[u], bip[u] && bip[v]);
        set(f[u], f[u] + f[v]);
        set(f[v], u);
        set(g[v], w);
    }
    
    int timeStamp() {
        return his.size();
    }
    
    void rollback(int t) {
        while (his.size() > t) {
            auto [x, y] = his.back();
            x = y;
            his.pop_back();
        }
    }
};
 

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    map<array<int, 2>, int> mp, mpB, mpAB;
    const int N = (1<<(__lg(m)+2));
    vector<vector<array<int, 2>>> ed(N), edAB(N);
    auto add = [&] (auto add, int p, int l, int r, int x, int y, array<int, 2>e) -> void {
        if(l >= y || r <= x) return;
        if(l >= x && r <= y) {
            ed[p].emplace_back(e);
            return;
        }
        int m = (l+r)>>1;
        add(add, (p<<1), l, m, x, y, e);
        add(add, (p<<1)^1, m, r, x, y, e);
    };
    auto addAB = [&] (auto addAB, int p, int l, int r, int x, int y, array<int, 2>e) -> void {
        if(l >= y || r <= x) return;
        if(l >= x && r <= y) {
            edAB[p].emplace_back(e);
            return;
        }
        int m = (l+r)>>1;
        addAB(addAB, (p<<1), l, m, x, y, e);
        addAB(addAB, (p<<1)^1, m, r, x, y, e);
    };
    F0R(i, m) {
        char C; int u, v; cin >> C >> u >> v;
        u--; v--;
        if(u > v) swap(u, v);
        if(C=='A') {
            if(mp.find({u, v})==mp.end()) {
                mp[{u, v}] = i;
                if(mpAB.find({u, v})==mpAB.end()) mpAB[{u, v}] = i;
            }
            else {
                add(add, 1, 0, m, mp[{u, v}], i, {u, v});
                mp.erase({u, v});
            }
        }
        if(C=='B') {
            if(mpB.find({u, v})==mpB.end()) {
                mpB[{u, v}] = i;
                if(mpAB.find({u, v})==mpAB.end()) mpAB[{u, v}] = i;
            }
            else {
                mpB.erase({u, v});
            }
        }
        if(mp.find({u, v})==mp.end() && mpB.find({u, v})==mpB.end()) {
            addAB(addAB, 1, 0, m, mpAB[{u, v}], i, {u, v});
            mpAB.erase({u, v});
        }
    }
    trav(u, mp) {
        add(add, 1, 0, m, u.s, m, u.f);
    }
    mp.clear();
    trav(u, mpAB) {
        addAB(addAB, 1, 0, m, u.s, m, u.f);
    }
    mpAB.clear();

    DSU d(n), dAB(n);
    vector<int> ans(m);
    auto dfs = [&] (auto dfs, int p, int l, int r, int comp, int compAB) -> void {
        int t = d.timeStamp();
        int tt = dAB.timeStamp();
        trav(u, ed[p]) {
            d.merge(u[0], u[1], comp);
        }
        trav(u, edAB[p]) {
            dAB.merge(u[0], u[1], compAB);
        }   
        if(r-l==1) {
            ans[l] = comp-compAB;
        }
        else {
            int m = (l+r)>>1;
            dfs(dfs, (p<<1), l, m, comp, compAB);
            dfs(dfs, (p<<1)^1, m, r, comp, compAB);
        }
        d.rollback(t);
        dAB.rollback(tt);
    };
    dfs(dfs, 1, 0, m, n, n);
    trav(u, ans) {
        cout << u << "\n";
    }
    return 0;
}   
