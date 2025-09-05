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
    
    void merge(int a, int b, int &ans, int &comp) {
        auto [u, xa] = find(a);
        auto [v, xb] = find(b);
        int w = xa ^ xb ^ 1;
        if (u == v) {
            if (bip[u] && w) {
                set(bip[u], 0);
                ans--;
            }
            return;
        }
        if (f[u] > f[v]) {
            std::swap(u, v);
        }
        comp--;
        ans -= bip[u];
        ans -= bip[v];
        set(bip[u], bip[u] && bip[v]);
        set(f[u], f[u] + f[v]);
        set(f[v], u);
        set(g[v], w);
        ans += bip[u];
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
    int n, q; cin >> n >> q;
    vector<int> g(n);
    const int N = (1<<(__lg(q)+2));
    vector<vector<array<int, 2>>> ed(N);
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
    F0R(i, n) {
        cin >> g[i]; g[i]--;
    }
    vector<int> t(n), ks(q);
    F0R(i, q) {
        int u, v; cin >> u >> v >> ks[i];
        u--; v--;
        add(add, 1, 0, q, t[u], i, {u, g[u]});
        g[u] = v;
        t[u] = i;
    }
    F0R(i, n) {
        add(add, 1, 0, q, t[i], q, {i, g[i]});
    }

    DSU d(n);
    vector<int> ans(q);
    auto dfs = [&] (auto dfs, int p, int l, int r, int bip, int comp) -> void {
        int t = d.timeStamp();
        trav(u, ed[p]) {
            d.merge(u[0], u[1], bip, comp);
        }
        if(r-l==1) {
            if(ks[l] % 3 != 2) {
                ans[l] = ks[l] % 3;
            }
            else {
                ans[l] = ((n-bip) % 2 ? 2 : 1);
            }
        }
        else {
            int m = (l+r)>>1;
            dfs(dfs, (p<<1), l, m, bip, comp);
            dfs(dfs, (p<<1)^1, m, r, bip, comp);
        }
        d.rollback(t);
    };
    dfs(dfs, 1, 0, q, n, n);
    trav(u, ans) {
        cout << u << "\n";
    }
    return 0;
}   
