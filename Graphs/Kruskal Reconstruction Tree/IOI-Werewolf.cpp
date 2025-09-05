#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define ii pair<int, int>
#define sz(v) (int)v.size()
#define all(v) v.begin(), v.end()
using namespace std;

const int N = 2e5+5, L = 20, mod = 1e9+7, inf = 1e18;

int n, m, q, timer;
vector<int> adj[2*N][2];
int val[2*N][2], up[2*N][L][2], in[2*N][2], out[2*N][2];

struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const {
        return w<o.w;
    }
};
vector<Edge> ed[2];

struct DSU {
    int timer; bool id;
    vector<int> par;
    void init(bool id_) {
        par.resize(n+m+5, 0);
        for (int i=0; i<n; i++) par[i] = i;
        id = id_;
        timer = n;
    }
    int find(int u) {
        if (par[u]==u) return u;
        return par[u] = find(par[u]);
    }
    void unite(int u, int v, int w) {
        u = find(u); v = find(v);
        if (u==v) return;
        par[timer] = timer;
        par[u] = timer; par[v] = timer;
        adj[timer][id].pb(u);
        if (u!=v) adj[timer][id].pb(v);
        val[timer][id] = w;
        timer++;
    }
} DSU[2];

void dfs(int u, int p, int id) {
    in[u][id] = ++timer;
    up[u][0][id] = p;
    for (int i=1; i<L; i++) {
        if (up[u][i-1][id]==-1) up[u][i][id] = -1;
        else up[u][i][id] = up[up[u][i-1][id]][i-1][id];
    }
    for (int v: adj[u][id]) {
        if (v!=p) dfs(v, u, id);
    }
    out[u][id] = timer;
}

struct Query {
    int x, l, r, typ, id;
    bool operator<(const Query& o) const {
        if (x==o.x) return typ<o.typ;
        return x<o.x;
    }
};

int find_(int u, int x, bool id) {
    for (int i=L-1; i>=0; i--) {
        if (!id) {
            if (up[u][i][id]!=-1 && val[up[u][i][id]][id]<=x) u = up[u][i][id];
        } else {
            if (up[u][i][id]!=-1 && val[up[u][i][id]][id]>=x) u = up[u][i][id];
        }
    }
    return u;
}

int bit[2*N];

void upd(int p, int x) {
    for (int i=p; i<2*N; i+=(i&-i)) {
        bit[i] += x;
    }
}

int get(int p) {
    int res = 0;
    for (int i=p; i; i-=(i&-i)) {
        res += bit[i];
    }
    return res;
}

int qry(int l, int r) {
    return get(r)-get(l-1);
}

vector<int> check_validity(int n_, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
    n = n_; m = sz(X); q = sz(S);
    for (int i=0; i<m; i++) {
        ed[0].pb({X[i], Y[i], max(X[i], Y[i])});
        ed[1].pb({X[i], Y[i], min(X[i], Y[i])});
    }
    sort(all(ed[0])); sort(all(ed[1])); reverse(all(ed[1]));
    for (int i=0; i<2; i++) {
        DSU[i].init(i);
        for (auto [u, v, w]: ed[i]) DSU[i].unite(u, v, w);
        timer = 0;
        dfs(DSU[i].timer-1, -1, i);
    }
    vector<Query> qs;
    for (int i=0; i<q; i++) {
        int s_rt = find_(S[i], L[i], 1), e_rt = find_(E[i], R[i], 0);
        qs.pb({in[e_rt][0], in[s_rt][1], out[s_rt][1], 0, i});
        qs.pb({out[e_rt][0], in[s_rt][1], out[s_rt][1], 2, i});
    }
    for (int i=0; i<n; i++) qs.pb({in[i][0], in[i][1], in[i][1], 1, -1});
    sort(all(qs));
    vector<int> res(q, 0);
    for (auto [x, l, r, typ, id]: qs) {
        if (typ==0) res[id] -= qry(l, r);
        else if (typ==2) res[id] += qry(l, r);
        else upd(l, 1);
    }
    for (int i=0; i<q; i++) {
        if (res[i]) res[i] = 1;
    }
    return res;
}
