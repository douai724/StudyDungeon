#include <catch2/catch_test_macros.hpp>

#include "util.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

TEST_CASE("Filename validity checker")
{
    REQUIRE(isValidDeckFileName("valid"));
    REQUIRE(isValidDeckFileName("Valid"));
    REQUIRE(isValidDeckFileName("0Valid"));
    REQUIRE(isValidDeckFileName("Valid0"));
    REQUIRE(isValidDeckFileName("9Valid"));
    REQUIRE(isValidDeckFileName("Valid9"));
    REQUIRE(isValidDeckFileName("") == false);
    REQUIRE_FALSE(isValidDeckFileName("file.name"));
    REQUIRE(isValidDeckFileName("01234567890123456789"));        // 20 character
    REQUIRE_FALSE(isValidDeckFileName("012345678901234567890")); // 21 characters
}

TEST_CASE("Timer")
{
    auto start_time = std::chrono::steady_clock::now();
    int duration_secs{2};
    REQUIRE_FALSE(timeComplete(start_time, duration_secs));
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    REQUIRE(timeComplete(start_time, duration_secs));
}


TEST_CASE("yesNoPrompt ")
{
    SECTION("handles valid inputs")
    {
        // Redirect cin
        std::istringstream in("Y\n");
        std::cin.rdbuf(in.rdbuf()); // redirect std::cin to in
        REQUIRE(yesNoPrompt() == true);

        // Redirect cin for "N"
        std::istringstream in2("N\n");
        std::cin.rdbuf(in2.rdbuf()); // redirect std::cin to in2
        REQUIRE(yesNoPrompt() == false);
    }

    SECTION("handles invalid inputs before valid input")
    {
        // Test invalid input followed by valid "Y"
        std::istringstream in("abc\nY\n");
        std::cin.rdbuf(in.rdbuf());
        REQUIRE(yesNoPrompt() == true);

        // Test invalid input followed by valid "N"
        std::istringstream in2("123\nN\n");
        std::cin.rdbuf(in2.rdbuf());
        REQUIRE(yesNoPrompt() == false);
    }
}

TEST_CASE("Convert ASCII art to lines")
{
    std::string testArt = R"(---
| |
---)";

    std::string line1 = "---";
    std::string line2 = "| |";
    std::string line3 = "---";

    std::vector<std::string> outputLines = convertAsciiArtToLines(testArt);

    REQUIRE(outputLines[0] == line1);
    REQUIRE(outputLines[1] == line2);
    REQUIRE(outputLines[2] == line3);
}
