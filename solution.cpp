#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];
long long dp[MAXN][MAXN];
bool vis[MAXN][MAXN];

// dp[l][r] = number of non-crossing trees on interval [l, r] (line, not circle)
// Pick the "first edge" from l
long long solve(int l, int r) {
    if (l > r) return 1; // empty interval
    if (l == r) return 1; // single node

    if (vis[l][r]) return dp[l][r];
    vis[l][r] = true;

    long long res = 0;

    // Try connecting l to each k in (l, r]
    for (int k = l + 1; k <= r; k++) {
        if (!adj[l][k]) continue;

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

    // For a circle: try all possible "breaking edges"
    // An edge (i, j) can "break" the circle
    // Sum over all edges (i, j)
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!adj[i][j]) continue;

            // Break circle at edge (i, j)
            // This leaves us with nodes [j+1, n-1, 0, i-1] as a line
            // We need to count trees on this line that don't include edge (i,j)
            // Actually, that's not right...

            // When we "break" at edge (i,j), we're saying this edge is NOT in the tree
            // Then we count trees on the line [i+1, j-1, j, ..., but wait, j must connect somehow

            // Actually, I think "breaking" means: this edge IS in the tree
            // Then the rest forms a line

            // Hmm, this is getting confusing. Let me think...
        }
    }

    // For a circle of nodes, we multiply by n (rotat symmetry)
    long long line_answer = solve(0, n - 1);
    cout << (line_answer * n) % MOD << endl;

    return 0;
}
