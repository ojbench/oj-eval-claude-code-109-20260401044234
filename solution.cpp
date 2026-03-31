#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];
long long dpt[MAXN][MAXN]; // trees
long long dpf[MAXN][MAXN]; // forests
bool vist[MAXN][MAXN];
bool visf[MAXN][MAXN];

long long forest(int l, int r);

// Number of non-crossing trees on interval [l, r]
long long tree(int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;

    if (vist[l][r]) return dpt[l][r];
    vist[l][r] = true;

    long long res = 0;

    // Pick node l, connect it to node k in (l, r]
    for (int k = l + 1; k <= r; k++) {
        if (!adj[l][k]) continue;

        // Nodes in (l, k) form a forest connecting to l
        // Nodes in (k, r] form a forest connecting to k
        // These forests are independent

        long long left = forest(l + 1, k - 1);
        long long right = forest(k + 1, r);

        res = (res + left * right % MOD) % MOD;
    }

    return dpt[l][r] = res;
}

// Number of non-crossing forests on interval [l, r]
long long forest(int l, int r) {
    if (l > r) return 1; // empty forest

    if (visf[l][r]) return dpf[l][r];
    visf[l][r] = true;

    long long res = 0;

    // A forest is a union of disjoint trees
    // Split point k: first tree is [l, k], remaining forest is [k+1, r]
    for (int k = l; k <= r; k++) {
        long long t = tree(l, k);
        long long f = (k < r) ? forest(k + 1, r) : 1;
        res = (res + t * f % MOD) % MOD;
    }

    return dpf[l][r] = res;
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

    memset(vist, false, sizeof(vist));
    memset(visf, false, sizeof(visf));

    long long ans = tree(0, n - 1);

    cout << ans << endl;

    return 0;
}
