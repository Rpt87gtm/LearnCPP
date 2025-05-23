#include <queue>
#include <rpt/graph/graph.hpp>

std::vector<int> rpt::BFS(const Graph &graph, const int &start) {
    std::queue<int> queue;
    std::vector<int> dist(graph.size(), -1);
    dist[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        for (auto child: graph[node]) {
            if (dist[child.target] == -1) {
                dist[child.target] = dist[node] + child.distance;
                queue.push(child.target);
            }
        }
    }

    return dist;
}

std::vector<int> rpt::Dijkstra(const Graph &graph, const int &start) {
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
            if (dist[child.target] > dist[node] + child.distance) {
                auto new_distance  = dist[node] + child.distance;
                dist[child.target] = new_distance;
                queue.push({new_distance, child.target});
            }
        }
    }

    return dist;
}

std::vector<std::pair<int, std::vector<int>>> rpt::Dijkstra_path(const Graph &graph, const int &start) {
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
    std::vector<std::pair<int, std::vector<int>>> dist_with_path(graph.size(), {INT_MAX, {}});
    dist_with_path[start] = {0, {start}};
    queue.push({0, start});

    while (!queue.empty()) {
        auto [distance, node] = queue.top();
        queue.pop();

        if (distance > dist_with_path[node].first) {
            continue;
        }
        for (auto child: graph[node]) {
            if (dist_with_path[child.target].first > dist_with_path[node].first + child.distance) {
                auto new_distance = dist_with_path[node].first + child.distance;
                auto new_path     = dist_with_path[node].second;
                new_path.push_back(child.target);
                dist_with_path[child.target] = {new_distance, new_path};
                queue.push({new_distance, child.target});
            }
        }
    }

    return dist_with_path;
}
