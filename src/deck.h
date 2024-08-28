/**
 * @file deck.h
 * @author Green Alligators
 * @brief
 * @version 0.1
 * @date 2024-08-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#ifndef DECK_H
#define DECK_H

#include "util.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>


/**
 * @brief The possible difficulties for a flashcard
 * @enum possible values: LOW (1), MEDIUM (2), and HIGH (3)
 *
 */
enum CardDifficulty
{
    UNKNOWN = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};


/**
 * @brief Converts a string into the CardDifficulty enum.
 * "LOW" -> LOW
 * "MEDIUM" -> MEDIUM
 * "HIGH" -> HIGH
 * Anything else is converted to UNKNOWN
 *
 * @param difficultyStr The card difficulty as a string
 * @return CardDifficulty
 */
CardDifficulty strToCardDifficulty(std::string difficultyStr);

/**
 * @brief Converts the card difficulty from enum to a string
 *
 * @param difficulty The CardDifficulty
 * @return std::string
 */
std::string cardDifficultyToStr(CardDifficulty difficulty);

/**
 * @brief This structure holds the information for each flashcard
 * A flashcard consists of a question, answer and difficulty. The number of times
 * the question has been answered is kept track of.
 *
 * @class
 *
 */
class FlashCard
{
public:
    /** The flashcard question */
    std::string question{};

    /** The flashcard answer */
    std::string answer{};

    /** The user defined difficulty */
    CardDifficulty difficulty = UNKNOWN;

    /** The number of times the question has been answered */
    int n_times_answered{};

    /**
         * @brief Prints the card question and answer
         *
         */
    void printCard()
    {
        std::cout << question << '\n';
        std::cout << answer << '\n';
        std::cout << "\n";
    }

    /**
         * @brief Used to
         *
         */
    void printCardAsTemplate()
    {
        std::cout << "Q: " << question << '\n' << "A: " << answer << '\n';
        std::cout << "D: " << difficulty << '\n' << "N: " << n_times_answered << '\n';
        std::cout << "-" << '\n';
    }
};


/**
 * @brief Class that defines a "deck" of flashcards
 * @class
 *
 */
class FlashCardDeck
{
    // TODO: add constructor
    // TODO add destructor
public:
    /** The name of the flashcard deck */
    std::string name{};

    /** Vector containing 0 or more flashcards */
    std::vector<FlashCard> cards{};

    /**
     * @brief Prints flashcard deck information and then each card
     *
     */
    void printDeck()
    {
        std::cout << name << std::endl;
        std::cout << "size: " << cards.size() << '\n';
        for (FlashCard card : cards)
        {
            card.printCard();
        }
    }

    /**
     * @brief Prints flashcard deck name and then each card as template for a deck file.
     *
     */
    void printDeckAsTemplate()
    {
        std::cout << name << std::endl;
        for (FlashCard card : cards)
        {
            card.printCardAsTemplate();
        }
    }
};

/**
 * @brief Create a flashcard object
 * @param question The card question
 * @param answer The card answer
 * @param difficulty The card difficulty
 * @param n_times_answered The number of time the card has been answered
 * @return FlashCard
 */
FlashCard createFlashCard(std::string question, std::string answer, CardDifficulty difficulty, int n_times_answered);


/**
 * @brief Load the decks from files stored with the ".deck" extension inside decks/
 * @details Will iterate through all files within the path directory that have a .deck suffix.
 * each deck file will be parsed and turned into a FlashCardDeck. All FlashCardDecks are added into
 * a vector and returned.
 *
 * @param deck_path Path on the file system to a directory where the deck files are located.
 * @return std::vector<FlashCardDeck>
 */
std::vector<FlashCardDeck> loadFlashCardDecks(std::filesystem::path deck_dir_path);


/**
 * @brief For a given deck file, read the contents in to create all the cards
 *
 * @param deck_file The path to the file containing the deck information
 * @return A FlashCardDeck after parsing the file.
 */
FlashCardDeck readFlashCardDeck(std::filesystem::path deck_file);

/**
 * @brief Write a deck of flashcards to disk
 * The standard location will be in Decks/ located with the executable
 * and use a suffix of ".deck"
 *
 * @param deck The FlashCard deck to be written to file
 * @param filename The file path for the deck file
 * @return true if successfully writes deck to file.
 */
bool writeFlashCardDeck(FlashCardDeck deck, std::filesystem::path filename);


/**
 * @brief Create example deck files
 * @details A helper function that will create some example deck files if no decks exist.
 * @return A vector of the example FlashCardDecks
 */
std::vector<FlashCardDeck> createExampleDecks();

/**
 * @brief Prompt the user for name of the file to save the deckfile to
 *
 * @param deck_dir Directory to append the filename to
 * @return std::filesystem::path
 */
std::filesystem::path createDeckFilename(std::filesystem::path deck_dir);


#endif
