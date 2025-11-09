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

template<class T> using V = vector<T>;

const ll mod = 1e9 + 7;

void solve()
{
    int n; cin >> n;
    string s; cin >> s;
    string X;
    trav(u, s) {
        if(X.empty() || X.back()!=u) {
            X += u;
        }    
        else X.pop_back();
    }
    int ll = count(all(X), '('), rr = count(all(X), ')');
    int rem = n-ll-rr;
    if(((rem+rr-ll)%4!=0) || (rem+rr-ll < 0)) {
        cout << -1 << "\n";
        return;
    }
    int x = (rem+rr-ll)>>1;
    string res = string(x, '(');
    res += X;
    res += string(rem-x, ')');
    int pr = 0;
    trav(u, res) {
        if(u=='(') pr++;
        else pr--;
        if(pr < 0) {
            cout << -1 << "\n";
            return;
        }
    }
    cout << res << "\n";
}

int main() {
    int t; cin >> t;
    while(t--) solve();   
    return 0;
}