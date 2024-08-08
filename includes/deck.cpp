
#include <windows.h>
#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;




// TODO define the Card class
/**
 * @brief Stores the data for a flashcard
 * 
 */
struct Card {
    std::string question;
    std::string answer;
    int difficulty;
    int n_times_answered;

};


/**
 * 
 */
//TODO define the Deck class

/**
 * 
 */
void create_card(){
    //TODO
};

/**
 * 
 */
void read_deck(){
    // TODO: take the path to a deck file and read the contents to create cards
    // Open file for reading
    // first line is the name of the deck
    // loop through in blocks of N to create a card
    // store cards in a deck
    // return deck
}


/**
 * 
 * 
 */
void write_deck(){
    // open file for writing
    // write name of deck to file
    // loop through each card in the deck
};


/**
 * @brief Function that will scan the deck directory and read in all the deck files found
 * 
 * @param deck_path 
 */
void load_decks(fs::path deck_path){
    // TODO create an array of Decks to store eacn deck in
    std::cout << deck_path << std::endl;

    // Check the deck directory exists
    if (fs::exists(deck_path) && fs::is_directory(deck_path)){
        std::cout << deck_path << " is a directory" << std::endl;
        // list out the contents of the directory
        for (const auto& entry : fs::directory_iterator(deck_path)){
            std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << std::endl;
            // TODO for each "<file>.deck" files, call read_deck() and add into the Deck array
        }
    } else {
        std::cerr << "Directory does not exist, or is not a directory";
        //TODO deal with error
    }

    //return deck_array;

};

