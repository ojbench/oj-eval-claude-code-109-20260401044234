#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];
long long dp[MAXN][MAXN];
bool vis[MAXN][MAXN];

//  dp[l][r] = number of non-crossing trees on interval [l, r]
// where the tree can have any structure, but must span all nodes [l, r]
long long solve(int l, int r) {
    if (l > r) return 1; // empty interval
    if (l == r) return 1; // single node

    if (vis[l][r]) return dp[l][r];
    vis[l][r] = true;

    long long res = 0;

    // Strategy: Pick the first edge involving node l
    // Try connecting l to each node k in (l, r]
    for (int k = l + 1; k <= r; k++) {
        if (!adj[l][k]) continue; // Edge (l, k) is forbidden

        // Edge (l, k) divides the interval:
        // Nodes in (l, k) are between l and k
        // Nodes in (k, r] are to the right of k

        long long mid = solve(l + 1, k - 1);
        long long right = solve(k + 1, r);

        res = (res + mid * right % MOD) % MOD;
    }

    return dp[l][r] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    memset(vis, false, sizeof(vis));

    cout << solve(0, n - 1) << endl;

    return 0;
}
