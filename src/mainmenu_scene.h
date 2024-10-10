/**
 * @file mainmenu_scene.h
 * @author Green Alligators
 * @brief Defines the scene for the main menu
 * @version 1.0.0
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "artwork.h"
#include "menu.h"
#include "util.h"
#include <algorithm>
#include <chrono>
#include <conio.h>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>

/**
 * @brief The class for the the main menu ui
 *
 */
class MainMenuScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Configures the objects that need to be redrawn after the initial scene rendering
     *
     * @param staticDrawn
     */
    void setStaticDrawn(bool staticDrawn) override;

    /**
     * @brief Construct a new Main Menu Scene object
     *
     * @param uiManager The UI manager for the scene
     * @param openSettingsScene function that will link to the setting scene
     * @param openHowToScene function that will link the "how-to" scene
     * @param openBrowseDecks function that will link to the browse decks scene
     * @param openEditDecks functions that will link to the edit decks scene
     */
    MainMenuScene(ConsoleUI::UIManager &uiManager,
                  std::function<void()> openSettingsScene,
                  std::function<void()> openHowToScene,
                  std::function<void()> openBrowseDecks,
                  std::function<void()> openEditDecks);

    /**
     * @brief Create a Main Menu object
     *
     * @param openSettingsScene function that will link to the setting scene
     * @param openHowToScene function that will link the "how-to" scene
     * @param openBrowseDecks function that will link to the browse decks scene
     * @param openEditDecks functions that will link to the edit decks scene
     */
    void createMainMenu(std::function<void()> openSettingsScene,
                        std::function<void()> openHowToScene,
                        std::function<void()> openBrowseDecks,
                        std::function<void()> openEditDecks);

    /**
     * @brief Initialise the scene
     *
     */
    void init() override;

    /**
     * @brief Actions to perform on events
     *
     */
    void update() override;

    /**
     * @brief The scene objects to render
     *
     * @param window the window UI to render in
     */
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;

    /**
     * @brief Input handler for the scene
     *
     */
    void handleInput() override;


private:
    ConsoleUI::UIManager &m_uiManager; ///< reference to the UI manager
    bool m_needsRedraw;                ///< Does the scene need redrawn
    bool m_staticDrawn = false;        ///< redraw the scene on update
};
#endif
