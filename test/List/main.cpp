#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <rpt/List.hpp>

TEST_CASE("default", "[List]") {
    rpt::List<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);

    REQUIRE(list.at(0) == 1);
    REQUIRE(list.at(1) == 2);
    REQUIRE(list.at(2) == 3);
    REQUIRE(list.at(3) == 4);
    REQUIRE(list.at(4) == 5);
}
