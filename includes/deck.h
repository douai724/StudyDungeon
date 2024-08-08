#pragma once
#ifndef DECK_H_
#define DECK_H_

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

#include <windows.h>
#include <string>
#include <filesystem>
void create_card();
void read_deck();
void write_deck();

/**
 * @brief 
 * 
 */
struct Card {
    std::string question;
    std::string answer;
    int difficulty;
    int n_times;

};

// TODO make struct Deck

/**
 * @brief Load the decks from files stored with the ".deck" extension inside decks/
 * 
 */
void load_decks(std::filesystem::path deck_path);

#endif
