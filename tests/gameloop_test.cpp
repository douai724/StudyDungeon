#include <catch2/catch_test_macros.hpp>

#include "card_types.h"
#include "gameloop.h"
#include "player.h"
#include "playing_card.h"
#include <vector>

TEST_CASE("Win condition")
{
    Player p1 = Player(100, 100, 5, std::vector<PlayingCard>());
    Player p2 = Player(100, 100, 5, std::vector<PlayingCard>());

    PlayingCard testCard = PlayingCard((enum Type)0, 10);

    p1.addCard(testCard);
    p2.addCard(testCard);

    Game testGame = Game(p1, p2);

    SECTION("Player 1 drops to 0 hp")
    {
        REQUIRE(testGame.isGameOver() == false);

        p1.setHitPoints(0);

        REQUIRE(testGame.isGameOver() == true);
    }

    SECTION("Player 2 drops to 0 hp")
    {
        REQUIRE(testGame.isGameOver() == false);

        p2.setHitPoints(0);

        REQUIRE(testGame.isGameOver() == true);
    }

    SECTION("Players are out of cards")
    {
        p1.removeCard(testCard);
        p2.removeCard(testCard);
        REQUIRE(testGame.isGameOver() == true);
    }
}
