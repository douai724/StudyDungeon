#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "menu.h"

class GameScene : public ConsoleUI::Scene
{
private:
    ConsoleUI::UIManager &m_uiManager;

public:
    GameScene(ConsoleUI::UIManager &uiManager);
    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;
};

#endif
