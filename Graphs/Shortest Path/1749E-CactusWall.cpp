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

int dx[] = {0, 1, 0, -1, 1, -1, -1, 1};
int dy[] = {1, 0, -1, 0, -1, -1, 1, 1};

void solve() {
    int n, m; cin >> n >> m;
    vector<string> s(n);
    F0R(i, n) cin >> s[i];
    vector<vector<int>> dist(n, vector<int>(m, mod));
    vector<vector<pair<int, int>>> par(n, vector<pair<int, int>>(m, {-1, -1}));
    deque<pair<int, pair<int, int>>> dq;
    auto can_be = [&] (int x, int y) -> bool {
        F0R(i, 4) {
            int nx = x+dx[i], ny=y+dy[i];
            if(0 > nx || nx >= n || 0 > ny || ny >= m) continue;
            if(s[nx][ny]=='#') {
                return false;
            }
        }
        return true;
    };
    F0R(i, n) {
        if(s[i][0]=='#') {
            dq.push_front({0, {i, 0}});
            dist[i][0] = 0;
        }
        else if(can_be(i, 0)) {
            dq.push_back({1, {i, 0}});
            dist[i][0] = 1;
        }
    }
    // cout << dq.size() << "\n";
    while(!dq.empty()) {
        auto [cur, pp] = dq.front();
        auto [x, y] = pp;
        // cout << x << " " << y << "\n";
        dq.pop_front();
        if(dist[x][y]!=cur) continue;
        FOR(i, 4, 7) {
            int nx = x+dx[i], ny=y+dy[i];
            if(0 > nx || nx >= n || 0 > ny || ny >= m) continue;
            if(!can_be(nx, ny)) continue;
            int val = s[nx][ny]!='#';
            if(dist[nx][ny] > dist[x][y]+val) {
                dist[nx][ny] = dist[x][y]+val;
                par[nx][ny] = {x, y};
                if(val==0) dq.push_front({dist[nx][ny], {nx, ny}});
                else dq.push_back({dist[nx][ny], {nx, ny}});
            }
        }
    }
    int ans = mod;
    pair<int, int> cur;
    F0R(i, n) if(dist[i][m-1] < ans) {
        ans = dist[i][m-1];
        cur = {i, m-1};
    }
    // cout << ans << "\n";
    if(ans==mod) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    auto dfs = [&] (auto dfs, pair<int, int> u) -> void {
        s[u.f][u.s] = '#';
        if(par[u.f][u.s].f != -1) dfs(dfs, par[u.f][u.s]);
    };
    dfs(dfs, cur);
    trav(u, s) {
        cout << u << "\n";
    }
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}   
