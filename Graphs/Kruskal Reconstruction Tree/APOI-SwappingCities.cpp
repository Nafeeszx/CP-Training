#include <bits/stdc++.h>
#define FOR(i, a, b) for (auto i = (a); i <= (b); i++)
#define ROF(i, a, b) for (auto i = (a); i >= (b); i--)
using namespace std;
int N, M, lgNM, timer;
vector<int> edge_cnt, node_cnt, l, r, p, w, lvl, deg3;
vector<vector<int>> par, ch;
int find(int x) {return p[x] == x ? x : p[x] = find(p[x]);}
void dfs(int x) {
    (x < N ? node_cnt : edge_cnt)[x]++;
    for (int i = 0; i < lgNM && par[x][i] != -1; i++)
        par[x][i + 1] = par[par[x][i]][i];
    l[x] = timer;
    if (x < N) timer++;
    for (int y : ch[x]) {
        par[y][0] = x;
        lvl[y] = lvl[x] + 1;
        dfs(y);
        deg3[x] |= deg3[y];
        node_cnt[x] += node_cnt[y];
        edge_cnt[x] += edge_cnt[y];
    }
    r[x] = timer;
}
int lca(int x, int y) {
    if (lvl[x] < lvl[y]) swap(x, y);
    FOR(i, 0, lgNM) if ((lvl[x] - lvl[y]) >> i & 1) x = par[x][i];
    if (x == y) return x;
    ROF(i, lgNM, 0) if (par[x][i] != par[y][i]) x = par[x][i], y = par[y][i];
    return par[x][0];
}
void init(int _N, int _M, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
    N = _N, M = _M; lgNM = __lg(N + M);
    l.resize(N + M);
    r.resize(N + M);
    w.resize(N + M);
    p.resize(N + M); iota(p.begin(), p.end(), 0);
    ch.resize(N + M);
    lvl.resize(N + M);
    deg3.resize(N + M);
    edge_cnt.resize(N + M);
    node_cnt.resize(N + M);
    par.resize(N + M, vector<int>(lgNM + 1, -1));
    vector<int> ord(M), deg(N);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {return W[i] < W[j];});
    FOR(oi, 0, M - 1) {
        int i = ord[oi], x = U[i], y = V[i];
        if (++deg[x] >= 3 || ++deg[y] >= 3) deg3[N + oi] = 1;
        x = find(x), y = find(y);
        ch[N + oi].push_back(x);
        if (x != y) ch[N + oi].push_back(y);
        p[x] = p[y] = N + oi, w[N + oi] = W[i];
    }
    dfs(N + M - 1);
}
bool check(int x) {
    return edge_cnt[x] >= node_cnt[x] || deg3[x];
}
int getMinimumFuelCapacity(int X, int Y) {
    if (!check(N + M - 1)) return -1;
    int Z = lca(X, Y);
    if (check(Z)) return w[Z];
    ROF(i, lgNM, 0) if (par[Z][i] != -1 && !check(par[Z][i])) Z = par[Z][i];
    return w[par[Z][0]];
}