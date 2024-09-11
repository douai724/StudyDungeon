#include "console_templates.h"
#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "gameloop.h"
#include "menu.h"
#include "util.h"
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>

class MainMenuScene : public ConsoleUI::Scene
{
public:
    MainMenuScene(ConsoleUI::UIManager& uiManager, std::function<void()> openFibonacciScene) 
        : m_uiManager(uiManager)
    {
        auto& menu = m_uiManager.createMenu("main", false);
        menu.addButton("Fibonacci Sequence", openFibonacciScene);
        menu.addButton("Exit", []() { exit(0); });
    }

    void update() override {}

    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override {
        window->clear();
        window->drawBorder();
        window->drawCenteredText("Main Menu", 2);
        m_uiManager.getMenu("main").draw(5, 4);
    }

    void handleInput() override {
        m_uiManager.getMenu("main").handleInput();
    }

private:
    ConsoleUI::UIManager& m_uiManager;
};

int main()
{
    ConsoleUI::UIManager uiManager;

    std::shared_ptr<MainMenuScene> mainMenuScene;
    std::shared_ptr<FibonacciScene> fibonacciScene;

    // Create FibonacciScene
    fibonacciScene = std::make_shared<FibonacciScene>(uiManager, [&]() {
        uiManager.setCurrentScene(mainMenuScene);
    });

    // Create MainMenuScene
    mainMenuScene = std::make_shared<MainMenuScene>(uiManager, [&]() {
        uiManager.setCurrentScene(fibonacciScene);
    });

    // Set initial scene
    uiManager.setCurrentScene(mainMenuScene);

    // Main game loop
    while (true)
    {
        uiManager.update();
        uiManager.render();
        uiManager.handleInput();
    }

    return 0;
}