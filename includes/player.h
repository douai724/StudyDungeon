#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <string.h>
#include <list>
#include "playing_card.h"

/** 
 * 
 */
class Player {
    private:
        int hitPoints;
        int maxHitPoints;
        std::list<PlayingCard> hand;
    public:
        /**
         * Constructor
         */
        Player(int hitPoints, int maxHitPoints, std::list<PlayingCard> hand);

        /** \brief Selects the card to play.
         * 
         * Selects a card from the available hand to play. Returns the card object 
         * and removes the card from the hand.
         */
        PlayingCard selectCard(int cardNum);

        /** \brief Returns the Hit Points of the player.
         * 
         */
        int getHitPoints();

        /** \brief Sets the Hit Points of the player to a set amount.
         * 
         * Sets the current Hit Points of the player to a set amount that is below the Max Hit Points.
         * This function should only be used for card abilities. To apply damage to the player, use the
         * damage(int amount) function.
         */
        void setHitPoints(int value);

        /** \brief Returns the Max Hit Points of the player.
         * 
         */
        int getMaxHitPoints();

        /** \brief Sets the Max Hit Points of the player.
         * 
         */
        void setMaxHitPoints(int value);

        /** \brief Returns the current hand of the player.
         * 
         */
        std::list<PlayingCard> getHand();

        /** \brief Sets the hand of the player.
         * 
         */
        void setHand(std::list<PlayingCard> hand);

        /** \brief Removes a specified card from the player's hand.
         * 
         */
        bool removeCard(PlayingCard card);

        /** \brief Adds a card to the player's hand.
         * 
         */
        bool addCard(PlayingCard card);
        
        /** \brief Applies damage to the player.
         * 
         */
        void damage(int amount);

        /** \brief Heals the player
         * 
         * Heals the player up to the maximum amount of hit points.
         */
        void heal(int amount);

};

#endif