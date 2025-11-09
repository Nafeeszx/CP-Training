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

int que(int a, int b) {
    cout << "? " << a << " " << b << endl;
    int x; cin >> x;
    return x;
}

void solve()
{
    int n; cin >> n;
    int p = que(1, n/4), q = que(n/4+1, n/2);
    bool one_pres_in_f = (p!=q);
    int gg = (one_pres_in_f? que(1, n/2) : que(n/2+1, n));
    if(!gg) { // k <= n/2
        if(one_pres_in_f) {
            int l = 0, r = n/2;
            while(r-l>1) {
                int m = (r+l)/2;
                (que(n/2+1, n/2+m) ? r : l) = m;
            }
            cout << "! " << r << endl;
        }
        else {
            int l = 0, r = n/2;
            while(r-l>1) {
                int m = (r+l)/2;
                (que(1, m) ? r : l) = m;
            }
            cout << "! " << r << endl;
        }
    }
    else { // k > n/2
        if(one_pres_in_f) {
            int l = n/2, r = n;
            while(r-l>1) {
                int m = (r+l)/2;
                (que(1, m)==0 ? r:l) = m; 
            }
            cout << "! " << r << endl;
        }
        else {
            
            int l = n/2, r = n;
            while(r-l>1) {
                int m = (r+l)/2;
                (que(n-m+1, n)==0 ? r:l) = m; 
            }
            cout << "! " << r << endl;
        }
    }
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}   
