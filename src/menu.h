/**
 * @file menu.h
 * @author Green Alligators
 * @brief Classes and functions for the UI system
 * @version @PROJECT_VERSION@
 * @date 2024-10-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef MENU_H
#define MENU_H

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

namespace ConsoleUI
{

class UIManager;


/**
 * @brief Set the Console Cursor Position
 *
 * @param x Number of characters from the left
 * @param y number of lines from the top
 */
void setConsoleCursorPosition(int x, int y);


/**
 * @brief Get the size of the console window
 *
 * @return COORD the X and Y dimensions of the console window
 */
COORD getConsoleWindowSize();

/**
 * @brief An object that stores ascii art in the form of a string
 *
 */
class AsciiArt
{
private:
    /** name of the art */
    std::string m_name;
    /** a vector of strings to represent the lines making up the art */
    std::vector<std::string> m_art;
    /** how wide the art is */
    size_t m_width;
    /** the height of the art */
    size_t m_height;
    /** left position of the art on the screen */
    int m_x;
    /** top position of the art on the screen */
    int m_y;

public:
    /**
     * @brief Construct a new Ascii Art object
     *
     * @param name name of the art
     * @param artLines vector of strings/lines that make up the art
     * @param x left most position to place the art
     * @param y top most position to place the art
     */
    AsciiArt(const std::string &name, const std::vector<std::string> &artLines, int x = 0, int y = 0);

    /**
     * @brief Get the Name of the art
     *
     * @return const std::string&
     */
    const std::string &getName() const;

    /**
     * @brief Get the lines comprising the art
     *
     * @return const std::vector<std::string>&
     */
    const std::vector<std::string> &getArt() const;

    /**
     * @brief Get the left most position
     *
     * @return int
     */
    int getX() const;

    /**
     * @brief Get the top most position
     *
     * @return int
     */
    int getY() const;

    /**
     * @brief Get the Width of the art
     *
     * @return size_t
     */
    size_t getWidth() const;

    /**
     * @brief Get the Height of the art
     *
     * @return size_t
     */
    size_t getHeight() const;

    /**
     * @brief Set the position of the top left corner
     *
     * @param x left most position
     * @param y top most position
     */
    void setPosition(int x, int y);
};

/**
 * @brief A object that holds art containing  256bit colour ANSI codes
 *
 */
class ANSIArt
{
private:
    /** name of the art */
    std::string name;
    /** vector lines/rows of 256bit colour values */
    std::vector<std::vector<int>> codes;
    /** width of the art */
    size_t width;
    /** height of the art */
    size_t height;
    /** left most position */
    int m_x;
    /** top most position */
    int m_y;

public:
    /**
     * @brief Construct a new ANSIArt object
     *
     * @param codes vector of vectors/rows of 256bit colour values
     * @param name name of the artwork
     * @param x left most position
     * @param y top most position
     */
    ANSIArt(std::vector<std::vector<int>> codes, const std::string &name, int x = 0, int y = 0);

    /**
     * @brief Get the width of the art
     *
     * @return size_t
     */
    size_t getWidth();

    /**
     * @brief Get the Height of the art
     *
     * @return size_t
     */
    size_t getHeight();

    /**
     * @brief Get the left most position
     *
     * @return int
     */
    int getX();

    /**
     * @brief Get the top most position
     *
     * @return int
     */
    int getY();

    /**
     * @brief Set the position of the top left corner of the artwork
     *
     * @param x left most position
     * @param y top most position
     */
    void setPosition(int x, int y);

    /**
     * @brief Get the Name of the artwork
     *
     * @return std::string
     */
    std::string getName();

    /**
     * @brief Convert the 256bit colour codes into a string of ANSI codes
     *
     * @return std::string
     */
    std::string toString();

    /**
     * @brief Get the 256bit colour codes
     *
     * @return std::vector<std::vector<int>>
     */
    std::vector<std::vector<int>> getCodes();
};


/**
 * @brief Object repesenting the Console window
 *
 */
class ConsoleWindow
{
public:
    /**
     * @brief Construct a new Console Window object
     *
     */
    ConsoleWindow();

    /**
     * @brief Destroy the Console Window object
     *
     */
    virtual ~ConsoleWindow() = default;

    /**
     * @brief Update the size of the console window
     *
     */
    void updateSize();

    /**
     * @brief Draws a border around the console
     *
     */
    void drawBorder();

    /**
     * @brief Draws a box
     *
     * @param x left most position
     * @param y top most position
     * @param width width of the box
     * @param height height of the box
     */
    void drawBox(int x, int y, size_t width, size_t height);

    /**
     * @brief Draws a horizontal line using specified character
     *
     * @param x left most position
     * @param y top most position
     * @param length length of the line
     * @param ch character to use to make the line
     */
    void drawHorizontalLine(int x, int y, size_t length, char ch = '-');

    /**
     * @brief Draws a vertical line using specified character
     *
     * @param x left most position
     * @param y top most position
     * @param length length of the line
     * @param ch character to use to make th line
     */
    void drawVerticalLine(int x, int y, size_t length, char ch = '|');

    /**
     * @brief Puts a character on the screen at a position
     *
     * @param x left most position
     * @param y top most position
     * @param ch character to draw
     */
    void drawCharacter(int x, int y, char ch);

    /**
     * @brief Puts a string of text on the srceen starting at a position
     *
     * @param text the string to be displayed
     * @param x left most position
     * @param y top most position
     */
    void drawText(const std::string &text, int x, int y);

    /**
     * @brief Put a string of text centered horizontally on the screen
     *
     * @param text string of text to be displayed
     * @param y top most position
     */
    void drawCenteredText(const std::string &text, int y);

    /**
     * @brief Create a blank text input field to recieve and display user input
     *
     * @param x left most positition
     * @param y top most position
     * @param maxLength maximum length of the input field
     * @return std::string
     */
    std::string getLine(int x, int y, size_t maxLength = 0);

    /**
     * @brief Clear everything on the screen
     *
     */
    void clear();

    /**
     * @brief Get the Size of the console window
     *
     * @return COORD
     */
    COORD getSize() const;

    /**
     * @brief Check to see if the console window has been resized
     *
     * @param uiManager
     */
    void checkWindowResize(UIManager &uiManager);

    /**
     * @brief Set the default size of the console window
     *
     * @param width console window width
     * @param height console window height
     */
    void setDefaultSize(short width, short height);

    /**
     * @brief Set the size of the console window
     *
     * @param width console window width
     * @param height console window height
     */
    void setConsoleWindowSize(short width, short height);

    /**
     * @brief The text to be added to a text box
     *
     * @param text
     */
    void addTextToBox(const std::string &text);

    /**
     * @brief Draws a text box of specified dimensions
     *
     * @param x left most position
     * @param y top most position
     * @param width width of the box
     * @param height height of the box
     */
    void drawTextBox(int x, int y, size_t width, size_t height);

    /**
     * @brief
     *
     * @param art
     */
    void addAsciiArt(const AsciiArt &art);

    /**
     * @brief
     *
     * @param name
     * @param x
     * @param y
     */
    void drawAsciiArt(const std::string &name, int x = -1, int y = -1);

    /**
     * @brief Get and ASCII art object by name
     *
     * @param name
     * @return AsciiArt*
     */
    AsciiArt *getAsciiArtByName(const std::string &name);

    /**
     * @brief Add an ansi art object to the consolewindow object
     *
     * @param art the ansi art oject to add
     */
    void addANSIArt(const ANSIArt &art);

    /**
     * @brief Draws the ansi art object at a location
     *
     * @param name name of the artwork to draw
     * @param x left most position
     * @param y top most position
     */
    void drawANSIArt(const std::string &name, int x, int y);

    /**
     * @brief Get an ANSI artwork by name
     *
     * @param name name of the artwork
     * @return ANSIArt*
     */
    ANSIArt *getANSIArtByName(const std::string &name);

    /**
     * @brief Draws a 256bit colour on the screen at a position
     *
     * @param code 256bit colour code
     * @param x left most position
     * @param y top most position
     */
    void drawANSICode(int code, int x, int y);

    /**
     * @brief Draws text on the screen wrapping the string to the next line
     * if it reaches the width
     *
     * @param text string of text to display
     * @param x left most position
     * @param y top most position
     * @param width maximum width of the text
     */
    void drawWrappedText(const std::string &text, int x, int y, size_t width);


private:
    /** window width */
    size_t m_width;
    /** window height */
    size_t m_height;
    /** textbox */
    std::vector<std::string> m_textBox;
    /** amount of characters that will fit in the text box */
    int m_textBoxCapacity;
    /** the ascii art objects to display on the console */
    std::vector<AsciiArt> m_asciiArts;
    /** the ansi art objects to display on the console */
    std::vector<ANSIArt> m_ANSIArt;
    /** the default window size */
    COORD m_defaultSize;
    /**
     * @brief On window resize, will display a warning message about resizing
     *
     * @param uiManager
     */
    void displayResizeWarning(UIManager &uiManager);
};

/**
 * @brief The class for the button object
 *
 */
class Button
{
public:
    /**
     * @brief Construct a new Button object
     *
     * @param label the label on the button
     * @param action the function to call when the button is activated
     */
    Button(const std::string &label, std::function<void()> action);

    /**
     * @brief Draw the button
     *
     * @param x left most position
     * @param y top most position
     * @param selected is the button selected
     */
    void draw(int x, int y, bool selected);

    /**
     * @brief Perform the action associated with the button
     *
     */
    void performAction() const;

    /**
     * @brief Get the Width of the button
     *
     * @return size_t
     */
    size_t getWidth() const;

    /**
     * @brief Get the Label of the button
     *
     * @return const std::string&
     */
    const std::string &getLabel() const;

private:
    /** the button label */
    std::string m_label;
    /** the function to run when button is activated */
    std::function<void()> m_action;
};

/**
 * @brief Defines the menu that is made of buttons
 *
 */
class Menu
{
public:
    /**
     * @brief Construct a new Menu object
     *
     * @param horizontal is the menu horizontal or vertical
     */
    Menu(bool horizontal = false);

    /**
     * @brief Add a button to the menu
     *
     * @param label the label on the button
     * @param action the function associtated with the button
     */
    void addButton(const std::string &label, std::function<void()> action);

    /**
     * @brief Draw the menu
     *
     * @param x left most position
     * @param y top most position
     */
    void draw(int x, int y);

    /**
     * @brief Handle the user input on the menu
     *
     */
    void handleInput();

    /**
     * @brief determines if the menu back button has been pressed
     *
     * @return true back button pressed
     * @return false back button not pressed
     */
    bool isBackButtonPressed() const;


    /**
     * @brief Get the number of buttons in the menu
     *
     * @return size_t
     */
    size_t getButtonCount() const;

    /**
     * @brief Get the width of the button by index
     *
     * @param index index of the button in the menu
     * @return size_t
     */
    size_t getButtonWidth(size_t index) const;

    /**
     * @brief Get the index of the selected menu button
     *
     * @return size_t
     */
    size_t getSelectedIndex() const
    {
        return m_selectedIndex;
    }

    /**
     * @brief select the previous button in the menu
     *
     */
    void selectPreviousButton();

    /**
     * @brief selecte the next button in the menu
     *
     */
    void selectNextButton();

    /**
     * @brief Get the width of the widest button in the menu
     *
     * @return size_t
     */
    size_t getMaxWidth() const;

    /**
     * @brief Perform the associated function from the button
     *
     */
    void activateSelectedButton();

    /**
     * @brief removes all buttons in the menu
     *
     */
    void clear();

private:
    /** all of the buttons in the menu */
    std::vector<Button> m_buttons;
    /** index of the selected button */
    size_t m_selectedIndex;
    /** is the menu to be layed out horizontally */
    bool horizontal_layout;
};

/**
 * @brief Defines a UI scene
 *
 */
class Scene
{
public:
    /**
     * @brief Destroy the Scene object
     *
     */
    virtual ~Scene() = default;

    /**
     * @brief What to perfrom on scene update
     *
     */
    virtual void update() = 0;

    /**
     * @brief Initialise the scene
     *
     */
    virtual void init() = 0;

    /**
     * @brief What to render in the console window
     *
     * @param window
     */
    virtual void render(std::shared_ptr<ConsoleWindow> window) = 0;

    /**
     * @brief Handle user input from the scene
     *
     */
    virtual void handleInput() = 0;

    /**
     * @brief //TODO
     *
     * @param staticDrawn
     */
    virtual void setStaticDrawn(bool staticDrawn) = 0;
};


/**
 * @brief Defines the UI manager
 *
 */
class UIManager
{
public:
    /**
     * @brief Construct a new UIManager object
     *
     */
    UIManager();

    /**
     * @brief Get the Window object
     *
     * @return std::shared_ptr<ConsoleWindow>
     */
    std::shared_ptr<ConsoleWindow> getWindow();

    /**
     * @brief Set the Current Scene object
     *
     * @param scene
     */
    void setCurrentScene(std::shared_ptr<Scene> scene);

    /**
     * @brief Initialise the UI
     *
     */
    void init();

    /**
     * @brief Called each time there is a event
     *
     */
    void update();

    /**
     * @brief Renders objects on the console window
     *
     */
    void render();

    /**
     * @brief Handles user input
     *
     */
    void handleInput();

    /**
     * @brief Create the UI menu
     *
     * @param name Name of the menu
     * @param horizontal is the menu layout horizontal
     * @return Menu&
     */
    Menu &createMenu(const std::string &name, bool horizontal = false);

    /**
     * @brief Get the Menu object by it's name
     *
     * @param name the name of the menu to retrieve
     * @return Menu&
     */
    Menu &getMenu(const std::string &name);

    /**
     * @brief Removes the named menu from the UI
     *
     * @param name
     */
    void clearMenu(const std::string &name);

    /**
     * @brief Removes all menus from the UI
     *
     */
    void clearAllMenus();

    /**
     * @brief Create a Ascii Art object
     *
     * @param name the name of the art
     * @param artLines the vector of strings representing the art
     * @param x left most position
     * @param y top most position
     * @return AsciiArt
     */
    AsciiArt createAsciiArt(const std::string &name, const std::vector<std::string> &artLines, int x = -1, int y = -1);

    /**
     * @brief Deteremine if the window has been resized
     *
     */
    void checkWindowResize();

    /** pointer to the current window */
    std::shared_ptr<ConsoleWindow> m_window;
    /** pointer to the current scene */
    std::shared_ptr<Scene> m_currentScene;
    /**all of the menus in the UI */
    std::unordered_map<std::string, Menu> m_menus;

    /**
     * @brief Get the Scenes of the UI
     *
     * @return std::vector<std::shared_ptr<Scene>>&
     */
    std::vector<std::shared_ptr<Scene>> &getScenes()
    {
        return m_scenes;
    }

private:
    /** all of the scenes in the UI */
    std::vector<std::shared_ptr<Scene>> m_scenes;
};


} // namespace ConsoleUI


#endif // MENU_H
