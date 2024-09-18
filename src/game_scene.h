#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "gameloop.h"
#include "menu.h"
#include "player.h"

class GameScene : public ConsoleUI::Scene
{
private:
    ConsoleUI::UIManager &m_uiManager;
    bool m_needsRedraw = true;
    Game game;

public:
    GameScene(ConsoleUI::UIManager &uiManager);
    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
};

#endif
