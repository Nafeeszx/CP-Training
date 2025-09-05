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

struct seg {
    struct Node {
        int val;
        multiset<int> ms;
    };
    int n;
    vector<Node> nodes;
    seg(int _n) {
        n = 1;
        while(n < _n) n <<=1;
        nodes.resize(n<<1);
        F0R(i, n<<1) {nodes[i].ms.insert(0); nodes[i].val=0;}
        // cout << n << "\n";
    }
    void add (int x, int y, int op, int val, int a, int l, int r) {
        if(y <= l || r <= x) return; 
        if(x <= l && r <= y) {
            if(op==0) nodes[a].ms.insert(val);
            else nodes[a].ms.erase(nodes[a].ms.find(val));
            nodes[a].val = *prev(nodes[a].ms.end());
            if(r-l>1) nodes[a].val = max(nodes[a].val, min(nodes[(a<<1)^1].val, nodes[(a<<1)+2].val));
            return;
        }
        int m = (l+r)>>1;
        add(x, y, op, val, (a<<1)^1, l, m);
        add(x, y, op, val, (a<<1)+2, m, r);
        nodes[a].val = *prev(nodes[a].ms.end());
        nodes[a].val = max(nodes[a].val, min(nodes[(a<<1)^1].val, nodes[(a<<1)+2].val));
    }
    void add(int x, int y, int op, int val) {
        add(x, y, op, val, 0, 0, n);
    }
    int query (int x, int y, int parmax, int a, int l, int r) {
        if(y <= l || r <= x) {
            return mod;
        } 
        if(x <= l && r <= y) {
            return max(parmax, nodes[a].val);
        }
        int m = (l+r)>>1;
        parmax = max(parmax, *prev(nodes[a].ms.end()));
        int lres = query(x, y, parmax, (a<<1)^1, l, m);
        int rres = query(x, y, parmax, (a<<1)+2, m, r);
        return min(lres, rres);
    }
    int query(int x, int y) {
        return query(x, y, 0, 0, 0, n);
    }
};

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<vector<int>> qs(n);
    vector<int> coords;
    vector<int> signs;
    F0R(i, n) {
        char x; cin >> x;
        if(x == '+') {
            int l, r, p; cin >> l >> r >> p;
            qs[i]={0, l, r, p};
            coords.push_back(l);
            coords.push_back(r);
            signs.push_back(i);
        }
        else if(x=='-') {
            int u; cin >> u;
            u--;
            qs[i] = qs[signs[u]];
            qs[i][0] = 1;
        }
        else {
            int l, r; cin >> l >> r;
            qs[i] = {2, l, r, -1};
            coords.push_back(l);
            coords.push_back(r);
        }
    }
    sort(all(coords));
    coords.erase(unique(all(coords)), coords.end());
    trav(u, qs) {
        int aa = lower_bound(all(coords), u[1]) - coords.begin();
        u[1] = aa;
        aa = lower_bound(all(coords), u[2]) - coords.begin();
        u[2] = aa;
    }
    seg X(coords.size());
    trav(u, qs) {
        auto &x = u;
        if(x[0]==2) {
            cout << X.query(x[1], x[2]) << "\n";
        }
        else X.add(x[1], x[2], x[0], x[3]);
    }
    return 0;
}   
