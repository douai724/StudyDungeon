#pragma once
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <functional>
#include <windows.h>

namespace ConsoleUI
{
    void setConsoleCursorPosition(int x, int y);
    COORD getConsoleWindowSize();

    class ConsoleWindow
    {
    private:
        int m_width;
        int m_height;
        std::vector<std::string> m_textBox;
        int m_textBoxCapacity;

    public:
        ConsoleWindow();
        void updateSize();
        void drawBorder();
        void drawText(const std::string& text, int x, int y, bool highlight = false);
        void drawCenteredText(const std::string& text, int y);
        void clear();
        COORD getSize() const;
        void addTextToBox(const std::string& text);
        void drawTextBox(int x, int y, int width, int height);
    };

    class Button {
    public:
        Button(const std::string& label, std::function<void()> action)
            : m_label(label), m_action(action) {}

        void draw(int x, int y, bool selected);
        void performAction() const { if (m_action) m_action(); }
        int getWidth() const { return static_cast<int>(m_label.length() + 4); }
        const std::string& getLabel() const { return m_label; }

    private:
        std::string m_label;
        std::function<void()> m_action;
    };

    class Menu
    {
    private:
        std::vector<Button> m_buttons;
        size_t m_selectedIndex;
        bool m_horizontal;
        std::vector<std::vector<Button>> m_pageHistory; // Added

    public:
        Menu(bool horizontal = false);
        void addButton(const std::string& label, std::function<void()> action);
        void draw(int x, int y);
        void handleInput();
        void goBack();
        bool isBackButtonPressed() const
        {
            return m_buttons[m_selectedIndex].getLabel() == "Back";
        }

        void pushPage();
        void popPage(); 
    };
}

#endif // MENU_H