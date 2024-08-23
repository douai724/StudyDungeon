#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "menu.h"
#include "util.h"
#include "gameloop.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <windows.h>

namespace fs = std::filesystem;

FlashCardDeck currentFlashCardDeck;

void addFlashcard()
{
    system("cls");
    std::cout << "Adding a new flashcard...\n";
    system("pause");
}

void reviewEasy()
{
    system("cls");
    std::cout << "Reviewing easy flashcards...\n";
    system("pause");
}

void reviewMedium()
{
    system("cls");
    std::cout << "Reviewing medium flashcards...\n";
    system("pause");
}

void reviewHard()
{
    system("cls");
    std::cout << "Reviewing hard flashcards...\n";
    system("pause");
}

void editCard()
{
    system("cls");
    std::cout << "Editing a flashcard...\n";
    system("pause");
}

void deleteCard()
{
    system("cls");
    std::cout << "Deleting a flashcard...\n";
    system("pause");
}

void browseDeck()
{
    int difficulty{0};
    system("cls");
    std::cout << "Browsing the deck...\n";
    system("pause");
    for (FlashCard fc : currentFlashCardDeck.cards)
    {
        system("cls");
        std::cout << fc.question << std::endl;
        std::cout << "Ready for answer?" << std::endl;
        std::getchar();
        std::cout << "What was the difficulty?" << std::endl;
        std::cin >> difficulty;
        std::cout << "You said difficulty of " << difficulty << std::endl;
        std::cout << "\n\nNEXT CARD?" << std::endl;
        system("pause");
    }
    system("pause");
}

void exitApp()
{
    system("cls");
    exit(0);
}

void about()
{
    system("cls");
    std::cout << project_name << '\n';
    std::cout << project_version << '\n';
    system("pause");
}

void controls()
{
    system("cls");
    std::cout << "Esc to go back (exits app when on main menu)\n";
    std::cout << "Arrow keys to navigate menu items\n";
    std::cout << "------------------------------------------------\n";
    system("pause");
}

void addButtonFunction(std::shared_ptr<GridMenu> mainMenu)
{
    int row = 0;
    int col = 0;
    bool positionFound = false;

    for (row = 0; row < mainMenu->getGridHeight(); ++row)
    {
        for (col = 0; col < mainMenu->getGridWidth(); ++col)
        {
            if (!mainMenu->isValidGridItem(row, col))
            {
                positionFound = true;
                break;
            }
        }
        if (positionFound)
            break;
    }

    if (positionFound)
    {
        mainMenu->addGridItem("New Button", []() {
            system("cls");
            std::cout << "New button clicked!\n";
            system("pause");
        }, row, col, 1, 1);
    }
}

int main()
{
    splashScreen();
    fs::path app_path = get_app_path();
    fs::path decks_dir = app_path;
    decks_dir.append("Decks");
    if (!fs::exists(decks_dir))
    {
        fs::create_directory(decks_dir);
        std::cerr << "Decks/ did not exist" << std::endl;
    }
    std::vector<FlashCardDeck> all_flashcard_decks = loadFlashCardDecks(decks_dir);

    currentFlashCardDeck = all_flashcard_decks.front();

    currentFlashCardDeck.printDeck();

    auto mainMenu = std::make_shared<GridMenu>("Flashcard Application", 3, 3);
    auto reviewMenu = std::make_shared<GridMenu>("Review Flashcards", 2, 2);
    auto editMenu = std::make_shared<GridMenu>("Edit Flashcards", 2, 2);
    auto testMenu = std::make_shared<GridMenu>("Test buttons", 3, 2);
    
    auto gameMenu = std::make_shared<GridMenu>("Game", 2, 1);
    auto cardsMenu = std::make_shared<GridMenu>("Select a card", 1, 10);
    
    gameMenu->addGridItem("Start", start, 0, 0);
    gameMenu->addGridItem("Exit", exitApp, 0, 1);

    //gameMenu->addItem();



    testMenu->addGridItem(
        "Add Button",
        [testMenu]() {
            addButtonFunction(testMenu);
        },
        0,
        0);

    testMenu->addGridItem(
        "Change Grid Size",
        [testMenu]() {
            system("cls");
            int newWidth, newHeight;
            std::cout << "Enter new grid width: ";
            std::cin >> newWidth;
            std::cout << "Enter new grid height: ";
            std::cin >> newHeight;
            testMenu->setGridWidth(newWidth);
            testMenu->setGridHeight(newHeight);
        },
        0,
        1);

    testMenu->addGridItem("Back", mainMenu, 2, 2);


    reviewMenu->addGridItem("Easy", reviewEasy, 0, 0);
    reviewMenu->addGridItem("Medium", reviewMedium, 0, 1);
    reviewMenu->addGridItem("Hard", reviewHard, 1, 0);
    reviewMenu->addGridItem("Back", mainMenu, 1, 1);

    editMenu->addGridItem("Edit Card", editCard, 0, 0);
    editMenu->addGridItem("Delete Card", deleteCard, 0, 1);
    editMenu->addGridItem("Browse Deck", browseDeck, 0, 2);
    editMenu->addGridItem("Back", mainMenu, 2, 2);

    mainMenu->addGridItem("Add Flashcard", addFlashcard, 0, 0);
    //mainMenu->addGridItem("Review Flashcards", reviewMenu, 0, 1);
    mainMenu->addGridItem("Play game", gameMenu, 0, 1);
    mainMenu->addGridItem("Edit Flashcards", editMenu, 1, 0);
    mainMenu->addGridItem("About", about, 1, 1);
    mainMenu->addGridItem("test menu", testMenu, 2, 0);

    mainMenu->addGridItem("Add Flashcard", addFlashcard, 0, 0);
    mainMenu->addGridItem("Review Flashcardsajsdkasdnakbdkasdbkakjaskjhdaksadjka", reviewMenu, 0, 1);
    mainMenu->addGridItem("Edit Flashcards", editMenu, 0, 2);
    mainMenu->addGridItem("About", about, 1, 0);
    mainMenu->addGridItem("Controls", controls, 1, 1);
    mainMenu->addGridItem("Test Menu", testMenu, 1, 2);
    mainMenu->addGridItem("Exit", exitApp, 2, 2);

    mainMenu->run();

    return 0;
}