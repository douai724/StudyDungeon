/**
 * @file deck.h
 * @author Green Alligators
 * @brief Functions and classes relating to flashcards.
 *
 * @details These functions are involved with the parsing of files to create flashcards which
 * are then converted into a deck. Cards are also parsed to text and written to file to save them.
 *
 * @version 0.2
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
 * @details possible values: EASY (1), MEDIUM (2), and HIGH (3)
 * \showenumvalues
 *
 */
enum CardDifficulty
{
    UNKNOWN = 0,
    EASY = 1,
    MEDIUM = 2,
    HIGH = 3
};

namespace fs = std::filesystem;

/**
 * @brief Converts a string into the CardDifficulty enum.
 * @details "EASY" -> EASY
 * "MEDIUM" -> MEDIUM
 * "HIGH" -> HIGH
 * Anything else is converted to UNKNOWN
 *
 * @param difficultyStr The card difficulty as a string
 * @return CardDifficulty
 */
CardDifficulty strToCardDifficulty(const std::string &difficultyStr);

/**
 * @brief Converts the card difficulty from enum to a string
 *
 * @param difficulty The CardDifficulty
 * @return std::string
 */
std::string cardDifficultyToStr(const CardDifficulty &difficulty);

/**
 * @brief This structure holds the information for each flashcard
 *
 * A flashcard consists of a question, answer and difficulty. The number of times
 * the question has been answered is kept track of.
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
    */
    void printCard();

    /**
    * @brief Used to
    */
    void printCardAsTemplate();

    /**
     * @brief Returns the card in template form as a string
     *
     * @return std::string
     */
    std::string stringCardAsTemplate();
};


/**
 * @brief Class that defines a "deck" of flashcards
 *
 *
 */
class FlashCardDeck
{
    // TODO: add constructor
    // TODO add destructor
public:
    /** The name of the flashcard deck */
    std::string name{};
    /** The path to the deckfile */
    std::filesystem::path filename{};
    /** Vector containing 0 or more flashcards */
    std::vector<FlashCard> cards{};

    /**
     * @brief Prints flashcard deck information and then each card
     */
    void printDeck();


    /**
     * @brief Prints flashcard deck name and then each card as template for a deck file.
     */
    void printDeckAsTemplate();
};


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
 * @details This will check the parent directory exists and write to a file. It does
 * perform the additional checks on the filename that writeFlashCardWithChecks does
 *
 * @param deck The FlashCard deck to be written to file
 * @param filename The file path for the deck file
 * @return true if successfully writes deck to file.
 */
bool writeFlashCardDeck(const FlashCardDeck &deck, std::filesystem::path filename);


/**
 * @brief Write a deck of flashcards to disk
 * @details The standard location will be in Decks/ located with the executable
 * and use a suffix of ".deck". This method checks
 *
 * @param deck The FlashCard deck to be written to file
 * @param filename The file path for the deck file
 * @param force_overwrite (default false) skip the overwrite confimration prompt
 * @return true if successfully writes deck to file.
 */
bool writeFlashCardDeckWithChecks(const FlashCardDeck &deck, std::filesystem::path filename, bool force_overwrite);


/**
 * @brief Create example deck files
 *
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


/**
 * @brief Updates an existing FlashCardDeck on file
 *
 * @param deck_to_update FlashCardDeck to write to file
 * @return true update was successful
 * @return false update was unsuccesssful
 */
bool updateDeckFile(FlashCardDeck &deck_to_update);

#endif
