#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	int n;
	cin >> n;

	int timer = 0;
	vector<ll> inversions(2 * n - 1);
	map<int, Tree<int>> sets;
	function<void(int)> dfs = [&](int idx) {
		int val;
		cin >> val;

		if (val == 0) {
			int idx_l = ++timer;
			dfs(idx_l);
			int idx_r = ++timer;
			dfs(idx_r);

			if (sets[idx_l].size() > sets[idx_r].size()) {
				sets[idx_l].swap(sets[idx_r]);
			}

			ll way_1 = 0;  // way 1: left set is joined to the right set
			ll way_2 = 0;  // way 2: right set is joined to the left set
			for (int v : sets[idx_l]) {
				int loc = sets[idx_r].order_of_key(v);
				way_1 += loc;
				way_2 += (int)sets[idx_r].size() - loc;
			}

			for (int v : sets[idx_l]) { sets[idx_r].insert(v); }
			sets[idx].swap(sets[idx_r]);
			sets.erase(idx_l);
			sets.erase(idx_r);

			inversions[idx] = inversions[idx_l] + inversions[idx_r] + min(way_1, way_2);
		} else if (val > 0) {
			sets[idx].insert(val);
		}
	};

	dfs(0);

	cout << inversions[0] << endl;
}