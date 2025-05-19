#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <rpt/List.hpp>
#include <rpt/mVector.hpp>
#include <rpt/sorts.hpp>
#include <vector>

TEST_CASE("vector sort", "[Sort]") {
    std::vector<int> vec{1, 4, 3, 2, 5};
    rpt::sort(vec);

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec[3] == 4);
    REQUIRE(vec[4] == 5);
}

TEST_CASE("mVector sort", "[Sort]") {
    rpt::mVector<int> vec{1, 4, 3, 2, 5};
    rpt::sort(vec);

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec[3] == 4);
    REQUIRE(vec[4] == 5);
}

TEST_CASE("list sort", "[Sort]") {
    rpt::List<int> vec{1, 4, 3, 2, 5};
    rpt::sort(vec);

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec[3] == 4);
    REQUIRE(vec[4] == 5);
}
