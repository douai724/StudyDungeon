/**
 * @file deck.cpp
 * @author Green Alligators
 * @brief
 * @version 0.1
 * @date 2024-08-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "deck.h"

namespace fs = std::filesystem;


CardDifficulty strToCardDifficulty(std::string s)
{
    if (s == "LOW")
    {
        return LOW;
    }
    else if (s == "MEDIUM")
    {
        return MEDIUM;
    }
    else if (s == "HIGH")
    {
        return HIGH;
    }
    else
    {
        return UNKNOWN;
    }
}

std::string cardDifficultyToStr(CardDifficulty d)
{
    switch (d)
    {
    case (LOW):
        return "LOW";
    case (MEDIUM):
        return "MEDIUM";
    case (HIGH):
        return "HIGH";
    };
    return "UNKNOWN";
}

/**
 * @brief Create a flashcard and fill in the card contents
 *
 * @return FlashCard
 */
FlashCard createFlashCard(std::string question, std::string answer, CardDifficulty difficulty, int n_times_answered)
{
    FlashCard card{};
    card.question = question;
    card.answer = answer;
    card.difficulty = difficulty;
    card.n_times_answered = n_times_answered;
    return card;
};

/**
 * @brief For a given deck file, read the contents in to create all the cards
 *
 * @param deck_file The path to the file containing the deck information
 * @return A FlashCardDeck after parsing the file.
 */
FlashCardDeck readFlashCardDeck(fs::path deck_file)
{

    /** The flashcard deck to store the flashcards in as read from the file */
    FlashCardDeck deck;

    // Open file for reading
    std::ifstream inf{deck_file};
    // temporary variables to use for reading data
    int lineCount{0};
    std::string strInput{};
    // keep track of current card in deck
    int cardNum{0};

    /** blank flashcard to begin filling in */
    FlashCard fc{};
    deck.cards.push_back(fc);

    // Read each line of the deck file and process to make flashcards
    while (std::getline(inf, strInput))
    {
        // First line of the file is the deck name
        if (lineCount == 0)
        {
            deck.name = strInput;
        }
        else
        {
            // parse line
            // if Q -> fc.question
            // if A -> fc.answer
            // if D -> fc.difficulty
            // if N -> fc.num_times
            // if '-' indicates the start of a new card
            if (strInput.starts_with("-"))
            {
                cardNum++;
                deck.cards.push_back(fc);
                std::cout << "NEW CARD" << '\n';
            }
            if (strInput.starts_with("Q:"))
            {
                deck.cards.at(cardNum).question = strInput;
            }
            if (strInput.starts_with("A:"))
            {
                deck.cards.at(cardNum).answer = strInput;
            }
            if (strInput.starts_with("D:"))
            {
                //deck.cards.at(cardNum).difficulty = strToCardDifficulty(strInput);
            }
        }

        lineCount++;
    }

    return deck;
};


/**
 * @brief Write a deck of flashcards to disk
 * The standard location will be in Decks/ located with the executable
 * and use a suffix of ".deck"
 *
 * @param deck The FlashCard deck to be written to file
 * @param filename The file path for the deck file
 */
void writeFlashCardDeck(FlashCardDeck deck, fs::path filename) {
    // check Decks/ exists
    // check for existance of
    // open file for writing
    // write name of deck to file
    // loop through each card in the deck
};


/**
 * @brief Function that will scan the deck directory and read in all the deck files found
 * TODO document
 * @param deck_path the path to look for ".deck" suffixed files
 */
std::vector<FlashCardDeck> loadFlashCardDecks(fs::path deck_path)
{
    std::cout << deck_path << std::endl;
    std::vector<FlashCardDeck> deck_array;
    // Check the deck directory exists
    if (fs::exists(deck_path) && fs::is_directory(deck_path))
    {
        std::cout << deck_path << " is a directory" << std::endl;
        // list out the contents of the directory
        for (const auto &entry : fs::directory_iterator(deck_path))
        {
            std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << std::endl;

            if (entry.is_regular_file() && entry.path().string().ends_with(".deck"))
            {
                FlashCardDeck fd{};
                fd = readFlashCardDeck(entry);
                deck_array.push_back(fd);
            }
        }
    }
    else
    {
        std::cerr << "Directory does not exist, or is not a directory";
        //TODO deal with error
    }

    return deck_array;
};
