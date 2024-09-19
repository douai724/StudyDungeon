/**
 * @file game_scene.cpp
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
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

    std::vector<PlayingCard> hand = GameScene::game.p1.getHand();

    window->drawText("Turn: " + std::to_string(GameScene::game.turn), 2, 1);
    window->drawText("You: " + std::to_string(GameScene::game.p1.getHitPoints()), 1, 2);
    window->drawText("Enemy: " + std::to_string(GameScene::game.p2.getHitPoints()), 10, 2);


    if (hand.size() == 0)
    {
        window->drawCenteredText("No cards in hand. Skip turn", 5);
    }
    else
    {
        int cardWidth = size.X / hand.size();
        for (int i = 0; i < (int)hand.size(); i++)
        {
            std::string option = hand[i].toString();
            std::string cardText = "";
            window->drawBox(size.X / hand.size() * i, 3 * size.Y / 5, size.X / 5, 2 * size.Y / 5);
            if (m_selectedIndex == i)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cardText = "+ [" + option + "] + ";
                int padding = cardText.length() < cardWidth ? (cardWidth - cardText.length()) / 2 : 0;
                window->drawText(cardText, size.X / hand.size() * i + padding, 4 * size.Y / 5);

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else
            {
                cardText = " [" + option + "]  ";
                int padding = cardText.length() < cardWidth ? (cardWidth - cardText.length()) / 2 : 0;
                window->drawText(cardText, size.X / hand.size() * i + padding, 4 * size.Y / 5);
            }
        }
    }

    m_needsRedraw = false;
}

void GameScene::handleInput()
{
    int key = _getch();
    if (key == _arrow_prefix) // Arrow key
    {
        key = _getch();
        switch (key)
        {
        case _key_left:
            if (m_selectedIndex > 0)
            {
                m_selectedIndex--;
            }
            break;
        case _key_right: // Down arrow
            if (m_selectedIndex < GameScene::game.p1.getHand().size() - 1)
            {
                m_selectedIndex++;
            }
            break;
        }
    }
    else if (key == _key_enter) // Enter key
    {
        // Player turn
        if (GameScene::game.p1.getHand().size() == 0)
        {
            GameScene::game.turn = 2; // skip turn
        }
        else
        {
            PlayingCard playerCard = GameScene::game.p1.getHand()[m_selectedIndex];
            GameScene::game.p1.removeCard(playerCard);
            GameScene::game.nextTurn(playerCard);
            if (GameScene::game.isGameOver())
            {
                m_goBack();
            }
        }

        // Bot turn
        if (GameScene::game.p2.getHand().size() == 0)
        {
            GameScene::game.turn = 1; // skip turn
        }
        else
        {
            PlayingCard botCard = GameScene::game.p2.getHand()[0];
            GameScene::game.p2.removeCard(botCard);
            GameScene::game.nextTurn(botCard);
            if (GameScene::game.isGameOver())
            {
                m_goBack();
            }
        }


        m_selectedIndex = 0;
    }
    else if (key == _key_esc)
    { // Escape key
        m_goBack();
    }

    m_needsRedraw = true;
}
