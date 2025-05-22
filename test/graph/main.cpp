#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <format>
#include <rpt/List.hpp>
#include <rpt/graph/graph.hpp>
#include <rpt/trees/tree.hpp>
#include <string>

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

    // std::cout << std::format("Start form node: {}\n", start);
    // for (int i = 0; i < dist_form_2.size(); i++) {
    //     std::cout << std::format("{} -> {}\n", i, dist_form_2[i]);
    // }
}
