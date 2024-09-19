#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "gameloop.h"
#include "menu.h"
#include "player.h"
#include <conio.h>

class GameScene : public ConsoleUI::Scene
{
private:
    ConsoleUI::UIManager &m_uiManager;
    bool m_needsRedraw = true;
    int m_selectedIndex = 0;
    std::function<void()> m_goBack;
    Game game;


public:
    GameScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack);
    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
};

#endif
