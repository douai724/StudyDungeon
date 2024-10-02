/**
 * @file settings_scene.h
 * @author Green Alligators
 * @brief The menu and settings for the over all game
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include "menu.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Class for a scene to show the program instructions.
 *
 *
 */
class SettingsScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Construct a new HowTo Scene object
     *
     * @param uiManager reference to the current UI mananger object
     * @param goBack a function to go back a scene
     */
    SettingsScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack);

    /**
     * @brief function for continuous updates to the program state seperate from rendering and input handling
     *
     */
    void update() override;
    /**
     * @brief renders the scene on the console window
     * @param window shared pointer to the console window that is rendered on
     *
     * draws the title of the scene, sets up a counter for the current number of the fib sequence and draws the buttons:
     * reset, update and back.
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void init();
    void incrementCards();
    void decrementCards();
    void incrementStudyMins();
    void decrementStudyMins();
    void resetDefault();
    void handleInput() override;

    void setStaticDrawn(bool staticDrawn) override
    {
        m_staticDrawn = staticDrawn;
    }

private:
    ConsoleUI::UIManager &m_uiManager; ///< Reference to the UI manager.
    int m_card_limit;                  ///< max flashcards per round
    int m_study_min;                   ///< limit on study duration studying flashcards
    std::function<void()> m_goBack;    ///< function to return to the previous scene
    bool m_staticDrawn = false;
};

#endif // SETTINGS_SCENE_H
