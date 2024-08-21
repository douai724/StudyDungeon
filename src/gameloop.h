#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "card_types.h"
#include "player.h"
#include "playing_card.h"
#include <iostream>
#include <string>

class Game
{
private:
    short turn; // 1 for p1, 2 for p2
    Player *p1;
    Player *p2;


    /**
         * Apply the damage effect to a player based on the damage card that is played
         */
    void damageEffect(PlayingCard &card);

public:
    /**
         * Constructor
         */
    Game(Player *p1, Player *p2);

    /**
         * 1. Get the card input
         * 2. Apply the effect
         * 3. Switch turns
         */
    void nextTurn();

    /**
         * Check if the game is over
         */
    bool isGameOver();
};


/**
 * Set up and start the game
 */
void start();

/**
 * Generate a random hand
 */
std::vector<PlayingCard> generateHand(int numCards);

#endif
