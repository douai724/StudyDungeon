#include "deck.h"
#include <windows.h>
#include <iostream>
#include <string> 


/**
 * 
 */
// TODO define the Card class

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
 * 
 */
void load_decks(){
    // TODO
    std::string deck_path = "Decks";
    std::cout << deck_path;

    char path[MAX_PATH];
    // This will return the path of the executable, can take this and build relative paths
    // for where the deck files whould be
    if(GetModuleFileName(NULL, path, MAX_PATH)){
        std::cout << "Program path: " << path << std::endl;
    } else {
        std::cerr << "Error getting path." << std::endl;

    }


    // take path and remove app name, then add on "decks\"

    // List the contents of decks\ and loop through each .deck file reading them in

};

