#ifndef PLAYER_H
#define PLAYER_H

#include "menu.h"
#include "playing_card.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

/**
 * @brief Class that represents a Player.
 *
 * Classes that inherit the Player class must implement the virtual function play().
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
     * @brief Construct a new Player object
     *
     */
    Player();

    /**
     * @brief Construct a new Player object
     *
     * @param hitPoints the current hit points of the player
     * @param maxHitPoints the maximum hit points of the player
     * @param hand the hand (list of cards) of the player
     */
    Player(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand);

    /**
     * @brief Returns the playing card picked by the player.
     *
     * @return PlayingCard the playing card selected by the player
     */
    virtual PlayingCard play();

    /**
     * @brief Returns the current hit points of the player.
     *
     * @return int the current hit points of the player
     */
    int getHitPoints();

    /**
      * @brief Sets the current hit points of the player.
      *
      * Sets the current hit points of the player to the value given, as long as the value
      * is less than the maximum hit points and more than -1. Note that this function should
      * not be used to damage or heal the player. To damage the player, use the damage() function.
      * To heal the player, use the heal() function.
      *
      * @param value the value for the hit points to be set to.
      */
    void setHitPoints(int value);

    /**
      * @brief Returns the max hit points of the player.
      *
      * @return int the max hit points of the player.
      */
    int getMaxHitPoints();

    /**
      * @brief Sets the maximum hit points of the player.
      *
      * @param value the value to set the player's maximum hit points.
      */
    void setMaxHitPoints(int value);

    /**
      * @brief Returns the player's hand
      *
      * @return std::vector<PlayingCard> the player's hand
      */
    std::vector<PlayingCard> getHand();

    /**
      * @brief Set the player's hand
      *
      * Set the player's hand to the given vector of playing cards. Note, this function should
      * not be used to add or remove a card for the player's hand. To add a card to the player's
      * hand, use addCard(). To remove a card from the player's hand, use removeCard().
      *
      * @param hand the vector of playing cards to set as the player's hand
      */
    void setHand(std::vector<PlayingCard> hand);

    /**
      * @brief Removes the given card from the player's hand.
      *
      * @param card the card to remove from the player's hand.
      */
    void removeCard(PlayingCard &card);

    /**
      * @brief Adds the given card to the player's hand.
      *
      * @param card the card to add to the player's hand.
      */
    void addCard(PlayingCard &card);

    /**
      * @brief Returns the PlayingCard object that corresponds to the index given.
      *
      * @param index the index of the card to get
      * @return PlayingCard the object that corresponds to the given index.
      */
    PlayingCard getCard(int index);

    /**
      * @brief Applies damage equal to amount to the player.
      *
      * @param amount the amount to damage the player.
      */
    void damage(int amount);

    /**
      * @brief Heals the player a given amount.
      *
      * @param amount the amount to heal the player.
      */
    void heal(int amount);

    /**
      * @brief Converts the player object to a string
      *
      * @return std::string the string version of the player.
      */
    std::string toString();

    /**
      * @brief Prints the hand of the player to std::cout
      *
      */
    void printHand();
};

/**
 * @brief Inherits the Player class to take user input through the game menu.
 *
 */
class User : public Player
{
public:
    /**
      * @brief Returns a PlayingCard object picked by the user.
      *
      * Returns a PlayingCard object picked by the player for the
      * turn.
      *
      * @return PlayingCard the card picked by the player.
      */
    PlayingCard play();

    /**
      * @brief Construct a new User object
      *
      * @param hitPoints the hit points of the User-Player
      * @param maxHitPoints the max hit points of the User-Player
      * @param hand the hand of the User-Player
      */
    User(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand);
};

/**
 * @brief Inherits the Player class to play as a basic bot.
 *
 */
class Bot : public Player
{
public:
    /**
      * @brief Returns a PlayingCard object picked by the bot.
      *
      * Returns a PlayingCard object picked by the bot for the
      * turn.
      *
      * @return PlayingCard the card picked by the bot.
      */
    PlayingCard play();

    /**
      * @brief Construct a new Bot object
      *
      * @param hitPoints the hit points of the Bot-Player
      * @param maxHitPoints the max hit points of the Bot-Player
      * @param hand the hand of the Bot-Player
      */
    Bot(int hitPoints, int maxHitPoints, std::vector<PlayingCard> hand);
};

#endif
