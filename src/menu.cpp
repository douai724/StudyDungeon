#include "menu.h"
#include <iostream>
#include <algorithm>
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

// ConsoleWindow implementation
ConsoleWindow::ConsoleWindow() : m_width(0), m_height(0), m_textBoxCapacity(14)
{
    updateSize();
}

void ConsoleWindow::updateSize()
{
    COORD size = getConsoleWindowSize();
    m_width = size.X;
    m_height = size.Y;
}

void ConsoleWindow::drawBorder()
{
    drawBox(0, 0, m_width, m_height);
}

void ConsoleWindow::drawBox(int x, int y, int width, int height)
{
    drawHorizontalLine(x, y, width);
    drawHorizontalLine(x, y + height - 1, width);
    drawVerticalLine(x, y, height);
    drawVerticalLine(x + width - 1, y, height);
}

void ConsoleWindow::drawHorizontalLine(int x, int y, int length)
{
    setConsoleCursorPosition(x, y);
    std::cout << std::string(length, '-');
}

void ConsoleWindow::drawVerticalLine(int x, int y, int length)
{
    for (int i = 0; i < length; ++i)
    {
        setConsoleCursorPosition(x, y + i);
        std::cout << '|';
    }
}

void ConsoleWindow::drawCharacter(int x, int y, char ch)
{
    setConsoleCursorPosition(x, y);
    std::cout << ch;
}

void ConsoleWindow::drawText(const std::string& text, int x, int y, bool highlight)
{
    setConsoleCursorPosition(x, y);
    if (highlight)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    }
    std::cout << text;
    if (highlight)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void ConsoleWindow::drawCenteredText(const std::string& text, int y)
{
    int x = static_cast<int>((m_width - text.length()) / 2);
    drawText(text, x, y);
}

void ConsoleWindow::clear()
{
    system("cls");
}

COORD ConsoleWindow::getSize() const
{
    return { static_cast<SHORT>(m_width), static_cast<SHORT>(m_height) };
}

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
    drawBox(x, y, width, height);
    for (size_t i = 0; i < m_textBox.size() && i < static_cast<size_t>(height - 2); ++i)
    {
        drawText(m_textBox[i].substr(0, width - 2), x + 1, y + i + 1);
    }
}

// Button implementation
Button::Button(const std::string& label, std::function<void()> action)
    : m_label(label), m_action(action) {}

void Button::draw(int x, int y, bool selected)
{
    std::string border = selected ? "+" : " ";
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

void Button::performAction() const
{
    if (m_action) m_action();
}

int Button::getWidth() const
{
    return static_cast<int>(m_label.length() + 4);
}

const std::string& Button::getLabel() const
{
    return m_label;
}

// Menu implementation
Menu::Menu(bool horizontal)
    : m_selectedIndex(0), m_horizontal(horizontal) {}

void Menu::addButton(const std::string& label, std::function<void()> action)
{
    m_buttons.emplace_back(label, action);
}

void Menu::draw(int x, int y)
{
    int currentX = x;
    int currentY = y;
    for (size_t i = 0; i < m_buttons.size(); ++i)
    {
        m_buttons[i].draw(currentX, currentY, i == m_selectedIndex);
        if (m_horizontal)
        {
            currentX += m_buttons[i].getWidth() + 1;
        }
        else
        {
            currentY += 1;
        }
    }
}

void Menu::handleInput()
{
    int key = _getch();
    if (key == 224)  // Arrow key
    {
        key = _getch();
        if (m_horizontal)
        {
            switch (key)
            {
            case 75:  // Left arrow
                m_selectedIndex = (m_selectedIndex - 1 + m_buttons.size()) % m_buttons.size();
                break;
            case 77:  // Right arrow
                m_selectedIndex = (m_selectedIndex + 1) % m_buttons.size();
                break;
            }
        }
        else
        {
            switch (key)
            {
            case 72:  // Up arrow
                m_selectedIndex = (m_selectedIndex - 1 + m_buttons.size()) % m_buttons.size();
                break;
            case 80:  // Down arrow
                m_selectedIndex = (m_selectedIndex + 1) % m_buttons.size();
                break;
            }
        }
    }
    else if (key == 13)  // Enter key
    {
        m_buttons[m_selectedIndex].performAction();
    }
}

bool Menu::isBackButtonPressed() const
{
    return m_buttons[m_selectedIndex].getLabel() == "Back";
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

// UIManager implementation
UIManager::UIManager() : m_window(std::make_shared<ConsoleWindow>()) {}

std::shared_ptr<ConsoleWindow> UIManager::getWindow()
{
    return m_window;
}

void UIManager::setCurrentScene(std::shared_ptr<Scene> scene)
{
    m_currentScene = scene;
}

void UIManager::update()
{
    if (m_currentScene)
    {
        m_currentScene->update();
    }
}

void UIManager::render()
{
    if (m_currentScene)
    {
        m_currentScene->render(m_window);
    }
}

void UIManager::handleInput()
{
    if (m_currentScene)
    {
        m_currentScene->handleInput();
    }
}

Menu& UIManager::createMenu(const std::string& name, bool horizontal)
{
    return m_menus.emplace(name, Menu(horizontal)).first->second;
}

Menu& UIManager::getMenu(const std::string& name)
{
    return m_menus.at(name);
}

}  // namespace ConsoleUI