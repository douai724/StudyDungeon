#include "game_scene.h"

GameScene::GameScene(ConsoleUI::UIManager &uiManager) : m_uiManager(uiManager)
{
    Player user = Player(100, 100, 5, generateDeck(20));
    Player bot = Player(100, 100, 5, generateDeck(20));

    GameScene::game = setUp(user, bot);
}

void GameScene::update()
{
    // TO DO
}

void GameScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    if (!m_needsRedraw)
    {
        return;
    }
    window->clear();
    window->drawBorder();

    Game thisGame = GameScene::game;
    Player user = thisGame.p1;

    std::vector<PlayingCard> hand = user.getHand();

    auto &menu = m_uiManager.createMenu("playerHand", false);
    for (int i = 0; i < (int)hand.size(); i++)
    {
        menu.addButton(hand[i].toString(), []() {});
    }

    // wait for player to press enter on a card
    // once the card is selected, play the next turn of the game.
    menu.draw(10, 20);
    m_needsRedraw = false;
}

void GameScene::handleInput()
{
    // TO DO
}
