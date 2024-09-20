#include <catch2/catch_test_macros.hpp>

#include "card_types.h"
#include "gameloop.h"
#include "player.h"
#include "playing_card.h"
#include <vector>

TEST_CASE("Win condition")
{
    std::vector<PlayingCard> deck1;
    std::vector<PlayingCard> deck2;

    PlayingCard testCard = PlayingCard((enum Type)0, 10);

    deck1.push_back(testCard);
    deck1.push_back(testCard);

    deck2.push_back(testCard);
    deck2.push_back(testCard);

    Player p1 = Player(100, 100, 1, deck1);
    Player p2 = Player(100, 100, 1, deck2);

    Game testGame = Game(p1, p2);

    SECTION("Player 1 drops to 0 hp")
    {
        REQUIRE(testGame.isGameOver() == false);

        testGame.p1.setHitPoints(0);

        REQUIRE(testGame.isGameOver() == true);
    }

    SECTION("Player 2 drops to 0 hp")
    {
        REQUIRE(testGame.isGameOver() == false);

        testGame.p2.setHitPoints(0);

        REQUIRE(testGame.isGameOver() == true);
    }

    SECTION("Players are out of cards")
    {
        testGame.p1.drawCard();
        testGame.p2.drawCard();
        REQUIRE(testGame.isGameOver() == true);
    }
}

TEST_CASE("Is player winner?")
{
    std::vector<PlayingCard> deck1;
    std::vector<PlayingCard> deck2;

    PlayingCard testCard = PlayingCard((enum Type)0, 10);

    deck1.push_back(testCard);
    deck1.push_back(testCard);

    deck2.push_back(testCard);
    deck2.push_back(testCard);

    Player p1 = Player(100, 100, 1, deck1);
    Player p2 = Player(100, 100, 1, deck2);

    Game testGame = Game(p1, p2);
    SECTION("Player 1 turn")
    {
        testGame.turn = 1;
        SECTION("Player 1 runs out of cards")
        {
            testGame.p1.drawCard();
            REQUIRE(testGame.isWinner() == false);
            REQUIRE(testGame.p1.getDeck().size() == 0);
        }

        SECTION("Player 1 has 0 hit points")
        {
            testGame.p1.setHitPoints(0);
            REQUIRE(testGame.isWinner() == false);
        }

        SECTION("Enemy runs out of cards")
        {
            testGame.p2.drawCard();
            REQUIRE(testGame.isWinner() == true);
        }

        SECTION("Enemy has 0 hit points")
        {
            testGame.p2.setHitPoints(0);
            REQUIRE(testGame.isWinner() == true);
        }
    }


    SECTION("Player 2 turn")
    {
        testGame.turn = 2;
        SECTION("Player 2 runs out of cards")
        {
            testGame.p2.drawCard();
            REQUIRE(testGame.isWinner() == false);
            REQUIRE(testGame.p2.getDeck().size() == 0);
        }

        SECTION("Player 2 has 0 hit points")
        {
            testGame.p2.setHitPoints(0);
            REQUIRE(testGame.isWinner() == false);
        }

        SECTION("Enemy runs out of cards")
        {
            testGame.p1.drawCard();
            REQUIRE(testGame.isWinner() == true);
        }

        SECTION("Enemy has 0 hit points")
        {
            testGame.p1.setHitPoints(0);
            REQUIRE(testGame.isWinner() == true);
        }
    }
}
