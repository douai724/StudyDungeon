#include "game_scene.h"

GameScene::GameScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack)
    : m_uiManager(uiManager), m_goBack(goBack)
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
    COORD size = window->getSize();


    Game thisGame = GameScene::game;
    Player user = thisGame.p1;
    std::vector<PlayingCard> hand = user.getHand();

    window->drawText("Turn: " + std::to_string(game.turn), 2, 1);
    window->drawText("You: " + std::to_string(user.getHitPoints()), 1, 2);
    window->drawText("Enemy: " + std::to_string(game.p2.getHitPoints()), 10, 2);


    if (hand.size() == 0)
    {
        window->drawCenteredText("No cards in hand. Skip turn", 5);
    }
    else
    {
        for (int i = 0; i < (int)hand.size(); i++)
        {
            std::string border = " "; //= m_selectedIndex == i ? "+" : " ";
            std::string option = hand[i].toString();
            if (m_selectedIndex == i)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                window->drawCenteredText("+ [" + option + "] + ", i * 2);

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else
            {
                window->drawCenteredText(" [" + option + "] ", i * 2);
            }
        }
    }

    m_needsRedraw = false;
}

void GameScene::handleInput()
{
    int key = _getch();
    if (key == 224) // Arrow key
    {
        key = _getch();
        switch (key)
        {
        case 72: // Up arrow
            if (m_selectedIndex > 0)
            {
                m_selectedIndex--;
            }
            break;
        case 80: // Down arrow
            if (m_selectedIndex < GameScene::game.p1.getHand().size() - 1)
            {
                m_selectedIndex++;
            }
            break;
        }
    }
    else if (key == 13) // Enter key
    {
        // Player turn
        PlayingCard playerCard = GameScene::game.p1.getHand()[m_selectedIndex];
        GameScene::game.p1.removeCard(playerCard);
        GameScene::game.nextTurn(playerCard);

        // Bot turn
        PlayingCard botCard = GameScene::game.p2.getHand()[0];
        GameScene::game.p2.removeCard(botCard);
        GameScene::game.nextTurn(botCard);
        m_selectedIndex = 0;
    }
    else if (key == 27)
    { // Escape key
        m_goBack();
    }

    m_needsRedraw = true;
}
