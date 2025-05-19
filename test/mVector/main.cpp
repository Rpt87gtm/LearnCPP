#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <rpt/mVector.hpp>

TEST_CASE("default constructor", "[Vector]") {
    rpt::mVector<int> vec{1, 2, 3, 4, 5};
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
    REQUIRE(vec[3] == 4);
    REQUIRE(vec[4] == 5);
}

TEST_CASE("at func", "[Vector]") {
    rpt::mVector<int> vec{1, 2, 3, 4, 5};

    vec.at(2) = 7;
    vec[3]    = 9;

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 7);
    REQUIRE(vec[3] == 9);
    REQUIRE(vec[4] == 5);
}

TEST_CASE("push_back", "[Vector]") {
    rpt::mVector<int> vec;
    vec.pushBack(1);
    vec.pushBack(2);
    vec.pushBack(3);

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}

TEST_CASE("pop_back", "[Vector]") {
    rpt::mVector<int> vec{1, 2, 3, 4, 5};

    auto value1 = vec.popBack();
    auto value2 = vec.popBack();

    REQUIRE(vec.size() == 3);

    REQUIRE((value1 == 5));
    REQUIRE((value2 == 4));

    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}