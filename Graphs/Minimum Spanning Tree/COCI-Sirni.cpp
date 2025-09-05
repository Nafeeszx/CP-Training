#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::vector;

// BeginCodeSnip{DSU (from the module)}
class DisjointSets {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
	DisjointSets(int size) : parents(size), sizes(size, 1) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	int find(int n) { return parents[n] == n ? n : (parents[n] = find(parents[n])); }

	bool unite(int n1, int n2) {
		n1 = find(n1);
		n2 = find(n2);
		if (n1 == n2) { return false; }
		if (sizes[n1] < sizes[n2]) { std::swap(n1, n2); }
		sizes[n1] += sizes[n2];
		parents[n2] = n1;
		return true;
	}
};
// EndCodeSnip

int main() {
	int card_num;
	std::cin >> card_num;
	vector<int> cards(card_num);
	for (int &c : cards) {
		std::cin >> c;
		assert(c >= 1);
	}

	std::sort(cards.begin(), cards.end());
	// we can erase the dupes bc modding them with the original one = 0
	cards.erase(std::unique(cards.begin(), cards.end()), cards.end());

	int largest = cards.back();  // since we sorted the cards already
	// next_largest[i] contains the index of lowest card value that's >= i
	vector<int> next_largest(largest + 1, -1);
	for (int i = 0; i < cards.size(); i++) { next_largest[cards[i]] = i; }
	for (int c = largest - 1; c >= 0; c--) {
		// if this isn't assigned yet, assign it the previous one
		if (next_largest[c] == -1) { next_largest[c] = next_largest[c + 1]; }
	}

	vector<vector<pair<int, int>>> good_links(largest + 1);
	for (int i = 0; i < cards.size() - 1; i++) {
		// get all relevant cards this card could be connected to
		good_links[cards[i + 1] % cards[i]].push_back({i, i + 1});
		for (int at = 2 * cards[i]; at <= largest; at += cards[i]) {
			int good_mod = next_largest[at];
			good_links[cards[good_mod] % cards[i]].push_back({i, good_mod});
		}
	}

	long long total_cost = 0;
	DisjointSets linked_cards(cards.size());
	for (int c = 0; c <= largest; c++) {
		for (const pair<int, int> &link : good_links[c]) {
			bool result = linked_cards.unite(link.first, link.second);
			total_cost += c * result;
		}
	}

	cout << total_cost << endl;
}