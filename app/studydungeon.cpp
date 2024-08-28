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

namespace fs = std::filesystem;

FlashCardDeck currentFlashCardDeck;

void addFlashcard()
{
    clearScreen();
    std::cout << "Adding a new flashcard...\n";
    pause();
}

void reviewEasy()
{
    clearScreen();
    std::cout << "Reviewing easy flashcards...\n";
    pause();
}

void reviewMedium()
{
    clearScreen();
    std::cout << "Reviewing medium flashcards...\n";
    pause();
}

void reviewHard()
{
    clearScreen();
    std::cout << "Reviewing hard flashcards...\n";
    pause();
}

void editCard()
{
    clearScreen();
    std::cout << "Editing a flashcard...\n";
    pause();
}

void deleteCard()
{
    clearScreen();
    std::cout << "Deleting a flashcard...\n";
    pause();
}

// Loop through the cards of a deck to answer them
void reviseDeck()
{
    int difficulty{0};
    clearScreen();
    std::cout << "Using the current deck to revise...\n";
    pause();
    for (FlashCard fc : currentFlashCardDeck.cards)
    {
        // FIXME to make it work properly
        clearScreen();
        std::cout << fc.question << std::endl;
        std::cout << "Ready for answer?" << std::endl;
        pause();
        std::cout << "What was the difficulty? LOW MEDIUM HIGH" << std::endl;
        // FIXME this isn't right
        std::cin >> difficulty;
        std::cout << "You said difficulty of " << difficulty << std::endl;
        std::cout << "The existing difficulty was " << fc.difficulty << std::endl;
        //TODO update difficulty of card
        fc.n_times_answered++;
        std::cout << "\n\nNEXT CARD?" << std::endl;
        pause();
    }
    // TODO Upon completion the deck should be written out so the difficulties and n_times_answered is updated.
}

void viewDeck()
{
    clearScreen();
    std::cout << "Current cards int the " << currentFlashCardDeck.name << " deck:\n\n";
    currentFlashCardDeck.printDeck();
    pause();
}

void exitApp()
{
    clearScreen();
    exit(0);
}

void about()
{
    clearScreen();
    std::cout << project_name << '\n';
    std::cout << project_version << '\n';
    pause();
}

void controls()
{
    clearScreen();
    std::cout << "Esc to go back (exits app when on main menu)\n";
    std::cout << "Arrow keys to navigate menu items\n";
    std::cout << "------------------------------------------------\n";
    pause();
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
        mainMenu->addGridItem(
            "New Button",
            []() {
                clearScreen();
                std::cout << "New button clicked!\n";
                pause();
            },
            row,
            col,
            1,
            1);
    }
}

int main()
{
    splashScreen();
    fs::path app_path = getAppPath();
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
    auto reviewMenu = std::make_shared<GridMenu>("Review Flashcards", 2, 3);
    auto editMenu = std::make_shared<GridMenu>("Edit Flashcards", 3, 3);
    auto testMenu = std::make_shared<GridMenu>("Test buttons", 3, 2);

    auto gameMenu = std::make_shared<GridMenu>("Game", 2, 1);
    auto cardsMenu = std::make_shared<GridMenu>("Select a card", 1, 10);

    gameMenu->addGridItem("Start", start, 0, 0);
    gameMenu->addGridItem("Exit", exitApp, 0, 1);

    //gameMenu->addItem();


    testMenu->addGridItem("Add Button", [testMenu]() { addButtonFunction(testMenu); }, 0, 0);

    testMenu->addGridItem(
        "Change Grid Size",
        [testMenu]() {
            clearScreen();
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

    reviewMenu->addGridItem("Revise Deck", reviseDeck, 0, 0);
    reviewMenu->addGridItem("Easy", reviewEasy, 0, 1);
    reviewMenu->addGridItem("Medium", reviewMedium, 1, 0);
    reviewMenu->addGridItem("Hard", reviewHard, 1, 1);
    reviewMenu->addGridItem("Back", mainMenu, 2, 1);

    editMenu->addGridItem("Edit Card", editCard, 0, 0);
    editMenu->addGridItem("Delete Card", deleteCard, 0, 1);
    editMenu->addGridItem("View Deck", viewDeck, 0, 2);
    editMenu->addGridItem("Back", mainMenu, 2, 2);

    // mainMenu->addGridItem("Add Flashcard", addFlashcard, 0, 0);
    // //mainMenu->addGridItem("Review Flashcards", reviewMenu, 0, 1);
    // mainMenu->addGridItem("Play game", gameMenu, 0, 1);
    // mainMenu->addGridItem("Edit Flashcards", editMenu, 1, 0);
    // mainMenu->addGridItem("About", about, 1, 1);
    // mainMenu->addGridItem("test menu", testMenu, 2, 0);

    mainMenu->addGridItem("Add Flashcard", addFlashcard, 0, 0);
    mainMenu->addGridItem("Review Flashcards", reviewMenu, 0, 1);
    mainMenu->addGridItem("Edit Flashcards", editMenu, 0, 2);
    mainMenu->addGridItem("About", about, 1, 0);
    mainMenu->addGridItem("Controls", controls, 1, 1);
    mainMenu->addGridItem("Test Menu", testMenu, 1, 2);
    mainMenu->addGridItem("Exit", exitApp, 2, 2);

    mainMenu->run();

    return 0;
}
