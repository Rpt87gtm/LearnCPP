#pragma once
#include <cassert>
#include <stdexcept>
#include <utility>
#include <vector>

namespace rpt {

using Distance   = int;
using TargetNode = int;

struct Edge {
public:
    Edge(TargetNode target_node, Distance distance_to_node) : target(target_node), distance(distance_to_node) {}

    Edge(std::initializer_list<int> list) {
        assert(list.size() == 2 && "Edge requires exactly 2 values");
        auto it = list.begin();
        target  = *it;
        it++;
        distance = *it;
    }

    bool operator>(const Edge &other) const noexcept { return distance > other.distance; }

    bool operator<(const Edge &other) const noexcept { return distance < other.distance; }

    TargetNode target;
    Distance distance;
};

using Node  = std::vector<Edge>;
using Graph = std::vector<Node>;

std::vector<int> BFS(const Graph &graph, const int &start);
std::vector<int> Dijkstra(const Graph &graph, const int &start);
std::vector<std::pair<int, std::vector<int>>> Dijkstra_path(const Graph &graph, const int &start);

} // namespace rpt