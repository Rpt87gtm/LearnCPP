#pragma once
#include <utility>
#include <vector>

namespace rpt {
using Distance = int;
using EdgeId   = int;
using Edge     = std::pair<EdgeId, Distance>;
using Node     = std::vector<Edge>;
using Graph    = std::vector<Node>;

std::vector<int> BFS(const Graph &graph, const int &start);
std::vector<int> Dijkstra(const Graph &graph, const int &start);
std::vector<std::pair<int, std::vector<int>>> Dijkstra_path(const Graph &graph, const int &start);

} // namespace rpt