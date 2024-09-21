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

/**
 * @brief Class for a scene which the user can simulate the fibonacci sequence.
 * 
 * !!! This scene is was a test for the Menu.h console UI System and will most likely not make it to the final release !!!
 * 
 */
class FibonacciScene : public ConsoleUI::Scene
{
public:
    /**
     * @brief Construct a new Fibonacci Scene object
     * 
     * @param uiManager reference to the current UI mananger object
     * @param goBack a function to go back a scene
     */
    FibonacciScene(ConsoleUI::UIManager &uiManager, std::function<void()> goBack);

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
    void handleInput() override;

private:
    ConsoleUI::UIManager &m_uiManager; ///< Reference to the UI manager.
    std::function<void()> m_goBack; ///< function to return to the previous scene
    unsigned long long m_fibNumber1; ///< first fibonacci number
    unsigned long long m_fibNumber2; ///< second fibonacci number

    void resetFibonacci(); ///< resets the fibonacci sequence
    void updateFibonacci(); ///< updates the next fibonacci number in the sequence
};

#endif // FIBONACCI_SCENE_H
