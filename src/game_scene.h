/**
 * @file game_scene.h
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "gameloop.h"
#include "menu.h"
#include "player.h"
#include "util.h"
#include <conio.h>

const int user_deck_size{60};
const int bot_deck_size{60};
const int user_hand_size{5};
const int bot_hand_size{5};

class GameScene : public ConsoleUI::Scene
{
private:
    ConsoleUI::UIManager &m_uiManager;
    bool m_needsRedraw = true;
    int m_selectedIndex = 0;
    std::function<void()> m_goBack;
    Game game;
    std::vector<PlayingCard> playlist;
    bool m_staticDrawn = false;

public:
    GameScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack);
    void update() override;
    void init() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
    void setStaticDrawn(bool staticDrawn) override;
    PlayingCard bot(Player &player);
};

#endif
