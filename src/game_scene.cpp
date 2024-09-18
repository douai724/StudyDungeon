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
    // get and show the player's hand as a menu
    // Player *user = GameScene::game.p1;
    //std::string testStr = GameScene::game.p1->toString();
    //window->drawText(GameScene::game.printPlayers(), 10, 10);
    Game thisGame = GameScene::game;
    //Player user = *thisGame.p1;
    //Player* other = thisGame.p1;
    Player back = thisGame.p1;


    // ===========================
    // The player objects are destroyed somewhere
    // Maybe because nothing references them
    // Or they are overwritten
    // I don't really know
    //


    // std::string test = user.toString();
    // std::string otherTest = other->toString();
    // std::string backTest = back->toString();
    std::cout << "Hello" << std::endl;
    std::cout << back.toString() << std::endl;
    //   std::cout << test << " " << otherTest << " " << backTest << std::endl;
    pause();
    //window->drawCenteredText(std::to_string(GameScene::game.turn), 10);
    // std::vector<PlayingCard> hand = user->getHand();

    //window->drawText("Hello", 10, 10);
    // auto &menu = m_uiManager.createMenu("playerHand", false);
    // for(int i = 0; i < (int)hand.size(); i++){
    //     menu.addButton(hand[i].toString(), [](){});
    // }
    // wait for player to press enter on a card
    // once the card is selected, play the next turn of the game.
    //  menu.draw(10, 20);
    m_needsRedraw = false;
}

void GameScene::handleInput()
{
    // TO DO
}
