#include <bits/stdc++.h>
using namespace std;

int travel_plan(int n, int m, int r[][2], int l[], int k, int p[]) {
	vector<vector<array<int, 2>>> adj(n);
	for (int i = 0; i < m; i++) {
		adj[r[i][0]].push_back({r[i][1], l[i]});
		adj[r[i][1]].push_back({r[i][0], l[i]});
	}

	// 1e9 because the answer is guaranteed to be less than that
	const array<int, 2> DEFAULT = {(int)1e9, (int)1e9};
	// dist[i] = {best distance, second best distance}
	vector<array<int, 2>> dist(n, DEFAULT);
	priority_queue<array<int, 2>> pq;
	for (int i = 0; i < k; i++) {
		pq.push({0, p[i]});
		dist[p[i]] = {0, 0};
	}

	while (!pq.empty()) {
		auto [time, at] = pq.top();
		pq.pop();
		time *= -1;  // undoing the negative number trick
		if (dist[at][1] < time) { continue; }
		for (const auto [nxt, weight] : adj[at]) {
			if (time + weight < dist[nxt][0]) {
				if (dist[nxt][0] < dist[nxt][1]) { pq.push({-dist[nxt][0], nxt}); }
				dist[nxt][1] = dist[nxt][0];
				dist[nxt][0] = time + weight;
			} else if (time + weight < dist[nxt][1]) {
				dist[nxt][1] = time + weight;
				pq.push({-dist[nxt][1], nxt});
			}
		}
	}

	return dist[0][1];
}