#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("shortcut.in", "r", stdin);
	freopen("shortcut.out", "w", stdout);

	int n, m, t;
	cin >> n >> m >> t;

	vector<int> fields(n);
	for (int i = 0; i < n; i++) { cin >> fields[i]; }

	// adj[i] = {travel time, adjacent node}
	vector<vector<pair<int, int>>> adj(n);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;

		adj[--u].push_back({c, --v});
		adj[v].push_back({c, u});
	}

	vector<int> cost(n, INT32_MAX);

	// prev stores parents for backtracking
	vector<int> prev(n, INT32_MAX);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	cost[0] = 0;

	// travel time, current node
	pq.push({0, 0});
	while (pq.size()) {
		pair<int, int> nxt = pq.top();
		pq.pop();

		int cur_cost = nxt.first;
		int cur_node = nxt.second;

		if (cur_cost != cost[cur_node]) { continue; }

		for (const pair<int, int> &u : adj[cur_node]) {
			// if this path is more optimal
			if (u.first + cur_cost < cost[u.second]) {
				cost[u.second] = u.first + cur_cost;
				pq.push({u.first + cur_cost, u.second});
				prev[u.second] = cur_node;
				/*
				 * keep paths lexicographically minimum by
				 * always choosing the lesser-indexed node
				 */
			} else if (u.first + cur_cost == cost[u.second] &&
			           cur_node < prev[u.second]) {
				prev[u.second] = cur_node;
				pq.push({u.first + cur_cost, u.second});
			}
		}
	}

	vector<long long> occ(n);
	// backtrack
	for (int i = 0; i < n; i++) {
		int cur = i;
		while (cur != INT32_MAX) {
			occ[cur] += fields[i];
			cur = prev[cur];
		}
	}

	long long ans = 0;
	for (int i = 0; i < n; i++) { ans = max(ans, (long long)(occ[i] * (cost[i] - t))); }
	cout << ans << '\n';
}