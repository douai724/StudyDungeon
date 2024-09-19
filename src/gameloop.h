/**
 * @file gameloop.h
 * @author Green Alligators
 * @brief
 * @version 0.1
 * @date 2024-08-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "card_types.h"
#include "player.h"
#include "playing_card.h"
#include "util.h"
#include <iostream>
#include <string>

/**
 * @brief Represents a Game.
 *
 */
class Game
{
public:
    /**
      * The current turn. 1 for Player 1; 2 for Player 2.
      */
    short turn;
    /**
      * Player 1
      */
    Player p1;
    /**
      * Player 2
      */
    Player p2;

    /**
      * @brief Apply the damage effect to the player whose turn it is.
      *
      * @param card the PlayingCard object.
      */
    void damageEffect(PlayingCard &card);

    /**
     * @brief Apply the heal effect to the player whose turn it is.
     *
     * @param card the PlayingCard object
     */
    void healEffect(PlayingCard &card);

    /**
     * @brief Swap the hands between the players
     *
     */
    void swapHandEffect();

    /**
     * @brief Construct a new Game object.
     *
     * @param p1 Player 1
     * @param p2 Player 2
     */
    Game(Player p1, Player p2);

    Game();

    /**
      * @brief Plays the next turn of the game.
      *
      */
    void nextTurn(PlayingCard nextCard);

    /**
      * @brief Checks if the game is over.
      *
      * Checks whether the game is over. Returns true if the game is over
      * by either one player reaching 0 hit points, or neither player having
      * any playing cards left. Returns false if none of these conditions are met.
      *
      * @return true
      * @return false
      */
    bool isGameOver();
};

/**
 * @brief Set up and start the game.
 *
 */
void start(Game game);

Game setUp(Player p1, Player p2);

/**
 * @brief Generates a hand.
 *
 * @param numCards the number of cards to add to the hand.
 * @return std::vector<PlayingCard> the generated hand.
 */
std::vector<PlayingCard> generateDeck(int numCards);

#endif
