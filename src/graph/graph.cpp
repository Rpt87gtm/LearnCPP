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
            if (dist[child.second] == -1) {
                dist[child.second] = dist[node] + child.first;
                queue.push(child.second);
            }
        }
    }

    return dist;
}