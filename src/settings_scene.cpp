/**
 * @file settings_scene.cpp
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "settings_scene.h"
#include <string>

SettingsScene::SettingsScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack)

    : m_uiManager(uiManager), m_goBack(goBack), m_card_limit(15), m_study_min(25)
{
    auto &menu = m_uiManager.createMenu("settings", true); // Horizontal menu
    menu.addButton("Increment Cards", [this]() { incrementCards(); });
    menu.addButton("Decrement Cards", [this]() { decrementCards(); });
    menu.addButton("Increment Time", [this]() { incrementStudyMins(); });
    menu.addButton("Decrement Time", [this]() { decrementStudyMins(); });
    menu.addButton("Defaults", [this]() { resetDefault(); });
    menu.addButton("Back", [this]() { m_goBack(); });
}

void SettingsScene::init()
{
    // No need for init
}

void SettingsScene::update()
{
    // No continuous updates needed for this scene
}


void SettingsScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{

    window->clear();
    window->drawBorder();
    window->drawCenteredText("Settings", 2);
    window->drawCenteredText("Number of Cards per Round: " + std::to_string(m_card_limit), 5);
    window->drawCenteredText("Study time (mins): " + std::to_string(m_study_min), 6);


    // window->drawCenteredText("Playing the Game", window->getSize().Y / 2 - 2);


    // Draw the menu at the bottom center of the screen
    auto windowSize = window->getSize();
    m_uiManager.getMenu("settings")
        .draw((windowSize.X - 30) / 2, windowSize.Y - 4); // Adjust 30 based on your menu width
}

void SettingsScene::handleInput()
{
    m_uiManager.getMenu("settings").handleInput();
}

// increment card limit up to max of 1000
void SettingsScene::incrementCards()
{
    if (m_card_limit < 1000)
    {
        m_card_limit++;
    }
}

// decrement hand limit to no less than 1
void SettingsScene::decrementCards()
{
    if (m_card_limit > 1)
    {
        m_card_limit--;
    }
}

// increment to a maximum of 1 hour
void SettingsScene::incrementStudyMins()
{
    if (m_study_min < 60)
    {
        m_study_min++;
    }
}

// decrement time to a minimum of 1 min
void SettingsScene::decrementStudyMins()
{
    if (m_study_min > 1)
    {
        m_study_min--;
    }
}

void SettingsScene::resetDefault()
{
    m_study_min = 25;
    m_card_limit = 15;
}
