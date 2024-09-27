/**
 * @file test_scene.h
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef FIBONACCI_SCENE_H
#define FIBONACCI_SCENE_H

#include "menu.h"
#include <functional>

class FibonacciScene : public ConsoleUI::Scene
{
public:
    FibonacciScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack);

    void init() override;
    void update() override;
    void render(std::shared_ptr<ConsoleUI::ConsoleWindow> window) override;
    void handleInput() override;

private:
    ConsoleUI::UIManager &m_uiManager;
    std::function<void()> m_goBack;
    unsigned long long m_fibNumber1;
    unsigned long long m_fibNumber2;

    void resetFibonacci();
    void updateFibonacci();
};

#endif // FIBONACCI_SCENE_H
