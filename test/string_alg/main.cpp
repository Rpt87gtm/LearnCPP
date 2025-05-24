#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <format>
#include <str_alg/substr.hpp>
#include <string>

TEST_CASE("defoult", "[Prefix function]") {
    std::string text = "abcabaccabcb";
    auto pi          = rpt::prefix_function(text);
    std::vector<int> expected{0, 0, 0, 1, 2, 1, 0, 0, 1, 2, 3, 0};
    REQUIRE(pi == expected);
}

TEST_CASE("one char", "[Prefix function]") {
    std::string text = "n";
    auto pi          = rpt::prefix_function(text);
    std::vector<int> expected{0};
    REQUIRE((pi == expected));
}

TEST_CASE("substring in first place", "[Prefix search]") {
    std::string pattern = "abc";
    std::string text    = "abcabaccabcb";
    auto index          = rpt::substring_index(text, pattern);
    REQUIRE((index == 0));
}

TEST_CASE("default", "[Prefix search]") {
    std::string pattern = "abc";
    std::string text    = "fbcabaccabcb";
    auto index          = rpt::substring_index(text, pattern);
    REQUIRE((index == 8));
}