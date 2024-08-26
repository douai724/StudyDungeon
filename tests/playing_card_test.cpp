#include <catch2/catch_test_macros.hpp>

#include "card_types.h"
#include "playing_card.h"

TEST_CASE("Retrieve members")
{
    PlayingCard testCard = PlayingCard(1, (enum Type)0, 10);

    SECTION("Get target")
    {
        REQUIRE(testCard.getTarget() == 1);
    }

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
    PlayingCard card1 = PlayingCard(1, (enum Type)0, 15);
    PlayingCard cardRef = card1;
    PlayingCard *cardPtr = &card1;

    PlayingCard card2 = PlayingCard(1, (enum Type)0, 15);

    REQUIRE(card1 == cardRef);
    REQUIRE(card1 == *cardPtr);
    REQUIRE(card1 == card2);
}
