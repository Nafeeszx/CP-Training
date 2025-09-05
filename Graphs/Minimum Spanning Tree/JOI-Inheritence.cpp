#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// BeginCodeSnip{DSU}
class DisjointSets {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
	DisjointSets(int size) : parents(size), sizes(size, 1) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	int get_ultimate(int n) {
		return parents[n] == n ? n : (parents[n] = get_ultimate(parents[n]));
	}

	int same_set(int n1, int n2) { return get_ultimate(n1) == get_ultimate(n2); }

	bool link(int n1, int n2) {
		n1 = get_ultimate(n1);
		n2 = get_ultimate(n2);
		if (n1 == n2) { return false; }
		if (sizes[n1] < sizes[n2]) { std::swap(n1, n2); }
		sizes[n1] += sizes[n2];
		parents[n2] = n1;
		return true;
	}
};
// EndCodeSnip

struct Railroad {
	int id;
	int city1;
	int city2;
	int cost;
};

int main() {
	int city_num;
	int rail_num;
	int child_num;
	std::cin >> city_num >> rail_num >> child_num;

	vector<Railroad> railroads(rail_num);
	for (int r = 0; r < rail_num; r++) {
		Railroad &rr = railroads[r];
		rr.id = r;
		std::cin >> rr.city1 >> rr.city2 >> rr.cost;
		rr.city1--;
		rr.city2--;
	}
	std::sort(railroads.begin(), railroads.end(),
	          [](const Railroad &r1, const Railroad &r2) { return r1.cost > r2.cost; });

	vector<DisjointSets> children(child_num, DisjointSets(city_num));
	vector<int> ownership(rail_num);
	for (int r = 0; r < rail_num; r++) {
		const Railroad &rr = railroads[r];
		int lo = 0;
		int hi = child_num - 1;
		int valid = -1;
		while (lo <= hi) {
			int mid = (lo + hi) / 2;
			if (!children[mid].same_set(rr.city1, rr.city2)) {
				valid = mid;
				hi = mid - 1;
			} else {
				lo = mid + 1;
			}
		}

		if (valid != -1) { children[valid].link(rr.city1, rr.city2); }
		ownership[rr.id] = valid + 1;
	}
	for (int c : ownership) { cout << c << '\n'; }
}