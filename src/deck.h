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


void create_flash_card();
void read_flashcard_deck();
void write_flashcard_deck();

/**
 * @brief This structure holds the information for each flashcard
 * A flashcard consists of a question, answer and difficulty. The number of times
 * the question has been answered is kept track of.
 *
 * @struct
 *
 */
struct FlashCard
{
    /** The flashcard question */
    std::string question;

    /** The flashcard answer */
    std::string answer;

    /** The user defined difficulty */
    int difficulty;

    /** The number of times the question has been answered */
    int n_times_answered;
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
    void print_deck()
    {
        std::cout << name << std::endl;
        std::cout << "size: " << cards.size() << '\n';
        for (FlashCard card : cards)
        {
            std::cout << card.question << '\n';
            std::cout << card.answer << '\n';
            std::cout << "---\n";
        }
    }
};

/**
 * @brief Load the decks from files stored with the ".deck" extension inside decks/
 * @fn
 * TODO document
 */
void load_flashcard_decks(std::filesystem::path deck_path);


/**
 * @brief Reads the contents of the deck file to create cards and returns the deck
 * @fn
 * TODO document
 * @param deck_file
 */
FlashCardDeck read_flashcard_deck(std::filesystem::path deck_file);


#endif
