#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX = 1000;

int G[MAX][MAX];       // Adjacency list (degree stored at G[i][0])
int c[MAX][MAX];       // Cost matrix
int U[MAX];            // Visited flag
int p[MAX];            // Parent array
int d[MAX];            // Distance array
int n, m, r;           // n = nodes, m = edges, r = source node

void dijkstra(int r) {
    for (int i = 1; i <= n; i++) {
        U[i] = 0;
        p[i] = -1;
        d[i] = INF;
    }

    d[r] = 0;

    for (int i = 1; i <= n; i++) {
        int v = -1;
        int minDist = INF;

        for (int j = 1; j <= n; j++) {
            if (!U[j] && d[j] < minDist) {
                minDist = d[j];
                v = j;
            }
        }

        if (v == -1) break; // No reachable unvisited nodes
        U[v] = 1;

        for (int j = 1; j <= G[v][0]; j++) {
            int w = G[v][j];
            if (!U[w] && d[v] + c[v][w] < d[w]) {
                d[w] = d[v] + c[v][w];
                p[w] = v;
            }
        }
    }
}

int main() {
    cin >> n >> m >> r;

    // Initialize graph
    for (int i = 1; i <= n; i++) {
        G[i][0] = 0;
        for (int j = 1; j <= n; j++) {
            c[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Read edges
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u][++G[u][0]] = v;
        G[v][++G[v][0]] = u;
        c[u][v] = c[v][u] = w;
    }

    // Run Dijkstra from source r
    dijkstra(r);

    // Print path from r to node 1
    int target = 1;
    if (d[target] == INF) {
        cout << "No path from " << r << " to " << target << endl;
    } else {
        vector<int> path;
        int current = target;
        int totalCost = 0;

        while (current != r) {
            path.push_back(current);
            if (p[current] == -1) {
                cout << "Incomplete path." << endl;
                return 0;
            }
            totalCost += c[p[current]][current];
            current = p[current];
        }

        path.push_back(r);
        reverse(path.begin(), path.end());

        for (int node : path) {
            cout << node << " ";
        }
        cout << endl << totalCost << endl;
    }

    return 0;
}