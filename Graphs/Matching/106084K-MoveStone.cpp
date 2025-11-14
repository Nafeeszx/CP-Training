#include<bits/stdc++.h>
using namespace std;
int n, m, i, j, k, a, b, cnt, A[510][510], ans;
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    cin>>n;
    //1, 2, 3~n+2, n+3~2*n+2
    cnt=2*n+2;int CNT=2*n+2;
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)
    {
        cin>>A[i][j];
        if(A[i][j]!=1)CNT++;
    }
    Dinic G=Dinic(CNT+3, 1, 2);
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)
    {
        if(A[i][j]>1)
        {
            cnt++;
            G.add_edge(1, cnt, A[i][j]-1);
            G.add_edge(cnt, i+2, A[i][j]-1);
            G.add_edge(cnt, j+2+n, A[i][j]-1);
        }
    }
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)if(!A[i][j])
    {
        ans+=2;
        cnt++;
        G.add_edge(cnt, 2, 1);
        G.add_edge(i+2, cnt, 1);
        G.add_edge(j+2+n, cnt, 1);
    }
    cout<<ans-G.flow();
}