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

string team (int x) {
    string res;
    F0R(i, x-1) res += "RL";
    res += 'R';
    return res;
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> c(n+1);
        F0R(i, n+1) cin >> c[i];
        vector<int> ls;
        bool ok = true;
        F0R(i, n) {
            if(c[i] > c[i+1] || c[i]==0) {
                ok = false;
                break;
            }
            ls.push_back(c[i]);
            c[i+1] -= c[i];
        }
        ok &= c[n]==0;
        if(!ok) {cout << "Impossible\n"; continue;}
        
        string res;
        trav(u, ls) res += team(u);
        trav(u, ls) res += 'L';
        cout <<  res << "\n";
    }
    return 0;
}   
