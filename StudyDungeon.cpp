// StudyDungeon.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include "includes/deck.h"
#include "includes/util.h"
#include "includes/artwork.h"
#include "includes/menu.h"




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


    // testing loading of cards from all available decks
    fs::path appDir = get_app_path();
    std::cout << "dir is: " << appDir << std::endl;
    
    fs::path deckDir = appDir.append("Decks");
    load_flashcard_decks(deckDir);

    std::string controls = "\n\nControls: Arrow keys to navigate, Enter to select, Esc to go back";

    // Menu system
    auto mainMenu = std::make_shared<Menu>("Flashcard Application" + controls);
    auto editMenu = std::make_shared<Menu>("Edit Flashcards" + controls);
    auto reviewMenu = std::make_shared<Menu>("Review Flashcards" + controls);

    auto flashcardMenu = std::make_shared<Menu>("Flashcard Menu" + controls);

    editMenu->addItem("Delete Flashcard", deleteFlashcard);
    editMenu->addItem("Browse Decks", browseDeck);
    editMenu->addItem("Edit Card", editCard);
    editMenu->addItem("Back to Main Menu", mainMenu);
    editMenu->addItem("Exit", exitProgram);

    reviewMenu->addItem("Open Flashcard", flashcardMenu);
    reviewMenu->addItem("Back to Main Menu", mainMenu);

    flashcardMenu->addItem("Easy", reviewFlashcards);
    flashcardMenu->addItem("Medium", reviewFlashcards);
    flashcardMenu->addItem("Hard", reviewFlashcards);
    flashcardMenu->addItem("Back to Review Menu", reviewMenu);
    flashcardMenu->addItem("Back to Main Menu", mainMenu);
    flashcardMenu->addItem("Exit", exitProgram);

    mainMenu->addItem("Add Flashcard", addFlashcard);
    mainMenu->addItem("Review Flashcards", reviewMenu);
    mainMenu->addItem("Edit Flashcards", editMenu);
    mainMenu->addItem("Exit", exitProgram);

    mainMenu->run();

    return 0;
}