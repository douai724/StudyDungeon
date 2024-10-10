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


TEST_CASE("ANSI art")
{

    ConsoleUI::ConsoleWindow testWindow{};
    std::vector<int> line1{24, 56, 24};
    std::vector<int> line2{50, 50, 50};
    std::vector<int> line3{230, 10, 230};

    std::vector<std::vector<int>> testANSI{};
    testANSI.push_back(line1);
    testANSI.push_back(line2);
    testANSI.push_back(line3);

    ConsoleUI::ANSIArt testArt(testANSI, "testANSI", 12, 3);

    SECTION("Get ANSI art name")
    {
        REQUIRE(testArt.getName() == "testANSI");
    }

    SECTION("Get ANSI art x position")
    {
        REQUIRE(testArt.getX() == 12);
    }

    SECTION("Get ANSI art y position")
    {
        REQUIRE(testArt.getY() == 3);
    }

    SECTION("Width should be 3")
    {
        REQUIRE(testArt.getWidth() == 3);
    }

    SECTION("Width should not be 0")
    {
        REQUIRE(testArt.getWidth() != 0);
    }

    SECTION("Height should be 3")
    {
        REQUIRE(testArt.getHeight() == 3);
    }

    SECTION("Height should not be 0")
    {
        REQUIRE(testArt.getHeight() != 0);
    }

    SECTION("Get ANSI codes")
    {
        REQUIRE(testArt.getCodes() == testANSI);
    }

    SECTION("ANSI to string")
    {
        std::string testString = key::ESC + "[48;5;24m  " + key::ESC + "[0m" + key::ESC + "[48;5;56m  " + key::ESC +
                                 "[0m" + key::ESC + "[48;5;24m  " + key::ESC + "[0m\n" + key::ESC + "[48;5;50m  " +
                                 key::ESC + "[0m" + key::ESC + "[48;5;50m  " + key::ESC + "[0m" + key::ESC +
                                 "[48;5;50m  " + key::ESC + "[0m\n" + key::ESC + "[48;5;230m  " + key::ESC + "[0m" +
                                 key::ESC + "[48;5;10m  " + key::ESC + "[0m" + key::ESC + "[48;5;230m  " + key::ESC +
                                 "[0m\n";

        REQUIRE(testArt.toString() == testString);
    }

    SECTION("Set ANSI art position")
    {
        REQUIRE(testArt.getX() == 12);
        REQUIRE(testArt.getY() == 3);

        testArt.setPosition(5, 17);

        REQUIRE(testArt.getX() == 5);
        REQUIRE(testArt.getY() == 17);
    }
}
