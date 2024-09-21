/**
 * @file menu.h
 * @author Green Alligators
 * @brief
 * @version 0.2
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
 * @class Menu
 * @brief Represents a menu system with buttons and navigation capabilities.
 *
 * The Menu class provides functionality to create and manage a menu with 
 * selectable buttons. It supports both horizontal and vertical layouts,
 * and handles user input for navigation and button activation.
 */
class Menu
{
public:
    /**
     * @brief Construct a new Menu object.
     * @param horizontal If true, creates a horizontal menu layout. If false (default), creates a vertical layout.
     */
    Menu(bool horizontal = false);

    /**
     * @brief Add a new button to the menu.
     * @param label The text label for the button.
     * @param action The function to be called when the button is activated.
     */
    void addButton(const std::string &label, std::function<void()> action);

    /**
     * @brief Draw the menu at the specified position.
     * @param x The x-coordinate to start drawing the menu.
     * @param y The y-coordinate to start drawing the menu.
     */
    void draw(int x, int y);

    /**
     * @brief Handle user input for menu navigation and button activation.
     */
    void handleInput();

    /**
     * @brief Check if the "Back" button is currently selected and pressed.
     * @return true if the "Back" button is pressed, false otherwise.
     */
    bool isBackButtonPressed() const;

    /**
     * @brief Save the current menu state and clear the buttons.
     * This function is used for creating sub-menus or nested menu structures.
     */
    void pushPage();

    /**
     * @brief Restore the previous menu state.
     * This function is used to return from a sub-menu to the parent menu.
     */
    void popPage();

    /**
     * @brief Get the total number of buttons in the menu.
     * @return The number of buttons in the menu.
     */
    size_t getButtonCount() const;

    /**
     * @brief Get the width of a specific button.
     * @param index The index of the button.
     * @return The width of the button at the specified index.
     */
    int getButtonWidth(size_t index) const;

    /**
     * @brief Get the index of the currently selected button.
     * @return The index of the selected button.
     */
    size_t getSelectedIndex() const;

    /**
     * @brief Select the previous button in the menu.
     */
    void selectPreviousButton();

    /**
     * @brief Select the next button in the menu.
     */
    void selectNextButton();

    /**
     * @brief Get the total width of all buttons in the menu.
     * @return The total width of the menu.
     */
    int getTotalWidth() const;

    /**
     * @brief Activate the currently selected button.
     */
    void activateSelectedButton();

    /**
     * @brief Clear all buttons from the menu.
     */
    void clear();

private:
    std::vector<Button> m_buttons; /**< Vector containing all menu buttons. */
    size_t m_selectedIndex; /**< Index of the currently selected button. */
    bool horizontal_layout; /**< Flag indicating if the menu is horizontal (true) or vertical (false). */
    std::vector<std::vector<Button>> m_pageHistory; /**< Stack of previous menu states for nested menus. */
};

/**
 * @class Scene
 * @brief Abstract base class representing a visual interface/layout for the console window.
 *
 * The Scene class defines the interface for different visual layouts or states
 * in the console application. It provides pure virtual functions for updating,
 * rendering, and handling input, which derived classes must implement.
 */
class Scene
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~Scene() = default;

    /**
     * @brief Pure virtual function to update the scene's state.
     *
     * This function should be implemented by derived classes to update
     * any internal state or logic of the scene.
     */
    virtual void update() = 0;

    /**
     * @brief Pure virtual function to render the scene.
     *
     * @param window A shared pointer to the ConsoleWindow object used for rendering.
     *
     * This function should be implemented by derived classes to draw
     * the scene's content to the provided console window.
     */
    virtual void render(std::shared_ptr<ConsoleWindow> window) = 0;

    /**
     * @brief Pure virtual function to handle user input for the scene.
     *
     * This function should be implemented by derived classes to process
     * and respond to user input specific to the scene.
     */
    virtual void handleInput() = 0;
};

/**
 * @class UIManager
 * @brief Manages the user interface, including scenes, menus, and the console window.
 *
 * The UIManager class is responsible for coordinating the different components
 * of the user interface. It manages the current scene, handles menu creation
 * and management, and provides access to the console window. This class serves
 * as the central point for UI-related operations in the application.
 */
class UIManager
{
public:
    /**
     * @brief Construct a new UIManager object.
     *
     * Initializes the UIManager with a new ConsoleWindow.
     */
    UIManager();

    /**
     * @brief Get the shared pointer to the ConsoleWindow object.
     * @return std::shared_ptr<ConsoleWindow> The console window used for rendering.
     */
    std::shared_ptr<ConsoleWindow> getWindow();

    /**
     * @brief Set the current active scene.
     * @param scene A shared pointer to the Scene object to be set as current.
     */
    void setCurrentScene(std::shared_ptr<Scene> scene);

    /**
     * @brief Update the current scene.
     *
     * Calls the update method of the current scene if one is set.
     */
    void update();

    /**
     * @brief Render the current scene.
     *
     * Calls the render method of the current scene if one is set.
     */
    void render();

    /**
     * @brief Handle input for the current scene.
     *
     * Calls the handleInput method of the current scene if one is set.
     */
    void handleInput();

    /**
     * @brief Create a new menu with the specified name.
     * @param name The name of the menu to create.
     * @param horizontal If true, creates a horizontal menu. If false, creates a vertical menu.
     * @return Menu& A reference to the newly created menu.
     */
    Menu& createMenu(const std::string& name, bool horizontal = false);

    /**
     * @brief Get a reference to an existing menu.
     * @param name The name of the menu to retrieve.
     * @return Menu& A reference to the requested menu.
     * @throw std::out_of_range if the menu doesn't exist.
     */
    Menu& getMenu(const std::string& name);

    /**
     * @brief Clear all buttons from a specific menu.
     * @param name The name of the menu to clear.
     */
    void clearMenu(const std::string& name);

    /**
     * @brief Clear all buttons from all menus except specific ones.
     *
     * Clears all menus except "Browse Decks", "Fibonacci Sequence", "Game", and "Exit".
     */
    void clearAllMenus();

    /**
     * @brief Create a new AsciiArt object.
     * @param artString A string containing the ASCII art.
     * @return AsciiArt The created AsciiArt object.
     */
    AsciiArt createAsciiArt(const char* artString);

private:
    std::shared_ptr<ConsoleWindow> m_window; /**< The main console window used for rendering. */
    std::shared_ptr<Scene> m_currentScene; /**< The currently active scene. */
    std::unordered_map<std::string, Menu> m_menus; /**< Map of menu names to Menu objects. */
};
} // namespace ConsoleUI


#endif // MENU_H
