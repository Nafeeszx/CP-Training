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
        int n, k; cin >> n >> k;
        vector<vector<int>> ch;
        int mx = -1, mxcnt = 0, id = -1, mn = mod, mnid = -1;
        F0R(i, k) {
            int l, r; cin >> l >> r;
            if(r-l+1 > mx) {
                mx = r-l+1;
                mxcnt = 1;
                id = i;
            }
            else if(r-l+1==mx) {
                mxcnt++;
            }
            if(r-l+1 < mn) {
                mn = r-l+1;
                mnid = i;
            }
            vector<int> xx;
            FOR(j, l, r) xx.push_back(j);
            ch.push_back(xx);
        }
        if(mxcnt >= 2 && mn > mx-2) {
            cout << "IMPOSSIBLE\n";
        }
        else {
            vector<int> p(n+1);
            F0R(i, k) {
                if(mxcnt >= 2 && i==mnid) {
                    p[ch[i][0]] = ch[id][1];    
                }
                else if(i!=id) {
                    p[ch[i][0]] = ch[id][0];
                }
                F0R(j, ch[i].size()-1) {
                    p[ch[i][j+1]] = ch[i][j];
                }
            }
            FOR(i, 1, n) cout << p[i] << " ";
            cout << "\n";
        }
    }
    return 0;
}