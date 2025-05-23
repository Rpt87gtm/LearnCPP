#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <format>
#include <rpt/List.hpp>
#include <rpt/graph/graph.hpp>
#include <rpt/trees/tree.hpp>
#include <string>

void print_graph(const std::vector<int> &dist, const int &start) {
    std::cout << std::format("Start from node: {}\n", start);
    for (int i = 0; i < dist.size(); i++) {
        std::cout << std::format("{} -> {}\n", i, dist[i]);
    }
}

TEST_CASE("BFS", "[Graph]") {
    rpt::Graph graph(6);
    graph[0] = {
      {1, 1}, // узел, вес → теперь {1, 1}
      {3, 1}  // узел, вес → теперь {3, 1}
    };
    graph[1] = {
      {2, 1}  // узел, вес → теперь {2, 1}
    };
    graph[2] = {
      {3, 1}  // узел, вес → теперь {3, 1}
    };
    graph[3] = {
      {4, 1}  // узел, вес → теперь {4, 1}
    };
    graph[4] = {
      {5, 1}, // узел, вес → теперь {5, 1}
      {0, 1}  // узел, вес → теперь {0, 1}
    };
    graph[5] = {};

    int start        = 0;
    auto dist_form_0 = rpt::BFS(graph, start);
    REQUIRE(dist_form_0 == std::vector<int>({0, 1, 2, 1, 2, 3}));

    start            = 1;
    auto dist_form_1 = rpt::BFS(graph, start);
    REQUIRE(dist_form_1 == std::vector<int>({4, 0, 1, 2, 3, 4}));

    start            = 2;
    auto dist_form_2 = rpt::BFS(graph, start);
    REQUIRE(dist_form_2 == std::vector<int>({3, 4, 0, 1, 2, 3}));

    start            = 3;
    auto dist_form_3 = rpt::BFS(graph, start);
    REQUIRE(dist_form_3 == std::vector<int>({2, 3, 4, 0, 1, 2}));

    start            = 4;
    auto dist_form_4 = rpt::BFS(graph, start);
    REQUIRE(dist_form_4 == std::vector<int>({1, 2, 3, 2, 0, 1}));

    start            = 5;
    auto dist_form_5 = rpt::BFS(graph, start);
    REQUIRE(dist_form_5 == std::vector<int>({-1, -1, -1, -1, -1, 0}));
}

TEST_CASE("Dijkstra with the unweighted graph", "[Graph]") {
    rpt::Graph graph(6);
    graph[0] = {
      {1, 1}, // узел, вес → теперь {1, 1}
      {3, 1}  // узел, вес → теперь {3, 1}
    };
    graph[1] = {
      {2, 1}  // узел, вес → теперь {2, 1}
    };
    graph[2] = {
      {3, 1}  // узел, вес → теперь {3, 1}
    };
    graph[3] = {
      {4, 1}  // узел, вес → теперь {4, 1}
    };
    graph[4] = {
      {5, 1}, // узел, вес → теперь {5, 1}
      {0, 1}  // узел, вес → теперь {0, 1}
    };
    graph[5] = {};

    int start        = 0;
    auto dist_form_0 = rpt::Dijkstra(graph, start);
    REQUIRE(dist_form_0 == std::vector<int>({0, 1, 2, 1, 2, 3}));

    start            = 1;
    auto dist_form_1 = rpt::Dijkstra(graph, start);
    REQUIRE(dist_form_1 == std::vector<int>({4, 0, 1, 2, 3, 4}));

    start            = 2;
    auto dist_form_2 = rpt::Dijkstra(graph, start);
    REQUIRE(dist_form_2 == std::vector<int>({3, 4, 0, 1, 2, 3}));

    start            = 3;
    auto dist_form_3 = rpt::Dijkstra(graph, start);
    REQUIRE(dist_form_3 == std::vector<int>({2, 3, 4, 0, 1, 2}));

    start            = 4;
    auto dist_form_4 = rpt::Dijkstra(graph, start);
    REQUIRE(dist_form_4 == std::vector<int>({1, 2, 3, 2, 0, 1}));

    start            = 5;
    auto dist_form_5 = rpt::Dijkstra(graph, start);
    REQUIRE(dist_form_5 == std::vector<int>({INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0}));
}

TEST_CASE("Dijkstra with the weighted graph", "[Graph]") {
    rpt::Graph graph(9);
    graph[0] = {
      {1, 2}, // узел, вес → теперь {1, 2}
      {2, 2}  // узел, вес → теперь {2, 2}
    };
    graph[1] = {
      {4, 3}, // узел, вес → теперь {4, 3}
      {3, 2}  // узел, вес → теперь {3, 2}
    };
    graph[2] = {
      {3, 1}  // узел, вес → теперь {3, 1}
    };
    graph[3] = {
      {4, 1}, // узел, вес → теперь {4, 1}
      {5, 3}  // узел, вес → теперь {5, 3}
    };
    graph[4] = {
      {7, 2}, // узел, вес → теперь {7, 2}
      {6, 3}  // узел, вес → теперь {6, 3}
    };
    graph[5] = {
      {6, 1}, // узел, вес → теперь {6, 1}
      {8, 2}  // узел, вес → теперь {8, 2}
    };
    graph[6] = {
      {2, 1}, // узел, вес → теперь {2, 1}
      {7, 1}  // узел, вес → теперь {7, 1}
    };
    graph[7] = {
      {8, 2}  // узел, вес → теперь {8, 2}
    };
    graph[8] = {};

    int start        = 0;
    auto dist_from_0 = rpt::Dijkstra(graph, start);
    REQUIRE(dist_from_0 == std::vector<int>({0, 2, 2, 3, 4, 6, 7, 6, 8}));

    start     = 3;
    auto dist = rpt::Dijkstra(graph, start);
    print_graph(dist, start);
}

namespace {
using rpt::Graph;

void check_path(
  std::vector<std::pair<int, std::vector<int>>> &dist, const Graph &graph, const std::vector<int> &expected) {
    for (int i = 0; i < expected.size(); i++) {
        std::cout << std::format(" path to node {}", i) << std::endl;

        if (dist[i].second.empty()) {
            REQUIRE(dist[i].first == INT_MAX); // Если пути нет, расстояние должно быть INT_MAX
            continue;
        }

        int path      = 0;
        auto it       = dist[i].second.begin();
        int prev_node = *it;
        it++;

        while (it != dist[i].second.end()) {
            auto edge_it =
              std::find_if(graph[prev_node].begin(), graph[prev_node].end(), [target = *it](const rpt::Edge &edge) {
                  return edge.first == target;
              });

            REQUIRE((edge_it != graph[prev_node].end()));
            path += edge_it->second;
            prev_node = *it;
            it++;
        }

        REQUIRE((dist[i].first == expected[i]));
        REQUIRE((path == expected[i]));
    }
}
} // namespace

TEST_CASE("Dijkstra path with the weighted graph", "[Graph]") {
    rpt::Graph graph(9);
    graph[0] = {
      {1, 2}, // узел, вес → теперь {1, 2}
      {2, 2}  // узел, вес → теперь {2, 2}
    };
    graph[1] = {
      {4, 3}, // узел, вес → теперь {4, 3}
      {3, 2}  // узел, вес → теперь {3, 2}
    };
    graph[2] = {
      {3, 1}  // узел, вес → теперь {3, 1}
    };
    graph[3] = {
      {4, 1}, // узел, вес → теперь {4, 1}
      {5, 3}  // узел, вес → теперь {5, 3}
    };
    graph[4] = {
      {7, 2}, // узел, вес → теперь {7, 2}
      {6, 3}  // узел, вес → теперь {6, 3}
    };
    graph[5] = {
      {6, 1}, // узел, вес → теперь {6, 1}
      {8, 2}  // узел, вес → теперь {8, 2}
    };
    graph[6] = {
      {2, 1}, // узел, вес → теперь {2, 1}
      {7, 1}  // узел, вес → теперь {7, 1}
    };
    graph[7] = {
      {8, 2}  // узел, вес → теперь {8, 2}
    };
    graph[8] = {};

    int start        = 0;
    auto dist_from_0 = rpt::Dijkstra_path(graph, start);
    std::vector<int> expected({0, 2, 2, 3, 4, 6, 7, 6, 8});
    check_path(dist_from_0, graph, expected);

    start     = 3;
    auto dist = rpt::Dijkstra_path(graph, start);
    std::vector<int> expected2({INT_MAX, INT_MAX, 5, 0, 1, 3, 4, 3, 5});
    check_path(dist, graph, expected2);
}