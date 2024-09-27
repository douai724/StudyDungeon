/**
 * @file howto_scene.cpp
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "howto_scene.h"
#include <string>

HowToScene::HowToScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack)
    : m_uiManager(uiManager), m_goBack(goBack)
{
    auto &menu = m_uiManager.createMenu("howto", true); // Horizontal menu
    // menu.addButton("Back", [this]() { m_goBack(); });
    // menu.addButton("Back", [this]() { m_goBack(); });
    menu.addButton("Back", [this]() { m_goBack(); });
}

void HowToScene::update()
{
    // No continuous updates needed for this scene
}


void HowToScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    window->clear();
    window->drawBorder();
    window->drawCenteredText("How to Play", 2);

    std::string howto_text = "How to Play";
    window->drawCenteredText(howto_text, window->getSize().Y / 2 - 2);


    // Draw the menu at the bottom center of the screen
    auto windowSize = window->getSize();
    m_uiManager.getMenu("howto").draw((windowSize.X - 30) / 2, windowSize.Y - 4); // Adjust 30 based on your menu width
}

void HowToScene::handleInput()
{
    m_uiManager.getMenu("howto").handleInput();
}
