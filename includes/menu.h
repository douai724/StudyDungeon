#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <windows.h>
#include <memory>

class Menu;

class MenuItem {
public:
    MenuItem(const std::string& label, void (*action)());
    MenuItem(const std::string& label, std::shared_ptr<Menu> subMenu);
    std::string label;
    void (*action)();
    std::shared_ptr<Menu> subMenu;
    bool isSubMenu() const { return subMenu != nullptr; }
};

class Menu {
private:
    std::vector<MenuItem> items;
    std::string title;
    int selectedIndex;
    HANDLE consoleHandle;

    void moveCursor(SHORT x, SHORT y);
    void setColor(WORD foreground, WORD background);
    int getArrowKeyNavigation();

public:
    Menu(const std::string& title);
    void addItem(const std::string& label, void (*action)());
    void addItem(const std::string& label, std::shared_ptr<Menu> subMenu);
    void centerText(const std::string& label);
    void display();
    void run();
};

#endif // MENU_H
