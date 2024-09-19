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
