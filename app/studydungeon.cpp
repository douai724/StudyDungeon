#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "gameloop.h"
#include "menu.h"
#include "util.h"
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>

int main()
{
    ConsoleUI::ConsoleWindow window;
    ConsoleUI::Menu mainMenu(false);  // Vertical menu
    ConsoleUI::Menu subMenu(true);    // Horizontal menu
    bool backPressed = false;

    mainMenu.addButton("Play", [&window, &mainMenu, &subMenu, &backPressed]() {
        // Switch to sub-menu
        mainMenu.pushPage();
        while (true)
        {
            window.clear();
            window.drawBorder();
            window.drawText("Study Dungeon", 5, 2);
            window.drawTextBox(5, 4, 70, 15);
            subMenu.draw(5, window.getSize().Y - 3);
            subMenu.handleInput();
            if (backPressed)
            {
                backPressed = false;
                mainMenu.popPage();
                break;
            }
        }
    });
    mainMenu.addButton("About", [&window]() {
        window.clear();
        window.drawBorder();
        window.drawText("About Study Dungeon", 5, 2);
        window.drawText("Press any key to return", 5, 4);
        _getch();
    });
    mainMenu.addButton("Exit", []() { clearScreen(); exit(0); });

    subMenu.addButton("Option 1", [&window]() {
        window.addTextToBox("Option 1 selected");
    });
    subMenu.addButton("Option 2", [&window]() {
        window.addTextToBox("Option 2 selected");
    });
    subMenu.addButton("Option 3", [&window]() {
        window.addTextToBox("Option 3 selected");
    });
    subMenu.addButton("Back", [&backPressed]() {
        // Set the flag to indicate back button press
        backPressed = true;
    });

    while (true)
    {
        window.clear();
        window.drawBorder();
        window.drawText("Study Dungeon", 5, 2);
        mainMenu.draw(5, 4);
        mainMenu.handleInput();
    }

    return 0;
}