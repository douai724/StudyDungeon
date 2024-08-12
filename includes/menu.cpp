#include "menu.h"
#include <iostream>
#include <conio.h>

// TODO document
MenuItem::MenuItem(const std::string& label, void (*action)()) : label(label), action(action), subMenu(nullptr) {}
MenuItem::MenuItem(const std::string& label, std::shared_ptr<Menu> subMenu) : label(label), action(nullptr), subMenu(subMenu) {}

// TODO Document
Menu::Menu(const std::string& title) : title(title), selectedIndex(0) {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

//TODO document
void Menu::addItem(const std::string& label, void (*action)()) {
    items.emplace_back(label, action);
}

//TODO document
void Menu::addItem(const std::string& label, std::shared_ptr<Menu> subMenu) {
    items.emplace_back(label, subMenu);
}

//TODO document
void Menu::moveCursor(SHORT x, SHORT y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(consoleHandle, coord);
}

//TODO document
void Menu::setColor(WORD foreground, WORD background) {
    SetConsoleTextAttribute(consoleHandle, foreground | (background << 4));
}

// TODO document
void Menu::display() {
    system("cls");
    std::cout << title << "\n\n";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i == static_cast<size_t>(selectedIndex)) {
            setColor(0, 15); // Black text on white background
        } else {
            setColor(15, 0); // White text on black background
        }
        std::cout << items[i].label << (items[i].isSubMenu() ? " >" : "") << "\n";
    }
    setColor(15, 0); // Reset to default colors
}

// TODO document
int Menu::getArrowKeyNavigation() {
    int ch = _getch();
    if (ch == 0 || ch == 224) { // Arrow key pressed
        switch (_getch()) {
            case 72: return -1; // Up arrow
            case 80: return 1;  // Down arrow
        }
    } else if (ch == 13) { // Enter key
        return 2;
    } else if (ch == 27) { // Esc key
        return 3;
    }
    return 0;
}

// TODO document
void Menu::run() {
    while (true) {
        display();
        int navigation = getArrowKeyNavigation();
        if (navigation == -1) { // Up arrow
            if (selectedIndex > 0) selectedIndex--;
        } else if (navigation == 1) { // Down arrow
            if (selectedIndex < static_cast<int>(items.size()) - 1) selectedIndex++;
        } else if (navigation == 2) { // Enter
            if (items[selectedIndex].isSubMenu()) {
                items[selectedIndex].subMenu->run();
            } else if (items[selectedIndex].action) {
                items[selectedIndex].action();
            }
        } else if (navigation == 3) { // Esc
            break; // Exit the menu
        }
    }
}