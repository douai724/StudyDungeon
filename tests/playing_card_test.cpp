#include <catch2/catch_test_macros.hpp>

#include "card_types.h"
#include "playing_card.h"

TEST_CASE("Retrieve members")
{
    PlayingCard testCard = PlayingCard((enum Type)0, 10);

    SECTION("Get value")
    {
        REQUIRE(testCard.getValue() == 10);
    }

    SECTION("Get type")
    {
        REQUIRE(testCard.getType() == (enum Type)0);
    }
}

TEST_CASE("Equality is correct")
{
    PlayingCard card1 = PlayingCard((enum Type)0, 15);

    SECTION("Cards are equal")
    {
        PlayingCard card2 = PlayingCard((enum Type)0, 15);

        REQUIRE(card1 == card2);
    }

    SECTION("Cards are different types")
    {
        PlayingCard card2 = PlayingCard((enum Type)1, 15);

        REQUIRE(card1 != card2);
    }

    SECTION("Cards have different values")
    {
        PlayingCard card2 = PlayingCard((enum Type)0, 20);

        REQUIRE(card1 != card2);
    }

    SECTION("Cards have different types and values")
    {
        PlayingCard card2 = PlayingCard((enum Type)1, 20);

        REQUIRE(card1 != card2);
    }
}
