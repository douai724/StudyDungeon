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

#include <algorithm>
#include <conio.h>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>


/**
 * @brief UI manager -> ConsoleWindow -> Scenes
 *
 */


/**
 * @brief Namespace for the console functions
 *
 */
namespace ConsoleUI
{
/**
     * @brief Set the Console Cursor Position object to a location on the console
     *
     * @param x axis
     * @param y axis
     */
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
    void drawBox(int x, int y, size_t width, size_t height);

    /**
         * @brief Draws a horizontal line of defined length using a character
         *
         * @param x starting number of characters from left
         * @param y starting number of lines from top
         * @param length length of the line
         * @param ch character to use for the line
         */
    void drawHorizontalLine(int x, int y, size_t length, char ch = '-');

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
      * @brief Like the windows implementation it gets a users input and returns it as a string.
      *
      * @param x coordinate for cursor position
      * @param y coordinate for cursor position
      * @param maxLength optional max length parameter to limit the number of characters entered (default is 0 meaning no limit)
      * @param delimiter character that indicates end of input (default is '\n', meaning pressing ENTER will return the input)
      * @return std::string the users input
      */
    std::string getLine(int x, int y, int maxLength = 0);

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
    void drawAsciiArt(const std::vector<std::string> &art, int x, int y);

private:
    /** max width of console */
    size_t m_width;

    /** max height of console */
    size_t m_height;

    /** vector of strings to be printed in a text box */
    std::vector<std::string> m_textBox;

    /** maximum lines in textbox */
    int m_textBoxCapacity;
};

/**
 * @brief Defines an ascii art object
 *
 */
class AsciiArt
{
public:
    AsciiArt() = default;

    /**
     * @brief Construct a new Ascii Art object
     *
     * @param artString
     */
    AsciiArt(const char *artString);

    /**
     * @brief Get the Art object as a string
     *
     * @return const std::vector<std::string>&
     */
    const std::vector<std::string> &getArt() const;

    /**
     * @brief Get the width of the ascii art
     *
     * @return int
     */
    int getWidth() const;

    /**
     * @brief Get the height of the ascii art
     *
     * @return int
     */
    int getHeight() const;

private:
    /** a vector of strings that make up the art*/
    std::vector<std::string> m_art;
    /** the maximum number of characters wide */
    int m_width;
    /** how many lines the art occupies */
    int m_height;
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

/**
 * @brief Constructs a menu system
 *
 */
class Menu
{
public:
    /** Contructs the menu  */
    Menu(bool horizontal = false);

    /**
     * @brief Creates a menu button
     *
     * @param label Text for the button
     * @param action fucntion to be called on submission
     */
    void addButton(const std::string &label, std::function<void()> action);

    /**
     * @brief Draws all items in the menu
     *
     * @param x number of characters from left to begin drawing
     * @param y number of lines from top to begin drawing
     */
    void draw(int x, int y);

    /**
     * @brief Processes keyboard input
     *
     */
    void handleInput();

    /**
     * @brief checks if the "back" button has been selected and submitted
     *
     * @return true
     * @return false
     */
    bool isBackButtonPressed() const;

    // TODO remove
    void pushPage();
    // TODO remove
    void popPage();

    size_t getButtonCount() const;
    int getButtonWidth(size_t index) const;
    size_t getSelectedIndex() const
    {
        return m_selectedIndex;
    }
    void selectPreviousButton();
    void selectNextButton();
    int getTotalWidth() const;
    void activateSelectedButton();
    void clear()
    {
        m_buttons.clear();
        m_selectedIndex = 0;
    }


private:
    /** Vector of all the menu buttons */
    std::vector<Button> m_buttons;
    /** index of selected button */
    size_t m_selectedIndex;

    /** controls layout -> true = horizontal, false = vertical */
    bool horizontal_layout;

    // TODO remove?
    std::vector<std::vector<Button>> m_pageHistory;
};


/**
 * @brief Defines a consoleWindow visual interface/layout
 *
 */
class Scene
{
public:
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void init() = 0;
    virtual void render(std::shared_ptr<ConsoleWindow> window) = 0;
    virtual void handleInput() = 0;
};


/**
 * @brief Manages the displaying of scenes
 *
 */
class UIManager
{
public:
    UIManager();
    std::shared_ptr<ConsoleWindow> getWindow();
    void setCurrentScene(std::shared_ptr<Scene> scene);
    void init();
    void update();
    void render();
    void handleInput();
    Menu &createMenu(const std::string &name, bool horizontal = false);
    Menu &getMenu(const std::string &name);
    void clearMenu(const std::string &name);
    void clearAllMenus();
    AsciiArt createAsciiArt(const char *artString);

private:
    std::shared_ptr<ConsoleWindow> m_window;
    std::shared_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, Menu> m_menus;
};
} // namespace ConsoleUI


#endif // MENU_H
