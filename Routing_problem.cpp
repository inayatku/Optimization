#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& adj_list) {
    int n = adj_list.size();
    vector<int> dist(n, INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist > dist[cur_node]) {
            continue;
        }

        for (const auto& neighbor : adj_list[cur_node]) {
            int next_node = neighbor.first;
            int edge_weight = neighbor.second;

            if (dist[cur_node] + edge_weight < dist[next_node]) {
                dist[next_node] = dist[cur_node] + edge_weight;
                pq.push(make_pair(dist[next_node], next_node));
            }
        }
    }

    return dist;
}

int main() {
    int num_nodes = 6;
    int num_edges = 9;

    vector<vector<pair<int, int>>> adj_list(num_nodes);
    vector<pair<int, pair<int, int>>> edges = {
        {0, {1, 7}},
        {0, {2, 9}},
        {0, {5, 14}},
        {1, {2, 10}},
        {1, {3, 15}},
        {2, {3, 11}},
        {2, {5, 2}},
        {3, {4, 6}},
        {5, {4, 9}}
    };

    for (const auto& edge : edges) {
        int src = edge.first;
        int dest = edge.second.first;
        int weight = edge.second.second;
        adj_list[src].push_back(make_pair(dest, weight));
        adj_list[dest].push_back(make_pair(src, weight));
    }

    int start = 0;

    vector<int> shortest_paths = dijkstra(start, adj_list);

    cout << "Shortest path distances from node " << start << ":\n";
    for (int i = 0; i < num_nodes; ++i) {
        cout << "Node " << i << ": " << shortest_paths[i] << endl;
    }

    return 0;
}
