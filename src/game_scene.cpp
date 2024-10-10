/**
 * @file game_scene.cpp
 * @author Green Alligators
 * @brief Classes and functions for the card duel game
 * @version 1.0.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "game_scene.h"

GameScene::GameScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack)
    : m_uiManager(uiManager), m_goBack(goBack)
{
    Player user = Player(100, 100, user_hand_size, generateDeck(user_deck_size));
    Player bot = Player(100, 100, bot_hand_size, generateDeck(bot_deck_size));

    GameScene::game = Game(user, bot);
}

void GameScene::update()
{
}

void GameScene::init()
{
    Player user = Player(100, 100, user_hand_size, generateDeck(user_deck_size));
    Player bot = Player(100, 100, bot_hand_size, generateDeck(bot_deck_size));

    GameScene::game = Game(user, bot);

    GameScene::playlist.clear();
}

void GameScene::setStaticDrawn(bool staticDrawn)
{

    m_staticDrawn = staticDrawn;
}

void GameScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{

    if (!m_staticDrawn)
    {
        window->clear();
        window->drawBorder();
        m_staticDrawn = true;
        window->drawANSIArt("frog", 60, -5);
    }

    if (!m_needsRedraw)
    {
        return;
    }
    COORD size = window->getSize();

    std::vector<PlayingCard> hand = GameScene::game.p1.getHand();

    window->drawText("YOU", 2, 2);
    window->drawText("DECK SIZE:" + std::to_string(GameScene::game.p1.getDeck().size()), 2, 4);
    window->drawText("HP: " + std::to_string(GameScene::game.p1.getHitPoints()) + "/" +
                         std::to_string(GameScene::game.p1.getMaxHitPoints()),
                     2,
                     6);
    // for (int i = 0; i < 5; i++)
    // {
    //     float calc = GameScene::game.p1.getHitPoints() / (float)GameScene::game.p1.getMaxHitPoints() * 5;
    //     if (calc > i)
    //     {
    //         window->drawANSIArt("heart", 16 * i + 1, 8);
    //     }
    //     else
    //     {
    //         window->drawANSIArt("heartEmpty", 16 * i + 1, 8);
    //     }
    // }


    window->drawText("ENEMY", size.X - 7, 2);
    window->drawText("DECK SIZE:" + std::to_string(GameScene::game.p2.getDeck().size()), size.X - 14, 4);
    window->drawText("HP: " + std::to_string(GameScene::game.p2.getHitPoints()) + "/" +
                         std::to_string(GameScene::game.p2.getMaxHitPoints()),
                     size.X - 13,
                     6);
    // for (int i = 0; i < 5; i++)
    // {
    //     float calc = GameScene::game.p2.getHitPoints() / (float)GameScene::game.p2.getMaxHitPoints() * 5;
    //     if (calc > i)
    //     {
    //         window->drawANSIArt("heart", 16 * i + 1 + size.X / 2, 8);
    //     }
    //     else
    //     {
    //         window->drawANSIArt("heartEmpty", 16 * i + 1 + size.X / 2, 8);
    //     }
    // }

    if (GameScene::playlist.size() > 1)
    {
        window->drawText("You played: " + playlist[playlist.size() - 2].toString(), 2, 15);
        window->drawText("Enemy played: " + playlist[playlist.size() - 1].toString(), 2, 16);
    }
    int hand_size_int = static_cast<int>(hand.size());
    if (hand_size_int == 0)
    {
        window->drawText("No cards in hand. Skip turn", 2, 5);
    }
    else
    {
        int cardWidth = (int)window->getANSIArtByName("frog")->getWidth();

        for (int i = 0; i < hand_size_int; i++)
        {

            std::string colour = "";

            switch (hand[i].getType())
            {
            case 0:
                colour = key::ESC + "[31m";
                break;
            case 1:
                colour = key::ESC + "[32m";
                break;
            default:
                colour = "";
            }

            std::string option = hand[i].toString();
            std::string cardText = " [" + colour + option + key::ESC + "[0m" + "]";

            int padding = option.length() + 2 < cardWidth ? (cardWidth - option.length() + 2) / 2 : 4;

            if (m_selectedIndex == i)
            {

                window->drawANSIArt("cardSelected", size.X / hand_size_int * i + 2, 3 * size.Y / 5 - 2);
            }
            else
            {
                window->drawANSIArt("card", size.X / hand_size_int * i + 2, 3 * size.Y / 5 - 2);
            }

            window->drawWrappedText(cardText,
                                    size.X / hand_size_int * i + padding,
                                    4 * size.Y / 5,
                                    size.X / 5 + colour.length());
        }
    }

    m_needsRedraw = false;
}

void GameScene::handleInput()
{
    int key = _getch();
    if (key == key::arrow_prefix || key == key::numlock) // Arrow key
    {
        key = _getch();
        switch (key)
        {
        case key::key_left:
            if (m_selectedIndex > 0)
            {
                m_selectedIndex--;
            }
            break;
        case key::key_right: // Down arrow
            if (m_selectedIndex < GameScene::game.p1.getHand().size() - 1)
            {
                m_selectedIndex++;
            }
            break;
        }
    }
    else if (key == key::key_enter) // Enter key
    {
        // Player turn
        if (GameScene::game.p1.getHand().size() == 0)
        {
            GameScene::game.turn = 2; // skip turn
        }
        if (!GameScene::game.isGameOver())
        {
            PlayingCard playerCard = GameScene::game.p1.getHand()[m_selectedIndex];
            GameScene::game.p1.removeCard(playerCard);
            GameScene::game.nextTurn(playerCard);
            GameScene::playlist.push_back(playerCard);
            if (GameScene::game.isGameOver())
            {
                short winner = GameScene::game.getWinner();
                std::string winText = "";
                if (winner == 1)
                {
                    winText = "You won! :)";
                }
                else
                {
                    winText = "You lost :(";
                }
                std::shared_ptr<ConsoleUI::ConsoleWindow> window = m_uiManager.getWindow();
                window->clear();
                window->drawBorder();
                window->drawCenteredText(winText, window->getSize().Y / 2);
                Sleep(1000);
                m_goBack();
            }
        }

        // Bot turn
        if (GameScene::game.p2.getHand().size() == 0)
        {
            GameScene::game.turn = 1; // skip turn
        }
        if (!GameScene::game.isGameOver())
        {
            PlayingCard botCard = GameScene::game.p2.getHand()[0];
            GameScene::game.p2.removeCard(botCard);
            GameScene::game.nextTurn(botCard);
            GameScene::playlist.push_back(botCard);
            if (GameScene::game.isGameOver())
            {
                short winner = GameScene::game.getWinner();
                std::string winText = "";
                if (winner == 1)
                {
                    winText = "You won! :)";
                }
                else
                {
                    winText = "You lost :(";
                }
                std::shared_ptr<ConsoleUI::ConsoleWindow> window = m_uiManager.getWindow();
                window->clear();
                window->drawBorder();
                window->drawCenteredText(winText, window->getSize().Y / 2);
                Sleep(1000);
                m_goBack();
            }
        }

        m_selectedIndex = 0;
        m_needsRedraw = true;
        m_staticDrawn = false;
    }
    else if (key == key::key_esc)
    { // Escape key
        m_goBack();
    }

    m_needsRedraw = true;
}
