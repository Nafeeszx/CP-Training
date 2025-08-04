#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for(auto& a : x)
#define FOR(i, a, b) for (int i=(a); i<=(signed)(b); i++)
#define ROF(i, a, b) for (int i=(a); i>=(signed)(b); i--)
#define F0R(i, a) for (int i=0; i<(signed)(a); i++)
#define vi vector<int>
#define pb push_back
#define rsz(x) resize(x)
#define sz(x) (x).size()
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

const ll mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(NULL); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> stmp(m);
    vector<vector<int>> ts(n);
    F0R(i, m) {
        int t, p; cin >> t >> p;
        p--;
        stmp[i] = {p, t};
        ts[p].push_back(t);
    }
    map<pair<int, int>, int> mp;

    F0R(i, n) if(ts[i].size() > 1000) {
        vector<ll> ans(n);
        ll prev = 0, i_sum = 0;
        bool on = false;
        for(auto [id, time] : stmp) {
            if(id==i) {
                i_sum += (time-prev)*on;
                on=!on;
                prev = time;
            }
            else {
                ans[id] = i_sum + on*(time-prev) - ans[id];
            }
        }
        F0R(u, n) {
            if(u != i) mp[minmax(u, i)] = ans[u];
        }
    }
    auto que = [&] (int a, int b) -> int {
        if(mp.count({a, b})) {
            return mp[{a, b}];
        }
        bool o1 = false, o2 = false;
        int i = 0, j = 0;
        int lst = -1;
        int ans = 0;
        while(i < ts[a].size() && j < ts[b].size()) {
            if(ts[a][i] < ts[b][j]) {
                if(o1&&o2) {
                    ans += ts[a][i]-lst;
                }
                else if(o2 && !o1) {
                    lst = ts[a][i];
                }
                o1 = !o1;
                i++;
            }
            else {
                if(o1&&o2) {
                    ans += ts[b][j]-lst;
                }
                else if(o1 && !o2) {
                    lst = ts[b][j];
                }
                o2 = !o2;
                j++;
            }
        }
        return mp[{a, b}] = ans;
    };

    int q; cin >> q;
    while(q--) {
        int a, b; cin >> a >> b; a--; b--;
        cout << que(a, b) << "\n";
    }
    return 0;
}