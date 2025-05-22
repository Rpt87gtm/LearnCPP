#include <queue>
#include <rpt/graph/graph.hpp>

std::vector<int> rpt::BFS(const Graph &graph, int start) {
    std::queue<int> queue;
    std::vector<int> dist(graph.size(), -1);
    dist[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        for (auto child: graph[node]) {
            if (dist[child.first] == -1) {
                dist[child.first] = dist[node] + child.second;
                queue.push(child.first);
            }
        }
    }

    return dist;
}

std::vector<int> rpt::Dijkstra(const Graph &graph, int start) {
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
    std::vector<int> dist(graph.size(), INT_MAX);
    dist[start] = 0;
    queue.push({0, start});

    while (!queue.empty()) {
        auto [distance, node] = queue.top();
        queue.pop();

        if (distance > dist[node]) {
            continue;
        }
        for (auto child: graph[node]) {
            if (dist[child.first] > dist[node] + child.second) {
                auto new_distance = dist[node] + child.second;
                dist[child.first] = new_distance;
                queue.push({new_distance, child.first});
            }
        }
    }

    return dist;
}
