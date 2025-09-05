// ~~ icebear love attttt ~~
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

template<class T>
    bool minimize(T &a, const T &b) {
        if (a > b) return a = b, true;
        return false;
    }

template<class T>
    bool maximize(T &a, const T &b) {
        if (a < b) return a = b, true;
        return false;
    }

#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define FORR(i,a,b) for(int i=(a); i>=(b); --i)
#define REP(i, n) for(int i=0; i<(n); ++i)
#define RED(i, n) for(int i=(n)-1; i>=0; --i)
#define MASK(i) (1LL << (i))
#define BIT(S, i) (((S) >> (i)) & 1)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define task "icebearat"

const int MOD = 1e9 + 7;
const int inf = 1e9 + 27092008;
const ll INF = 1e18 + 27092008;
const int N = 2e5 + 5;
struct Event {
    Event(int _day = 0, int _L = 0, int _R = 0):
        day(_day), L(_L), R(_R) {}
    int day, L, R;
};

struct Edge {
    int u, v, w;
    bool operator < (const Edge &other) const {
        return w < other.w;
    }
} E[N];

vector<int> G[N];
struct DSU_tree {
    int node;
    int par[N], weight[N];

    DSU_tree(int n = 0): node(n) {
        FOR(i, 1, n) par[i] = i, weight[i] = 0;
    }

    int root(int v) {
        return (par[v] == v ? v : par[v] = root(par[v]));
    }

    void unite(int u, int v, int w) {
        u = root(u);
        v = root(v);
        if (u == v) return;
        node++;
        par[u] = par[v] = par[node] = node;
        G[node].pb(u);
        G[node].pb(v);
        weight[node] = w;
    }
} dsu_tree;

int numNode, numQuery, restTime;
int par[20][N], timeIn[N], timeOut[N], eulerTour[N], timerEuler = 0;

class SegmentTree {
private:
    int sizeTree;
    struct Node {
        int minValue, freqMin, lazyValue;
        Node (int _min = 0, int _freq = 0, int _lazy = 0):
            minValue(_min), freqMin(_freq), lazyValue(_lazy) {}
        friend Node combine(const Node &L, const Node &R) {
            Node res;
            res = L;
            if (res.minValue > R.minValue) res = R;
            else if (res.minValue == R.minValue)  res.freqMin += R.freqMin;
            res.lazyValue = 0;
            return res;
        }
    };
    vector<Node> nodes;

    void pushDown(int id) {
        if (nodes[id].lazyValue) {
            nodes[id << 1].minValue += nodes[id].lazyValue;
            nodes[id << 1 | 1].minValue += nodes[id].lazyValue;
            nodes[id << 1].lazyValue += nodes[id].lazyValue;
            nodes[id << 1 | 1].lazyValue += nodes[id].lazyValue;
            nodes[id].lazyValue = 0;
        }
    }

    void update(int id, int l, int r, int u, int v, int k) {
        if (l > v || r < u) return;
        if (u <= l && r <= v) {
            nodes[id].minValue += k;
            nodes[id].lazyValue += k;
            return;
        }
        pushDown(id);
        int mid = (l + r) >> 1;
        update(id << 1, l, mid, u, v, k);
        update(id << 1 | 1, mid + 1, r, u, v, k);
        nodes[id] = combine(nodes[id << 1], nodes[id << 1 | 1]);
    }

    Node get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return Node(inf, 0, 0);
        if (u <= l && r <= v) return nodes[id];
        pushDown(id);
        int mid = (l + r) >> 1;
        Node L = get(id << 1, l, mid, u, v);
        Node R = get(id << 1 | 1, mid + 1, r, u, v);
        return combine(L, R);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            nodes[id] = Node((eulerTour[l] <= numNode ? 0 : inf), 1, 0);
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        nodes[id] = combine(nodes[id << 1], nodes[id << 1 | 1]);
    }

public:
    SegmentTree(int n = 0): sizeTree(n), nodes(4 * n + 5) {}

    void init() {
        build(1, 1, sizeTree);
    }

    void update(int u, int v, int k) {
        update(1, 1, sizeTree, u, v, k);
    }

    int getZeros(int u, int v) {
        Node res = get(1, 1, sizeTree, u, v);
        return (res.minValue == 0 ? res.freqMin : 0);
    }
} IT;

void dfs(int u) {
    timeIn[u] = ++timerEuler;
    eulerTour[timerEuler] = u;
    for(int v : G[u]) if (v != par[0][u]) {
        par[0][v] = u;
        dfs(v);
    }
    timeOut[u] = timerEuler;
}

int findRoot(int u, int k) { // root R contains u and weight <= k
    RED(j, 20) if (dsu_tree.weight[par[j][u]] <= k)
        u = par[j][u];
    return u;
}

void build_DSUtree() {
    dsu_tree = DSU_tree(numNode);
    sort(E + 1, E + numNode);
    FOR(i, 1, numNode - 1) dsu_tree.unite(E[i].u, E[i].v, E[i].w);

    timerEuler = par[0][dsu_tree.node] = 0;
    dfs(dsu_tree.node);
    IT = SegmentTree(dsu_tree.node);
    IT.init();

    FOR(j, 1, 19) FOR(i, 1, dsu_tree.node)
        par[j][i] = par[j - 1][par[j - 1][i]];
    dsu_tree.weight[0] = inf;
}

void init(void) {
    cin >> numNode;
    FOR(i, 1, 2 * numNode) G[i].clear();
    FOR(i, 1, numNode - 1) cin >> E[i].u >> E[i].v >> E[i].w;
}

void process(void) {
    build_DSUtree();
    cin >> numQuery >> restTime;
    queue<Event> events;
    int day, node, limit;
    while(numQuery--) {
        cin >> day >> node >> limit;
        while(!events.empty() && events.front().day <= day) {
            auto curEvent = events.front();
            events.pop();
            IT.update(curEvent.L, curEvent.R, -1);
        }

        int root = findRoot(node, limit);
        cout << IT.getZeros(timeIn[root], timeOut[root]) << '\n';
        IT.update(timeIn[root], timeOut[root], +1);

        events.push(Event(day + restTime, timeIn[root], timeOut[root]));
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    int tc = 1;
    cin >> tc;
    while(tc--) {
        init();
        process();
    }
    return 0;
}
