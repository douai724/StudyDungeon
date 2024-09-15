#include "game_scene.h"

GameScene::GameScene(ConsoleUI::UIManager &uiManager) : m_uiManager(uiManager)
{
    //m_uiManager.clearAllMenus();
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
    window->drawCenteredText("This is some OTHER text", 2);

    m_needsRedraw = false;
}

void GameScene::handleInput()
{
    // TO DO
}
