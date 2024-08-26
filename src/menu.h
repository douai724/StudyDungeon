/**
 * @file menu.h
 * @author Green Aligators
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

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>

class MenuItem
{
public:
    std::string label;
    std::function<void()> action;
    std::shared_ptr<class Menu> subMenu;

    MenuItem(const std::string &label, std::function<void()> action);
    MenuItem(const std::string &label, std::shared_ptr<Menu> subMenu);

    bool isSubMenu() const
    {
        return subMenu != nullptr;
    }
};

class Menu
{
protected:
    std::string title;
    std::vector<MenuItem> items;
    int selectedIndex;
    HANDLE consoleHandle;

    void setColor(WORD foreground, WORD background);
    void moveCursor(SHORT x, SHORT y);

public:
    Menu(const std::string &title);
    virtual ~Menu() = default;

    void addItem(const std::string &label, std::function<void()> action);
    void addItem(const std::string &label, std::shared_ptr<Menu> subMenu);

    virtual void display() = 0;
    virtual void run() = 0;

    int getArrowKeyNavigation();
};

struct GridItem
{
    MenuItem item;
    int row;
    int col;
    int width;
    int height;

    GridItem(const MenuItem &item, int row, int col, int width, int height)
        : item(item), row(row), col(col), width(width), height(height)
    {
    }
};

class GridMenu : public Menu
{
private:
    int gridWidth;
    int gridHeight;
    int selectedRow;
    int selectedCol;
    std::vector<GridItem> gridItems;

    void drawBorder(int width, int height);
    void drawGridItem(const GridItem &item, int startX, int startY, int width, int height);
    std::pair<int, int> findNextValidItem(int startRow, int startCol, int rowDelta, int colDelta) const;
    void executeSelectedItem();

public:
    GridMenu(const std::string &title, int width, int height);

    void addGridItem(const std::string &label,
                     std::function<void()> action,
                     int row,
                     int col,
                     int width = 1,
                     int height = 1);
    void addGridItem(const std::string &label,
                     std::shared_ptr<Menu> subMenu,
                     int row,
                     int col,
                     int width = 1,
                     int height = 1);

    void display() override;
    void run() override;
    void handleNavigation(int navigation);

    bool isValidGridItem(int row, int col) const;
    int getGridWidth() const;
    int getGridHeight() const;
    void setGridWidth(int width);
    void setGridHeight(int height);
    void deleteSelectedItem();
};

#endif
