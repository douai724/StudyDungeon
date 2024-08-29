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

#include "util.h"
#include <algorithm>
#include <conio.h>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

/**
 * @brief Class that represents a menu item
 * 
 */
class MenuItem
{
public:
    /*Name of item*/
    std::string label;
    /*button action that calls a function*/
    std::function<void()> action;
    /*button action that calls another menu*/
    std::shared_ptr<class Menu> subMenu;

    /**
     * @brief Construct a new Menu Item object that calls a function
     * 
     * @param label button text
     * @param action function the button will call
     */
    MenuItem(const std::string &label, std::function<void()> action);
    /**
     * @brief Construct a new Menu Item object that calls another menu (submenu)
     * 
     * @param label button text
     * @param submenu menu the button will call
     */
    MenuItem(const std::string &label, std::shared_ptr<Menu> subMenu);

    /**
     * @brief checks if a button calls an action or a submenu
     * 
     * @return true the menu calls a submenu
     * @return false the menu calls an action
     */
    bool isSubMenu() const
    {
        return subMenu != nullptr;
    }
};

/**
 * @brief Basic implementation of the menu system. (currently sidelined in favour of GridMenu)
 * #TODO fix the basic up and down menu. broken ever since the grid implementation.
 */
class Menu
{
protected:
    std::string title;
    std::vector<MenuItem> items;
    /*cursor location*/
    int selectedIndex;
    HANDLE consoleHandle;
    /*changes colour of foreground/background to either black or white*/
    void setColor(WORD foreground, WORD background);
    /*move cursor to  a specific location on the console*/
    void moveCursor(SHORT x, SHORT y);

public:
    Menu(const std::string &title);
    virtual ~Menu() = default;

    void addItem(const std::string &label, std::function<void()> action);
    void addItem(const std::string &label, std::shared_ptr<Menu> subMenu);

    virtual void display()=0;
    virtual void run()=0;

    int getArrowKeyNavigation();

    // Getters and Setters
    std::string getTitle() const { return title; }
    void setTitle(const std::string &newTitle) { title = newTitle; }
    std::vector<MenuItem> &getItems() { return items; }
    int getSelectedIndex() const { return selectedIndex; }
    void setSelectedIndex(int newIndex) { selectedIndex = newIndex; }
    HANDLE getConsoleHandle() const { return consoleHandle; }
};

/**
 * @brief GridItem struct that uses a Menuitem object for the button function
 * 
 */
struct GridItem
{
    MenuItem item;
    /*x,y position on the GridMenu*/
    int row;
    int col;
    /*width and height of the item. (extends from wherever the row,col start position of the item is)*/
    int width;
    int height;
    /**
     * @brief Construct a new Grid Item object on a specific grid location at a specified size. 
     * default button size: width = 1, height = 1
     * 
     * @param item MenuItem object that adds button functionality
     * @param row x-axis on grid
     * @param col y-axis on grid
     * @param width width on button from the starting x,y coords
     * @param height height on button from the starting x,y coords
     */
    GridItem(const MenuItem &item, int row, int col, int width, int height)
        : item(item), row(row), col(col), width(width), height(height)
    {
    }
};

/**
 * @brief GridMenu that extends the functionality of the Menu class.
 * 
 */
class GridMenu : public Menu
{
public:
    std::pair<int, int> findNextValidItem(int startRow, int startCol, int rowDelta, int colDelta) const;
    void executeSelectedItem();

private:
    int gridWidth;
    int gridHeight;
    int selectedRow;
    int selectedCol;
    /*vector that contains all gridItems in a certain menu*/
    std::vector<GridItem> gridItems;

    /**
     * @brief draws a border around the console edges by calculating the width and height of the console.
     * 
     * @param width width of the console
     * @param height height of the console
     */
    void drawBorder(int width, int height);
    /**
     * @brief Draws a border around each button similarly to the drawBorder function. highlights the button white if it the selected 
     * rows/cols is the same as the items rows/cols position. And handles the labels location on the button and text wrapping if overflow
     * occurs.
     * 
     * @param item pointer to a Griditem object that it will draw on the console
     * @param startX starting x-axis location of GridItem 
     * @param startY starting y-axis location of GridItem 
     * @param width width of the item
     * @param height height of the item
     */
    void drawGridItem(const GridItem &item, int startX, int startY, int width, int height);

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

    void logError(const std::string& message);
    bool isValidGridItem(int row, int col) const;
    int getGridWidth() const;
    int getGridHeight() const;
    void setGridWidth(int width);
    void setGridHeight(int height);
    void deleteSelectedItem();

    // Getters and Setters
    std::vector<GridItem> &getGridItems() { return gridItems; }
    int getSelectedRow() const { return selectedRow; }
    void setSelectedRow(int newRow) { selectedRow = newRow; }
    int getSelectedCol() const { return selectedCol; }
    void setSelectedCol(int newCol) { selectedCol = newCol; }
};

#endif