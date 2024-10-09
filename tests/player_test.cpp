#include <catch2/catch_test_macros.hpp>

#include "player.h"
#include "playing_card.h"
#include <vector>

TEST_CASE("Hit points are updated and retrieved")
{
    Player testPlayer = Player(100, 100, 5, std::vector<PlayingCard>());

    SECTION("Retrieving hit points")
    {
        REQUIRE(testPlayer.getHitPoints() == 100);
    }

    SECTION("Updating hit points with positive int")
    {
        testPlayer.setHitPoints(50);
        REQUIRE(testPlayer.getHitPoints() == 50);
    }

    SECTION("Updating hit points with negative int")
    {
        testPlayer.setHitPoints(-100);
        REQUIRE(testPlayer.getHitPoints() == -100);
    }
}

TEST_CASE("MAXIMUM hit points are updated and retrieved")
{
    Player testPlayer = Player(100, 100, 5, std::vector<PlayingCard>());

    SECTION("Retrieving MAXIMUM hit points")
    {
        REQUIRE(testPlayer.getMaxHitPoints() == 100);
    }

    SECTION("Updating MAXIMUM hit points with positive int")
    {
        testPlayer.setMaxHitPoints(50);
        REQUIRE(testPlayer.getMaxHitPoints() == 50);
    }

    SECTION("MAXIMUM hit points that are negative are not accepted")
    {
        testPlayer.setMaxHitPoints(-1);
        REQUIRE(testPlayer.getMaxHitPoints() == 100);
    }
}

TEST_CASE("Player hand is updated and retrieved")
{
    // set up cards
    PlayingCard card1 = PlayingCard((enum Type)0, 5);
    PlayingCard card2 = PlayingCard((enum Type)0, 10);

    // set up hand
    std::vector<PlayingCard> testHand;
    testHand.push_back(card1);
    testHand.push_back(card2);

    // set up player with empty hand
    Player testPlayer = Player(100, 100, 5, std::vector<PlayingCard>());

    REQUIRE(testPlayer.getHand().size() == 0);

    SECTION("Update and retrieve hand")
    {
        testPlayer.setHand(testHand);

        REQUIRE(testPlayer.getHand()[0] == card1);
        REQUIRE(testPlayer.getHand()[1] == card2);
        REQUIRE(testPlayer.getHand().size() == (int)2);
    }

    SECTION("Remove a card from hand")
    {
        testPlayer.setHand(testHand);
        testPlayer.removeCard(card1);

        REQUIRE(testPlayer.getHand().size() == (int)1);
        REQUIRE(testPlayer.getHand()[0] == card2);
    }

    SECTION("Add card to hand")
    {
        PlayingCard card3 = PlayingCard((enum Type)0, 25);
        testPlayer.setHand(testHand);
        testPlayer.addCard(card3);

        REQUIRE(testPlayer.getHand().size() == (int)3);
        REQUIRE(testPlayer.getHand()[0] == card1);
        REQUIRE(testPlayer.getHand()[1] == card2);
        REQUIRE(testPlayer.getHand()[2] == card3);
    }

    SECTION("Get the card that corresponds with the index")
    {
        testPlayer.setHand(testHand);

        // within bounds
        REQUIRE_NOTHROW(testPlayer.getCard(0) == card1);
        REQUIRE_NOTHROW(testPlayer.getCard(1) == card2);

        // out of bounds
        REQUIRE_THROWS(testPlayer.getCard(-1));
        REQUIRE_THROWS(testPlayer.getCard(3));
    }
}

TEST_CASE("Player deck is updated and retrieved")
{
    // set up cards
    PlayingCard card1 = PlayingCard((enum Type)0, 5);
    PlayingCard card2 = PlayingCard((enum Type)0, 10);

    // set up deck
    std::vector<PlayingCard> testDeck;
    testDeck.push_back(card1);
    testDeck.push_back(card2);

    // set up player with empty deck
    Player testPlayer = Player(100, 100, 5, std::vector<PlayingCard>());

    REQUIRE(testPlayer.getDeck().size() == 0);

    SECTION("Update and retrieve deck")
    {
        testPlayer.setDeck(testDeck);

        REQUIRE(testPlayer.getDeck()[0] == card1);
        REQUIRE(testPlayer.getDeck()[1] == card2);
        REQUIRE(testPlayer.getDeck().size() == (int)2);
    }
}

TEST_CASE("Effects are applied")
{
    Player testPlayer = Player(100, 100, 5, std::vector<PlayingCard>());

    REQUIRE(testPlayer.getHitPoints() == 100);

    SECTION("Positive value damage is applied")
    {
        testPlayer.damage(10);

        REQUIRE(testPlayer.getHitPoints() == 90);

        testPlayer.damage(15);

        REQUIRE(testPlayer.getHitPoints() == 75);
    }

    SECTION("Negative value damage is not applied")
    {
        testPlayer.damage(-10);

        REQUIRE(testPlayer.getHitPoints() == 100);
    }

    SECTION("Positive value healing is applied")
    {
        testPlayer.setHitPoints(50);

        testPlayer.heal(10);

        REQUIRE(testPlayer.getHitPoints() == 60);

        testPlayer.heal(15);

        REQUIRE(testPlayer.getHitPoints() == 75);
    }

    SECTION("Negative value healing is not applied")
    {
        testPlayer.setHitPoints(50);

        testPlayer.heal(-10);

        REQUIRE(testPlayer.getHitPoints() == 50);
    }

    SECTION("Healing amount surpasses max hit points")
    {
        testPlayer.setHitPoints(90);

        testPlayer.heal(20);

        REQUIRE(testPlayer.getHitPoints() == 100);
    }

    SECTION("Healing at full hit points")
    {
        testPlayer.heal(10);

        REQUIRE(testPlayer.getHitPoints() == 100);
    }
}

TEST_CASE("Player default constructor")
{
    Player testPlayer{};
    SECTION("members are correctly initialized to defaults")
    {
        REQUIRE(testPlayer.getMaxHitPoints() == 100);
        REQUIRE(testPlayer.getHitPoints() == 100);
        REQUIRE(testPlayer.getHandSize() == 5);
        REQUIRE(testPlayer.getDeck().size() == 0);
    }
}

TEST_CASE("Player hand size is updated and retrieved")
{
    Player testPlayer = Player(100, 100, 1, std::vector<PlayingCard>());

    SECTION("Retrieve hand size")
    {
        REQUIRE(testPlayer.getHandSize() == 1);
    }

    SECTION("Update hand size")
    {
        testPlayer.setHandSize(2);
        REQUIRE(testPlayer.getHandSize() == 2);
    }
}
