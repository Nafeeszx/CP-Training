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

const ll mod = 1e9 + 7, B = 1000033;

struct Trie {
    
    struct Node {
        array<int, 26> ch;
        int cnt;
        Node() {ch.fill(-1),cnt = 0;}
    };
    
    vector<Node> trie;
    int root;
    
    void init() {
        root = new_node();
    }
    
    int new_node() {
        trie.emplace_back();
        return trie.size() - 1;
    }
    
    void insert(const string &s) {
        int now = root;
        for (char c : s) {
            if (trie[now].ch[c-'a']==-1) trie[now].ch[c-'a'] = new_node();
            now = trie[now].ch[c-'a'];
        }
        ++trie[now].cnt;
    }
    
};

void solve()
{
    int n, m; string s; cin >> n >> m >> s;
    vector<ll> ts;
    Trie T;
    T.init();
    F0R(i, m) {
        string x; cin >> x;
        reverse(all(x));
        T.insert(x);
    }
    sort(all(ts));
    ts.erase(unique(all(ts)), ts.end());
    vector<int> ans(n+1);
    F0R(i, n) {
        int curr = T.root;
        ROF(j, i, 0) {
            int nxt = T.trie[curr].ch[s[j]-'a'];
            if(nxt==-1) break;
            if(T.trie[nxt].cnt) {
                ans[i+1] = max(ans[i+1], ans[j]+1);
            }
            curr = nxt;
        }
        ans[i+1] = max(ans[i], ans[i+1]);
    }
    cout << ans[n] << "\n";
}

int main() 
{	
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}   
