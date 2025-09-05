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

const int N = 1501;


int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,k; cin >> n >> k;
    k++;
    vector<bitset<N>> v(n), build(n);
    vector<int> base(k, -1);
    string res(n, '0');
    int ans = 0;
    F0R(i, n) {
        build[i][i] = 1;
        string s; cin >> s;
        if(ans) continue;
        s += '1';
        F0R(j, k) v[i][j] = (s[j]=='1');
        F0R(j, k) {
            if(!v[i][j]) continue;
            if(base[j]!=-1) {
                v[i] ^= v[base[j]];
                build[i] ^= build[base[j]];
            }
        }
        if(v[i].count()==0) {
            int gg = build[i].count();
            // cout << gg << "\n";
            for(int x = 0, y = 0; x < n; x++) {
                if(build[i][x]) {
                    if(y < gg/2) res[x] = '1';
                    else res[x] = '2';
                    y++; 
                }
            } 
            ans = 1;
            continue;
        }
        int cur_base;
        F0R(j, k) if(v[i][j]) {
            cur_base = j;
            break;
        }
        base[cur_base] = i;
    }
    if(ans) {
        cout << res << "\n";
    }
    else {
        cout << "*\n";
    }
    return 0;
}   
