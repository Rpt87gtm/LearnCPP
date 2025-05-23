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

struct Node {
public:
    Node() = default;

    explicit Node(std::vector<Edge> edges) : edges(std::move(edges)) {}

    // Node(std::initializer_list<Edge> init_list) : edges(init_list) {}

    Node(std::initializer_list<std::pair<TargetNode, Distance>> init_list) {
        edges.reserve(init_list.size());
        for (const auto &[target, dist]: init_list) {
            edges.emplace_back(target, dist);
        }
    }

    const std::vector<Edge> &get_edges() const noexcept { return edges; }

    std::vector<Edge> &get_edges() noexcept { return edges; }

    void add_edge(TargetNode target, Distance dist) { edges.emplace_back(target, dist); }

    bool empty() const noexcept { return edges.empty(); }

private:
    std::vector<Edge> edges;
};

using Graph = std::vector<Node>;

std::vector<int> BFS(const Graph &graph, const int &start);
std::vector<int> Dijkstra(const Graph &graph, const int &start);
std::vector<std::pair<int, std::vector<int>>> Dijkstra_path(const Graph &graph, const int &start);

} // namespace rpt