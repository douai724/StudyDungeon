#include "game_scene.h"

GameScene::GameScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack)
    : m_uiManager(uiManager), m_goBack(goBack)
{
    Player user = Player(100, 100, 5, generateDeck(20));
    Player bot = Player(100, 100, 5, generateDeck(20));

    GameScene::game = setUp(user, bot);
    // auto &menu = m_uiManager.createMenu("playerHand", false);

    // for (int i = 0; i < (int)user.getHand().size(); i++)
    // {
    //     menu.addButton(user.getHand()[i].toString(), [](){});
    // }
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
    m_needsRedraw = false;
    // auto &menu = m_uiManager.getMenu("playerHand");
    // menu.draw(10, 20);
    //m_needsRedraw = false;
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
    }
    else if (key == 27)
    { // Escape key
        m_goBack();
    }

    //m_uiManager.getMenu("playerHand").handleInput();
    // if enter key pressed
    // get the current selected card
    // play the card
    // remove the card from the player's hand
    // the player hand needs to be redrawn
    // nextTurn?
    m_needsRedraw = true;
}
