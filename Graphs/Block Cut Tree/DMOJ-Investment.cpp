#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
#include <numeric>

// Using common types and macros inferred from the code style
using namespace std;
using ll = long long;

// Global Variables (from image 1: image_87865f.jpg)
const int N_MAX = 500100;
vector<int> adj1[N_MAX], adj2[N_MAX];
int vis[N_MAX], CC, limit, id[N_MAX], dep[N_MAX], in[N_MAX], low[N_MAX], par[N_MAX], sz[N_MAX], C2, w[N_MAX];
set<pair<int, int>> st[N_MAX];
ll dp[22][N_MAX][2]; // Assuming K is at most 21
const ll BG = 1e18; // A large number representing -infinity

struct DSU {
    int par[N_MAX];
    int abp(int n) {
        return par[n] == n ? n : par[n] = abp(par[n]);
    }
    void init() {
        iota(par, par + N_MAX, 0);
    }
    void merge(int a, int b) {
        par[abp(a)] = abp(b);
    }
} cycles;

// DFS for Bridge-Finding (from image 1: image_87865f.jpg)
void dfs1(int n, int p) {
    low[n] = id[n] = ++C2;
    for (auto i : adj1[n]) {
        if (i == p) continue;
        if (!id[i]) {
            dep[i] = dep[n] + 1;
            dfs1(i, n);
            low[n] = min(low[n], low[i]);
            if (low[i] > id[n]) {
                adj2[n].push_back(++CC);
                adj2[CC].push_back(i);
            }
        } else if (dep[i] < dep[n]) {
            st[n].insert({dep[i], ++CC});
            low[n] = min(low[n], low[i]);
        }
    }
}

// Helper DFS functions for tree construction (from image 2: image_878a01.png)
void dfsC(int n) {
    for (auto i : adj1[n]) {
        if (dep[i] - dep[n] - 1) continue;
        dfsC(i);
        if (st[i].size() && st[i].begin()->first < dep[n]) {
            if (st[n].size()) cycles.merge(st[i].begin()->second, st[n].begin()->second);
            st[n].insert(*st[i].begin());
        }
    }
    if (st[n].size()) {
        in[n] = st[n].begin()->second;
    }
}

void dfs2(int n, int p) {
    for (auto i : adj1[n]) {
        if (dep[i] == dep[n] + 1) {
            dfs2(i, n);
        }
    }
    adj2[cycles.abp(in[n])].push_back(n);
    par[cycles.abp(in[n])] = p;
}

// Tree Dynamic Programming (from image 3: image_878a84.jpg)
void dfs3(int n) {
    for (int i = 0; i < 22; ++i) {
        dp[i][n][0] = dp[i][n][1] = -BG;
    }

    if (n <= limit) { // Node n is an original planet (leaf in component tree)
        dp[0][n][0] = 0;
        dp[1][n][1] = w[n];
    } else { // Node n is a component
        dp[0][n][0] = 0;
        dp[1][n][1] = 0; // Profit comes from vertices, not components themselves
    }

    for (auto x : adj2[n]) {
        dfs3(x);
        for (int i = 21; i >= 0; --i) {
             // Temporary arrays for knapsack logic
            ll bruh1 = dp[i][n][1];
            ll bruh2 = dp[i][n][0];
            for (int j = 0; j <= i; ++j) {
                if (x <= limit) { // If child is a planet
                    if (dp[j][n][0] != -BG && max(dp[i - j][x][0], dp[i - j][x][1]) != -BG)
                        bruh2 = max(bruh2, dp[j][n][0] + max(dp[i - j][x][0], dp[i - j][x][1]));
                    if (dp[j][n][1] != -BG && max(dp[i - j][x][0], dp[i - j][x][1]) != -BG)
                        bruh1 = max(bruh1, dp[j][n][1] + max(dp[i - j][x][0], dp[i - j][x][1]));
                } else { // If child is a component
                    if (dp[j][n][0] != -BG && dp[i-j][x][0] != -BG)
                        bruh2 = max(bruh2, dp[j][n][0] + dp[i-j][x][0]);
                    
                    ll term1 = -BG, term2 = -BG;
                    if (dp[j][n][1] != -BG && max(dp[i - j][x][0], dp[i - j][x][1]) != -BG)
                        term1 = dp[j][n][1] + max(dp[i - j][x][0], dp[i - j][x][1]);
                    if (dp[j][n][0] != -BG && dp[i-j][x][1] != -BG)
                        term2 = dp[j][n][0] + dp[i-j][x][1];
                    bruh1 = max(bruh1, max(term1, term2));
                }
            }
            dp[i][n][1] = bruh1;
            dp[i][n][0] = bruh2;
        }
    }
}


// Main logic and I/O (from image 4: image_878ade.png)
void solve() {
    int n, m, k, q;
    cin >> n >> m;// >> k >> q;
    while (m--) {
        int a, b;
        cin >> a >> b;
        adj1[a].push_back(b);
        adj1[b].push_back(a);
    }
    // for (int i = 1; i <= n; ++i) {
    //     cin >> w[i];
    // }

    cycles.init();
    CC = limit = n;
    dfs1(1, 0);
    dfsC(1);
    dfs2(1, 0);
    for (int i = n + 1; i <= CC; ++i) {
        if (cycles.par[i] == i) {
            adj2[par[i]].push_back(i);
        }
    }

    for(int i = 1; i <= CC; ++i) {
        cout << i << ":: ";
        for(int x : adj2[i]) {
            cout << x << " ";
        }
        cout << "\n";
    }
    // dfs3(1);
    // ll ans = 0;
    // for (int i = 0; i <= k; ++i) {
    //     ll current_profit = max(dp[i][1][0], dp[i][1][1]);
    //     if (current_profit != -BG) { // Only consider reachable states
    //         ans = max(ans, (ll)(k - i) * q + current_profit);
    //     }
    // }
    // cout << ans << '\n';
}

signed main() {
    // Basic setup for speed, can be customized
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // #ifdef multicase
    //     cin >> t;
    // #endif
    while (t--) {
        solve();
    }
    return 0;
}