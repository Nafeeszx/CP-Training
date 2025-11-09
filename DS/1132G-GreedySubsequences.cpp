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

const ll mod = 1e9+7;

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
//internally 1 indexing
    public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        //v is 1 indexed
        size = _n - 1;
        d = std::vector<S>(4 * _n + 5, e());
        lz = std::vector<F>(4 * _n + 5, id());
        arr = v;
        build(1, 1, size);
    }
    void build(int tv, int tl, int tr) {
        if(tl == tr) d[tv] = arr[tl];
        else {
            int tm = (tl + tr) >> 1;
            build(tv*2, tl, tm);
            build(tv*2+1, tm+1, tr);
            d[tv] = op(d[tv*2], d[tv*2 + 1]);
        }
    }
    void push(int tv, int tl, int tr) {
        if(lz[tv]==id()) return;
        d[tv] = mapping(lz[tv], d[tv]);
        if(tl < tr) {
            lz[tv*2] = composition(lz[tv*2], lz[tv]);
            lz[tv*2+1] = composition(lz[tv*2+1], lz[tv]);
        }
        lz[tv] = id();
    }
    void update(int l, int r, F f, int tv, int tl, int tr, int init) {
        push(tv, tl, tr);
        if(r < l) return;
        if(l == tl && r == tr) {
            lz[tv] = f;
            push(tv, tl, tr);
        }
        else {
            int tm = (tl + tr) / 2;
            update(l, min(tm, r), f, tv*2, tl, tm, init);
            update(max(tm+1, l), r, f, tv*2+1, tm+1, tr, init);
            d[tv] = op(d[tv*2], d[tv*2+1]);
        }
    }
    S get(int l, int r, int tv, int tl, int tr) {
        push(tv, tl, tr);
        if(r < l) return e();
        if(l == tl && r == tr) {
            return d[tv];
        }
        else {
            int tm = (tl + tr) / 2;
            return op(get(l, min(tm, r), tv*2, tl, tm),
            get(max(tm+1, l), r, tv*2+1, tm+1, tr));
        }
    }
    void apply(int l, int r, F f) {
        update(l, r, f, 1, 1, size, l);
    }
    S prod(int l, int r) {
        return get(l, r, 1, 1, size);
    }
  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<S> arr;
    std::vector<F> lz;
};

using S = int;
S op(S a, S b) {
    return max(a, b);
}
S e() {
    return 0;
}
using F = int;
S mapping (F f, S s) {
    return f+s;
}
F composition (F f, F g) {
    return f+g;
}
F id () {
    return 0;
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<int> p(n); F0R(i, n) {cin >> p[i]; p[i]--;}
    vector<vector<int>> adj(n);
    stack<pair<int, int>> XD;
    vector<int> indeg(n);
    ROF(i, n-1, 0) {
        while(!XD.empty() && p[i] >= XD.top().f) XD.pop();
        if(!XD.empty()) {adj[XD.top().s].push_back(i); indeg[i]++;}
        XD.push({p[i], i});
    }   
    vector<int> roots;
    F0R(i, n) {
        if(indeg[i]==0) roots.push_back(i);
    }
    vector<int> tin(n, -1), tout(n, -1);
    int timer = 0;
    auto dfs = [&] (auto dfs, int u) -> void {
        tin[u] = timer++;
        trav(v, adj[u]) {
            dfs(dfs, v);
        }
        tout[u] = timer;
    };
    trav(u, roots) dfs(dfs, u);
    lazy_segtree<S, op, e, F, mapping, composition, id> ST(vector<S>(n+1, 0));
    F0R(i, k) {
        ST.apply(tin[i]+1, tout[i], 1);
    } 
    cout << ST.prod(1, n) << " ";
    FOR(i, k, n-1) {
        ST.apply(tin[i-k]+1, tout[i-k], -1);
        ST.apply(tin[i-k]+1, tin[i-k]+1, -mod);
        ST.apply(tin[i]+1, tout[i], 1);
        cout << ST.prod(1, n) << " ";
    }
    cout << "\n";
    return 0;
}   
