/**
 * Description: Given J jobs and W workers (J <= W), computes the minimum cost
 * to assign each prefix of jobs to distinct workers.
 *
 * @tparam T a type large enough to represent integers on the order of J *
 * max(|C|)
 * @param C a matrix of dimensions JxW such that C[j][w] = cost to assign j-th
 * job to w-th worker (possibly negative)
 *
 * vector<T> answer =  a vector of length J, with the j-th entry equaling the minimum cost
 * to assign the first (j+1) jobs to distinct workers
 * Time: O(J^2W)
 * Source:
	 * http://e-maxx.ru/algo/assignment_hungary#6
	 * https://en.wikipedia.org/wiki/Hungarian_algorithm
 * Verification:
	 * https://www.spoj.com/problems/BABY/
	 * https://open.kattis.com/problems/cordonbleu
	 * more problems at https://codeforces.com/blog/entry/63701
 */

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for(auto& a : x)
#define FOR(i, a, b) for (int i=(a); i<=(signed)(b); i++)
#define ROF(i, a, b) for (int i=(a); i>=(signed)(b); i--)
#define F0R(i, a) for (int i=0; i<(signed)(a); i++)
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pb push_back
#define rsz(x) resize(x)
#define sz(x) (x).size()
#define f first
#define s second
#define all(v) (v).begin(), (v).end()
typedef long long ll;

double ckmin(double &a, double b) { return a > b ? ((a = b), true) : false; }

template<class T> using V = vector<T>;
vector<int> hungarian(const vector<vector<double>> &C) {
	const int J = (int)size(C), W = (int)size(C[0]);
	assert(J <= W);
    using T = double;
	/// job[w] = job assigned to w-th worker, or -1 if no job assigned
	/// note: a W-th worker was added for convenience
	vector<int> job(W + 1, -1);
	vector<T> ys(J), yt(W + 1); /// potentials
	/// -yt[W] will equal the sum of all deltas
	vector<T> answers;
	const T inf = numeric_limits<T>::max();
	for (int j_cur = 0; j_cur < J; ++j_cur) { /// assign j_cur-th job
		int w_cur = W;
		job[w_cur] = j_cur;
		/// min reduced cost over edges from Z to worker w
		vector<T> min_to(W + 1, inf);
		vector<int> prv(W + 1, -1); /// previous worker on alternating path
		vector<bool> in_Z(W + 1);   /// whether worker is in Z
		while (job[w_cur] != -1) {  /// runs at most j_cur + 1 times
			in_Z[w_cur] = true;
			const int j = job[w_cur];
			T delta = inf;
			int w_next;
			for (int w = 0; w < W; ++w) {
				if (!in_Z[w]) {
					if (ckmin(min_to[w], C[j][w] - ys[j] - yt[w]))
						prv[w] = w_cur;
					if (ckmin(delta, min_to[w])) w_next = w;
				}
			}
			/// delta will always be non-negative,
			/// except possibly during the first time this loop runs
			/// if any entries of C[j_cur] are negative
			for (int w = 0; w <= W; ++w) {
				if (in_Z[w]) ys[job[w]] += delta, yt[w] -= delta;
				else min_to[w] -= delta;
			}
			w_cur = w_next;
		}
		/// update assignments along alternating path
		for (int w; w_cur != -1; w_cur = w) job[w_cur] = job[w = prv[w_cur]];
		answers.push_back(-yt[W]);
	}
	return job;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    int n; cin >> n;
    vector<vector<double>> v(n, vector<double>(n));
    vector<pair<int, int>> p(n), q(n);
    F0R(i, n) cin >> p[i].f >> p[i].s;
    F0R(i, n) cin >> q[i].f >> q[i].s;
    F0R(i, n) {
        F0R(j, n) {
            v[j][i] = sqrt((p[i].f-q[j].f)*(p[i].f-q[j].f)+(p[i].s-q[j].s)*(p[i].s-q[j].s));
        }
    }

    vector<int> pt = hungarian(v);
    F0R(i, n) {
        cout << pt[i]+1 << " ";
    }
    return 0;
}