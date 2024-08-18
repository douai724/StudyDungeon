
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;




// TODO define the Card class
/**
 * @brief Stores the data for a flashcard
 *
 */
struct FlashCard {
    std::string question;
    std::string answer;
    int difficulty;
    int n_times_answered;

};


/**
 * @brief A deck of flashcards
 *
 */
class FlashCardDeck {
    public:
        std::vector<FlashCard> cards {};
        std::string name {};

        void print_deck(){
            std::cout << name << std::endl;
            std::cout << "size: " << cards.size() << '\n';
            for(FlashCard card : cards) {
                std::cout << card.question << '\n';
                std::cout << card.answer << '\n';
                std::cout << "---\n";
            }
        }
};


/**
 * @brief Create a flashcard object
 *
 * @return FlashCard
 */
FlashCard create_flashcard(){
    //TODO
    FlashCard card;
    return card;
};

/**
 * @brief For a given deck file, read the contents in to create all the cards
 * TODO document
 * @param deck_file
 */
FlashCardDeck read_flashcard_deck(fs::path deck_file){
    // TODO: take the path to a deck file and read the contents to create cards
    FlashCardDeck deck;

    // Open file for reading
    std::ifstream inf {deck_file};
    int lineCount {0};
    std::string deck_name {""};
    std::string strInput{};
    int cardNum {0}; // keep track of current card in deck
    FlashCard fc{};
    deck.cards.push_back(fc);
    //
    // TODO need to acount for final - in deck file
    // shuold look fto see if card is blank
    while (std::getline(inf, strInput)){
        if(lineCount == 0){
            deck.name = strInput;
        } else {

        }
        if (strInput.starts_with("-")){
            cardNum++;
            deck.cards.push_back(fc);
            std::cout << "NEW CARD" << '\n';
        }
        if(strInput.starts_with("Q:")){
            deck.cards.at(cardNum).question = strInput;
        }
        if(strInput.starts_with("A:")){
            deck.cards.at(cardNum).answer = strInput;
        }

        // parse line
        // if Q -> fc.question
        // if A -> fc.answer
        // if D -> fc.difficulty
        // if N -> fc.num_times

        // std::cout << strInput << '\n';
        lineCount++;
    }

    // std::cout << "name of deck: " << deck_name << '\n';
    // std::cout << "number of lines read: " << lineCount << '\n';
    // std::cout << fc.question << '\n';
    // deck.print_deck();
    // first line is the name of the deck
    // loop through in blocks of N to create a card
    // store cards in a deck
    return deck;
};


/**
 *
 * TODO document
 */
void write_flashcard_deck(){
    // open file for writing
    // write name of deck to file
    // loop through each card in the deck
};


/**
 * @brief Function that will scan the deck directory and read in all the deck files found
 * TODO document
 * @param deck_path
 */
void load_flashcard_decks(fs::path deck_path){
    // TODO create an array of Decks to store eacn deck in
    std::cout << deck_path << std::endl;
    std::vector<FlashCardDeck> deck_array;
    // Check the deck directory exists
    if (fs::exists(deck_path) && fs::is_directory(deck_path)){
        std::cout << deck_path << " is a directory" << std::endl;
        // list out the contents of the directory
        for (const auto& entry : fs::directory_iterator(deck_path)){
            std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << std::endl;
            // TODO for each "<file>.deck" files, call read_deck() and add into the Deck array
            if (entry.is_regular_file()){
                // read_flashcard_deck(entry);
                deck_array.push_back(read_flashcard_deck(entry));
            }
        }
    } else {
        std::cerr << "Directory does not exist, or is not a directory";
        //TODO deal with error
    }
    for(FlashCardDeck d : deck_array){
        d.print_deck();
    }
    //return deck_array;

};
