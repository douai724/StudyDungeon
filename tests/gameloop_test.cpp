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
        REQUIRE(testGame.getWinner() == 2);
    }

    SECTION("Player 2 drops to 0 hp")
    {
        REQUIRE(testGame.isGameOver() == false);

        testGame.p2.setHitPoints(0);

        REQUIRE(testGame.isGameOver() == true);
        REQUIRE(testGame.getWinner() == 1);
    }

    SECTION("Players are out of cards")
    {
        testGame.p1.drawCard();
        testGame.p2.drawCard();
        REQUIRE(testGame.isGameOver() == true);
    }

    SECTION("Player 1 is out of cards")
    {
        testGame.p1.drawCard();
        REQUIRE(testGame.isGameOver() == true);
        REQUIRE(testGame.getWinner() == 2);
    }

    SECTION("Player 2 is out of cards")
    {
        testGame.p2.drawCard();
        REQUIRE(testGame.isGameOver() == true);
        REQUIRE(testGame.getWinner() == 1);
    }
}

TEST_CASE("CARD EFFECTS")
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

    SECTION("Swap hand")
    {
    }

    SECTION("Damage")
    {

        PlayingCard damage_card1 = PlayingCard((enum Type)0, 5);
        PlayingCard damage_card2 = PlayingCard((enum Type)0, 10);
        // turn 1 effect should apply to p2
        testGame.turn = 1;
        testGame.damageEffect(damage_card1);
        REQUIRE(testGame.p1.getHitPoints() == 100);
        REQUIRE(testGame.p2.getHitPoints() == 95);
        // turn 2 effect should apply to p1
        testGame.turn = 2;
        testGame.damageEffect(damage_card2);
        REQUIRE(testGame.p1.getHitPoints() == 90);
        REQUIRE(testGame.p2.getHitPoints() == 95);
    }


    SECTION("Heal")
    {
        PlayingCard heal_card1 = PlayingCard((enum Type)1, 10);
        PlayingCard heal_card2 = PlayingCard((enum Type)1, 3);
        // turn 1 effects should apply to p1
        testGame.p1.setHitPoints(90);
        testGame.p2.setHitPoints(95);
        testGame.turn = 1;
        testGame.healEffect(heal_card1);
        std::cout << "p2 hp: " << std::to_string(testGame.p2.getHitPoints()) << std::endl;
        REQUIRE(testGame.p1.getHitPoints() == 100);
        REQUIRE(testGame.p2.getHitPoints() == 95);
        // turn != 1 effects should apply to p2
        testGame.turn = 2;
        testGame.healEffect(heal_card2);
        REQUIRE(testGame.p1.getHitPoints() == 100);
        REQUIRE(testGame.p2.getHitPoints() == 98);
    }
}

TEST_CASE("Constructor")
{
    SECTION("default constructor members can be accessed")
    {
        Game testGame{};

        REQUIRE_NOTHROW(testGame.p1);

        REQUIRE_NOTHROW(testGame.p2);

        REQUIRE_NOTHROW(testGame.turn);
    }
}

TEST_CASE("Switch turn in game")
{
    Game testGame{};

    SECTION("First turn is player 1's")
    {
        REQUIRE(testGame.turn == 1);
    }

    SECTION("Swap to player 2's turn")
    {
        testGame.switchTurn();
        REQUIRE(testGame.turn == 2);
    }

    SECTION("Swap to player 1's turn")
    {
        testGame.switchTurn();
        testGame.switchTurn();
        REQUIRE(testGame.turn == 1);
    }
}

TEST_CASE("Switch hands")
{
    std::vector<PlayingCard> deck1;
    std::vector<PlayingCard> deck2;

    PlayingCard testCard1 = PlayingCard((enum Type)0, 10);
    PlayingCard testCard2 = PlayingCard((enum Type)0, 20);

    deck1.push_back(testCard1);
    deck2.push_back(testCard2);

    Game testGame{};
    testGame.p1.setHand(deck1);
    testGame.p2.setHand(deck2);
    // check the decks start off correct
    REQUIRE(testGame.p1.getHand().at(0) == deck1.at(0));
    REQUIRE(testGame.p2.getHand().at(0) == deck2.at(0));
    // switch hands and check order is now reversed
    testGame.swapHandEffect();
    REQUIRE(testGame.p1.getHand().at(0) == deck2.at(0));
    REQUIRE(testGame.p2.getHand().at(0) == deck1.at(0));
    // switch back and check in original order
    testGame.swapHandEffect();
    REQUIRE(testGame.p1.getHand().at(0) == deck1.at(0));
    REQUIRE(testGame.p2.getHand().at(0) == deck2.at(0));
}

TEST_CASE("Deck generated is correct size")
{
    int n_cards{13};
    std::vector<PlayingCard> deck = generateDeck(n_cards);
    REQUIRE(deck.size() == n_cards);
}

TEST_CASE("Next turn")
{

    std::vector<PlayingCard> deck1;
    std::vector<PlayingCard> deck2;


    for (int i = 1; i <= 5; i++)
    {
        PlayingCard testCard1 = PlayingCard((enum Type)0, i);
        PlayingCard testCard2 = PlayingCard((enum Type)0, 10 + i);
        deck1.push_back(testCard1);
        deck2.push_back(testCard2);
    }


    Game testGame{};
    testGame.p1.setDeck(deck1);
    testGame.p2.setDeck(deck2);

    SECTION("P1 turn")
    {
        REQUIRE(testGame.turn == 1);
        testGame.p1.drawCard();
        PlayingCard playerCard = testGame.p1.getHand()[0];
        testGame.p1.removeCard(playerCard);
        REQUIRE(testGame.p1.getDeck().size() == 4);
        REQUIRE(testGame.p2.getHitPoints() == 100);
        testGame.nextTurn(playerCard);
        // check applies effect
        REQUIRE(testGame.p2.getHitPoints() == 99);
        // check draws card to hand
        REQUIRE(testGame.p1.getHandSize() == 5);
        REQUIRE(testGame.p1.getDeck().size() == 3);
        // REQUIRE(testGame.p1.getHitPoints() == 90);
        // check turn switches
        REQUIRE(testGame.turn == 2);
    }

    SECTION("P2 turn")
    {
        testGame.turn = 2;
        REQUIRE(testGame.turn == 2);
        testGame.p2.drawCard();
        PlayingCard playerCard = testGame.p2.getHand()[0];
        testGame.p1.removeCard(playerCard);
        REQUIRE(testGame.p2.getDeck().size() == 4);
        REQUIRE(testGame.p1.getHitPoints() == 100);
        testGame.nextTurn(playerCard);
        // check applies effect
        REQUIRE(testGame.p1.getHitPoints() == 89);
        // check draws card to hand
        REQUIRE(testGame.p2.getHandSize() == 5);
        REQUIRE(testGame.p2.getDeck().size() == 3);
        // REQUIRE(testGame.p1.getHitPoints() == 90);
        // check turn switches
        REQUIRE(testGame.turn == 1);
    }
}
