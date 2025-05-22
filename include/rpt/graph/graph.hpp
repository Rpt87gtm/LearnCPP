#pragma once
#include <utility>
#include <vector>

namespace rpt {
using Distance = int;
using EdgeId   = int;
using Edge     = std::pair<Distance, EdgeId>;
using Node     = std::vector<Edge>;
using Graph    = std::vector<Node>;

std::vector<int> BFS(const Graph &graph, int start);

} // namespace rpt