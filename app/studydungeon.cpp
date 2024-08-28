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
    
    auto mainMenu = std::make_shared<GridMenu>("Study Dungeon", 3, 1);
    auto aboutMenu = std::make_shared<GridMenu>("About & How to use", 1, 1);
    aboutMenu->addGridItem("Use arrow keys to navigate menu. Press esc to go back or exit.", [](){}, 0, 0);

    auto deckMenu = std::make_shared<GridMenu>("Flashcard decks", 1, (int)all_flashcard_decks.size());
    
     for(int i = 0; i < (int)all_flashcard_decks.size(); i++){
        std::string deckName = all_flashcard_decks[i].name;
        FlashCardDeck curr = all_flashcard_decks[i];
        auto flashcardMenu = std::make_shared<GridMenu>(deckName, 3, 1);
        deckMenu->addGridItem(deckName, [flashcardMenu, deckName, curr](){
            currentFlashCardDeck = curr;
            auto editMenu = std::make_shared<GridMenu>("Edit", 1, 1);
            
            flashcardMenu->addGridItem("Play", start, 0, 0);
            flashcardMenu->addGridItem("Edit", editMenu, 0, 1);
            flashcardMenu->addGridItem("Exit", exitApp, 0, 2);
            flashcardMenu->run();
        }, i, 0);
    }

    mainMenu->addGridItem("PLAY", deckMenu, 0, 0);
    mainMenu->addGridItem("ABOUT", aboutMenu, 0, 1);
    mainMenu->addGridItem("EXIT", exitApp, 0, 2);

    mainMenu->run();   

    return 0;
}
