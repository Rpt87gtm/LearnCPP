#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <format>
#include <rpt/List.hpp>
#include <rpt/graph/graph.hpp>
#include <rpt/trees/tree.hpp>
#include <string>

void print_graph(const std::vector<int> &dist, const int &start) {
    std::cout << std::format("Start form node: {}\n", start);
    for (int i = 0; i < dist.size(); i++) {
        std::cout << std::format("{} -> {}\n", i, dist[i]);
    }
}

TEST_CASE("BFS", "[Graph]") {
    rpt::Graph graph(6);
    graph[0] = {
      {1, 1},
      {1, 3}
    };
    graph[1] = {
      {1, 2}
    };
    graph[2] = {
      {1, 3}
    };
    graph[3] = {
      {1, 4}
    };
    graph[4] = {
      {1, 5},
      {1, 0}
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

TEST_CASE("Dijkstra with the unweighted graph ", "[Graph]") {
    rpt::Graph graph(6);
    graph[0] = {
      {1, 1},
      {1, 3}
    };
    graph[1] = {
      {1, 2}
    };
    graph[2] = {
      {1, 3}
    };
    graph[3] = {
      {1, 4}
    };
    graph[4] = {
      {1, 5},
      {1, 0}
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

TEST_CASE("Dijkstra with the weighted graph ", "[Graph]") {
    rpt::Graph graph(9);
    graph[0] = {
      {2, 1},
      {2, 2}
    };
    graph[1] = {
      {3, 4},
      {2, 3},
    };
    graph[2] = {
      {1, 3}
    };
    graph[3] = {
      {1, 4},
      {3, 5},
    };
    graph[4] = {
      {2, 7},
      {3, 6}
    };
    graph[5] = {
      {1, 6},
      {2, 8},
    };

    graph[6] = {
      {1, 2},
      {1, 7},
    };
    graph[7] = {
      {2, 8},
    };
    graph[8] = {};

    int start        = 0;
    auto dist_form_0 = rpt::Dijkstra(graph, start);
    REQUIRE(dist_form_0 == std::vector<int>({0, 2, 2, 3, 4, 6, 7, 6, 8}));

    start     = 3;
    auto dist = rpt::Dijkstra(graph, start);
    print_graph(dist, start);
}
