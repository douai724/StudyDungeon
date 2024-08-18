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

#include "includes/artwork.h"
#include "includes/deck.h"
#include "includes/menu.h"
#include "includes/util.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>


namespace fs = std::filesystem;

/*examples of setting up a menu */
void addFlashcard()
{
    system("cls");
    std::cout << "Adding a new flashcard...\n";
    // Implement flashcard addition logic here
    system("pause");
}

void reviewFlashcards()
{
    system("cls");
    std::cout << "Reviewing flashcards...\n";
    // Implement flashcard review logic here
    system("pause");
}

void deleteFlashcard()
{
    system("cls");
    std::cout << "Deleting a flashcard...\n";
    // Implement flashcard deletion logic here
    system("pause");
}

void browseDeck()
{
    system("cls");
    std::cout << "Browsing the deck...\n";
    // Implement deck browsing logic here
    system("pause");
}

void editCard()
{
    system("cls");
    std::cout << "Editing a card...\n";
    // Implement card editing logic here
    system("pause");
}

void exitProgram()
{
    system("cls");
    std::cout << "Exiting...\n";
    exit(0);
}
/* end of examples*/

void print_stuff()
{
    system("cls");
    load_flashcard_decks(get_app_path().append("Decks"));
    system("pause");
}

int main()
{


    // testing loading of cards from all available decks
    fs::path appDir = get_app_path();
    std::cout << "dir is: " << appDir << std::endl;

    fs::path deckDir = appDir.append("Decks");
    load_flashcard_decks(deckDir);

    // Menu system
    auto mainMenu = std::make_shared<Menu>("Flashcard Application");
    auto editMenu = std::make_shared<Menu>("Edit Flashcards");

    editMenu->addItem("Delete Flashcard", deleteFlashcard);
    editMenu->addItem("Browse Deck", browseDeck);
    editMenu->addItem("Edit Card", editCard);

    mainMenu->addItem("Add Flashcard", addFlashcard);
    mainMenu->addItem("Review Flashcards", reviewFlashcards);
    mainMenu->addItem("Edit Flashcards", editMenu);
    mainMenu->addItem("PRINT STUFF", print_stuff);
    mainMenu->addItem("Exit", exitProgram);

    mainMenu->run();

    return 0;
}
