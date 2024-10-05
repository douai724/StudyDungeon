/**
 * @file howto_scene.h
 * @author Green Alligators
 * @brief
 * @version @PROJECT_VERSION@
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef HOWTO_SCENE_H
#define HOWTO_SCENE_H

#include "menu.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Class for a scene to show the program instructions.
 *
 */
class HowToScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Construct a new HowTo Scene object
     *
     * @param uiManager reference to the current UI mananger object
     * @param goBack a function to go back a scene
     */
    HowToScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack);

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

    /**
     * @brief Initialise the scene
     *
     */
    void init();

    /**
     * @brief Handle the input for the scene
     *
     */
    void handleInput() override;

    /**
     * @brief Set if the scene will need to be redrawn on update
     *
     * @param staticDrawn Should the scene be redrawn on updates
     */
    void setStaticDrawn(bool staticDrawn) override;

private:
    ConsoleUI::UIManager &m_uiManager; ///< Reference to the UI manager.
    std::function<void()> m_goBack;    ///< function to return to the previous scene
    bool m_staticDrawn = false;        ///< Is the scene to be redrawn on update
};

#endif // HOWTO_SCENE_H
