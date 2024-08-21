/**
 * @file StudyDungeon.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "artwork.h"
#include "config.hpp"
#include "deck.h"
#include "menu.h"
#include "util.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>


namespace fs = std::filesystem;

/** Holds the current flashcard deck */
FlashCardDeck currentFlashCardDeck;

/*examples of setting up a menu */
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
    system("cls");
    std::cout << "Browsing the deck...\n";
    currentFlashCardDeck.printDeck();
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

int main()
{
    /** path to where the executable is */
    fs::path app_path = get_app_path();
    /** path to where Decks should be located */
    fs::path decks_dir = app_path;
    decks_dir.append("Decks");
    if (!fs::exists(decks_dir))
    {
        fs::create_directory(decks_dir);
        std::cerr << "Decks/ did not exist" << std::endl;
    }
    std::vector<FlashCardDeck> all_flashcard_decks = loadFlashCardDecks(decks_dir);

    /**A pointer to the current flashcard deck */

    currentFlashCardDeck = all_flashcard_decks.front();
    // FIXME protect against there being no decks
    // TODO would it make more sense to make currentDeck an index?

    currentFlashCardDeck.printDeck();


    auto mainMenu = std::make_shared<GridMenu>("Flashcard Application", 2, 3);
    auto reviewMenu = std::make_shared<GridMenu>("Review Flashcards", 2, 2);
    auto editMenu = std::make_shared<GridMenu>("Edit Flashcards", 2, 2);
    auto testMenu = std::make_shared<GridMenu>("Test buttons", 3, 2);

    testMenu->addGridItem(
        "Large Button",
        []() {
            system("cls");
            std::cout << "large button clicked\n";
            system("pause");
        },
        0,
        0,
        2,
        1);

    testMenu->addGridItem(
        "Button 1",
        []() {
            system("cls");
            std::cout << "Button 1 clicked\n";
            system("pause");
        },
        0,
        2);
    testMenu->addGridItem(
        "Button 2",
        []() {
            system("cls");
            std::cout << "Button 2 clicked\n";
            system("pause");
        },
        1,
        1);
    testMenu->addGridItem(
        "Button 3",
        []() {
            system("cls");
            std::cout << "Button 3 clicked\n";
            system("pause");
        },
        1,
        0);
    testMenu->addGridItem(
        "Button 4",
        []() {
            system("cls");
            std::cout << "Button 4 clicked\n";
            system("pause");
        },
        1,
        2);

    reviewMenu->addGridItem("Easy", reviewEasy, 0, 0);
    reviewMenu->addGridItem("Medium", reviewMedium, 0, 1);
    reviewMenu->addGridItem("Hard", reviewHard, 1, 0);
    reviewMenu->addGridItem("Back", mainMenu, 1, 1);

    editMenu->addGridItem("Edit Card", editCard, 0, 0);
    editMenu->addGridItem("Delete Card", deleteCard, 0, 1);
    editMenu->addGridItem("Browse Deck", browseDeck, 1, 0);
    editMenu->addGridItem("Back", mainMenu, 1, 1);

    mainMenu->addGridItem("Add Flashcard", addFlashcard, 0, 0);
    mainMenu->addGridItem("Review Flashcards", reviewMenu, 0, 1);
    mainMenu->addGridItem("Edit Flashcards", editMenu, 1, 0);
    mainMenu->addGridItem("About", about, 1, 1);
    mainMenu->addGridItem("test menu", testMenu, 2, 0);

    mainMenu->addGridItem("Exit", exitApp, 2, 1);

    mainMenu->run();

    return 0;
}
