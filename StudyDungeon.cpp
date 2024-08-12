// StudyDungeon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "includes/deck.h"
#include "includes/util.h"
#include "includes/artwork.h"
#include "includes/menu.h"
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

/*examples of setting up a menu */
void addFlashcard() {
    system("cls");
    std::cout << "Adding a new flashcard...\n";
    // Implement flashcard addition logic here
    system("pause");
}

void reviewFlashcards() {
    system("cls");
    std::cout << "Reviewing flashcards...\n";
    // Implement flashcard review logic here
    system("pause");
}

void deleteFlashcard() {
    system("cls");
    std::cout << "Deleting a flashcard...\n";
    // Implement flashcard deletion logic here
    system("pause");
}

void browseDeck() {
    system("cls");
    std::cout << "Browsing the deck...\n";
    // Implement deck browsing logic here
    system("pause");
}

void editCard() {
    system("cls");
    std::cout << "Editing a card...\n";
    // Implement card editing logic here
    system("pause");
}

void exitProgram() {
    system("cls");
    std::cout << "Exiting...\n";
    exit(0);
}
/* end of examples*/

int main() {
    auto mainMenu = std::make_shared<Menu>("Flashcard Application");
    auto editMenu = std::make_shared<Menu>("Edit Flashcards");

    editMenu->addItem("Delete Flashcard", deleteFlashcard);
    editMenu->addItem("Browse Deck", browseDeck);
    editMenu->addItem("Edit Card", editCard);

    mainMenu->addItem("Add Flashcard", addFlashcard);
    mainMenu->addItem("Review Flashcards", reviewFlashcards);
    mainMenu->addItem("Edit Flashcards", editMenu);
    mainMenu->addItem("Exit", exitProgram);

    mainMenu->run();

    return 0;
}