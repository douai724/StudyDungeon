#pragma once
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include <windows.h>

namespace ConsoleUI
{
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

    private:
        int m_width;
        int m_height;
        std::vector<std::string> m_textBox;
        int m_textBoxCapacity;
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

    private:
        std::shared_ptr<ConsoleWindow> m_window;
        std::shared_ptr<Scene> m_currentScene;
        std::unordered_map<std::string, Menu> m_menus;
    };
}

#endif // MENU_H