#include "game_scene.h"

GameScene::GameScene(ConsoleUI::UIManager &uiManager) : m_uiManager(uiManager)
{
    m_uiManager.clearAllMenus();
}

void GameScene::update()
{
    // TO DO
}

void GameScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    window->clear();
    window->drawCenteredText("This is somet text", 2);
}

void GameScene::handleInput()
{
    // TO DO
}
