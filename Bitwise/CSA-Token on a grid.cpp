#include <bits/stdc++.h>

using namespace std;

const int maxn = 24, maxm = 1000, mod = 1000000007;
char grid[maxn][maxm];
int n,m;
int f[1<<maxn], g[1<<maxn], res[maxn+1], cc[26], z[1 << maxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", grid+i); 
	}
	for (int i = 0; i < n; i++) z[1<<i] = i;
	for (int i = 0; i < 1 << n; i++) f[i] = 1;
    for (int column = 0; column < m; column++) {
        int prev = 0;
        int sum = 1;
        for (int i = 0; i < 26; i++) cc[i] = 0;
        for (int bmask = 1; bmask < 1 << n; bmask++) {
            int mask = bmask ^ (bmask >> 1);
            int xx = mask ^ prev;
            int row = z[xx];
            if (grid[row][column] != '.') {
                int let = grid[row][column] - 'a';
                sum -= (1 << cc[let]) - 1;
                cc[let] += ((mask >> row) & 1) == 1 ? +1 : -1;
                sum += (1 << cc[let]) - 1;
            }
            f[mask] = (int) (((long long) f[mask] * sum) % mod);
            prev = mask;
        }
    }
    for (int level = n-1; level >= 0; level--) {
        for (int i = (1<<n)-1; i >= 0; i--) {
            if (((i >> level) & 1) == 1) {
                f[i] -= f[i ^ (1 << level)];
                if (f[i] < 0) f[i] += mod;
            }
        }
    }

    for (int i = 0; i < n; i++) res[i] = 0;
    for (int i = 0; i < 1 << n; i++) {
    	int k = n - __builtin_popcount(i);
    	res[k] += f[i];
    	if (res[k] >= mod) res[k] -= mod;
    }
    for (int i = 0; i < n; i++) {
    	printf("%d ", res[i]);
    }
    printf("%d\n", res[n]);
}