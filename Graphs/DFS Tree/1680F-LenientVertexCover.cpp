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

void solve()
{
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    vector<pair<int, int>> ed;
    F0R(i, m) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        ed.emplace_back(u, v);
    }
    vector<int> col(n), bad_ed(m), h(n), vis(n), used(m);
    auto dfs = [&] (auto dfs, int u, int cl=0, int ban_active = -1) -> void {
        col[u] = cl;
        vis[u] = 1;
        trav(v, adj[u]) if(!vis[v.f]) {
            if(ban_active != -1 && v.s==ban_active) continue;
            // cerr << v.s << " ";
            h[v.f] = h[u]+1;
            used[v.s] = 1;
            dfs(dfs, v.f, cl^1, ban_active);
            
        }
    };
    dfs(dfs, 0);
    // cerr << "\n";
    int cnt = 0;
    F0R(i, m) {
        auto [u, v] = ed[i];
        if(col[u] == col[v]) bad_ed[i] = 1, cnt++;
    }
    if(cnt==0) {
        string res;
        F0R(i, n) {
            if(col[i]) res += '1';
            else res += '0';
        }
        cout << "YES\n";
        cout << res << "\n";
        return;
    }
    if(cnt==1) {
        int mustcol;
        string res;
        F0R(i, m) if(bad_ed[i]) {
            mustcol = col[ed[i].f];
            break;
        }
        F0R(i, n) {
            if(col[i]==mustcol) res += '1';
            else res += '0';
        }
        cout << "YES\n";
        cout << res << "\n";
        return;
    }
    vector<int> subt(n), goodt(n);
    // F0R(i, n) cerr << h[i] << " ";
    F0R(i, m) if(!used[i]) {
        if(bad_ed[i]) {
            auto [u, v] = ed[i];
            // cerr << u << " " << v << " asd\n";
            if(h[v] > h[u]) {
                subt[v]++;
                subt[u]--;
            }
            else {
                subt[v]--;
                subt[u]++;
            }
        } else {
            auto [u, v] = ed[i];
            // cerr << u << " " << v << " ads\n";
            if(h[v] > h[u]) {
                goodt[v]++;
                goodt[u]--;
            }
            else {
                goodt[v]--;
                goodt[u]++;
            }
        }
    }
    // cerr << "jk " << cnt << "\n";;
    vis = vector<int>(n);
    int go = 0;
    string res;
    int banned = 0, nnode;
    auto dfs1 =[&] (auto dfs1, int u)-> void {
        vis[u]=1;
        trav(v, adj[u]) if(!vis[v.f]) {
            dfs1(dfs1, v.f);
            goodt[u] += goodt[v.f];
            subt[u] += subt[v.f];
            if(subt[v.f]==cnt && goodt[v.f]==0) {
                go = 1;
                banned = v.s;
                nnode = u;
            } 
        }
        // cerr << u << ": " << subt[u] << " " << goodt[u] << "\n";
    };
    dfs1(dfs1, 0);
    if(!go) {
        cout << "NO\n";
        return;
    }
    vis=vector<int>(n);
    // cerr << banned << "\n";
    dfs(dfs,0,0,banned);
    // cerr << "\n";
    F0R(i, n) {
        if(col[i]==col[nnode]) res += '1';
        else res += '0';
    }
    cout << "YES\n";
    cout << res << "\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();    
    return 0;
}   
