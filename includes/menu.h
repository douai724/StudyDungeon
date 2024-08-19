#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <windows.h>

class Menu;

class MenuItem {
public:
    std::string label;
    std::function<void()> action;
    std::shared_ptr<Menu> subMenu;

    MenuItem(const std::string& label, std::function<void()> action);
    MenuItem(const std::string& label, std::shared_ptr<Menu> subMenu);

    bool isSubMenu() const { return subMenu != nullptr; }
};

class Menu {
protected:
    std::string title;
    std::vector<MenuItem> items;
    int selectedIndex;
    HANDLE consoleHandle;

    void setColor(WORD foreground, WORD background);
    void moveCursor(SHORT x, SHORT y);
    int getArrowKeyNavigation();

public:
    Menu(const std::string& title);
    virtual ~Menu() = default;

    void addItem(const std::string& label, std::function<void()> action);
    void addItem(const std::string& label, std::shared_ptr<Menu> subMenu);

    virtual void display() = 0;
    virtual void run() = 0;
};

class GridMenu : public Menu {
private:
    int gridWidth;
    int gridHeight;
    int selectedRow;
    int selectedCol;

    struct GridItem {
        MenuItem item;
        int row;
        int col;
        int width;
        int height;

        GridItem(const MenuItem& item, int row, int col, int width = 1, int height = 1)
            : item(item), row(row), col(col), width(width), height(height) {}
    };

    std::vector<GridItem> gridItems;

    void drawBorder(int width, int height);
    void drawGridItem(const GridItem& item, int startX, int startY, int width, int height);
    void executeSelectedItem();
    bool isValidGridItem(int row, int col) const;
    std::pair<int, int> findNextValidItem(int startRow, int startCol, int rowDelta, int colDelta) const;

public:
    GridMenu(const std::string& title, int width, int height);

    void addGridItem(const std::string& label, std::function<void()> action, int row, int col, int width = 1, int height = 1);
    void addGridItem(const std::string& label, std::shared_ptr<Menu> subMenu, int row, int col, int width = 1, int height = 1);

    void display() override;
    void run() override;
    void handleNavigation(int navigation);
};

#endif // MENU_H