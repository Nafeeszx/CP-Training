#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for (auto &a : x)
#define FOR(i, a, b) for (int i = (a); i <= (signed)(b); i++)
#define ROF(i, a, b) for (int i = (a); i >= (signed)(b); i--)
#define F0R(i, a) for (int i = 0; i < (signed)(a); i++)
#define vi vector<int>
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

const ll inf = 1e18;

const int N = 105;

int gauss(vector<bitset<N>> a, int n,
          int m)
{
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n;
         ++col)
    {
        for (int i = row; i < n; ++i)
            if (a[i][col])
            {
                swap(a[i], a[row]);
                break;
            }
        if (!a[row][col])
            continue;
        where[col] = row;
        for (int i = 0; i < n; ++i)
            if (i != row && a[i][col])
                a[i] ^= a[row];
        ++row;
    }
    int ok = 1;
    F0R(i, n) {
        if(a[i].count()==1 && a[i][n]==1) ok = 0;
    }
    return ok;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> deg(n);
    vector<vector<int>> adj(n);
    F0R(i, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        deg[u]++;
        deg[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bitset<N>> a;
    F0R(i, n) {
        bitset<N> pp;
        if(deg[i] % 2 ==0) {
            trav(x, adj[i]) {
                pp[x] = 1;
            }
            pp[n] = 1;
        }
        else {
            trav(x, adj[i]) {
                pp[x] = 1;
            }
            pp[i] = 1;
        }
        a.push_back(pp);
    }
    int c = gauss(a, n, n);
    if(c) {
        cout << "Y\n";
    }
    else {
        cout << "N\n";
    }
    return 0;
}
