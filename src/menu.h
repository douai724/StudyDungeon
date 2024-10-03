#pragma once
#ifndef MENU_H
#define MENU_H

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

void setConsoleCursorPosition(int x, int y);
COORD getConsoleWindowSize();

class UIManager;

class AsciiArt
{
private:
    std::string m_name;
    std::vector<std::string> m_art;
    int m_width;
    int m_height;
    int m_x;
    int m_y;

public:
    AsciiArt(const std::string &name, const std::vector<std::string> &artLines, int x = 0, int y = 0);

    const std::string &getName() const;
    const std::vector<std::string> &getArt() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void setPosition(int x, int y);
};

class ANSIArt
{
private:
    std::string name;
    std::vector<std::vector<int>> codes;
    int width;
    int height;
    int x;
    int y;

public:
    ANSIArt(std::vector<std::vector<int>> codes, const std::string &name, int x = 0, int y = 0);

    int getWidth();
    int getHeight();
    int getX();
    int getY();
    void setPosition(int x, int y);
    std::string getName();
    std::string toString();
    std::vector<std::vector<int>> getCodes();
};

class ConsoleWindow
{
public:
    ConsoleWindow();
    virtual ~ConsoleWindow() = default;
    void updateSize();
    void drawBorder();
    void drawBox(int x, int y, size_t width, size_t height);
    void drawHorizontalLine(int x, int y, size_t length, char ch = '-');
    void drawVerticalLine(int x, int y, int length, char ch = '|');
    void drawCharacter(int x, int y, char ch);
    void drawText(const std::string &text, int x, int y);
    void drawCenteredText(const std::string &text, int y);
    std::string getLineWithAbort(int x, int y, int maxLength);
    std::string getLine(int x, int y, int maxLength = 0);
    void clear();
    COORD getSize() const;
    void checkWindowResize(UIManager &uiManager);
    void setDefaultSize(short width, short height);
    void setConsoleWindowSize(short width, short height);
    void addTextToBox(const std::string &text);
    void drawTextBox(int x, int y, int width, int height);
    void addAsciiArt(const AsciiArt &art);
    void drawAsciiArt(const std::string &name, int x = -1, int y = -1);
    AsciiArt *getAsciiArtByName(const std::string &name);

    void addANSIArt(const ANSIArt &art);
    void drawANSIArt(const std::string &name, int x, int y);
    ANSIArt *getANSIArtByName(const std::string &name);
    void drawANSICode(int code, int x, int y);

    void drawWrappedText(const std::string &text, int x, int y, int width);


private:
    size_t m_width;
    size_t m_height;
    std::vector<std::string> m_textBox;
    int m_textBoxCapacity;
    std::vector<AsciiArt> m_asciiArts;
    std::vector<ANSIArt> m_ANSIArt;
    COORD m_defaultSize;
    void displayResizeWarning(UIManager &uiManager);
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
    size_t getButtonCount() const;
    int getButtonWidth(size_t index) const;
    size_t getSelectedIndex() const
    {
        return m_selectedIndex;
    }
    void selectPreviousButton();
    void selectNextButton();
    int getMaxWidth() const;
    void activateSelectedButton();
    void clear()
    {
        m_buttons.clear();
        m_selectedIndex = 0;
    }

private:
    std::vector<Button> m_buttons;
    size_t m_selectedIndex;
    bool horizontal_layout;
    std::vector<std::vector<Button>> m_pageHistory;
};

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void init() = 0;
    virtual void render(std::shared_ptr<ConsoleWindow> window) = 0;
    virtual void handleInput() = 0;
    virtual void setStaticDrawn(bool staticDrawn) = 0;
};

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
    AsciiArt createAsciiArt(const std::string &name, const std::vector<std::string> &artLines, int x = -1, int y = -1);
    void checkWindowResize();
    std::shared_ptr<ConsoleWindow> m_window;
    std::shared_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, Menu> m_menus;
    std::vector<std::shared_ptr<Scene>> &getScenes()
    {
        return m_scenes;
    }

private:
    std::vector<std::shared_ptr<Scene>> m_scenes;
};

} // namespace ConsoleUI

#endif // MENU_H
