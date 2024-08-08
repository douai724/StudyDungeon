#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "player.h"
#include "playing_card.h"

class GameState {
    private:
        bool turn = 0; // 0 for user, 1 for enemy
        Player player;
        Player enemy;
    public:

        /**
         * Constructor
         */
        GameState(Player player, Player enemy);

        /** \brief Checks if a player has lost by losing all Hit Points
         * 
         */
        bool didPlayerLose(Player player);

        /** \brief Game is a draw if neither of the players have any cards left
         * 
         */
        bool isGameDraw();

        /**
         * Player selects card
         * Card is executed and its effects applied
         * Next players turn
         */
        void nextTurn(Player player, PlayingCard card);

};


/**
 * The actual gameloop
 * 1. Sets up the players
 * 2. Sets up their hands
 * 3. Creates the game object
 * 4. Plays the game until win condition
 */
void gameloop();

/**
 * Generates a hand of size numCards
 */
std::vector<PlayingCard> generateHand(int numCards);

#endif