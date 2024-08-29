/**
 * @file playing_card.h
 * @author Green Alligators
 * @brief
 * @version 0.1
 * @date 2024-08-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#ifndef PLAYING_CARD_H
#define PLAYING_CARD_H

#include "card_types.h"
#include <string>

/**
 * @brief
 *
 */
class PlayingCard
{
private:
    /**
     * The target of the card's effect. 0 is for the player that possesses this card.
     * 1 is for the enemy player.
     */
    bool target;
    /**
     * The value modifier that goes with the card effect.
     */
    int value;

    /**
     * The effect/type of the card, e.g. damage, heal
     */
    enum Type cardType;

public:
    /**
     * @brief Construct a new Playing Card object.
     *
     * Default Constructor.
     *
     */
    PlayingCard();

    /**
     * @brief Construct a new Playing Card object.
     *
     * @param target the target of the card
     * @param cardType the effect of the card
     * @param value the value modifier of the card
     */
    PlayingCard(bool target, enum Type cardType, int value);

    /**
     * @brief Compares another PlayingCard object to this.
     *
     * Comparas another PlayingCard object to this. Returns true if both
     * PlayingCard objects possess the same member values. Returns false
     * otherwise.
     *
     * @param other The card to compare this to.
     * @return true
     * @return false
     */
    bool operator==(PlayingCard &other);

    /**
     * @brief Returns the value of the card.
     *
     * @return int the value of the card.
     */
    int getValue();

    /**
     * @brief Returns the target of the card.
     *
     * @return true
     * @return false
     */
    bool getTarget();

    /**
     * @brief Get the type of the card
     *
     * @return enum Type the type
     */
    enum Type getType();

    /**
     * @brief Converts this PlayingCard object to string.
     *
     * @return std::string the string version of this PlayingCard.
     */
    std::string toString();
};
#endif
