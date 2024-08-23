#ifndef PLAYER_H
#define PLAYER_H

#include "playing_card.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

/**
 *
 */
class Player
{
private:
    int hitPoints;
    int maxHitPoints;
    std::vector<PlayingCard> hand;

public:
    /**
         * Default constructor
         */
    Player();

    /**
         * Constructor
         */
    Player(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand);

    // picks a card to play.
    virtual PlayingCard play();

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
    std::vector<PlayingCard> getHand();

    /** \brief Sets the hand of the player.
         *
         */
    void setHand(std::vector<PlayingCard> hand);

    /** \brief Removes a specified card from the player's hand.
         *
         */
    void removeCard(PlayingCard &card);

    /** \brief Adds a card to the player's hand.
         *
         */
    void addCard(PlayingCard &card);

    // returns a pointer to a playing card
    PlayingCard getCard(int index);

    /** \brief Applies damage to the player.
         *
         */
    void damage(int amount);

    /** \brief Heals the player
         *
         * Heals the player up to the maximum amount of hit points.
         */
    void heal(int amount);

    /** \brief Represents the player as a string
         *
         */
    std::string toString();

    void printHand();
};

class User : public Player
{
    // picks a card to play.
public:
    PlayingCard play();
    User(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand);
};

class Bot : public Player
{
    // picks a card to play.
public:
    PlayingCard play();
    Bot(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand);
};

#endif
