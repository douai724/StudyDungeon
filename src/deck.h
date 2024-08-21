/**
 * @file deck.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-08-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#ifndef DECK_H_
#define DECK_H_


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
    LOW = 1,
    MEDIUM,
    HIGH
};


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
    std::string question;

    /** The flashcard answer */
    std::string answer;

    /** The user defined difficulty */
    CardDifficulty difficulty;

    /** The number of times the question has been answered */
    int n_times_answered;

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
 * @fn
 * TODO document
 */
std::vector<FlashCardDeck> loadFlashCardDecks(std::filesystem::path deck_path);


/**
 * @brief Reads the contents of the deck file to create cards and returns the deck
 * @fn
 * TODO document
 * @param deck_file
 */
FlashCardDeck readFlashCardDeck(std::filesystem::path deck_file);

/**
 * @brief Write a deck of flashcards to disk
 * The standard location will be in Decks/ located with the executable
 * and use a suffix of ".deck"
 *
 * @param deck The FlashCard deck to be written to file
 * @param filename The file path for the deck file
 */
void writeFlashCardDeck(FlashCardDeck deck, std::filesystem::path filename);

#endif
