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

const ll mod = 998244353, inf = mod*mod;


template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    int ceil_pow2(int n) {
        int x = 0;
        while ((1U << x) < (unsigned int)(n)) x++;
        return x;
    }
    segtree() : segtree(0) {}
    segtree(int n) : segtree(std::vector<S>(n, e())) {}
    segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

using S = int;

S op (S a, S b) {
    return min(a, b);
}

S e() {
    return mod;    
}

using T = pair<int, int>;

T mn (T a, T b) {
    return min(a, b);
}

T e1() {
    return {mod, mod};
}

T mx (T a, T b) {
    return max(a, b);
}

T e2() {
    return {-mod, -mod};
}



int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m, q; cin >> n >> m >> q;
        vector<vector<int>> adj(2*n);
        vector<int> par(2*n);
        vector<pair<int, int>> ed(m);
        F0R(i, m) {
            cin >> ed[i].f >> ed[i].s;
            ed[i].f--; ed[i].s--;
        }    
        int id = n;
        auto find = [&] (auto find, int u) -> int {
            return par[u] == u ? u : par[u] = find(find, par[u]);
        };
        F0R(i, n) {
            par[i] = i;
        }
        vector<int> id_e(2*n-1);
        F0R(i, m) {
            auto unite = [&] (int u, int v) -> void {
                u = find(find, u), v = find(find, v);
                if (u == v)
                return;
                par[u] = par[v] = par[id] = id;
                adj[id] = {u, v};
                id_e[id] = i;
                id++;
            };
            unite(ed[i].f, ed[i].s);
        }
        vector<int> et, tin(2*n-1), tout(2*n-1), et1;
        auto dfs1 = [&] (auto dfs1, int u) -> void {
            tin[u] = et.size();
            et.push_back(u);
            et1.push_back(tin[u]);
            trav(v, adj[u]) {
                dfs1(dfs1, v);
                et.push_back(u);
                et1.push_back(tin[u]);
            }
            tout[u] = et.size();
        };
        dfs1(dfs1, 2*n-2);
        // trav(x, et) cout << x << " ";
        // cout << "\n";
        segtree<S, op, e>ST(et1);
        auto lca = [&] (int u, int v) -> int {
            int uu = tin[u];
            int vv = tin[v];
            int g = ST.prod(uu, vv+1);
            return et[g];
        };

        segtree<T, mn, e1> STmn(n);
        segtree<T, mx, e2> STmx(n);
        F0R(i, n) {
            STmn.set(i, {tin[i], i});
            STmx.set(i, {tin[i], i});
        }

        F0R(_, q) {
            int u, v; cin >> u >> v;
            if(u==v) {
                cout << 0 << " ";
                continue;
            }
            u--;
            auto aaa = STmn.prod(u, v);
            auto bbb = STmx.prod(u, v);
            int x = lca(aaa.s, bbb.s);
            int ads = id_e[x];
            cout << ads+1 << " ";
        }
        cout << "\n";

    }
    return 0;
}   
