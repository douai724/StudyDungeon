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

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include <windows.h>


/**
 * @brief Namespace for the consol functions
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

    class ConsoleWindow
    {
    public:
        ConsoleWindow();
        void updateSize();
        void drawBorder();
        void drawBox(int x, int y, int width, int height);
        void drawHorizontalLine(int x, int y, int length);
        void drawVerticalLine(int x, int y, int length);
        void drawCharacter(int x, int y, char ch);
        void drawText(const std::string& text, int x, int y, bool highlight = false);
        void drawCenteredText(const std::string& text, int y);
        void clear();
        COORD getSize() const;
        void addTextToBox(const std::string& text);
        void drawTextBox(int x, int y, int width, int height);
        void drawAsciiArt(const std::vector<std::string>& art, int x, int y);

    private:
        int m_width;
        int m_height;
        std::vector<std::string> m_textBox;
        int m_textBoxCapacity;
    };

    class AsciiArt
    {
    public:
        AsciiArt() = default;
        AsciiArt(const char* artString);
        const std::vector<std::string>& getArt() const;
        int getWidth() const;
        int getHeight() const;

    private:
        std::vector<std::string> m_art;
        int m_width;
        int m_height;
    };

    class Button {
    public:
        Button(const std::string& label, std::function<void()> action);
        void draw(int x, int y, bool selected);
        void performAction() const;
        int getWidth() const;
        const std::string& getLabel() const;

    private:
        std::string m_label;
        std::function<void()> m_action;
    };

    class Menu
    {
    public:
        Menu(bool horizontal = false);
        void addButton(const std::string& label, std::function<void()> action);
        void draw(int x, int y);
        void handleInput();
        bool isBackButtonPressed() const;
        void pushPage();
        void popPage();

        size_t getButtonCount() const;
        int getButtonWidth(size_t index) const;
        size_t getSelectedIndex() const {
            return m_selectedIndex;
        }
        void selectPreviousButton();
        void selectNextButton();
        int getTotalWidth() const;
        void activateSelectedButton();
        void clear() {
            m_buttons.clear();
            m_selectedIndex = 0;
        }   



    private:
        std::vector<Button> m_buttons;
        size_t m_selectedIndex;
        bool m_horizontal;
        std::vector<std::vector<Button>> m_pageHistory;
    };

    class Scene
    {
    public:
        virtual ~Scene() = default;
        virtual void update() = 0;
        virtual void render(std::shared_ptr<ConsoleWindow> window) = 0;
        virtual void handleInput() = 0;
    };

    class UIManager
    {
    public:
        UIManager();
        std::shared_ptr<ConsoleWindow> getWindow();
        void setCurrentScene(std::shared_ptr<Scene> scene);
        void update();
        void render();
        void handleInput();
        Menu& createMenu(const std::string& name, bool horizontal = false);
        Menu& getMenu(const std::string& name);
        void clearMenu(const std::string& name);
        void clearAllMenus();
        AsciiArt createAsciiArt(const char* artString);

    private:
        std::shared_ptr<ConsoleWindow> m_window;
        std::shared_ptr<Scene> m_currentScene;
        std::unordered_map<std::string, Menu> m_menus;
    };
}

#endif // MENU_H