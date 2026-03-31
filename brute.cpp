#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 505;

int n;
int adj[MAXN][MAXN];

// Check if two edges cross on a circle
bool edges_cross(int a1, int b1, int a2, int b2) {
    if (a1 == a2 || a1 == b2 || b1 == a2 || b1 == b2) return false; // share endpoint

    // Normalize so a1 < b1 and a2 < b2
    if (a1 > b1) swap(a1, b1);
    if (a2 > b2) swap(a2, b2);

    // Two chords (a1,b1) and (a2,b2) on a circle cross iff
    // a1 < a2 < b1 < b2 or a2 < a1 < b2 < b1
    return (a1 < a2 && a2 < b1 && b1 < b2) || (a2 < a1 && a1 < b2 && b2 < b1);
}

// Check if a set of edges forms a valid non-crossing tree
bool is_valid_tree(const vector<pair<int,int>>& edges) {
    // Check if edges cross
    for (int i = 0; i < (int)edges.size(); i++) {
        for (int j = i + 1; j < (int)edges.size(); j++) {
            if (edges_cross(edges[i].first, edges[i].second, edges[j].first, edges[j].second)) {
                return false;
            }
        }
    }

    // Check if it forms a connected tree (n-1 edges, all nodes connected)
    if ((int)edges.size() != n - 1) return false;

    // Check connectivity using DFS
    vector<vector<int>> graph(n);
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(n, false);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int v : graph[u]) {
            if (!visited[v]) dfs(v);
        }
    };
    dfs(0);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) return false;
    }

    return true;
}

// Brute force: enumerate all possible edge sets
long long brute_force() {
    vector<pair<int,int>> all_edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj[i][j]) {
                all_edges.push_back({i, j});
            }
        }
    }

    long long count = 0;
    int m = all_edges.size();

    // Try all subsets of size n-1
    function<void(int, vector<pair<int,int>>&)> enumerate = [&](int idx, vector<pair<int,int>>& current) {
        if ((int)current.size() == n - 1) {
            if (is_valid_tree(current)) {
                count++;
                cout << "Tree " << count << ": ";
                for (auto [u, v] : current) {
                    cout << "(" << u << "," << v << ") ";
                }
                cout << endl;
            }
            return;
        }
        if (idx == m) return;
        if (m - idx < n - 1 - (int)current.size()) return; // pruning

        // Include current edge
        current.push_back(all_edges[idx]);
        enumerate(idx + 1, current);
        current.pop_back();

        // Exclude current edge
        enumerate(idx + 1, current);
    };

    vector<pair<int,int>> current;
    enumerate(0, current);

    return count;
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

    cout << brute_force() << endl;

    return 0;
}
