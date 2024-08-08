#ifndef PLAYING_CARD_H
#define PLAYING_CARD_H

#include "player.h"
#include <string>

class PlayingCard {
    private:
        bool target; // 0 for player that possesses this card, 1 for the enemy
        std::string description;
    public:

        /**
         * Constructor
         */
        PlayingCard(bool target, std::string description);

        /** \brief Apply the effects of the card to the target
         * 
         */
        void playCard(Player target);
};

class DamageCard: public PlayingCard {
    private:
        int damageValue;
};

class HealCard: public PlayingCard {
    private:
        int healValue;
};

class SwapHandCard: public PlayingCard {
    
};

#endif