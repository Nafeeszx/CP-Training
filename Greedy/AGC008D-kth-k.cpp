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

const int N = 505;
int pos[N][N];

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    set<int> ss;
    F0R(i, n) {
        cin >> a[i].f;
        a[i].f--;
        a[i].s = i;
        ss.insert(a[i].f);
        pos[i][i] = a[i].f;
    }
    sort(all(a));
    bool ok = true;

    int pp = 0;
    F0R(i, n) {
        F0R(j, a[i].s) {
            while(pp < a[i].f && ss.count(pp)) {
                pp++;
            }
            if(pp >= a[i].f) {
                ok = false;
                break;
            } 
            pos[a[i].s][j] = pp++;
        }
        if(!ok) break;
    }
    // F0R(i, n) {
    //     F0R(j, i) {
    //         cout << pos[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    if(!ok) {
        cout << "No\n";
        return 0;
    }
    F0R(i, n) {
        FOR(j, a[i].s+1, n-1) {
            while(pp < n*n && (ss.count(pp) || pp <= a[i].f)) {
                pp++;
            }
            if(pp >= n*n) {
                ok = false;
                break;
            } 
            pos[a[i].s][j] = pp++;
        }
        if(!ok) break;
    }
    if(!ok) {
        cout << "No\n";
        return 0;
    }
    vector<int> res(n*n);
    F0R(i, n) {
        F0R(j, n) {
            res[pos[i][j]] = i+1;
        }
    }
    cout << "Yes\n";
    trav(u, res) cout << u << " ";
    cout << "\n";
    return 0;
}   
