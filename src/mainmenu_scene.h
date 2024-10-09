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


class MainMenuScene : public ConsoleUI::Scene
{
public:
    void setStaticDrawn(bool staticDrawn) override;


    MainMenuScene(ConsoleUI::UIManager &uiManager,
                  std::function<void()> openSettingsScene,
                  std::function<void()> openHowToScene,
                  std::function<void()> openBrowseDecks,
                  std::function<void()> openEditDecks);


    void createMainMenu(std::function<void()> openSettingsScene,
                        std::function<void()> openHowToScene,
                        std::function<void()> openBrowseDecks,
                        std::function<void()> openEditDecks);


    void init() override;

    void update() override;


    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;


    void handleInput() override;


private:
    ConsoleUI::UIManager &m_uiManager;
    bool m_needsRedraw;
    bool m_staticDrawn = false;
};
#endif
