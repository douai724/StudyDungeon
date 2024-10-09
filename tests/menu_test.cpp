#include "menu.h"
#include "util.h"
#include <Windows.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("ASCII art")
{

    ConsoleUI::ConsoleWindow testWindow{};
    std::string testSanta = R"(
       __
     /'-.'\
    /    \()
   /.----.\
   | o__o |
   _''- ''_
 ['  \  /  ']
 |\   \/   /|
 |_|______|_|
 {_[   [=]]_}
  \|""""""|/
   |   |  |
   |   |  |
   |___|__|
   [__][__]
    )";

    std::vector<std::string> convertedTestSanta = convertAsciiArtToLines(testSanta);
    ConsoleUI::AsciiArt testArt("testSanta", convertedTestSanta, 12, 3);

    SECTION("Get ASCII art name")
    {
        REQUIRE(testArt.getName() == "testSanta");
    }

    SECTION("Get ASCII art x position")
    {
        REQUIRE(testArt.getX() == 12);
    }

    SECTION("Get ASCII art y position")
    {
        REQUIRE(testArt.getY() == 3);
    }

    SECTION("Get ASCII art in string format")
    {
        REQUIRE(testArt.getArt() == convertedTestSanta);
    }

    SECTION("Santa width should be 13")
    {
        REQUIRE(testArt.getWidth() == 13);
    }

    SECTION("Santa width should not be 0")
    {
        REQUIRE(testArt.getWidth() != 0);
    }

    SECTION("Santa height should be 17")
    {
        REQUIRE(testArt.getHeight() == 17);
    }

    SECTION("Santa height should not be 0")
    {
        REQUIRE(testArt.getHeight() != 0);
    }
}
