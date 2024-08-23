#ifndef MENU_H
#define MENU_H

#include <conio.h>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>

class Menu;

class MenuItem
{
public:
    MenuItem(const std::string &label, std::function<void()> action);
    MenuItem(const std::string &label, std::shared_ptr<Menu> subMenu);

    std::string label;
    std::function<void()> action;
    std::shared_ptr<Menu> subMenu;
    bool isSubMenu() const { return subMenu != nullptr; }
};

class Menu
{
public:
    Menu(const std::string &title);
    void addItem(const std::string &label, std::function<void()> action);
    void addItem(const std::string &label, std::shared_ptr<Menu> subMenu);
    virtual void run() {} // Declare run() as virtual with an empty body

protected:
    void setColor(WORD foreground, WORD background);
    void moveCursor(SHORT x, SHORT y);
    static int getArrowKeyNavigation();

    std::string title;
    std::vector<MenuItem> items;
    int selectedIndex;
    HANDLE consoleHandle;
};

class GridItem
{
public:
    GridItem(const MenuItem &item, int row, int col, int width, int height)
        : item(item), row(row), col(col), width(width), height(height)
    {
    }

    MenuItem item;
    int row;
    int col;
    int width;
    int height;
};

class GridMenu : public Menu
{
public:
    GridMenu(const std::string &title, int width, int height);
    void addGridItem(const std::string &label, std::function<void()> action, int row, int col, int width = 1, int height = 1);
    void addGridItem(const std::string &label, std::shared_ptr<Menu> subMenu, int row, int col, int width = 1, int height = 1);
    void display();
    void run() override; // Override the run() function
    int getGridWidth() const;
    int getGridHeight() const;
    void setGridWidth(int width);
    void setGridHeight(int height);
    bool isValidGridItem(int row, int col) const;

private:
    void drawBorder(int width, int height);
    void drawGridItem(const GridItem &item, int startX, int startY, int width, int height);
    std::pair<int, int> findNextValidItem(int startRow, int startCol, int rowDelta, int colDelta) const;
    void handleNavigation(int navigation);
    void executeSelectedItem();

    int gridWidth;
    int gridHeight;
    int selectedRow;
    int selectedCol;
    std::vector<GridItem> gridItems;
};

#endif