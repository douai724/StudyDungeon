#include <catch2/catch_test_macros.hpp>

#include "util.h"

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
