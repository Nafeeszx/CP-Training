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

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<pair<int, int>> x;
        vector<pair<int, int>> p(3*n+1);
        FOR(i, 1, 3*n) {
            int a, b; cin >> a >> b;
            p[i] = {a, b};
            x.push_back({a, -i});
            x.push_back({b, i});
        }
        sort(all(x));
        vector<int> done(3*n+1);
        set<pair<int, int>> st;
        vector<vector<int>> res;
        bool ok = true;
        trav(u, x) {
            auto [cc, id] = u;
            if(id < 0) {
                id = -id;
                st.insert({p[id].s, id});
            }
            else {
                if(done[id]) continue;
                vector<int> y;
                while(y.size() < 3) {
                    if(st.empty()) {
                        ok = false;
                        break;
                    }
                    auto it = st.begin();
                    auto p = (*it).s;
                    st.erase(it);
                    y.push_back(p);
                    done[p] = 1;
                }
                res.push_back(y);

            }
        }
        if(ok) {
            cout << "Yes\n";
            trav(x, res) {
                trav(u, x) cout << u << " ";
                cout << "\n";
            }
        }
        else {
            cout << "No\n";
        }
    }
    return 0;
}