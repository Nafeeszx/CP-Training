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

bool in (pair<int, int> a, pair<int, int> b) {
    if(a.f <= b.f && b.s <= a.s) return true;
    return false;
}

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    priority_queue<pair<int, int>> ls, rs;
    vector<int> taken(n);
    F0R(i, n) {
        cin >> a[i].f >> a[i].s;
        ls.push({a[i].f, i});
        rs.push({-a[i].s, i});
    }
    vector<char> ans(n, 'N');
    while(ls.top().f  >= -rs.top().f) {
        taken[ls.top().s] = 1;
        taken[rs.top().s] = 1;
        ls.pop();
        rs.pop();
    }
    vector<pair<pair<int, int>, int>> pp;
    F0R(i, n) {
        if(taken[i]) continue;
        pp.push_back({a[i], i});
    }
    sort(all(pp));
    stack<pair<pair<int, int>, int>> st;
    trav(u, pp) {
        if(!st.empty()) {
            auto x = st.top();
            if(in(x.f, u.f)) {
                ans[x.s] = 'T';
                st.pop();
                continue;
            }
            if(in(u.f, x.f)) {
                ans[u.s] = 'T';
                st.pop();
                continue;
            }
        }
        st.push(u);
    }
    char now = 'N';
    while(!st.empty()) {
        auto x = st.top();
        st.pop();
        ans[x.s] = now;
        if(now=='N') now='T';
        else if(now=='T') now='N';
    }
    trav(u, ans) cout << u;
    cout << "\n";
}

int main() {    
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}


