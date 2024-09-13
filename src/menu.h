/**
 * @file menu.h
 * @author Green Alligators
 * @brief
 * @version 0.1
 * @date 2024-08-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef MENU_H
#define MENU_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>


/**
 * @brief UI manager -> ConsoleWindow -> Scenes
 *
 */


namespace ConsoleUI
{
void setConsoleCursorPosition(int x, int y);
COORD getConsoleWindowSize();

/**
     * @brief Sets up and controls the console window
     *
     */
class ConsoleWindow
{
public:
    ConsoleWindow();
    /**
         * @brief updates the maximum size of the console window
         *
         */
    void updateSize();

    /**
         * @brief Draws a border around the console
         *
         */
    void drawBorder();

    /**
         * @brief Draws a box on the console starting from top-left corner
         *
         * @param x starting number of characters from left
         * @param y starting number of lines from top
         * @param width width of box
         * @param height height of box
         */
    void drawBox(int x, int y, int width, int height);

    /**
         * @brief Draws a horizontal line of defined length using a character
         *
         * @param x starting number of characters from left
         * @param y starting number of lines from top
         * @param length length of the line
         * @param ch character to use for the line
         */
    void drawHorizontalLine(int x, int y, int length, char ch = '-');

    /**
         * @brief  Draws a vertical line of defined length using a character
         *
         * @param x starting number of characters from left
         * @param y starting number of lines from top
         * @param length length of the line
         * @param ch character to use for the line
         */
    void drawVerticalLine(int x, int y, int length, char ch = '|');

    /**
         * @brief Draws a character as a specific coordinate
         *
         * @param x number of characters from left
         * @param y number of lines from top
         * @param ch Character to print
         */
    void drawCharacter(int x, int y, char ch);

    /**
         * @brief Prints text to console starting from specific location
         *
         * @param text Text to write
         * @param x number of characters from left
         * @param y number of lines from top
         * @param highlight bool to toggle text background on/off
         */
    void drawText(const std::string &text, int x, int y, bool highlight = false);

    /**
         * @brief Centers on X-axis at specific y
         *
         * @param text Text to write
         * @param y number of lines from top (from top)
         */
    void drawCenteredText(const std::string &text, int y);

    /**
         * @brief Clears the screen
         *
         */
    void clear();

    /**
         * @brief Gets the max width and height of the console
         *
         * @return COORD
         */
    COORD getSize() const;

    /**
         * @brief
         *
         * @param text
         */
    void addTextToBox(const std::string &text);

    /**
         * @brief
         *
         * @param x number of characters from left
         * @param y number of lines from top
         * @param width wdith of the box
         * @param height height of the box
         */
    void drawTextBox(int x, int y, int width, int height);

private:
    /** max width of console */
    int m_width;

    /** max height of console */
    int m_height;

    /** vector of strings to be printed in a text box */
    std::vector<std::string> m_textBox;

    /** maximum lines in textbox */
    int m_textBoxCapacity;
};

class Button
{
public:
    Button(const std::string &label, std::function<void()> action);
    void draw(int x, int y, bool selected);
    void performAction() const;
    int getWidth() const;
    const std::string &getLabel() const;

private:
    std::string m_label;
    std::function<void()> m_action;
};

class Menu
{
public:
    Menu(bool horizontal = false);
    void addButton(const std::string &label, std::function<void()> action);
    void draw(int x, int y);
    void handleInput();
    bool isBackButtonPressed() const;
    void pushPage();
    void popPage();

private:
    std::vector<Button> m_buttons;
    size_t m_selectedIndex;
    bool m_horizontal;
    std::vector<std::vector<Button>> m_pageHistory;
};

/**
     * @brief
     *
     */
class Scene
{
public:
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void render(std::shared_ptr<ConsoleWindow> window) = 0;
    virtual void handleInput() = 0;
};

/**
     * @brief
     *
     */
class UIManager
{
public:
    UIManager();
    std::shared_ptr<ConsoleWindow> getWindow();
    void setCurrentScene(std::shared_ptr<Scene> scene);
    void update();
    void render();
    void handleInput();
    Menu &createMenu(const std::string &name, bool horizontal = false);
    Menu &getMenu(const std::string &name);

private:
    std::shared_ptr<ConsoleWindow> m_window;
    std::shared_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, Menu> m_menus;
};
} // namespace ConsoleUI

#endif // MENU_H
