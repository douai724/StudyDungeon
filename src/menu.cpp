/**
 * @file menu.cpp
 * @author Green Alligators
 * @brief
 * @version 0.2
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "menu.h"
#include "util.h"
#include <algorithm>
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>


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
    return {static_cast<short>(csbi.srWindow.Right - csbi.srWindow.Left + 1),
            static_cast<short>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1)};
}

// ConsoleWindow implementation
ConsoleWindow::ConsoleWindow() : m_width(0), m_height(0), m_textBoxCapacity(14)
{

    setDefaultSize(1300, 740);
    setConsoleWindowSize(m_defaultSize.X, m_defaultSize.Y); 
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

void ConsoleWindow::drawBox(int x, int y, size_t width, size_t height)
{
    drawHorizontalLine(x, y, width);
    drawHorizontalLine(x, y + height - 1, width);
    drawVerticalLine(x, y, height);
    drawVerticalLine(x + width - 1, y, height);
}

void ConsoleWindow::drawHorizontalLine(int x, int y, size_t length, char ch)
{
    setConsoleCursorPosition(x, y);
    std::cout << std::string(length, ch);
}

void ConsoleWindow::drawVerticalLine(int x, int y, int length, char ch)
{
    for (int i = 0; i < length; ++i)
    {
        setConsoleCursorPosition(x, y + i);
        std::cout << ch;
    }
}

void ConsoleWindow::drawCharacter(int x, int y, char ch)
{
    setConsoleCursorPosition(x, y);
    std::cout << ch;
}

void ConsoleWindow::drawText(const std::string &text, int x, int y)
{
    setConsoleCursorPosition(x, y);

    std::cout << text;

}

void ConsoleWindow::drawCenteredText(const std::string &text, int y)
{
    int x = static_cast<int>((m_width - text.length()) / 2);
    drawText(text, x, y);
}


std::string ConsoleWindow::getLine(int x, int y, int maxLength)
{
    std::string input;
    int cursorPos = 0;

    while (true)
    {
        // Clear the input area
        setConsoleCursorPosition(x, y);
        std::cout << std::string(maxLength, ' ');

        // Display the current input
        setConsoleCursorPosition(x, y);
        std::cout << input;

        // Set the cursor position
        setConsoleCursorPosition(x + cursorPos, y);

        // Get user input
        int ch = _getch();

        if (ch == _key_esc) // Escape key
        {
            return "\x1B"; // Return the escape character to indicate abort
        }
        else if (ch == _arrow_prefix || ch == _numlock) // Arrow key prefix
        {
            ch = _getch();
            switch (ch)
            {
            case _key_left: // Left arrow
                if (cursorPos > 0)
                    cursorPos--;
                break;
            case _key_right: // Right arrow
                if (cursorPos < input.length())
                    cursorPos++;
                break;
            }
        }
        else if (ch == _key_enter) // Enter key
        {
            break;
        }
        else if (ch == _key_backspace) // Backspace
        {
            if (cursorPos > 0)
            {
                input.erase(cursorPos - 1, 1);
                cursorPos--;
            }
        }
        else if (ch >= 32 && ch <= 126 && input.length() < maxLength) // Printable characters
        {
            input.insert(cursorPos, 1, static_cast<char>(ch));
            cursorPos++;
        }
    }

    return input;
}

void ConsoleWindow::clear()
{
    clearScreen();
}

COORD ConsoleWindow::getSize() const
{
    return {static_cast<SHORT>(m_width), static_cast<SHORT>(m_height)};
}

void ConsoleWindow::addTextToBox(const std::string &text)
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
        drawText(m_textBox[i].substr(0, width - 2), static_cast<int>(x + 1), static_cast<int>(y + i + 1));
    }
}


void ConsoleWindow::drawWrappedText(const std::string &text, int x, int y, int width)
{
    std::istringstream words(text);
    std::string word;
    std::string line;
    int currentY = y;

    while (words >> word)
    {
        if (line.length() + word.length() + 1 > width)
        {
            drawText(line, x, currentY++);
            line = word + " ";
        }
        else
        {
            line += word + " ";
        }
    }

    if (!line.empty())
    {
        drawText(line, x, currentY);
    }
}

// Console buffering



void ConsoleWindow::addAsciiArt(const AsciiArt &art)
{
    m_asciiArts.push_back(art);
}

void ConsoleWindow::drawAsciiArt(const std::string &name, int x, int y)
{
    AsciiArt *art = getAsciiArtByName(name);
    if (art)
    {
        art->setPosition(x, y);

        int artX = art->getX();
        int artY = art->getY();
        int width = art->getWidth();
        int height = art->getHeight();

        if (artX + width > m_width || artY + height > m_height)
        {
            // Art is too big for the console, display text alternative
            std::string textAlt = art->getName();
            int textX = artX + (width - textAlt.length()) / 2;
            int textY = artY + height / 2;
            drawText(textAlt, textX, textY);
        }
        else
        {
            // Draw the ASCII art
            const std::vector<std::string> &artLines = art->getArt();
            for (size_t i = 0; i < artLines.size(); ++i)
            {
                drawText(artLines[i], artX, artY + static_cast<int>(i));
            }
        }
    }
}

void ConsoleWindow::checkWindowResize(UIManager &uiManager)
{
    COORD currentSize = getConsoleWindowSize();
    if (currentSize.X != m_width || currentSize.Y != m_height)
    {
        updateSize();
        displayResizeWarning(uiManager);
    }
}

void ConsoleWindow::displayResizeWarning(UIManager &uiManager)
{
    clearScreen();
    uiManager.getWindow()->drawCenteredText("Warning: Window size has changed.", 18); 
    uiManager.getWindow()->drawCenteredText("The new size may affect the app experience.", 19);
    uiManager.getWindow()->drawCenteredText("Do you want to keep the new size (y) or revert to the default size (n)?", 20);

    while (true)
    {
        int ch = _getch();
        if (ch == 'y' || ch == 'Y')
        {
            // Keep the new size, do nothing 
            for (auto &scene : uiManager.getScenes())
            {
                scene->setStaticDrawn(false);
            }
            break;
        }
        else if (ch == 'n' || ch == 'N')
        {
            setConsoleWindowSize(m_defaultSize.X, m_defaultSize.Y);
            updateSize();
            for (auto &scene : uiManager.getScenes())
            {
                scene->setStaticDrawn(false);
            }
            
            break;
        }
    }
}

void ConsoleWindow::setConsoleWindowSize(short width, short height)
{
    // Get the console window handle
    HWND consoleWindow = GetConsoleWindow();

    // Set the console buffer size to match the window size
    COORD bufferSize = {width, height};
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    // Set the console window size
    RECT rect;
    GetWindowRect(consoleWindow, &rect);
    MoveWindow(consoleWindow, rect.left, rect.top, width, height, TRUE);

    // Set the internal window size
    SMALL_RECT internalRect = {0, 0, static_cast<short>(width - 1), static_cast<short>(height - 1)};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &internalRect);
}

void ConsoleWindow::setDefaultSize(short width, short height)
{
    m_defaultSize = {width, height};
    setConsoleWindowSize(width, height);
}


void AsciiArt::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

AsciiArt *ConsoleWindow::getAsciiArtByName(const std::string &name)
{
    for (auto &art : m_asciiArts)
    {
        if (art.getName() == name)
        {
            return &art;
        }
    }
    return nullptr;
}


AsciiArt::AsciiArt(const std::string &name, const std::vector<std::string> &artLines, int x, int y)
    : m_name(name), m_art(artLines), m_width(0), m_height(static_cast<int>(artLines.size())), m_x(x), m_y(y)
{
    for (const auto &line : artLines)
    {
        m_width = max(m_width, static_cast<int>(line.length()));
    }
}

const std::string &AsciiArt::getName() const
{
    return m_name;
}

const std::vector<std::string> &AsciiArt::getArt() const
{
    return m_art;
}

int AsciiArt::getX() const
{
    return m_x;
}

int AsciiArt::getY() const
{
    return m_y;
}

int AsciiArt::getWidth() const
{
    return m_width;
}

int AsciiArt::getHeight() const
{
    return m_height;
}


// Button implementation
Button::Button(const std::string &label, std::function<void()> action) : m_label(label), m_action(action)
{
}

void Button::draw(int x, int y, bool selected)
{
    std::string border = selected ? "+" : " ";
    setConsoleCursorPosition(x, y);
    if (selected) {
        std::cout << border + "[" << m_label << "]" << border;
    } else {
        std::cout << border << _ESC + "[31;1;4m[" << m_label << "]" + _ESC + +"[0m" << border;
    }
}

void Button::performAction() const
{
    if (m_action)
        m_action();
}

int Button::getWidth() const
{
    return static_cast<int>(m_label.length() + 4);
}

const std::string &Button::getLabel() const
{
    return m_label;
}

// Menu implementation
Menu::Menu(bool horizontal) : m_selectedIndex(0), horizontal_layout(horizontal)
{
}

void Menu::addButton(const std::string &label, std::function<void()> action)
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
        if (horizontal_layout)
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
    if (key == _arrow_prefix || key == 0) // Arrow key
    {
        key = _getch();
        if (horizontal_layout)
        {
            switch (key)
            {
            case _key_left: // Left arrow
                m_selectedIndex = (m_selectedIndex - 1 + m_buttons.size()) % m_buttons.size();
                break;
            case _key_right: // Right arrow
                m_selectedIndex = (m_selectedIndex + 1) % m_buttons.size();
                break;
            }
        }
        else
        {
            switch (key)
            {
            case _key_up: // Up arrow
                m_selectedIndex = (m_selectedIndex - 1 + m_buttons.size()) % m_buttons.size();
                break;
            case _key_down: // Down arrow
                m_selectedIndex = (m_selectedIndex + 1) % m_buttons.size();
                break;
            }
        }
    }
    else if (key == _key_enter)
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


size_t Menu::getButtonCount() const
{
    return m_buttons.size();
}

int Menu::getButtonWidth(size_t index) const
{
    if (index < m_buttons.size())
    {
        return m_buttons[index].getWidth();
    }
    return 0;
}

void Menu::selectPreviousButton()
{
    if (m_selectedIndex > 0)
    {
        m_selectedIndex--;
    }
}

void Menu::selectNextButton()
{
    if (m_selectedIndex < m_buttons.size() - 1)
    {
        m_selectedIndex++;
    }
}

void Menu::activateSelectedButton()
{
    if (m_selectedIndex < m_buttons.size())
    {
        m_buttons[m_selectedIndex].performAction();
    }
}

int Menu::getMaxWidth() const
{
    int maxWidth = 0;
    for (const auto &button : m_buttons)
    {
        maxWidth = max(button.getWidth(), maxWidth);
    }
    return maxWidth;
}

// UIManager implementation
UIManager::UIManager() : m_window(std::make_shared<ConsoleWindow>())
{
}

std::shared_ptr<ConsoleWindow> UIManager::getWindow()
{
    return m_window;
}

void UIManager::setCurrentScene(std::shared_ptr<Scene> scene)
{
    for (auto &scene : getScenes()) {scene->setStaticDrawn(false);}
    m_currentScene = scene;
    m_scenes.push_back(scene);
    if (m_currentScene)
    {
        m_currentScene->init();
    }
}

void UIManager::init()
{
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

void UIManager::checkWindowResize() {
    if (m_window) {
        m_window->checkWindowResize(*this);
    }
}

Menu &UIManager::createMenu(const std::string &name, bool horizontal)
{
    return m_menus.emplace(name, Menu(horizontal)).first->second;
}

Menu &UIManager::getMenu(const std::string &name)
{
    return m_menus.at(name);
}

void UIManager::clearMenu(const std::string &name)
{
    if (m_menus.find(name) != m_menus.end())
    {
        m_menus[name].clear();
    }
}

void UIManager::clearAllMenus()
{
    for (auto &[name, menu] : m_menus)
    {

        if (name != "Browse Decks" || "Fibonacci Sequence" || "Game" || "Exit" || "howto")
        {
            menu.clear();
        }
    }
}

AsciiArt UIManager::createAsciiArt(const std::string &name, const std::vector<std::string> &artLines, int x, int y)
{
    return AsciiArt(name, artLines, x, y);
}

} // namespace ConsoleUI
