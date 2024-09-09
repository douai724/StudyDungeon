#include "menu.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

namespace ConsoleUI
{
    void setConsoleCursorPosition(int x, int y)
    {
        COORD coord;
        coord.X = static_cast<short>(x);
        coord.Y = static_cast<short>(y);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    COORD getConsoleWindowSize()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return { static_cast<short>(csbi.srWindow.Right - csbi.srWindow.Left + 1),
                 static_cast<short>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1) };
    }

    ConsoleWindow::ConsoleWindow() : m_textBoxCapacity(10) { updateSize(); }

    void ConsoleWindow::updateSize()
    {
        COORD size = getConsoleWindowSize();
        m_width = size.X;
        m_height = size.Y;
    }

    void ConsoleWindow::drawBorder()
    {
        updateSize();
        // Draw top border
        setConsoleCursorPosition(0, 0);
        std::cout << static_cast<char>(218) << std::string(m_width - 2, static_cast<char>(196)) << static_cast<char>(191);
        // Draw side borders
        for (int i = 1; i < m_height - 1; ++i)
        {
            setConsoleCursorPosition(0, i);
            std::cout << static_cast<char>(179);
            setConsoleCursorPosition(m_width - 1, i);
            std::cout << static_cast<char>(179);
        }
        // Draw bottom border
        setConsoleCursorPosition(0, m_height - 1);
        std::cout << static_cast<char>(192) << std::string(m_width - 2, static_cast<char>(196)) << static_cast<char>(217);
    }

    void ConsoleWindow::drawText(const std::string& text, int x, int y, bool highlight)
    {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height)
        {
            setConsoleCursorPosition(x, y);
            if (highlight)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            std::cout << text.substr(0, m_width - x);
            if (highlight)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
        }
    }

    void ConsoleWindow::drawCenteredText(const std::string& text, int y)
    {
        int x = static_cast<int>((m_width - text.length()) / 2);
        drawText(text, x, y);
    }

    void ConsoleWindow::clear() { system("cls"); }

    COORD ConsoleWindow::getSize() const { return { static_cast<SHORT>(m_width), static_cast<SHORT>(m_height) }; }

    void ConsoleWindow::addTextToBox(const std::string& text)
    {
        m_textBox.push_back(text);
        if (m_textBox.size() > m_textBoxCapacity)
        {
            m_textBox.erase(m_textBox.begin());
        }
    }

    void ConsoleWindow::drawTextBox(int x, int y, int width, int height)
    {
        // Draw box border
        for (int i = 0; i < height; ++i)
        {
            drawText(std::string(width, ' '), x, y + i);
            drawText("|", x, y + i);
            drawText("|", x + width - 1, y + i);
        }
        drawText("+" + std::string(width - 2, '-') + "+", x, y);
        drawText("+" + std::string(width - 2, '-') + "+", x, y + height - 1);

        // Draw text
        int startIndex = max(0, static_cast<int>(m_textBox.size()) - height + 2);
        for (int i = startIndex; i < m_textBox.size(); ++i)
        {
            drawText(m_textBox[i].substr(0, width - 4), x + 2, y + 1 + i - startIndex);
        }
    }


    void Button::draw(int x, int y, bool selected)
    {
        std::string border = selected ? ">" : " ";
        setConsoleCursorPosition(x, y);
        if (selected)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        }
        std::cout << border << "[" << m_label << "]" << border;
        if (selected)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }

    

    Menu::Menu(bool horizontal) : m_selectedIndex(0), m_horizontal(horizontal) {}

    void Menu::addButton(const std::string& label, std::function<void()> action)
    {
        m_buttons.emplace_back(label, action);
    }

    void Menu::draw(int x, int y)
    {
        COORD windowSize = getConsoleWindowSize();
        int totalWidth = 0;
        int maxHeight = 0;
        for (const auto& button : m_buttons)
        {
            totalWidth += button.getWidth() + 1;
            maxHeight = max(maxHeight, 3);
        }

        int startX = m_horizontal ? max(0, x + static_cast<int>((windowSize.X - totalWidth) / 2)) : x;
        int startY = m_horizontal ? y : max(0, y + static_cast<int>((windowSize.Y - maxHeight) / 2));

        for (int i = 0; i < m_buttons.size(); ++i)
        {
            int buttonX = m_horizontal ? startX : x;
            int buttonY = m_horizontal ? y : startY + i * 2;
            m_buttons[i].draw(buttonX, buttonY, i == m_selectedIndex);
            if (m_horizontal) startX += m_buttons[i].getWidth() + 1;
        }
    }

    void Menu::handleInput()
    {
    int key = _getch();
    if (key == 224) // Arrow key
    {
        key = _getch();
        if (m_horizontal)
        {
            switch (key)
            {
            case 75: // Left arrow
                m_selectedIndex = (m_selectedIndex - 1 + m_buttons.size()) % m_buttons.size();
                break;
            case 77: // Right arrow
                m_selectedIndex = (m_selectedIndex + 1) % m_buttons.size();
                break;
            }
        }
        else
        {
            switch (key)
            {
            case 72: // Up arrow
                m_selectedIndex = (m_selectedIndex - 1 + m_buttons.size()) % m_buttons.size();
                break;
            case 80: // Down arrow
                m_selectedIndex = (m_selectedIndex + 1) % m_buttons.size();
                break;
            }
        }
    }
    else if (key == 13) // Enter key
    {
        m_buttons[m_selectedIndex].performAction();

    }
    else if (key == 27) // Escape key
    {
        goBack();
    }
    }

    void Menu::pushPage()
    {
        m_pageHistory.push_back(m_buttons);
        m_buttons.clear();
        m_selectedIndex = 0;
    }

    void Menu::popPage()
    {
        if (!m_pageHistory.empty())
        {
            m_buttons = m_pageHistory.back();
            m_pageHistory.pop_back();
            m_selectedIndex = 0;
        }
    }

    void Menu::goBack()
    {
        popPage();
    }
}