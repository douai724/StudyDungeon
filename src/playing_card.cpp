/**
 * @file playing_card.cpp
 * @author Green Alligators
 * @brief This file defines the classes and methods used for a Playing Card
 * @version @PROJECT_VERSION@
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "playing_card.h"

PlayingCard::PlayingCard(enum Type cardType, int value)
{
    PlayingCard::cardType = cardType;
    PlayingCard::value = value;
}

PlayingCard::PlayingCard()
{
    PlayingCard::cardType = (enum Type)0;
    PlayingCard::value = 0;
}

bool PlayingCard::operator==(PlayingCard &other)
{
    if (this->value == other.value && this->cardType == other.cardType)
    {
        return true;
    }
    return false;
}

int PlayingCard::getValue()
{
    return PlayingCard::value;
}

enum Type PlayingCard::getType()
{
    return PlayingCard::cardType;
}

std::string PlayingCard::toString()
{
    std::string type;
    switch (PlayingCard::cardType)
    {
    case 0:
        return "Deal " + std::to_string(PlayingCard::value) + " damage.";
    case 1:
        return "Heal " + std::to_string(PlayingCard::value) + " hit points.";
    case 2:
        return "Swap hands with the enemy player.";
    default:
        return "Unknown ability";
    }
}
