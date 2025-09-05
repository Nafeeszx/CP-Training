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
template<class T1, class T2> bool cmin(T1 &x, const T2 &y) { if (y < x) { x = y; return 1; } return 0; }

const ll mod = 1e9 + 7, inf = 1e18;

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        string s, t; cin >> s >> t;
        vector<int> pref(m), suf(m+1); 
        {
            int j = n-1, ok = 1;
            suf[m] = n;
            ROF(i, m-1, 0) {
                while(j >= 0 && t[i]!=s[j]) j--;
                if(j < 0) {
                    ok = 0;
                    break;
                }
                suf[i] = j--;
            }
            if(!ok) {
                cout << -1 << "\n";
                continue;
            }
        }
        {   
            int j = 0;
            F0R(i, m-1) {
                while(t[i] != s[j]) j++;
                pref[i+1] = ++j;
            }
        }
        vector<vector<int>> lcp(n+1, vector<int>(m+1));
        ROF(j, n-1, 0) ROF(i, m-1, 0) {
            lcp[j][i] = (s[j]==t[i] ? 1+lcp[j+1][i+1] : 0);
        }

        int ans = 1e9; // first it holds cursor move (home too if j > 0)
        F0R(i, m) {
            FOR(j, pref[i], n-1) {
                int len = lcp[j][i];
                if(suf[i+len] >= j+len) { // was it possible to get the last m-i-len characters by pressing right?
                    ans = min(ans, (j>0)+j+(m-i-len));
                }
            }
        }
        ans+=n-m; // number of deletion added
        cout << ans << "\n";
    }
    return 0;
}   
