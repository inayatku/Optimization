#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

void dijkstra(int start, vector<vector<pair<int, int>>> &graph, vector<int> &dist, vector<int> &prev) {
    dist.assign(graph.size(), INF);
    prev.assign(graph.size(), -1);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const auto &edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

vector<int> reconstruct_path(int start, int end, const vector<int> &prev) {
    vector<int> path;
    for (int v = end; v != start; v = prev[v]) {
        path.push_back(v);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    vector<vector<pair<int, int>>> graph = {
        {{1, 5}, {2, 1}},
        {{2, 2}, {3, 3}},
        {{1, 1}, {3, 4}},
        {{4, 6}},
        {}
    };

    int start_node = 0;
    vector<int> dist;
    vector<int> prev;

    dijkstra(start_node, graph, dist, prev);

    for (int i = 0; i < graph.size(); i++) {
        cout << "Shortest distance from " << start_node << " to " << i << ": " << dist[i] << endl;
        if (prev[i] != -1) {
            cout << "Path: ";
            vector<int> path = reconstruct_path(start_node, i, prev);
            for (int j = 0; j < path.size(); j++) {
                if (j != path.size() - 1) {
                    cout << path[j] << " -> ";
                } else {
                    cout << path[j];
                }
            }
            cout << endl;
        }
    }

    return 0;
}
