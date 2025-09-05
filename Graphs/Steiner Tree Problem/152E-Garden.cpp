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


template<class T1, class T2> bool cmin(T1 &x, const T2 &y) { if (y < x) { x = y; return 1; } return 0; }

const int inf = 1e9;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, k; cin >> N >> M >> k;
    vector<vector<int>> a(N, vector<int>(M));
    F0R(i, N) F0R(j, M) cin >> a[i][j];
    int n = N*M;
    vector<int> id;
    F0R(i, k) {
        int u, v; cin >> u >> v; u--; v--;
        id.emplace_back(u*M+v);
    } 

    using pa = pair<int, int>;
    int m = id.size(), i;
    vector f(1 << m, vector<int>(n, inf));
    vector pre(1 << m, vector(n, pair{-1, -1}));
    for (i = 0; i < m; i++) f[1 << i][id[i]] = a[id[i]/M][id[i]%M];
    i = 0;
    for (int S = 1; S < 1 << m; S++)
    {
        auto &d = f[S];
        priority_queue<pa, vector<pa>, greater<pa>> q;
        for (i = 0; i < n; i++)
        {
            for (int T = S - 1 & S; T; T = T - 1 & S)
                if (cmin(d[i], f[T][i] + f[S ^ T][i] - a[i/M][i%M]))
                    pre[S][i] = {-2, T};

            if (d[i] != inf) q.push({d[i], i});
        }
        while (q.size())
        {
            auto [_, u] = q.top(); q.pop();
            if (_ != d[u]) continue;
            F0R(k, 4) {
                int xx = u/M+dx[k], yy=u%M+dy[k];
                if(xx < 0 || xx >= N || yy < 0 || yy >= M) continue;
                int v = xx*M+yy;
                if (cmin(d[v], d[u] + a[xx][yy])) {
                    q.push({d[v], v});
                    pre[S][v] = {u, -10};
                }
            }
        }
    }
    vector<int> chosen;
    int S = (1 << m) - 1, u = min_element(all(f[S])) - f[S].begin();
    auto dfs = [&](auto &&dfs, int S, int u) {
        auto [x, y] = pre[S][u];
        while (x >= 0)
        {
            u = x;
            chosen.push_back(u);
            tie(x, y) = pre[S][u];
        }
        if (x == -1) return;
        dfs(dfs, y, u); dfs(dfs, S ^ y, u);
    };
    chosen.push_back(u);
    dfs(dfs, S, u);
    cout << f[S][u] << "\n";
    vector<vector<char>> ans(N, vector<char>(M, '.'));
    trav(u, chosen) {
        int xx = u/M, yy = u%M;
        ans[xx][yy] = 'X';
    }
    trav(u, ans) {
        trav(v, u) cout << v;
        cout << "\n";
    }

    
    return 0;
}   
