#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_NODES = 1000;

int adjacencyList[MAX_NODES][MAX_NODES];   // Stores neighbors for each node
int edgeCost[MAX_NODES][MAX_NODES];        // Cost from node to node
int visited[MAX_NODES];                    // Visited flag for each node
int parent[MAX_NODES];                     // Previous node on the shortest path
int distanceFromSource[MAX_NODES];         // Distance from source node
int totalNodes, totalEdges, sourceNode;    // Graph metadata

void dijkstra(int source) {
    for (int i = 1; i <= totalNodes; i++) {
        visited[i] = 0;
        parent[i] = -1;
        distanceFromSource[i] = INF;
    }

    distanceFromSource[source] = 0;

    for (int i = 1; i <= totalNodes; i++) {
        int currentNode = -1;
        int minDistance = INF;

        for (int j = 1; j <= totalNodes; j++) {
            if (!visited[j] && distanceFromSource[j] < minDistance) {
                minDistance = distanceFromSource[j];
                currentNode = j;
            }
        }

        if (currentNode == -1) break; // No more reachable nodes
        visited[currentNode] = 1;

        for (int j = 1; j <= adjacencyList[currentNode][0]; j++) {
            int neighbor = adjacencyList[currentNode][j];
            if (!visited[neighbor] && distanceFromSource[currentNode] + edgeCost[currentNode][neighbor] < distanceFromSource[neighbor]) {
                distanceFromSource[neighbor] = distanceFromSource[currentNode] + edgeCost[currentNode][neighbor];
                parent[neighbor] = currentNode;
            }
        }
    }
}

int main() {
    cin >> totalNodes >> totalEdges >> sourceNode;

    // Initialize graph
    for (int i = 1; i <= totalNodes; i++) {
        adjacencyList[i][0] = 0;
        for (int j = 1; j <= totalNodes; j++) {
            edgeCost[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Read edges
    for (int i = 1; i <= totalEdges; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        adjacencyList[from][++adjacencyList[from][0]] = to;
        adjacencyList[to][++adjacencyList[to][0]] = from;
        edgeCost[from][to] = edgeCost[to][from] = cost;
    }

    // Run Dijkstra from source
    dijkstra(sourceNode);

    // Print path from sourceNode to node 1
    int targetNode = 1;
    if (distanceFromSource[targetNode] == INF) {
        cout << "No path from " << sourceNode << " to " << targetNode << endl;
    } else {
        vector<int> path;
        int current = targetNode;
        int totalPathCost = 0;

        while (current != sourceNode) {
            path.push_back(current);
            if (parent[current] == -1) {
                cout << "Incomplete path." << endl;
                return 0;
            }
            totalPathCost += edgeCost[parent[current]][current];
            current = parent[current];
        }

        path.push_back(sourceNode);
        reverse(path.begin(), path.end());

        for (int node : path) {
            cout << node << " ";
        }
        cout << endl << totalPathCost << endl;
    }

    return 0;
}
