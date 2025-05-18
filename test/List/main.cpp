#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <rpt/List.hpp>

TEST_CASE("initializer list counstuctor", "[List]") {
    rpt::List<int> list{1, 2, 3, 4, 5};

    REQUIRE(list.size() == 5);
    REQUIRE(list.at(0) == 1);
    REQUIRE(list.at(1) == 2);
    REQUIRE(list.at(2) == 3);
    REQUIRE(list.at(3) == 4);
    REQUIRE(list.at(4) == 5);
}

TEST_CASE("at ref", "[List]") {
    rpt::List<int> list{1, 2, 3};
    list.at(1) = 7;

    REQUIRE(list.size() == 3);
    REQUIRE(list.at(0) == 1);
    REQUIRE(list.at(1) == 7);
    REQUIRE(list.at(2) == 3);
}

TEST_CASE("push back", "[List]") {
    rpt::List<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);

    REQUIRE(list.size() == 5);
    REQUIRE(list.at(0) == 1);
    REQUIRE(list.at(1) == 2);
    REQUIRE(list.at(2) == 3);
    REQUIRE(list.at(3) == 4);
    REQUIRE(list.at(4) == 5);
}

TEST_CASE("push front", "[List]") {
    rpt::List<int> list;

    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    list.pushFront(4);
    list.pushFront(5);

    REQUIRE(list.size() == 5);
    REQUIRE(list.at(0) == 5);
    REQUIRE(list.at(1) == 4);
    REQUIRE(list.at(2) == 3);
    REQUIRE(list.at(3) == 2);
    REQUIRE(list.at(4) == 1);
}

TEST_CASE("pop back", "[List]") {
    rpt::List<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);

    int value_at_4 = list.popBack();
    int value_at_3 = list.popBack();

    REQUIRE(list.size() == 3);
    REQUIRE(list.at(0) == 1);
    REQUIRE(list.at(1) == 2);
    REQUIRE(list.at(2) == 3);
    REQUIRE(value_at_3 == 4);
    REQUIRE(value_at_4 == 5);
}

TEST_CASE("pop front", "[List]") {
    rpt::List<int> list;

    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);

    int value_at_0 = list.popFront();
    int value_at_1 = list.popFront();

    REQUIRE(list.size() == 3);
    REQUIRE(value_at_0 == 1);
    REQUIRE(value_at_1 == 2);
    REQUIRE(list.at(0) == 3);
    REQUIRE(list.at(1) == 4);
    REQUIRE(list.at(2) == 5);
}
