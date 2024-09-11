#include "test_scene.h"
#include <string>

FibonacciScene::FibonacciScene(ConsoleUI::UIManager& uiManager, std::function<void()> goBack)
    : m_uiManager(uiManager), m_goBack(goBack), m_fibNumber1(0), m_fibNumber2(1)
{
    auto& menu = m_uiManager.createMenu("fibonacci", true);  // Horizontal menu
    menu.addButton("Reset", [this]() { resetFibonacci(); });
    menu.addButton("Update", [this]() { updateFibonacci(); });
    menu.addButton("Back", [this]() { m_goBack(); });
}

void FibonacciScene::update()
{
    // No continuous updates needed for this scene
}

void FibonacciScene::render(std::shared_ptr<ConsoleUI::ConsoleWindow> window)
{
    window->clear();
    window->drawBorder();
    window->drawCenteredText("Fibonacci Sequence", 2);

    std::string fibText = "Current Fibonacci Number: " + std::to_string(m_fibNumber2);
    window->drawCenteredText(fibText, window->getSize().Y / 2 - 2);

    // Draw the menu at the bottom center of the screen
    auto windowSize = window->getSize();
    m_uiManager.getMenu("fibonacci").draw((windowSize.X - 30) / 2, windowSize.Y - 4);  // Adjust 30 based on your menu width
}

void FibonacciScene::handleInput()
{
    m_uiManager.getMenu("fibonacci").handleInput();
}

void FibonacciScene::resetFibonacci()
{
    m_fibNumber1 = 0;
    m_fibNumber2 = 1;
}

void FibonacciScene::updateFibonacci()
{
    unsigned long long nextFib = m_fibNumber1 + m_fibNumber2;
    m_fibNumber1 = m_fibNumber2;
    m_fibNumber2 = nextFib;
}