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

const int MAXN = (int)6e5 + 5;
ll par[MAXN], W[MAXN], sz[MAXN], lf[MAXN];
ll ans[MAXN];
vector<int> adj[MAXN];

int xx;

int getPar(int x) {
  if (x == par[x]) {
    return x;
  }
  
  return par[x] = getPar(par[x]);
}

void uni(int a, int b, int w) {
    a = getPar(a);
    b = getPar(b);
    
    if (a == b) {
        return;
    }
    
    ++xx;
    W[xx] = w;
    par[xx] = xx;
    par[a] = xx;
    par[b] = xx;
    adj[xx].push_back(a);
    adj[xx].push_back(b);
}

void subt(int u) {
    if(lf[u]) sz[u]++;
    trav(v, adj[u]) {
        subt(v);
        sz[u] += sz[v];
    }
}

void dfs(int u, int p=-1) {
    if(p != -1) {
        ans[u] = ans[p] + W[p] * (sz[p]-sz[u]);
    }
    trav(v, adj[u]) dfs(v, u);
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    xx = n-1;
    vector<int> w(n);
    F0R(i, n) {
        cin >> w[i];
        lf[i] = 1;
    }
    vector<tuple<int, int, int>> ed;
    F0R(i, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        if(u < v) swap(u, v);
        ed.emplace_back(max(w[u], w[v]), u, v);
    }
    sort(all(ed));
    F0R(i, 2*n) par[i]=i;
    trav(uu, ed) {
        auto [w, u, v] = uu;
        uni(u, v, w);
    }
    subt(xx);
    dfs(xx);
    F0R(i, n) cout << ans[i]+w[i] << " ";
    return 0;
}   
